package teacher.pojo;

import file.pojo.TaskFile;
import login.pojo.User;

public class StuTaskFiles {
    private User user;
    private TaskFile taskFile;

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public TaskFile getTaskFile() {
        return taskFile;
    }

    public void setTaskFile(TaskFile taskFile) {
        this.taskFile = taskFile;
    }

    @Override
    public String toString() {
        return "StuTaskFiles{" +
                "user=" + user +
                ", taskFile=" + taskFile +
                '}';
    }
}
