package teacher.service.impl;

import file.mapper.TaskFileMapper;
import file.pojo.TaskFile;
import login.mapper.UserMapper;
import login.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import teacher.mapper.TeaCourseMapper;
import teacher.mapper.TeaCourseTaskMapper;
import teacher.pojo.StuTaskFiles;
import teacher.pojo.TeaCourse;
import teacher.pojo.TeaTask;
import teacher.service.TeaCourseTaskService;
import util.Html2Text;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

@Service
public class TeaCourseTaskServiceImpl implements TeaCourseTaskService {

    private final TeaCourseTaskMapper teaCourseTaskMapper;
    private final UserMapper userMapper;

    private final TeaCourseMapper teaCourseMapper;

    private final TaskFileMapper taskFileMapper;

    @Autowired
    public TeaCourseTaskServiceImpl(TeaCourseTaskMapper teaCourseTaskMapper, UserMapper userMapper, TeaCourseMapper teaCourseMapper, TaskFileMapper taskFileMapper) {
        this.teaCourseTaskMapper = teaCourseTaskMapper;
        this.userMapper = userMapper;
        this.teaCourseMapper = teaCourseMapper;
        this.taskFileMapper = taskFileMapper;
    }

    public List<TeaTask> findTasks(TeaCourse teaCourse) {
        List<TeaTask> teaTasks = teaCourseTaskMapper.selectAllByCourseId(teaCourse.getId());

        for (TeaTask teaTask : teaTasks) {
            teaTask.setPlainTextContent(Html2Text.StripHT(teaTask.getContent(), 100));

            SimpleDateFormat f = new SimpleDateFormat("yyyy-MM-dd HH:mm");
            teaTask.sethUpdateTime(f.format(teaTask.getUpdateTime()));
            if (teaTask.getDeadline() != null)
                teaTask.sethDeadline(f.format(teaTask.getDeadline()));
            teaTask.setTeacher(userMapper.selectById(teaTask.getWriterId()));
        }

        return teaTasks;
    }

    public TeaTask findTaskById(Integer taskId) {
        TeaTask teaTask = teaCourseTaskMapper.selectByTaskId(taskId);
        SimpleDateFormat f = new SimpleDateFormat("yyyy-MM-dd HH:mm");

        teaTask.sethUpdateTime(f.format(teaTask.getUpdateTime()));
        if (teaTask.getDeadline() != null)
            teaTask.sethDeadline(f.format(teaTask.getDeadline()));

        teaTask.setTeacher(userMapper.selectById(teaTask.getWriterId()));

        return teaTask;
    }

    public boolean addTask(TeaTask teaTask) {
        return teaCourseTaskMapper.insertTask(teaTask) > 0;
    }

    public boolean updateTask(TeaTask teaTask) {
        return teaCourseTaskMapper.updateTask(teaTask) > 0;
    }

    public boolean deleteTask(TeaTask teaTask) {
        return teaCourseTaskMapper.deleteTask(teaTask.getId()) > 0;
    }

    public List<StuTaskFiles> findStuTaskFiles(Integer courseId, Integer taskId) {
        List<User> students = teaCourseMapper.selectCourseStudent(courseId);

        if (students != null) {
            List<StuTaskFiles> stuTaskFiles = new ArrayList<StuTaskFiles>();

            for (User s : students) {
                StuTaskFiles stf = new StuTaskFiles();
                stf.setUser(s);

                TaskFile taskFile = taskFileMapper.selectByTaskIdStudentId(taskId, s.getId());

                if (taskFile != null) {
                    stf.setTaskFile(taskFile);
                    taskFile.sethUploadTime(new SimpleDateFormat("yyyy-MM-dd HH:mm").format(taskFile.getUploadTime()));
                }

                stuTaskFiles.add(stf);
            }


            return stuTaskFiles;
        } else
            return null;
    }

}

