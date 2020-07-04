package student.service;

import student.pojo.StuCourse;
import student.pojo.StuTask;

import java.util.List;

public interface StuCourseTaskService {

    /**
     * 获取课程所有作业
     * @param stuCourse 课程对象
     * @return 作业集合
     */
    List<StuTask> findTasks(StuCourse stuCourse);


    /**
     * 根据id获取作业对象
     * @param taskId 作业id
     * @return 作业对象
     */
    StuTask findTaskById(Integer taskId);

}
