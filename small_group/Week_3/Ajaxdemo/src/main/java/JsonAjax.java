import com.alibaba.fastjson2.JSON;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;


//将User对象转换为json字符串并响应
@WebServlet("/jsonAjax")
public class JsonAjax extends HttpServlet
{
    User user;
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //创建User对象
        user=new User();
        user.setId(1);
        user.setUsername("zhangsan");
        user.setPassword("123456");

        //将user对象转换为json字符串
        String jsonString=JSON.toJSONString(user);

        //设置响应内容类型
        resp.setContentType("application/json;charset=utf-8");
        //将json字符串写入响应
        resp.getWriter().write(jsonString);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        doGet(req, resp);
    }
}
