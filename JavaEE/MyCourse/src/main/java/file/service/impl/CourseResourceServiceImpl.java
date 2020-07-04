package file.service.impl;

import file.mapper.CourseResourceMapper;
import file.pojo.CourseResource;
import file.service.CourseResourceService;
import org.apache.commons.io.FileUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.UUID;

@Service
public class CourseResourceServiceImpl implements CourseResourceService {
    private static final String BASE_DIR = "/upload/";

    private final CourseResourceMapper courseResourceMapper;

    @Autowired
    public CourseResourceServiceImpl(CourseResourceMapper courseResourceMapper) {
        this.courseResourceMapper = courseResourceMapper;
    }

    public boolean uploadFiles(List<File> files, String webInfPath, List<String> fileNames, Integer courseId) throws IOException {
        String courseDirStr = webInfPath + BASE_DIR + "course-" + courseId;
        File courseDir = new File(courseDirStr);
        if (!courseDir.exists()) {
            if (!courseDir.mkdirs())
                return false;
        }

        String resourceDirStr = courseDirStr + "/resource";
        File resourceDirFile = new File(resourceDirStr);
        if (!resourceDirFile.exists()) {
            if (!resourceDirFile.mkdirs())
                return false;
        }

        for (int i = 0; i < files.size(); i++) {
            CourseResource resource = new CourseResource();

            String uuid = UUID.randomUUID().toString();
            String uuidFileName = resourceDirStr + "/" + uuid;
            File uuidFile = new File(uuidFileName);

            resource.setCourseId(courseId);
            resource.setFileName(fileNames.get(i));
            resource.setUploadTime(new Date());
            resource.setFilePath(uuidFile.getAbsolutePath());

            FileUtils.copyFile(files.get(i), uuidFile);

            if (courseResourceMapper.insert(resource) < 1) {
                uuidFile.deleteOnExit();
                return false;
            }
        }

        return true;
    }

    public List<CourseResource> findByCourseId(Integer courseId) {
        List<CourseResource> courseResources = courseResourceMapper.selectAllByCourseId(courseId);

        for (CourseResource resource : courseResources) {
            SimpleDateFormat f = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
            resource.sethUploadTime(f.format(resource.getUploadTime()));
            File file = new File(resource.getFilePath());
            String fileSizeStr;
            long fileSize = file.length();
            if (fileSize < 1024)
                fileSizeStr = Long.toString(fileSize) + "B";
            else if (fileSize < 1024 * 1024)
                fileSizeStr = String.format("%.2f", fileSize / 1024.0) + "KB";
            else if (fileSize < 1024 * 1024 * 1024)
                fileSizeStr = String.format("%.2f", fileSize / 1024.0 / 1024.0) + "MB";
            else
                fileSizeStr = String.format("%.2f", fileSize / 1024.0 / 1024.0 / 1024.0) + "GB";
            resource.sethFileSize(fileSizeStr);
        }

        return courseResources;
    }

    public CourseResource findByResourceId(Integer resourceId) {
        return courseResourceMapper.selectById(resourceId);
    }

    public boolean deleteResource(Integer resourceId) {
        CourseResource resource = courseResourceMapper.selectById(resourceId);
        if (resource == null)
            return false;

        File file = new File(resource.getFilePath());
        if (!file.delete())
            return false;
        courseResourceMapper.delete(resourceId);

        return true;
    }
}
