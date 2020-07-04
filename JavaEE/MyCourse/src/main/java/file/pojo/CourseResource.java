package file.pojo;

import java.util.Date;

public class CourseResource {
    private Integer id;
    private Integer courseId;
    private String fileName;
    private String filePath;
    private Date uploadTime;

    private String hUploadTime;
    private String hFileSize;

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

    public Date getUploadTime() {
        return uploadTime;
    }

    public void setUploadTime(Date uploadTime) {
        this.uploadTime = uploadTime;
    }

    public String gethUploadTime() {
        return hUploadTime;
    }

    public void sethUploadTime(String hUploadTime) {
        this.hUploadTime = hUploadTime;
    }

    public String gethFileSize() {
        return hFileSize;
    }

    public void sethFileSize(String hFileSize) {
        this.hFileSize = hFileSize;
    }

    @Override
    public String toString() {
        return "CourseResource{" +
                "id=" + id +
                ", courseId=" + courseId +
                ", fileName='" + fileName + '\'' +
                ", filePath='" + filePath + '\'' +
                ", uploadTime=" + uploadTime +
                ", hUploadTime='" + hUploadTime + '\'' +
                ", hFileSize='" + hFileSize + '\'' +
                '}';
    }
}
