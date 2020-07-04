package file.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.pojo.TaskFile;
import file.service.TaskFileService;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.struts2.ServletActionContext;
import org.springframework.beans.factory.annotation.Autowired;
import util.DownloadFileNameOp;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;


public class TaskFileDownloadAction extends ActionSupport {
    private static final Logger LOG = LogManager.getLogger(TaskFileDownloadAction.class);

    private Integer taskId;
    private User user;


    private TaskFile taskFile;
    private File file;

    private final TaskFileService taskFileService;

    @Autowired
    public TaskFileDownloadAction(TaskFileService taskFileService) {
        this.taskFileService = taskFileService;
    }


    public String download() {
        user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskId == null)
            return ERROR;

        taskFile = taskFileService.findByTaskIdStudentId(taskId, user.getId());

        if (taskFile != null)
            return SUCCESS;
        else
            return ERROR;
    }

    private Integer studentId;
    public String teacherDownload() {
        user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskId == null || studentId == null)
            return ERROR;

        taskFile = taskFileService.findByTaskIdStudentId(taskId, studentId);

        if (taskFile != null)
            return SUCCESS;
        else
            return ERROR;
    }

    public InputStream getInputStream() throws FileNotFoundException {

        file = new File(taskFile.getFilePath());


        return new FileInputStream(file);
    }


    public Integer getTaskId() {
        return taskId;
    }

    public void setTaskId(Integer taskId) {
        this.taskId = taskId;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public Integer getStudentId() {
        return studentId;
    }

    public void setStudentId(Integer studentId) {
        this.studentId = studentId;
    }

    public String getFileName() throws Exception {
        LOG.debug("fileName: " + taskFile.getFileName());

        //return new String(taskFile.getFileName().getBytes(), "ISO-8859-1");
       // return new String(taskFile.getFileName().getBytes(), "UTF-8");
        return DownloadFileNameOp.downToUtf8String(taskFile.getFileName(), ServletActionContext.getRequest());

    }



    public Long getContentLength() {
        return file.length();
    }
}
