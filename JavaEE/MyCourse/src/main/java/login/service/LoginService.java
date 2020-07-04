package login.service;

import login.pojo.User;

public interface LoginService {

    /**
     * 根据账号和密码进行登录
     * @param user 用户对象
     * @return user详细信息，null表示邮箱或密码错误
     */
    User loginByEmailPassword(User user);

    /**
     * 注册用户
     * @param user 用户对象
     * @return 注册结果状态
     */
    int REGISTER_EMAIL_EXISTS = 1;
    int REGISTER_ERROR = 2;
    int REGISTER_SUCC = 3;
    int registerUser(User user);
}
