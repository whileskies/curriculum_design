package file.service;

import file.pojo.CourseResource;

import java.io.File;
import java.io.IOException;
import java.util.List;

public interface CourseResourceService {

    boolean uploadFiles(List<File> files, String webInfPath, List<String> fileNames, Integer courseId) throws IOException;

    List<CourseResource> findByCourseId(Integer courseId);

    CourseResource findByResourceId(Integer resourceId);

    boolean deleteResource(Integer resourceId);

}
