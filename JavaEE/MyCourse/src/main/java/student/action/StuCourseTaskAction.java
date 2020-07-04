package student.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import file.pojo.TaskFile;
import file.service.TaskFileService;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import student.pojo.StuCourse;
import student.pojo.StuTask;
import student.service.StuCourseService;
import student.service.StuCourseTaskService;

import java.text.SimpleDateFormat;
import java.util.List;


public class StuCourseTaskAction extends ActionSupport{
    private static final Logger LOG = LogManager.getLogger(StuCourseTaskAction.class);

    private final StuCourseTaskService stuCourseTaskService;
    private final StuCourseService stuCourseService;
    private final TaskFileService taskFileService;

    @Autowired
    public StuCourseTaskAction(StuCourseTaskService stuCourseTaskService, StuCourseService stuCourseService, TaskFileService taskFileService) {
        this.stuCourseTaskService = stuCourseTaskService;
        this.stuCourseService = stuCourseService;
        this.taskFileService = taskFileService;
    }



    private List<StuTask> stuTasks;
    private StuCourse stuCourse;
    private Integer courseId;

    public String getTasks() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (courseId == null)
            return ERROR;

        StuCourse s = new StuCourse();
        s.setId(courseId);

        stuTasks = stuCourseTaskService.findTasks(s);
        stuCourse = stuCourseService.findStuCourse(s);
        LOG.debug("stuTasks: " + stuTasks);
        LOG.debug("stuCourse: " + stuCourse);

        return SUCCESS;
    }


    private Integer taskId;
    private StuTask stuTask;

    private TaskFile taskFile;

    public String taskDetail() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskId == null || courseId == null)
            return ERROR;

        stuTask = stuCourseTaskService.findTaskById(taskId);

        StuCourse s = new StuCourse();
        s.setId(courseId);

        stuCourse = stuCourseService.findStuCourse(s);

        taskFile = taskFileService.findByTaskIdStudentId(taskId, user.getId());
        if (taskFile != null) {
            SimpleDateFormat f = new SimpleDateFormat("yyyy-MM-dd HH:mm");
            taskFile.sethUploadTime(f.format(taskFile.getUploadTime()));
        }

        if (stuTask == null || stuCourse == null)
            return ERROR;
        else
            return SUCCESS;

    }


    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public List<StuTask> getStuTasks() {
        return stuTasks;
    }

    public void setStuTasks(List<StuTask> stuTasks) {
        this.stuTasks = stuTasks;
    }

    public StuCourse getStuCourse() {
        return stuCourse;
    }

    public void setStuCourse(StuCourse stuCourse) {
        this.stuCourse = stuCourse;
    }

    public Integer getTaskId() {
        return taskId;
    }

    public void setTaskId(Integer taskId) {
        this.taskId = taskId;
    }

    public StuTask getStuTask() {
        return stuTask;
    }

    public void setStuTask(StuTask stuTask) {
        this.stuTask = stuTask;
    }

    public TaskFile getTaskFile() {
        return taskFile;
    }

    public void setTaskFile(TaskFile taskFile) {
        this.taskFile = taskFile;
    }
}
