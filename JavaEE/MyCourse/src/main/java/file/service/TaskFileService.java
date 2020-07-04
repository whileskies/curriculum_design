package file.service;

import file.pojo.TaskFile;

import java.io.File;
import java.io.IOException;

public interface TaskFileService {

    boolean upload(File file, String webInfPath, String fileName, Integer taskId, Integer courseId, Integer userId) throws IOException;

    TaskFile findByTaskIdStudentId(Integer taskId, Integer studentId);

    TaskFile findTaskFile(Integer taskId, Integer userId);

    File downloadAsZip(String webInfPath, Integer taskId) throws IOException;
}
