package teacher.service.impl;

import login.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import teacher.mapper.TeaCourseMapper;
import teacher.service.TeaCourseStudentService;

import java.util.List;

@Service
public class TeaCourseStudentServiceImpl implements TeaCourseStudentService {

    private final TeaCourseMapper teaCourseMapper;

    @Autowired
    public TeaCourseStudentServiceImpl(TeaCourseMapper teaCourseMapper) {
        this.teaCourseMapper = teaCourseMapper;
    }

    public List<User> findAllByCourseId(Integer courseId) {
        return teaCourseMapper.selectCourseStudent(courseId);
    }
}
