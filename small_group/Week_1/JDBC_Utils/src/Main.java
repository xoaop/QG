package src;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Main {


    public static void main(String[] args) throws SQLException {

        JdbcUtils.getConnection();

        ResultSet r;
        r= JdbcUtils.query("users","1");

        while(r.next())
        {
            int id =r.getInt(1);
            String name= r.getString(2);
            int age= r.getInt(3);
            String gender=r.getString(4);
            String bir=r.getString(5);

            System.out.println(id+" "+name+" "+age+" "+gender+" "+bir);
        }

        JdbcUtils.update("users","age=30","id=1");
        JdbcUtils.insert("users","id,name","3,\"xoa\"","1");
        JdbcUtils.delete("users","id=3");





    }
}
