package teacher.pojo;

import java.util.Date;
import java.util.List;

public class TeaCourse {
    private Integer id;
    private String code;
    private String name;
    private Date createTime;

    private Integer studentCount;

    private List<TeaTask> teaTasks;

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

    public List<TeaTask> getTeaTasks() {
        return teaTasks;
    }

    public void setTeaTasks(List<TeaTask> teaTasks) {
        this.teaTasks = teaTasks;
    }

    @Override
    public String toString() {
        return "StuCourse{" +
                "id=" + id +
                ", code='" + code + '\'' +
                ", name='" + name + '\'' +
                ", createTime=" + createTime +
                ", studentCount=" + studentCount +
                '}';
    }
}
