package teacher.service.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import teacher.mapper.TeaCourseMapper;
import teacher.pojo.TeaCourse;
import teacher.service.TeaCourseService;

@Service
public class TeaCourseServiceImpl implements TeaCourseService {
    private final TeaCourseMapper teaCourseMapper;

    @Autowired
    public TeaCourseServiceImpl(TeaCourseMapper teaCourseMapper) {
        this.teaCourseMapper = teaCourseMapper;
    }

    public TeaCourse findTCourse(TeaCourse teaCourse) {
        if (teaCourse.getId() != null)
            return teaCourseMapper.selectByCourseId(teaCourse.getId());
        if (teaCourse.getCode() != null)
            return teaCourseMapper.selectByCode(teaCourse.getCode());
        return null;
    }

    public boolean deleteByCourseId(Integer courseId) {
        return teaCourseMapper.delete(courseId) > 0;
    }
}
