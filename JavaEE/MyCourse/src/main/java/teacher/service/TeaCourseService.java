package teacher.service;

import teacher.pojo.TeaCourse;

public interface TeaCourseService {
    /**
     * 根据courseId或courseCode查询课程信息
     * @param teaCourse 课程对象
     * @return 查找结果对象
     */
    TeaCourse findTCourse(TeaCourse teaCourse);

    boolean deleteByCourseId(Integer courseId);
}
