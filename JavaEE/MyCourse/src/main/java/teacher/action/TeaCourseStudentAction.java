package teacher.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import login.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import teacher.pojo.TeaCourse;
import teacher.service.TeaCourseService;
import teacher.service.TeaCourseStudentService;

import java.util.List;

public class TeaCourseStudentAction extends ActionSupport {

    private Integer courseId;

    private List<User> students;

    private TeaCourse teaCourse;

    @Autowired
    private TeaCourseService teaCourseService;

    @Autowired
    private TeaCourseStudentService teaCourseStudentService;

    public String findStudents() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if(user == null)
            return LOGIN;

        if(courseId == null)
            return ERROR;

        students = teaCourseStudentService.findAllByCourseId(courseId);

        TeaCourse c = new TeaCourse();
        c.setId(courseId);

        teaCourse = teaCourseService.findTCourse(c);

        return SUCCESS;
    }

    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public void setStudents(List<User> students) {
        this.students = students;
    }

    public List<User> getStudents() {
        return students;
    }

    public TeaCourse getTeaCourse() {
        return teaCourse;
    }

    public void setTeaCourse(TeaCourse teaCourse) {
        this.teaCourse = teaCourse;
    }
}
