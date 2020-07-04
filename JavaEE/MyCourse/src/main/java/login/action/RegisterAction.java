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

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;


public class RegisterAction extends ActionSupport implements ServletResponseAware {

    private static final Logger LOG = LogManager.getLogger(RegisterJson.class);

    private String email;
    private String password;
    private String role;
    private String name;
    private String schoolId;
    private String school;
    private String dept;
    private String major;
    private String schoolClass;

    private final LoginService loginService;

    private HttpServletResponse response;

    @Autowired
    public RegisterAction(LoginService loginService) {
        this.loginService = loginService;
    }

    public String toRegister() {
        return SUCCESS;
    }

    public String register() throws IOException {
        RegisterJson registerJson = new RegisterJson();
        registerJson.code = REGISTER_CODE;
        if (email == null || email.trim().length() == 0 || password == null || password.trim().length() == 0 ||
                (!role.equals("s") && !role.equals("t")) || name == null || name.trim().length() == 0 ||
            !testEmail(email) || !testPassword(password)) {
            registerJson.msg = "存在非法字段";
            registerJson.status = INVALID_FILD_STATUS;
        } else {
            User user = new User();
            user.setEmail(email.trim());
            user.setPassword(password.trim());
            user.setRole(role);
            user.setName(name.trim());
            if (schoolId == null)
                user.setSchoolId("");
            else
                user.setSchoolId(schoolId.trim());
            if (school == null)
                user.setSchool("");
            else
                user.setSchool(school.trim());
            if (dept == null)
                user.setDept("");
            else
                user.setDept(dept.trim());
            if (major == null)
                user.setMajor("");
            else
                user.setMajor(major.trim());
            if (schoolClass == null)
                user.setSchoolClass("");
            else
                user.setSchoolClass(schoolClass);

            int ret = loginService.registerUser(user);

            if (ret == LoginService.REGISTER_SUCC) {
                registerJson.msg = "注册成功";
                registerJson.status = SUCC_STATUS;
                registerJson.data.put("user_id", user.getId().toString());
                registerJson.data.put("user_role", user.getRole());
                ActionContext.getContext().getSession().put("user", user);
            } else if (ret == LoginService.REGISTER_EMAIL_EXISTS) {
                registerJson.msg = "邮箱已存在";
                registerJson.status = EMAIL_EXITS_STATUS;
            } else if (ret == LoginService.REGISTER_ERROR) {
                registerJson.msg = "注册失败";
                registerJson.status = ERROR_STATUS;
            }
        }

        response.setCharacterEncoding("utf-8");
        response.setContentType("application/json;charset=utf-8");
        String ret = JSON.toJSONString(registerJson);
        LOG.debug("json: " + ret);
        PrintWriter writer = response.getWriter();
        writer.print(ret);
        writer.flush();
        writer.close();

        return NONE;
    }

    private boolean testEmail(String email) {
        String re = "^[A-Za-z\\d]+([-_.][A-Za-z\\d]+)*@([A-Za-z\\d]+[-.])+[A-Za-z\\d]{2,4}$";
        return Pattern.matches(re, email);
    }

    private boolean testPassword(String password) {
        String re = "^[0-9a-zA-Z_]{6,18}$";
        return Pattern.matches(re, password);
    }


    private static final int REGISTER_CODE = 2;
    private static final int SUCC_STATUS = 0;
    private static final int INVALID_FILD_STATUS = 1;
    private static final int EMAIL_EXITS_STATUS = 2;
    private static final int ERROR_STATUS = 3;


    class RegisterJson {
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
    }


    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSchoolId() {
        return schoolId;
    }

    public void setSchoolId(String schoolId) {
        this.schoolId = schoolId;
    }

    public String getSchool() {
        return school;
    }

    public void setSchool(String school) {
        this.school = school;
    }

    public String getDept() {
        return dept;
    }

    public void setDept(String dept) {
        this.dept = dept;
    }

    public String getMajor() {
        return major;
    }

    public void setMajor(String major) {
        this.major = major;
    }

    public String getSchoolClass() {
        return schoolClass;
    }

    public void setSchoolClass(String schoolClass) {
        this.schoolClass = schoolClass;
    }

    public void setServletResponse(HttpServletResponse response) {
        this.response = response;
    }
}
