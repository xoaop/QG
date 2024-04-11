package dao.impl;

import utils.JdbcUtils;

import java.sql.ResultSet;

public class Userdao implements dao.Userdao
{
    public static ResultSet search_user(String username , String password) throws Exception
    {
        JdbcUtils.getConnection();

        ///表名为users
        ResultSet resultSet = JdbcUtils.query("users", "username = " + username + " and password = " + password);

        return resultSet;
    }



}
