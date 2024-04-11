package utils;


import java.io.*;
import java.sql.*;
import java.util.Properties;

public class JdbcUtils
{
    private static final Properties properties=new Properties();
    private static final String URL="jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USERNAME="root";
    private static final String PASSWORD="yourpassword";
    private static final String DRIVER="com.mysql.jdbc.Driver";
    public static Connection connection;
    public static PreparedStatement preparedStatement;

    static
    {
        try {
//            InputStream inputStream=JdbcUtils.class.getClassLoader().getResourceAsStream("jdbc.properties");
//            properties.load(inputStream);
//            URL=properties.getProperty("url");
//            USERNAME=properties.getProperty("username");
//            PASSWORD=properties.getProperty("password");
//            DRIVER=properties.getProperty("driver");
            Class.forName(DRIVER);
        } catch (Exception e)
        {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }
    public static Connection getConnection() {
        try {
            if(connection==null)
                connection=DriverManager.getConnection(URL, USERNAME, PASSWORD);

            return connection;
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }

    }

    public static void close()
    {
        try
        {
            if (preparedStatement != null)
            {
                preparedStatement.close();
            }
            if (connection != null)
            {
                connection.close();
            }
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    public static ResultSet query(String table,String condition)
    {
        try
        {
            String sql=String.format("select * from %s where %s",table,condition);
            preparedStatement=connection.prepareStatement(sql);
            return preparedStatement.executeQuery();
        }catch (SQLException e)
        {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    public static int update(String table, String update, String condition)
    {
        try
        {
            String sql="UPDATE " + table + " SET " + update + " where "+condition;
            preparedStatement=connection.prepareStatement(sql);
            return preparedStatement.executeUpdate();
        } catch (SQLException e)
        {
            e.printStackTrace();
            throw new RuntimeException(e);
        }


    }

    public static int insert(String table,String columns,String values)
    {
        try
        {
            String sql="insert into " + table + "(" + columns + ") values (" + values + ")";
            preparedStatement=connection.prepareStatement(sql);
            return preparedStatement.executeUpdate(sql);
        } catch (SQLException e)
        {
            e.printStackTrace();
            throw new RuntimeException(e);
        }

    }

    public static int delete(String table,String condition)
    {
        try
        {
            String sql=String.format("delete from %s where %s",table,condition);
            preparedStatement=connection.prepareStatement(sql);
            return preparedStatement.executeUpdate();
        } catch (SQLException e)
        {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

}
