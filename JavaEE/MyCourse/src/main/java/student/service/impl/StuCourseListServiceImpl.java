package student.service.impl;

import login.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import student.mapper.StuCourseMapper;
import student.pojo.StuCourse;
import student.service.StuCourseListService;

import java.util.List;

@Service
public class StuCourseListServiceImpl implements StuCourseListService {
    private final StuCourseMapper stuCourseMapper;

    @Autowired
    public StuCourseListServiceImpl(StuCourseMapper stuCourseMapper) {
        this.stuCourseMapper = stuCourseMapper;
    }


    public List<StuCourse> findSCourses(User user) {
        List<StuCourse> stuCourses = stuCourseMapper.selectByStudentId(user.getId());

        for (StuCourse stuCourse : stuCourses) {
            stuCourse.setStudentCount(stuCourseMapper.selectStudentCount(stuCourse.getId()));
            stuCourse.setTeacher(stuCourseMapper.selectTeacherByCourseId(stuCourse.getId()));
        }

        return stuCourses;
    }

    public int enterCourse(StuCourse course, User student) {
        StuCourse old = stuCourseMapper.selectByCode(course.getCode());
        if (old == null)
            return ENTER_COURSE_NOT_EXISTS;
        course.setId(old.getId());
        course.setName(old.getName());
        if (stuCourseMapper.selectEnterTimeByStudentId(course.getId(), student.getId()) != null)
            return ENTER_HAS_ENTERED;
        boolean ret = stuCourseMapper.insertCourseStudent(course.getId(), student.getId(), course.getEnterTime()) > 0;
        if (ret)
            return ENTER_SUCC;
        else
            return ENTER_FAIL;
    }
}
