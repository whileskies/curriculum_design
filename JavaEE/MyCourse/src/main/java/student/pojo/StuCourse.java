package student.pojo;

import login.pojo.User;

import java.util.Date;
import java.util.List;

public class StuCourse {
    private Integer id;
    private String code;
    private String name;
    private Date createTime;

    private Integer studentCount;

    private User teacher;

    private Date EnterTime;

    private List<StuTask> stuTasks;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Date getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Date createTime) {
        this.createTime = createTime;
    }

    public Integer getStudentCount() {
        return studentCount;
    }

    public void setStudentCount(Integer studentCount) {
        this.studentCount = studentCount;
    }

    public User getTeacher() {
        return teacher;
    }

    public void setTeacher(User teacher) {
        this.teacher = teacher;
    }

    public Date getEnterTime() {
        return EnterTime;
    }

    public void setEnterTime(Date enterTime) {
        EnterTime = enterTime;
    }

    public List<StuTask> getStuTasks() {
        return stuTasks;
    }

    public void setStuTasks(List<StuTask> stuTasks) {
        this.stuTasks = stuTasks;
    }

    @Override
    public String toString() {
        return "StuCourse{" +
                "id=" + id +
                ", code='" + code + '\'' +
                ", name='" + name + '\'' +
                ", createTime=" + createTime +
                ", studentCount=" + studentCount +
                ", teacher=" + teacher +
                ", EnterTime=" + EnterTime +
                '}';
    }
}
