package login.mapper;

import login.pojo.User;

public interface UserMapper {
    User selectByEmailPassword(User user);

    User selectById(Integer id);

    User selectByEmail(String email);

    int insertUser(User user);
}
