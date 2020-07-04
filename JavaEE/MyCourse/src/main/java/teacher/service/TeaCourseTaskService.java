package teacher.service;

import teacher.pojo.StuTaskFiles;
import teacher.pojo.TeaCourse;
import teacher.pojo.TeaTask;

import java.util.List;

public interface TeaCourseTaskService {

    /**
     * 获取课程所有作业
     * @param teaCourse 课程对象
     * @return 作业集合
     */
    List<TeaTask> findTasks(TeaCourse teaCourse);


    /**
     * 根据id获取作业对象
     * @param taskId 作业id
     * @return 作业对象
     */
    TeaTask findTaskById(Integer taskId);

    /**
     * 增加作业
     * @param teaTask 作业
     * @return 是否成功
     */
    boolean addTask(TeaTask teaTask);

    /**
     * 修改作业
     * @param teaTask 作业
     * @return 是否成功
     */
    boolean updateTask(TeaTask teaTask);

    /**
     * 删除作业
     * @param teaTask 作业对象
     * @return 是否成功删除
     */
    boolean deleteTask(TeaTask teaTask);

    /**
     * 获取学生作业文件集
     * @param courseId 课程id
     * @param taskId 作业id
     * @return 作业集
     */
    List<StuTaskFiles> findStuTaskFiles(Integer courseId, Integer taskId);

}
