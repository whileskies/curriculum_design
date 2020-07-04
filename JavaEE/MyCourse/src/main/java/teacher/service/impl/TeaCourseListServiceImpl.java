package teacher.service.impl;

import login.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import teacher.mapper.TeaCourseMapper;
import teacher.pojo.TeaCourse;
import teacher.service.TeaCourseListService;
import util.GenerateCode;

import java.util.Date;
import java.util.List;

@Service
public class TeaCourseListServiceImpl implements TeaCourseListService {
    private final TeaCourseMapper teaCourseMapper;

    @Autowired
    public TeaCourseListServiceImpl(TeaCourseMapper teaCourseMapper) {
        this.teaCourseMapper = teaCourseMapper;
    }

    public List<TeaCourse> findTCourses(User user) {
        List<TeaCourse> teaCourses = teaCourseMapper.selectByTeacherId(user.getId());

        for (TeaCourse teaCourse : teaCourses) {
            teaCourse.setStudentCount(teaCourseMapper.selectStudentCount(teaCourse));
        }

        return teaCourses;
    }

    public boolean addCourse(TeaCourse teaCourse, User user) {
        String code = GenerateCode.generate();

        boolean norepeat = false;

        while (!norepeat) {
            if (teaCourseMapper.selectByCode(code) == null)
                norepeat = true;
            else
                code = GenerateCode.generate();
        }

        teaCourse.setCode(code);
        teaCourse.setCreateTime(new Date());

        boolean ret = teaCourseMapper.insertCourse(teaCourse) > 0 && teaCourseMapper.insertCourseTeacher(teaCourse.getId(), user.getId()) > 0;
        if (ret) {
            teaCourse = teaCourseMapper.selectByCode(code);
        }
        return ret;
    }
}
