package student.mapper;

import student.pojo.StuNotice;

import java.util.List;

public interface StuCourseNoticeMapper {
    List<StuNotice> selectAllByCourseId(Integer courseId);



}
