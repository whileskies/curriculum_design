package student.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import login.mapper.UserMapper;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import student.pojo.StuCourse;
import student.pojo.StuNotice;
import student.service.StuCourseNoticeService;
import student.service.StuCourseService;

import java.util.List;


public class StuCourseNoticeAction extends ActionSupport{
    private static final Logger LOG = LogManager.getLogger(StuCourseNoticeAction.class);

    private Integer courseId;

    private final StuCourseNoticeService stuCourseNoticeService;

    private final StuCourseService stuCourseService;

    private final UserMapper userMapper;

    @Autowired
    public StuCourseNoticeAction(StuCourseNoticeService stuCourseNoticeService, StuCourseService stuCourseService, UserMapper userMapper) {
        this.stuCourseNoticeService = stuCourseNoticeService;
        this.stuCourseService = stuCourseService;
        this.userMapper = userMapper;
    }

/*    private void autoLogin() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user != null)
            return;

        user = new User();

        user.setEmail("gt110@qq.com");
        user.setPassword("gt1997531");
        user = userMapper.selectByEmailPassword(user);

        ActionContext.getContext().getSession().put("user", user);
    }*/

    private List<StuNotice> stuNotices;
    private StuCourse stuCourse;

    public String getNotice() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (courseId == null)
            return ERROR;

        StuCourse s = new StuCourse();
        s.setId(courseId);

        stuNotices = stuCourseNoticeService.findNotices(s);
        stuCourse = stuCourseService.findStuCourse(s);
        LOG.debug("stuNotices: " + stuNotices);
        LOG.debug("stuCourse: " + stuCourse);

        return SUCCESS;
    }


    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public List<StuNotice> getStuNotices() {
        return stuNotices;
    }

    public void setStuNotices(List<StuNotice> stuNotices) {
        this.stuNotices = stuNotices;
    }

    public StuCourse getStuCourse() {
        return stuCourse;
    }

    public void setStuCourse(StuCourse stuCourse) {
        this.stuCourse = stuCourse;
    }
}
