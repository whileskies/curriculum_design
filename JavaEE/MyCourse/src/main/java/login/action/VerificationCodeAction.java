package login.action;

import com.google.code.kaptcha.Producer;
import com.opensymphony.xwork2.ActionSupport;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.struts2.interceptor.ServletRequestAware;
import org.apache.struts2.interceptor.ServletResponseAware;
import org.springframework.beans.factory.annotation.Autowired;

import javax.imageio.ImageIO;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.awt.image.BufferedImage;
import java.io.IOException;


public class VerificationCodeAction extends ActionSupport implements ServletRequestAware, ServletResponseAware {
    private final static Logger LOG = LogManager.getLogger(VerificationCodeAction.class);
    private HttpServletRequest request;
    private HttpServletResponse response;

    private final Producer captchaProducer;

    @Autowired
    public VerificationCodeAction(Producer captchaProducer) {
        this.captchaProducer = captchaProducer;
    }

    public String execute() throws IOException {
        HttpSession session = request.getSession();
        response.setDateHeader("Expires", 0);
        response.setHeader("Cache-Control", "no-store, no-cache, must-revalidate");
        response.addHeader("Cache-Control", "post-check=0, pre-check=0");
        response.setHeader("Pragma", "no-cache");
        response.setContentType("image/jpeg");

        //生成验证码
        String capText = captchaProducer.createText();
        session.setAttribute("verificationCode", capText);
        LOG.debug("verificationCode: " + capText);


        //向客户端写出
        BufferedImage bi = captchaProducer.createImage(capText);
        ServletOutputStream out = response.getOutputStream();
        ImageIO.write(bi, "jpg", out);
        try {
            out.flush();
        } finally {
            out.close();
        }

        return NONE;
    }

    public void setServletRequest(HttpServletRequest request) {
        this.request = request;
    }

    public void setServletResponse(HttpServletResponse response) {
        this.response = response;
    }

}
