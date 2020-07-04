package student.pojo;

import login.pojo.User;

import java.util.Date;

public class StuNotice {
    private Integer id;
    private Integer courseId;
    private String title;
    private String content;
    private String plainTextContent;
    private Integer writerId;
    private Date createTime;
    private Date updateTime;

    private User teacher;
    private String hUpdateTime;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String getPlainTextContent() {
        return plainTextContent;
    }

    public void setPlainTextContent(String plainTextContent) {
        this.plainTextContent = plainTextContent;
    }

    public Integer getWriterId() {
        return writerId;
    }

    public void setWriterId(Integer writerId) {
        this.writerId = writerId;
    }

    public Date getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Date createTime) {
        this.createTime = createTime;
    }

    public Date getUpdateTime() {
        return updateTime;
    }

    public void setUpdateTime(Date updateTime) {
        this.updateTime = updateTime;
    }

    public User getTeacher() {
        return teacher;
    }

    public void setTeacher(User teacher) {
        this.teacher = teacher;
    }

    public String gethUpdateTime() {
        return hUpdateTime;
    }

    public void sethUpdateTime(String hUpdateTime) {
        this.hUpdateTime = hUpdateTime;
    }

    @Override
    public String toString() {
        return "TeaNotice{" +
                "id=" + id +
                ", courseId=" + courseId +
                ", title='" + title + '\'' +
                ", content='" + content + '\'' +
                ", plainTextContent='" + plainTextContent + '\'' +
                ", writerId=" + writerId +
                ", createTime=" + createTime +
                ", updateTime=" + updateTime +
                ", teacher=" + teacher +
                ", hUpdateTime='" + hUpdateTime + '\'' +
                '}';
    }
}
