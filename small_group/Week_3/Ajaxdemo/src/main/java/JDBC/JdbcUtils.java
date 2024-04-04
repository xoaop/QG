package JDBC;


import java.io.FileNotFoundException;
import java.io.IOException;
import java.sql.*;
import java.util.Properties;

public class JdbcUtils
{
    private static final String URL;
    private static final String USERNAME;
    private static final String PASSWORD;
    private static final String DRIVER;
    public static Connection connection;
    public static PreparedStatement preparedStatement;

    static
    {
        try {
            Properties properties=new Properties();
            properties.load(JdbcUtils.class.getClassLoader().getResourceAsStream("jdbc.properties"));
            URL=properties.getProperty("url");
            USERNAME=properties.getProperty("username");
            PASSWORD=properties.getProperty("password");
            DRIVER=properties.getProperty("driver");
            Class.forName(DRIVER);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        } catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }
    public static void getConnection() throws SQLException {

            if(connection==null)
                connection=DriverManager.getConnection(URL, USERNAME, PASSWORD);

    }

    public static void close() throws SQLException
    {

        if (preparedStatement != null)
        {
            preparedStatement.close();
        }
        if (connection != null)
        {
            connection.close();
        }

    }

    public static ResultSet query(String table,String condition) throws SQLException
    {

        String sql=String.format("select * from %s where %s",table,condition);
        preparedStatement=connection.prepareStatement(sql);
        return preparedStatement.executeQuery();

    }

    public static int update(String table, String update, String condition) throws SQLException
    {

        String sql="UPDATE " + table + " SET " + update + " where "+condition;
        preparedStatement=connection.prepareStatement(sql);
        return preparedStatement.executeUpdate();

    }

    public static int insert(String table,String columns,String values,String condition) throws SQLException
    {

        String sql="insert into " + table + "(" + columns + ") values (" + values + ")";
        preparedStatement=connection.prepareStatement(sql);
        return preparedStatement.executeUpdate(sql);

    }

    public static int delete(String table,String condition) throws SQLException

    {

            String sql=String.format("delete from %s where %s",table,condition);
            preparedStatement=connection.prepareStatement(sql);
            return preparedStatement.executeUpdate();

    }

}
