package teacher.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.pojo.CourseResource;
import file.service.CourseResourceService;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import teacher.pojo.TeaCourse;
import teacher.service.TeaCourseService;

import java.util.List;


public class TeaCourseResourceAction extends ActionSupport {
    private static final Logger LOG = LogManager.getLogger(TeaCourseResourceAction.class);

    private Integer courseId;

    private TeaCourse teaCourse;

    private final TeaCourseService teaCourseService;
    private final CourseResourceService courseResourceService;

    @Autowired
    public TeaCourseResourceAction(TeaCourseService teaCourseService, CourseResourceService courseResourceService) {
        this.teaCourseService = teaCourseService;
        this.courseResourceService = courseResourceService;
    }

    private List<CourseResource> resources;

    public String getResource() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (courseId == null)
            return ERROR;

        TeaCourse c = new TeaCourse();
        c.setId(courseId);

        teaCourse = teaCourseService.findTCourse(c);

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

    public TeaCourse getTeaCourse() {
        return teaCourse;
    }

    public void setTeaCourse(TeaCourse teaCourse) {
        this.teaCourse = teaCourse;
    }

    public List<CourseResource> getResources() {
        return resources;
    }

    public void setResources(List<CourseResource> resources) {
        this.resources = resources;
    }
}
