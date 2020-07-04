package student.service.impl;

import login.mapper.UserMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import student.mapper.StuCourseTaskMapper;
import student.pojo.StuCourse;
import student.pojo.StuTask;
import student.service.StuCourseTaskService;
import util.Html2Text;

import java.text.SimpleDateFormat;
import java.util.List;

@Service
public class StuCourseTaskServiceImpl implements StuCourseTaskService {

    private final StuCourseTaskMapper stuCourseTaskMapper;
    private final UserMapper userMapper;

    @Autowired
    public StuCourseTaskServiceImpl(StuCourseTaskMapper stuCourseTaskMapper, UserMapper userMapper) {
        this.stuCourseTaskMapper = stuCourseTaskMapper;
        this.userMapper = userMapper;
    }

    public List<StuTask> findTasks(StuCourse stuCourse) {
        List<StuTask> stuTasks = stuCourseTaskMapper.selectAllByCourseId(stuCourse.getId());

        for (StuTask stuTask : stuTasks) {
            stuTask.setPlainTextContent(Html2Text.StripHT(stuTask.getContent(), 100));

            SimpleDateFormat f = new SimpleDateFormat("yyyy-MM-dd HH:mm");
            stuTask.sethUpdateTime(f.format(stuTask.getUpdateTime()));
            if (stuTask.getDeadline() != null)
                stuTask.sethDeadline(f.format(stuTask.getDeadline()));
            stuTask.setTeacher(userMapper.selectById(stuTask.getWriterId()));
        }

        return stuTasks;
    }

    public StuTask findTaskById(Integer taskId) {
        StuTask stuTask = stuCourseTaskMapper.selectByTaskId(taskId);
        SimpleDateFormat f = new SimpleDateFormat("yyyy-MM-dd HH:mm");

        stuTask.sethUpdateTime(f.format(stuTask.getUpdateTime()));
        if (stuTask.getDeadline() != null)
            stuTask.sethDeadline(f.format(stuTask.getDeadline()));

        stuTask.setTeacher(userMapper.selectById(stuTask.getWriterId()));

        return stuTask;
    }


}

