package student.service;

import login.pojo.User;
import student.pojo.StuCourse;

import java.util.List;

public interface StuCourseListService {
    /**
     * 查询user用户拥有的课程
     * @param user 用户
     * @return 课程列表
     */
    List<StuCourse> findSCourses(User user);

    /**
     * 进入课堂
     * @param course 课程对象
     * @param student 学生对象
     * @return 状态码
     */
    int ENTER_COURSE_NOT_EXISTS = 0;
    int ENTER_HAS_ENTERED = 1;
    int ENTER_FAIL = 2;
    int ENTER_SUCC = 3;
    int enterCourse(StuCourse course, User student);
}
