package teacher.service;

import login.pojo.User;

import java.util.List;

public interface TeaCourseStudentService {
    List<User> findAllByCourseId(Integer courseId);
}
