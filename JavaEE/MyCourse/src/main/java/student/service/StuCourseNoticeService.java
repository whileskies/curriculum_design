package student.service;

import student.pojo.StuCourse;
import student.pojo.StuNotice;

import java.util.List;

public interface StuCourseNoticeService {

    /**
     * 获取课程所有通知
     * @param stuCourse 课程对象
     * @return 通知集合
     */
    List<StuNotice> findNotices(StuCourse stuCourse);


}
