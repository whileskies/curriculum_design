package file.mapper;

import file.pojo.TaskFile;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface TaskFileMapper {

    TaskFile selectByTaskIdStudentId(@Param("taskId") Integer taskId, @Param("studentId") Integer StudentId);

    List<TaskFile> selectAllByTaskId(Integer taskId);

    int insert(TaskFile taskFile);

    int update(TaskFile taskFile);
}
