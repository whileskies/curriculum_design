package student.service.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import student.mapper.StuCourseMapper;
import student.pojo.StuCourse;
import student.service.StuCourseService;

@Service
public class StuCourseServiceImpl implements StuCourseService {
    private final StuCourseMapper stuCourseMapper;

    @Autowired
    public StuCourseServiceImpl(StuCourseMapper stuCourseMapper) {
        this.stuCourseMapper = stuCourseMapper;
    }

    public StuCourse findStuCourse(StuCourse stuCourse) {
        if (stuCourse.getId() != null)
            return stuCourseMapper.selectByCourseId(stuCourse.getId());
        if (stuCourse.getCode() != null)
            return stuCourseMapper.selectByCode(stuCourse.getCode());
        return null;
    }
}
