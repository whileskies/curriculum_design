package teacher.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import login.pojo.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import teacher.pojo.TeaCourse;
import teacher.pojo.TeaNotice;
import teacher.service.TeaCourseNoticeService;
import teacher.service.TeaCourseService;

import java.util.Date;
import java.util.List;


public class TeaCourseNoticeAction extends ActionSupport{
    private static final Logger LOG = LogManager.getLogger(TeaCourseNoticeAction.class);

    private Integer courseId;

    private final TeaCourseNoticeService teaCourseNoticeService;

    private final TeaCourseService teaCourseService;

    @Autowired
    public TeaCourseNoticeAction(TeaCourseNoticeService teaCourseNoticeService, TeaCourseService teaCourseService) {
        this.teaCourseNoticeService = teaCourseNoticeService;
        this.teaCourseService = teaCourseService;
    }


    private List<TeaNotice> teaNotices;
    private TeaCourse teaCourse;

    public String getNotice() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (courseId == null)
            return ERROR;

        TeaCourse c = new TeaCourse();
        c.setId(courseId);

        teaNotices = teaCourseNoticeService.findNotices(c);
        teaCourse = teaCourseService.findTCourse(c);
        LOG.debug("teaNotices: " + teaNotices);
        LOG.debug("teaCourse: " + teaCourse);

        return SUCCESS;
    }

    private String noticeName;
    private String noticeContent;

    public String addNotice() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (noticeName == null || noticeName.trim().equals("") ||
            noticeContent == null || courseId == null)
            return ERROR;

        TeaNotice teaNotice = new TeaNotice();
        teaNotice.setTitle(noticeName.trim());
        teaNotice.setContent(noticeContent);
        teaNotice.setCourseId(courseId);
        teaNotice.setWriterId(user.getId());
        teaNotice.setCreateTime(new Date());
        teaNotice.setUpdateTime(new Date());

        if (teaCourseNoticeService.addNotice(teaNotice))
            return SUCCESS;
        else
            return ERROR;
    }


    private Integer noticeId;
    public String deleteNotice() {
        User user = (User) ActionContext.getContext().getSession().get("user");

        if (user == null)
            return LOGIN;

        if (noticeId == null || courseId == null)
            return ERROR;

        TeaNotice teaNotice = new TeaNotice();
        teaNotice.setId(noticeId);
        if (teaCourseNoticeService.deleteNotice(teaNotice))
            return SUCCESS;
        else
            return ERROR;
    }


    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public List<TeaNotice> getTeaNotices() {
        return teaNotices;
    }

    public void setTeaNotices(List<TeaNotice> teaNotices) {
        this.teaNotices = teaNotices;
    }

    public TeaCourse getTeaCourse() {
        return teaCourse;
    }

    public void setTeaCourse(TeaCourse teaCourse) {
        this.teaCourse = teaCourse;
    }

    public String getNoticeName() {
        return noticeName;
    }

    public void setNoticeName(String noticeName) {
        this.noticeName = noticeName;
    }

    public String getNoticeContent() {
        return noticeContent;
    }

    public void setNoticeContent(String noticeContent) {
        this.noticeContent = noticeContent;
    }

    public Integer getNoticeId() {
        return noticeId;
    }

    public void setNoticeId(Integer noticeId) {
        this.noticeId = noticeId;
    }
}


