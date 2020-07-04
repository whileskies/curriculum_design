package teacher.mapper;

import login.pojo.User;
import org.apache.ibatis.annotations.Param;
import teacher.pojo.TeaCourse;

import java.util.List;


public interface TeaCourseMapper {
    List<TeaCourse> selectByTeacherId(Integer teacherId);

    TeaCourse selectByCode(String code);

    TeaCourse selectByCourseId(Integer courseId);

    int selectStudentCount(TeaCourse teaCourse);

    int insertCourse(TeaCourse teaCourse);

    int insertCourseTeacher(@Param("courseId") Integer courseId, @Param("teacherId") Integer teacherId);

    List<User> selectCourseStudent(Integer courseId);

    int delete(Integer courseId);
}