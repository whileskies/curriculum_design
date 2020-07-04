package teacher.action;

import com.alibaba.fastjson.JSON;
import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.struts2.interceptor.ServletResponseAware;
import org.springframework.beans.factory.annotation.Autowired;
import teacher.pojo.TeaCourse;
import teacher.pojo.TeaTask;
import teacher.service.TeaCourseListService;
import teacher.service.TeaCourseService;
import teacher.service.TeaCourseTaskService;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.List;


public class TeaCourseListAction extends ActionSupport implements ServletResponseAware {
    private static final Logger LOG = LogManager.getLogger(TeaCourseListAction.class);

    private final TeaCourseListService TeaCourseListService;

    @Autowired
    private TeaCourseTaskService teaCourseTaskService;

    @Autowired
    private TeaCourseService teaCourseService;

    @Autowired
    public TeaCourseListAction(TeaCourseListService TeaCourseListService) {
        this.TeaCourseListService = TeaCourseListService;
    }



    private List<TeaCourse> teaCourses;

    public String showCourseList() {

        User user = (User) ActionContext.getContext().getSession().get("user");

        LOG.debug(user);
        if (user == null)
            return LOGIN;

        teaCourses = TeaCourseListService.findTCourses(user);
        LOG.debug("courses: " + teaCourses);

        for (TeaCourse t : teaCourses) {
            List<TeaTask> teaTasks = teaCourseTaskService.findTasks(t);
            for (TeaTask task : teaTasks) {
                if (task.getTitle().length() > 12)
                    task.setTitle(task.getTitle().substring(0, 12) + "...");
            }

            if (teaTasks.size() > 3)
                t.setTeaTasks(teaTasks.subList(0, 3));
            else
                t.setTeaTasks(teaTasks);
        }

        return SUCCESS;
    }

    public List<TeaCourse> getTeaCourses() {
        return teaCourses;
    }

    public void setTeaCourses(List<TeaCourse> teaCourses) {
        this.teaCourses = teaCourses;
    }

    private HttpServletResponse response;
    private String courseName;

    private static final int CREATE_COURSE_CODE = 3;
    private static final int SUCC_STATUS = 0;
    private static final int INVAID_FILED_STATUS = 1;
    private static final int FAIL_STATUS = 2;



    public String createCourse() throws IOException {
        User user = (User) ActionContext.getContext().getSession().get("user");
        LOG.debug(user);
        if (user == null)
            return LOGIN;

        CreateCourseJson createCourseJson = new CreateCourseJson();
        createCourseJson.code = CREATE_COURSE_CODE;
        if (courseName == null || courseName.trim().equals("")) {
            createCourseJson.msg = "存在空字段";
            createCourseJson.status = INVAID_FILED_STATUS;
        } else {
            TeaCourse teaCourse = new TeaCourse();
            teaCourse.setName(courseName.trim());
            boolean ret = TeaCourseListService.addCourse(teaCourse, user);
            if (ret) {
                //创建课程成功
                createCourseJson.msg = "创建成功";
                createCourseJson.status = SUCC_STATUS;
                createCourseJson.data.put("code", teaCourse.getCode());
                createCourseJson.data.put("id", teaCourse.getId());
            } else {
                createCourseJson.msg = "创建失败";
                createCourseJson.status = FAIL_STATUS;
            }
        }

        response.setCharacterEncoding("utf-8");
        response.setContentType("application/json;charset=utf-8");
        String ret = JSON.toJSONString(createCourseJson);
        LOG.debug("json: " + ret);
        PrintWriter writer = response.getWriter();
        writer.print(ret);
        writer.flush();
        writer.close();

        return NONE;
    }

    class CreateCourseJson {
        int code;
        String msg;
        int status;
        HashMap<String, Object > data = new HashMap<String, Object>();

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

        public HashMap<String, Object> getData() {
            return data;
        }

        public void setData(HashMap<String, Object> data) {
            this.data = data;
        }
    }


    private Integer courseId;
    public String deleteCourse() {
        User user = (User) ActionContext.getContext().getSession().get("user");
        if (user == null)
            return LOGIN;

        if (courseId == null)
            return ERROR;

        if (teaCourseService.deleteByCourseId(courseId)) {
            return SUCCESS;
        } else {
            return ERROR;
        }
    }

    public void setServletResponse(HttpServletResponse response) {
        this.response = response;
    }

    public String getCourseName() {
        return courseName;
    }

    public void setCourseName(String courseName) {
        this.courseName = courseName;
    }

    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }
}



