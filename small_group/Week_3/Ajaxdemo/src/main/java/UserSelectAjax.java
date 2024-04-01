import JDBC.JdbcUtils;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;


import java.io.IOException;


/*
*   通过Ajax验证用户名是否存在
*/

@WebServlet("/userSelectAjax")
public class UserSelectAjax extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException
    {
        String username=req.getParameter("username");

        //如果用户名为zhangsan则返回true，否则返回false
        //这里应该是从数据库中查询，这里为了简单直接写死
        //只有zhangsan这个用户存在
        if(username.equals("zhangsan"))
        {
            resp.getWriter().write("true");
            return;
        }
        else
        {
            resp.getWriter().write("false");
        }

    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException
    {
        doGet(req, resp);
    }
}
