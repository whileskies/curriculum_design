package student.mapper;

import student.pojo.StuTask;

import java.util.List;

public interface StuCourseTaskMapper {
    List<StuTask> selectAllByCourseId(Integer courseId);

    StuTask selectByTaskId(Integer taskId);
}
