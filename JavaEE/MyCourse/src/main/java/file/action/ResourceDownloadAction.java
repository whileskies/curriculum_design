package file.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.pojo.CourseResource;
import file.service.CourseResourceService;
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


public class ResourceDownloadAction extends ActionSupport {
    private static final Logger LOG = LogManager.getLogger(ResourceDownloadAction.class);

    private User user;

    private Integer resourceId;
    private CourseResource resource;
    private File file;

    private final CourseResourceService courseResourceService;

    @Autowired
    public ResourceDownloadAction(CourseResourceService courseResourceService) {
        this.courseResourceService = courseResourceService;
    }


    public String download() {
        user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (resourceId == null)
            return ERROR;

        resource = courseResourceService.findByResourceId(resourceId);

        if (resource != null)
            return SUCCESS;
    else
            return ERROR;
    }


    public InputStream getInputStream() throws FileNotFoundException {

        file = new File(resource.getFilePath());

        return new FileInputStream(file);
    }


    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }


    public String getFileName() throws Exception {
        LOG.debug("fileName: " + resource.getFileName());

        return DownloadFileNameOp.downToUtf8String(resource.getFileName(), ServletActionContext.getRequest());

    }


    public Long getContentLength() {
        return file.length();
    }

    public Integer getResourceId() {
        return resourceId;
    }

    public void setResourceId(Integer resourceId) {
        this.resourceId = resourceId;
    }

    public CourseResource getResource() {
        return resource;
    }

    public void setResource(CourseResource resource) {
        this.resource = resource;
    }

    public File getFile() {
        return file;
    }

    public void setFile(File file) {
        this.file = file;
    }
}
