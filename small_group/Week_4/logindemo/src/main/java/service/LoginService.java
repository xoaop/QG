package service;

import dao.impl.Userdao;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import utils.JdbcUtils;

import java.sql.ResultSet;

public class LoginService {

    public void login(HttpServletRequest request, HttpServletResponse response) throws Exception
    {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        ResultSet resultSet = Userdao.search_user(username, password);

        if (resultSet.next())
        {
            response.getWriter().write("Login successful");
        }
        else
        {
            response.getWriter().write("Login failed");
        }

        JdbcUtils.close();

        return;

    }

    public void register(HttpServletRequest request, HttpServletResponse response) throws Exception {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        ResultSet resultset = Userdao.search_user(username, password);

        if (resultset.next())
        {
            response.getWriter().write("User already exists");
        }
        else
        {
            JdbcUtils.insert("users", "username, password", username + ", " + password);
            response.getWriter().write("User registered successfully");
        }

        return;

    }

}
