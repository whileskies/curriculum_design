package file.service.impl;

import file.mapper.TaskFileMapper;
import file.pojo.TaskFile;
import file.service.TaskFileService;
import login.mapper.UserMapper;
import login.pojo.User;
import org.apache.commons.io.FileUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import teacher.mapper.TeaCourseMapper;
import teacher.mapper.TeaCourseTaskMapper;
import teacher.pojo.TeaCourse;
import teacher.pojo.TeaTask;

import java.io.*;
import java.util.Date;
import java.util.List;
import java.util.UUID;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

@Service
public class TaskFileServiceImpl implements TaskFileService {
    private static final Logger LOG = LogManager.getLogger(TaskFileServiceImpl.class);
    private static final String BASE_DIR = "/upload/";

    private final TaskFileMapper taskFileMapper;

    private final TeaCourseTaskMapper teaCourseTaskMapper;

    private final TeaCourseMapper teaCourseMapper;

    private final UserMapper userMapper;

    @Autowired
    public TaskFileServiceImpl(TaskFileMapper taskFileMapper, TeaCourseTaskMapper teaCourseTaskMapper, TeaCourseMapper teaCourseMapper, UserMapper userMapper) {
        this.taskFileMapper = taskFileMapper;
        this.teaCourseTaskMapper = teaCourseTaskMapper;
        this.teaCourseMapper = teaCourseMapper;
        this.userMapper = userMapper;
    }

    public boolean upload(File file, String webInfPath, String fileName, Integer taskId, Integer courseId, Integer userId) throws IOException {
        String courseDirStr = webInfPath + BASE_DIR + "course-" + courseId;
        File courseDir = new File(courseDirStr);
        if (!courseDir.exists()) {
            if (!courseDir.mkdirs())
                return false;
        }

        String taskDirStr = courseDirStr + "/task-" + taskId;
        File taskDir = new File(taskDirStr);
        if (!taskDir.exists()) {
            if (!taskDir.mkdirs())
                return false;
        }

        File taskFile = null;

        TaskFile old = taskFileMapper.selectByTaskIdStudentId(taskId, userId);
        if (old != null) {
            //原文件存在，替换
            taskFile = new File(old.getFilePath());
            FileUtils.copyFile(file, taskFile);

            old.setFileName(fileName);
            old.setUploadTime(new Date());

            if (taskFileMapper.update(old) > 0) {
                return true;
            } else {
                taskFile.deleteOnExit();
                return false;
            }

        } else {
            String uuidName = UUID.randomUUID().toString();
            String taskFileName = taskDirStr + "/" + uuidName;
            taskFile = new File(taskFileName);

            //原文件不存在
            TaskFile tf = new TaskFile();
            tf.setFileName(fileName);
            tf.setTaskId(taskId);
            tf.setUserId(userId);
            tf.setUploadTime(new Date());
            tf.setFilePath(taskFile.getAbsolutePath());

            FileUtils.copyFile(file, taskFile);

            if(taskFileMapper.insert(tf) > 0) {
                return true;
            } else {
                taskFile.deleteOnExit();
                return false;
            }
        }

    }

    public TaskFile findByTaskIdStudentId(Integer taskId, Integer studentId) {
        return taskFileMapper.selectByTaskIdStudentId(taskId, studentId);
    }

    public TaskFile findTaskFile(Integer taskId, Integer userId) {
        return taskFileMapper.selectByTaskIdStudentId(taskId, userId);
    }

    public File downloadAsZip(String webInfPath, Integer taskId) throws IOException {
        String tmpDir = webInfPath + BASE_DIR + "tmp/";

        TeaTask task = teaCourseTaskMapper.selectByTaskId(taskId);
        TeaCourse teaCourse = teaCourseMapper.selectByCourseId(task.getCourseId());

        String zipName = tmpDir +  teaCourse.getName() + "-" + task.getTitle() + ".zip";

        ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(zipName));

        List<TaskFile> taskFiles = taskFileMapper.selectAllByTaskId(taskId);

        for (TaskFile t : taskFiles) {
            BufferedInputStream bis = new BufferedInputStream(
                    new FileInputStream(t.getFilePath())
            );

            User stu = userMapper.selectById(t.getUserId());

            String entryName = "";

            if (!stu.getSchoolId().equals(""))
                entryName += stu.getSchoolId() + "-";
            entryName += stu.getName() + "-" + t.getFileName();

            zos.putNextEntry(new ZipEntry(entryName));

            while (true) {
                byte[] b = new byte[100];
                int len = bis.read(b);
                if (len  == -1)
                    break;
                zos.write(b, 0, len);
            }

            bis.close();
        }

        zos.close();

        return new File(zipName);
    }


}
