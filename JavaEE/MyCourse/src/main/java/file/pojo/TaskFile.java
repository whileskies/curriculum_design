package file.pojo;

import java.util.Date;

public class TaskFile {
    private Integer id;
    private Integer taskId;
    private Integer userId;
    private Date uploadTime;
    private String fileName;
    private String filePath;

    private String hUploadTime;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getTaskId() {
        return taskId;
    }

    public void setTaskId(Integer taskId) {
        this.taskId = taskId;
    }

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public Date getUploadTime() {
        return uploadTime;
    }

    public void setUploadTime(Date uploadTime) {
        this.uploadTime = uploadTime;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public String gethUploadTime() {
        return hUploadTime;
    }

    public void sethUploadTime(String hUploadTime) {
        this.hUploadTime = hUploadTime;
    }

    @Override
    public String toString() {
        return "TaskFile{" +
                "id=" + id +
                ", taskId=" + taskId +
                ", userId=" + userId +
                ", uploadTime=" + uploadTime +
                ", fileName='" + fileName + '\'' +
                ", filePath='" + filePath + '\'' +
                ", hUploadTime='" + hUploadTime + '\'' +
                '}';
    }
}
