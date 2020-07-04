package file.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.service.CourseResourceService;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.struts2.ServletActionContext;
import org.springframework.beans.factory.annotation.Autowired;

import java.io.File;
import java.io.IOException;
import java.util.List;


public class ResourceUploadAction extends ActionSupport {
    private static final Logger LOG = LogManager.getLogger(ResourceUploadAction.class);
    private List<File> file;
    private List<String> fileFileName;
    private List<String> fileContentType;

    private final CourseResourceService courseResourceService;

    private Integer courseId;

    @Autowired
    public ResourceUploadAction(CourseResourceService courseResourceService) {
        this.courseResourceService = courseResourceService;
    }

    public String uploadFiles() throws IOException {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (courseId == null)
            return ERROR;

        LOG.debug("fileName: " + fileFileName  + " courseId: " + courseId);
        String webInfPath = ServletActionContext.getRequest().getSession().getServletContext().getRealPath("/WEB-INF");

        if (courseResourceService.uploadFiles(file, webInfPath, fileFileName, courseId))
            return NONE;
        else
            return ERROR;
    }


    public List<File> getFile() {
        return file;
    }

    public void setFile(List<File> file) {
        this.file = file;
    }

    public List<String> getFileFileName() {
        return fileFileName;
    }

    public void setFileFileName(List<String> fileFileName) {
        this.fileFileName = fileFileName;
    }

    public List<String> getFileContentType() {
        return fileContentType;
    }

    public void setFileContentType(List<String> fileContentType) {
        this.fileContentType = fileContentType;
    }

    public int getCourseId() {
        return courseId;
    }

    public void setCourseId(int courseId) {
        this.courseId = courseId;
    }
}
