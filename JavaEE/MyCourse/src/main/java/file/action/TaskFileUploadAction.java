package file.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.service.TaskFileService;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.struts2.ServletActionContext;
import org.springframework.beans.factory.annotation.Autowired;

import java.io.File;
import java.io.IOException;


public class TaskFileUploadAction extends ActionSupport {
    private static final Logger LOG = LogManager.getLogger(TaskFileUploadAction.class);

    private File file;

    private String fileFileName;

    private String fileContentType;

    private Integer taskId;

    private Integer courseId;

    private final TaskFileService taskFileService;

    @Autowired
    public TaskFileUploadAction(TaskFileService taskFileService) {
        this.taskFileService = taskFileService;
    }


    public String upload() throws IOException {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (fileFileName == null || fileFileName.trim().equals("") ||
            taskId == null || courseId == null)
            return ERROR;

        LOG.debug("fileName: " + fileFileName + " taskId: " + taskId + " courseId: " + courseId);

        String webInfPath = ServletActionContext.getRequest().getSession().getServletContext().getRealPath("/WEB-INF");

        if (taskFileService.upload(file, webInfPath, fileFileName, taskId, courseId, user.getId())) {
            return NONE;
        } else
            return ERROR;

    }

    public File getFile() {
        return file;
    }

    public void setFile(File file) {
        this.file = file;
    }

    public String getFileFileName() {
        return fileFileName;
    }

    public void setFileFileName(String fileFileName) {
        this.fileFileName = fileFileName;
    }

    public String getFileContentType() {
        return fileContentType;
    }

    public void setFileContentType(String fileContentType) {
        this.fileContentType = fileContentType;
    }

    public Integer getTaskId() {
        return taskId;
    }

    public void setTaskId(Integer taskId) {
        this.taskId = taskId;
    }

    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }
}
