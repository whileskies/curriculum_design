package student.service;

import student.pojo.StuCourse;

public interface StuCourseService {
    /**
     * 根据courseId或courseCode查询课程信息
     * @param stuCourse 课程对象
     * @return 查找结果对象
     */
    StuCourse findStuCourse(StuCourse stuCourse);
}
