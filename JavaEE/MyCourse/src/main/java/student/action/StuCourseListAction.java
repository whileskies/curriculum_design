package student.action;

import com.alibaba.fastjson.JSON;
import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import login.mapper.UserMapper;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.struts2.interceptor.ServletResponseAware;
import org.springframework.beans.factory.annotation.Autowired;
import student.pojo.StuCourse;
import student.pojo.StuTask;
import student.service.StuCourseListService;
import student.service.StuCourseService;
import student.service.StuCourseTaskService;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;
import java.util.List;


public class StuCourseListAction extends ActionSupport implements ServletResponseAware {
    private static final Logger LOG = LogManager.getLogger(StuCourseListAction.class);
    @Autowired
    private UserMapper userMapper;

    private final StuCourseListService stuCourseListService;

    private final StuCourseService stuCourseService;

    @Autowired
    private StuCourseTaskService stuCourseTaskService;

    @Autowired
    public StuCourseListAction(StuCourseListService stuCourseListService, StuCourseService stuCourseService) {
        this.stuCourseListService = stuCourseListService;
        this.stuCourseService = stuCourseService;
    }


    private List<StuCourse> stuCourses;
    public String showCourseList() {

        User user = (User) ActionContext.getContext().getSession().get("user");

        LOG.debug(user);
        if (user == null)
            return LOGIN;

        stuCourses = stuCourseListService.findSCourses(user);
        LOG.debug("stuCourses: " + stuCourses);


        for (StuCourse s : stuCourses) {
            List<StuTask> stuTasks = stuCourseTaskService.findTasks(s);
            for (StuTask task : stuTasks) {
                if (task.getTitle().length() > 12)
                    task.setTitle(task.getTitle().substring(0, 12) + "...");
            }

            if (stuTasks.size() > 3)
                s.setStuTasks(stuTasks.subList(0, 3));
            else
                s.setStuTasks(stuTasks);
        }

        return SUCCESS;
    }

    public List<StuCourse> getStuCourses() {
        return stuCourses;
    }

    public void setStuCourses(List<StuCourse> stuCourses) {
        this.stuCourses = stuCourses;
    }

    private HttpServletResponse response;
    private String courseCode;

    private static final int ENTER_COURSE_CODE = 4;
    private static final int SUCC_STATUS = 0;
    private static final int INVAID_FILED_STATUS = 1;
    private static final int NO_COURSE_STATUS = 2;
    private static final int HAS_ENTERED_STATUS = 3;
    private static final int ERROR_STATUS = 4;


    public String enterCourse() throws IOException {
        User user = (User) ActionContext.getContext().getSession().get("user");
        LOG.debug(user);
        if (user == null)
            return LOGIN;

        EnterCourseJson enterCourseJson = new EnterCourseJson();
        enterCourseJson.code = ENTER_COURSE_CODE;

        if (courseCode == null || courseCode.trim().equals("")) {
            enterCourseJson.msg = "存在空字段";
            enterCourseJson.status = INVAID_FILED_STATUS;
        } else {
            StuCourse stuCourse = new StuCourse();
            stuCourse.setCode(courseCode.trim().toUpperCase());
            stuCourse.setEnterTime(new Date());

            int ret = stuCourseListService.enterCourse(stuCourse, user);

            if (ret == StuCourseListService.ENTER_COURSE_NOT_EXISTS) {
                enterCourseJson.msg = "该课程不存在";
                enterCourseJson.status = NO_COURSE_STATUS;
            } else if (ret == StuCourseListService.ENTER_HAS_ENTERED) {
                enterCourseJson.msg = "已加入该课程";
                enterCourseJson.status = HAS_ENTERED_STATUS;
            } else if (ret == StuCourseListService.ENTER_FAIL) {
                enterCourseJson.msg = "加入失败";
                enterCourseJson.status = ERROR_STATUS;
            } else if (ret == StuCourseListService.ENTER_SUCC) {
                enterCourseJson.msg = "加入成功";
                enterCourseJson.status = SUCC_STATUS;
                enterCourseJson.name = stuCourse.getName();
            }

            LOG.debug("stuCourse: " + stuCourse);
        }

        response.setCharacterEncoding("utf-8");
        response.setContentType("application/json;charset=utf-8");
        String ret = JSON.toJSONString(enterCourseJson);
        LOG.debug("json: " + ret);
        PrintWriter writer = response.getWriter();
        writer.print(ret);
        writer.flush();
        writer.close();

        return NONE;
    }

    class EnterCourseJson {
        int code;
        String msg;
        int status;
        String name;

        public int getCode() {
            return code;
        }

        public void setCode(int code) {
            this.code = code;
        }

        public String getMsg() {
            return msg;
        }

        public void setMsg(String msg) {
            this.msg = msg;
        }

        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }

    public void setServletResponse(HttpServletResponse response) {
        this.response = response;
    }

    public String getCourseCode() {
        return courseCode;
    }

    public void setCourseCode(String courseCode) {
        this.courseCode = courseCode;
    }



}
