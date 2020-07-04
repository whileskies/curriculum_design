package file.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.service.TaskFileService;
import login.pojo.User;
import org.apache.struts2.ServletActionContext;
import org.apache.struts2.interceptor.ServletRequestAware;
import org.springframework.beans.factory.annotation.Autowired;
import util.DownloadFileNameOp;

import javax.servlet.http.HttpServletRequest;
import java.io.*;

public class ZipTaskFileDownloadAction extends ActionSupport implements ServletRequestAware {

    private Integer taskId;
    private File file;

    private final TaskFileService taskFileService;

    @Autowired
    public ZipTaskFileDownloadAction(TaskFileService taskFileService) {
        this.taskFileService = taskFileService;
    }

    public String downloadZip() throws IOException {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskId == null)
            return ERROR;

        String webInf = ServletActionContext.getRequest().getSession().getServletContext().getRealPath("/WEB-INF");
        file = taskFileService.downloadAsZip(webInf, taskId);

        return SUCCESS;
    }

    public InputStream getInputStream() throws FileNotFoundException {
        return new FileInputStream(file);
    }

    public String getFileName() throws Exception {
        //return new String(file.getName().getBytes("UTF-8"), "ISO-8859-1");
        return DownloadFileNameOp.downToUtf8String(file.getName(), ServletActionContext.getRequest());
    }

    public Long getContentLength() {
        return file.length();
    }

    public Integer getTaskId() {
        return taskId;
    }

    public void setTaskId(Integer taskId) {
        this.taskId = taskId;
    }



    private HttpServletRequest request;
    public void setServletRequest(HttpServletRequest request) {
        this.request = request;
    }
}
