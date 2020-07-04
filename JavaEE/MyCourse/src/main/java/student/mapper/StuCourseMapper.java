package student.mapper;

import login.pojo.User;
import org.apache.ibatis.annotations.Param;
import student.pojo.StuCourse;

import java.util.Date;
import java.util.List;


public interface StuCourseMapper {
    List<StuCourse> selectByStudentId(Integer studentId);

    StuCourse selectByCourseId(Integer courseId);

    StuCourse selectByCode(String code);

    int selectStudentCount(Integer courseId);

    User selectTeacherByCourseId(Integer courseId);

    Date selectEnterTimeByStudentId(@Param("courseId") Integer courseId, @Param("studentId") Integer studentId);

    int insertCourseStudent(@Param("courseId") Integer courseId, @Param("studentId") Integer studentId, @Param("enterTime") Date enterTime);

}