package student.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.pojo.CourseResource;
import file.service.CourseResourceService;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import student.pojo.StuCourse;
import student.service.StuCourseService;

import java.util.List;


public class StuCourseResourceAction extends ActionSupport {
    private static final Logger LOG = LogManager.getLogger(StuCourseResourceAction.class);

    private Integer courseId;

    private StuCourse stuCourse;

    @Autowired
    private StuCourseService stuCourseService;
    @Autowired
    private CourseResourceService courseResourceService;


    private List<CourseResource> resources;

    public String getResource() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (courseId == null)
            return ERROR;

        StuCourse s = new StuCourse();
        s.setId(courseId);

        stuCourse = stuCourseService.findStuCourse(s);

        resources = courseResourceService.findByCourseId(courseId);
        LOG.debug("resources " + resources);

        return SUCCESS;
    }


    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public StuCourse getStuCourse() {
        return stuCourse;
    }

    public void setStuCourse(StuCourse stuCourse) {
        this.stuCourse = stuCourse;
    }

    public List<CourseResource> getResources() {
        return resources;
    }

    public void setResources(List<CourseResource> resources) {
        this.resources = resources;
    }
}
