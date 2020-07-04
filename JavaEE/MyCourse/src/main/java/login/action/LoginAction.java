package login.action;


import com.alibaba.fastjson.JSON;
import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import login.pojo.User;
import login.service.LoginService;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.struts2.interceptor.ServletResponseAware;
import org.springframework.beans.factory.annotation.Autowired;

import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;


public class LoginAction extends ActionSupport implements ServletResponseAware {

    private String email;
    private String password;
    private String verificationCode;

    private final LoginService loginService;

    private ServletResponse response;

    private static final Logger LOG = LogManager.getLogger(LoginAction.class);

    @Autowired
    public LoginAction(LoginService loginService) {
        this.loginService = loginService;
    }

    public String toLogin() {
        return SUCCESS;
    }

    public String login() throws IOException {
        LoginJson loginJson = new LoginJson();
        loginJson.code = LOGIN_CODE;
        if (email == null || email.trim().length() == 0 || password == null || password.trim().length() == 0
            || verificationCode == null || verificationCode.trim().length() == 0) {
            loginJson.msg = "存在空字段";
            loginJson.status = FAIL_EMPYT_PARAM;
        } else {
            Map<String, Object> session = ActionContext.getContext().getSession();
            String realVerificationCode = (String) session.get("verificationCode");

            if (verificationCode.equals(realVerificationCode)) {
                User user = new User();
                user.setEmail(email);
                user.setPassword(password);

                user = loginService.loginByEmailPassword(user);
                if (user == null) {
                    loginJson.msg = "账号或密码错误";
                    loginJson.status = FAIL_EMAIL_PASS;
                } else {
                    LOG.debug("user: " + user);
                    loginJson.msg = "登录成功";
                    loginJson.status = SUCC_STATUS;
                    loginJson.data.put("user_id", user.getId().toString());
                    loginJson.data.put("user_role", user.getRole());

                    ActionContext.getContext().getSession().put("user", user);
                }

            } else {
                loginJson.msg = "验证码错误";
                loginJson.status = FAIL_VERIFICATION;
            }
        }

        response.setCharacterEncoding("utf-8");
        response.setContentType("application/json;charset=utf-8");
        String ret = JSON.toJSONString(loginJson);
        LOG.debug("ret: " + loginJson);
        LOG.debug("json: " + ret);
        PrintWriter writer = response.getWriter();
        writer.print(ret);
        writer.flush();
        writer.close();

        return NONE;
    }

    public String logout() {
        ActionContext.getContext().getSession().remove("user");
        return SUCCESS;
    }

    public void setServletResponse(HttpServletResponse response) {
        this.response = response;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setVerificationCode(String verificationCode) {
        this.verificationCode = verificationCode;
    }

    /**
     * code:登录业务代码
     * msg:消息
     * status:0-成功 1-验证码错误 2-邮箱或密码错误 3-存在空字段
     * data:{'user_id' : '1', 'user_role' : 's'}
     */

    private static final int LOGIN_CODE = 1;
    private static final int SUCC_STATUS = 0;
    private static final int FAIL_VERIFICATION = 1;
    private static final int FAIL_EMAIL_PASS = 2;
    private static final int FAIL_EMPYT_PARAM = 3;

    class LoginJson {
        int code;
        String msg;
        int status;
        Map<String, String> data = new HashMap<String, String>();


        public int getCode() {
            return code;
        }

        public void setCode(int code) {
            this.code = code;
        }

        public String getMsg() {
            return msg;
        }

        public void setMsg(String msg) {
            this.msg = msg;
        }

        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }

        public Map<String, String> getData() {
            return data;
        }

        public void setData(Map<String, String> data) {
            this.data = data;
        }

        @Override
        public String toString() {
            return "LoginJson{" +
                    "code=" + code +
                    ", msg='" + msg + '\'' +
                    ", status=" + status +
                    ", data=" + data +
                    '}';
        }
    }

}

