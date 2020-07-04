package teacher.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.service.CourseResourceService;
import login.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;

public class ResourceDeleteAction extends ActionSupport {

    private Integer resourceId;

    private Integer courseId;

    @Autowired
    private CourseResourceService courseResourceService;

    public String delete() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (resourceId == null || courseId == null)
            return ERROR;

        if (courseResourceService.deleteResource(resourceId)) {
            return SUCCESS;
        } else {
            return ERROR;
        }

    }


    public Integer getResourceId() {
        return resourceId;
    }

    public void setResourceId(Integer resourceId) {
        this.resourceId = resourceId;
    }

    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }
}
