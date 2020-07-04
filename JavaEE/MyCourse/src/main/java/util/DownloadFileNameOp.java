package util;

import javax.servlet.http.HttpServletRequest;

public class DownloadFileNameOp {
    public static String downToUtf8String(String s, HttpServletRequest request) throws Exception {
        String agent = request.getHeader("User-Agent");
        agent = agent.toLowerCase();
        if (agent.contains("firefox")) {
            s = s.replaceAll("\\s+", "-");
            s = new String(s.getBytes(), "iso8859-1");
        } else {
            s = java.net.URLEncoder.encode(s, "UTF-8");
        }
        return s;
    }
}
