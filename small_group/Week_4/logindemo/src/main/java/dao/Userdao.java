package dao;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.sql.ResultSet;

public interface Userdao
{
    public static ResultSet search_user(String username, String password) throws Exception {
        return null;
    }

}
