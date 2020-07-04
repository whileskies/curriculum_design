package login.service.impl;

import login.mapper.UserMapper;
import login.pojo.User;
import login.service.LoginService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class LoginServiceImpl implements LoginService {
    private final UserMapper userMapper;

    @Autowired
    public LoginServiceImpl(UserMapper userMapper) {
        this.userMapper = userMapper;
    }

    public User loginByEmailPassword(User user) {
        return userMapper.selectByEmailPassword(user);
    }

    public int registerUser(User user) {
        User u = userMapper.selectByEmail(user.getEmail());
        if (u == null) {
            int ret = userMapper.insertUser(user);
            if (ret > 0) {
                return REGISTER_SUCC;
            } else {
                return REGISTER_ERROR;
            }
        } else {
            return REGISTER_EMAIL_EXISTS;
        }
    }
}
