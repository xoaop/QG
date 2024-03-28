import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

//通过地址栏传递参数进行get请求
@WebServlet("/req1")
public class reqdemo extends HttpServlet
{
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        System.out.println("get...");
        String username = req.getParameter("username");
        String password=req.getParameter("password");

        //若用户名或密码有空，设置状态码404
        if(username==null||password==null)
        {
            System.out.println("Parameter is null");
            resp.setStatus(404);
        }
        //用户名与密码若相等，设置状态码200
        else if(username.equals(password))
        {
            System.out.println("username equals to password");
            resp.setStatus(200);
        }
        //用户名与密码若不相等，设置状态码500
        else
        {
            System.out.println("username doesn't equal to password");
            resp.setStatus(500);
        }


    }

    //通过req.html传参进行post请求
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        System.out.println("post...");

        String username = req.getParameter("username");
        String password=req.getParameter("password");

        //若用户名为zhangsan，密码为123，状态码为200
        if(username.equals("zhangsan")&&password.equals("123"))
        {
            System.out.println("correct");
            resp.setStatus(200);
        }
        //若用户名不为zhangsan，密码不为123，重定向调用doget
        else
        {
            resp.sendRedirect("req1");
        }
    }
}
