package controller;

import dao.impl.Userdao;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.lang.reflect.Method;

@WebServlet("/loginServlet/*")
public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) {

        System.out.println("get...");

        Class clazz;
        try {
            //获取LoginService类
            clazz = Class.forName("service.LoginService");
            //获取请求路径
            String name = request.getRequestURI();
            //获取方法名
            String methodName = name.substring(name.lastIndexOf("/") + 1);
            //获取指定方法
            Method method = clazz.getMethod(methodName, HttpServletRequest.class, HttpServletResponse.class);
            //调用方法
            Object o = clazz.newInstance();
            method.invoke(o, request, response);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {

        System.out.println("post...");

        doGet(request, response);
    }
}
