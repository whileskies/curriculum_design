package teacher.mapper;

import teacher.pojo.TeaTask;

import java.util.List;

public interface TeaCourseTaskMapper {
    List<TeaTask> selectAllByCourseId(Integer courseId);

    TeaTask selectByTaskId(Integer taskId);

    int insertTask(TeaTask teaTask);

    int updateTask(TeaTask teaTask);

    int deleteTask(Integer taskId);
}
