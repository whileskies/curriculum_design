package teacher.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import teacher.pojo.StuTaskFiles;
import teacher.pojo.TeaCourse;
import teacher.pojo.TeaTask;
import teacher.service.TeaCourseService;
import teacher.service.TeaCourseTaskService;

import java.util.Date;
import java.util.List;


public class TeaCourseTaskAction extends ActionSupport{
    private static final Logger LOG = LogManager.getLogger(TeaCourseTaskAction.class);

    private Integer courseId;
    private final TeaCourseTaskService teaCourseTaskService;
    private final TeaCourseService teaCourseService;

    @Autowired
    public TeaCourseTaskAction(TeaCourseTaskService teaCourseTaskService, TeaCourseService teaCourseService) {
        this.teaCourseTaskService = teaCourseTaskService;
        this.teaCourseService = teaCourseService;
    }


    private List<TeaTask> teaTasks;
    private TeaCourse teaCourse;

    public String getTasks() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (courseId == null)
            return ERROR;

        TeaCourse c = new TeaCourse();
        c.setId(courseId);

        teaTasks = teaCourseTaskService.findTasks(c);
        teaCourse = teaCourseService.findTCourse(c);
        LOG.debug("teaTasks: " + teaTasks);
        LOG.debug("teaCourse: " + teaCourse);

        return SUCCESS;
    }

    private String taskName;
    private String taskContent;
    private long deadlineTime;

    public String addTask() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskName == null || taskName.trim().equals("") ||
            taskContent == null || courseId == null)
            return ERROR;

        TeaTask teaTask = new TeaTask();
        teaTask.setTitle(taskName.trim());
        teaTask.setContent(taskContent);
        teaTask.setCourseId(courseId);
        teaTask.setWriterId(user.getId());
        teaTask.setCreateTime(new Date());
        teaTask.setUpdateTime(new Date());
        if (deadlineTime != 0)
            teaTask.setDeadline(new Date(deadlineTime));

        if (teaCourseTaskService.addTask(teaTask))
            return SUCCESS;
        else
            return ERROR;
    }

    public String updateTask() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskName == null || taskName.trim().equals("") ||
                taskContent == null || courseId == null || taskId == null)
            return ERROR;

        TeaTask teaTask = teaCourseTaskService.findTaskById(taskId);
        if (teaTask == null || !courseId.equals(teaTask.getCourseId())) return ERROR;

        teaTask.setTitle(taskName.trim());
        teaTask.setContent(taskContent);
        teaTask.setWriterId(user.getId());
        teaTask.setUpdateTime(new Date());
        if(deadlineTime != 0)
            teaTask.setDeadline(new Date(deadlineTime));
        else
            teaTask.setDeadline(null);

        if (teaCourseTaskService.updateTask(teaTask))
            return SUCCESS;
        else
            return ERROR;
    }


    private Integer taskId;

    public String deleteTask() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskId == null || courseId == null)
            return ERROR;

        TeaTask teaTask = new TeaTask();
        teaTask.setId(taskId);
        if (teaCourseTaskService.deleteTask(teaTask))
            return SUCCESS;
        else
            return ERROR;
    }


    private TeaTask teaTask;
    public String toUpdate() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskId == null || courseId == null)
            return ERROR;

        teaTask = teaCourseTaskService.findTaskById(taskId);
        TeaCourse t = new TeaCourse();
        t.setId(courseId);

        teaCourse = teaCourseService.findTCourse(t);

        if (teaTask == null || teaCourse == null)
            return ERROR;
        else
            return SUCCESS;
    }


    private List<StuTaskFiles> stuTaskFiles;
    private int allNum = 0;
    private int uploadNum = 0;
    public String taskDetail() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (taskId == null || courseId == null)
            return ERROR;

        teaTask = teaCourseTaskService.findTaskById(taskId);

        TeaCourse t = new TeaCourse();
        t.setId(courseId);
        teaCourse = teaCourseService.findTCourse(t);

        stuTaskFiles = teaCourseTaskService.findStuTaskFiles(courseId, taskId);

        LOG.debug("stuTaskFiles: " + stuTaskFiles);

        allNum = stuTaskFiles.size();
        for (StuTaskFiles s : stuTaskFiles) {
            if (s.getTaskFile() != null)
                uploadNum++;
        }

        return SUCCESS;
    }



    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public List<TeaTask> getTeaTasks() {
        return teaTasks;
    }

    public void setTeaTasks(List<TeaTask> teaTasks) {
        this.teaTasks = teaTasks;
    }

    public TeaCourse getTeaCourse() {
        return teaCourse;
    }

    public void setTeaCourse(TeaCourse teaCourse) {
        this.teaCourse = teaCourse;
    }

    public String getTaskName() {
        return taskName;
    }

    public void setTaskName(String taskName) {
        this.taskName = taskName;
    }

    public String getTaskContent() {
        return taskContent;
    }

    public void setTaskContent(String taskContent) {
        this.taskContent = taskContent;
    }

    public long getDeadlineTime() {
        return deadlineTime;
    }

    public void setDeadlineTime(long deadlineTime) {
        this.deadlineTime = deadlineTime;
    }

    public Integer getTaskId() {
        return taskId;
    }

    public void setTaskId(Integer taskId) {
        this.taskId = taskId;
    }

    public TeaTask getTeaTask() {
        return teaTask;
    }

    public void setTeaTask(TeaTask teaTask) {
        this.teaTask = teaTask;
    }

    public List<StuTaskFiles> getStuTaskFiles() {
        return stuTaskFiles;
    }

    public void setStuTaskFiles(List<StuTaskFiles> stuTaskFiles) {
        this.stuTaskFiles = stuTaskFiles;
    }

    public int getAllNum() {
        return allNum;
    }

    public void setAllNum(int allNum) {
        this.allNum = allNum;
    }

    public int getUploadNum() {
        return uploadNum;
    }

    public void setUploadNum(int uploadNum) {
        this.uploadNum = uploadNum;
    }
}
