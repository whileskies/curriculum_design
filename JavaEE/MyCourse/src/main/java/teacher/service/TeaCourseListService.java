package teacher.service;

import login.pojo.User;
import teacher.pojo.TeaCourse;

import java.util.List;

public interface TeaCourseListService {
    /**
     * 查询user用户拥有的课程
     * @param user 用户
     * @return 课程列表
     */
    List<TeaCourse> findTCourses(User user);

    /**
     * 添加新课程
     * @param teaCourse 课程对象
     * @param user 创建者对象
     * @return 是否成功
     */
    boolean addCourse(TeaCourse teaCourse, User user);
}
