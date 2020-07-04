package file.mapper;

import file.pojo.CourseResource;

import java.util.List;

public interface CourseResourceMapper {
    CourseResource selectById(Integer id);

    List<CourseResource> selectAllByCourseId(Integer courseId);

    int insert(CourseResource courseResource);

    int delete(Integer resourceId);
}
