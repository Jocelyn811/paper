//注释 运行命令行，在终端上运行。
//g++ main.cpp -o test libglfw3dll.a libopengl32.a
//.\test


/*
#include <iostream>
#include <GL/gl.h>
#include "glfw3.h"
 */
/*#define GLEW_STATIC
const GLint WIDTH=800,HEIGHT=600;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(WIDTH,HEIGHT,"Learn OpenGL B18030409",nullptr,nullptr);

int screenWidth,screenHeight;
glfwGetFramebufferSize(window,&screenWidth,&screenHeight);
if(window==nullptr){
    str:: cout <<"Failed to creat GLFW window" << std::endl;
    glfwTerminate();
    return -1;

}
glfwMakeContextCurrent(window);
glewExperimental = GL_TRUE;
if(glewInit()!=GLEW_OK){
    std::cout<<"failed to initialize GLEW"<<std::endl;
    glfwTerminate();
    return -1;
}
while (!glfwWindowShouldClose(window)){
    glViewport(0,0,screenWidth,screenHeight);
    glfwPollEvents();
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);


}
glfwTerminate();
    return 0;
}
  */
 /*
 #version 330 core
 layout(location=0) in vec3 position;
 void main()
 {
     gl_Position=vec4(position,1.0f);//四维向量
 } 
*/
/*
#version 330 core
out vec4 color;
void main(){
    color =vec4(1.0f,0.0f,0.0f,1.0f);
}
*/
//注释
/*
#ifndef Shader_h
#define Shader_h
//或者#pragma once
#include <iostream>
 #include<string>
 #include<fsream>
 #include<sstream>
 #include<GL/glew.h>
class Shader
{
    GLuint vertex, fragment;
    public:
    GLuint Program;
    Shader(const GLchar *vertexPath,const GLchar *fragmentPath)
    {
        
      std::string vertexCode;
      std::string framentCode;
      std::ifstream vShaderFile;
      std::ifstream fShaderFile;
      vShaderFile
        .exceptions(std::ifstream::badbit);
      fShaderFile
        .exceptions(std::ifstream::badbit);
      try{
          vShaderFile.open(vertexPath);
          fShaderFile.open(fragmentPath);
          std::stringstream vShaderStream,fShaderStream;
          vShaderStream<<vShaderFile.rdbuf();
          fShaderStream<<fShaderFile.rdbuf();
          vShaderFile.close();
          fShaderFile.close();
          vertexCode=vShaderStream.str();
          fragmentCode=fShaderStram.str();
      }catch(std::ifstream::failure e){
          std::cout<<"ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ"<<std::endl;
      }
      const GLchar *vShaderCode=vertexCode.c_str();
      const GLchar *fShaderCode=fragmentCode.c_str();
      GLint success;
      GLchar infolog[512];
      vertex =glCreatShader(GL_VERTEX_SHADER);
      glShaderSource(vertex,1,&vShaderCode,NULL);
      glCompileShader(vertex);
      glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
      if(!success){
          glGetShaderInfolog(vertex,512,NULL,infolog);
          std::cout<<"ERROR::SHADER::CERTEX::COMPILATION_FAILED"<<infolog<<std::endl;
      }
      this->Program=glCreateProgram();
      glAttachShader(this->Program,vertex);
      glAttachShader(this->Program,fragment);
      glLinkProgram(this->Program);
      glGetProgram(this->Program,GL_LINK_STATUS,&success);
      if(!success){
          glGetProgramInfolog()
      }
    }

    ~Shader(){
        glDetachShader(this->Program,vertex);
        glDetachShader(this->Program,fragment);
        glDetachShader(vertex);
        glDetachShader(fragment);
        glDetachShader(this->Program);
        //后面应该还有

    }
    void Use(){
        //不知道是不是在这里
        glfwMakeContextCurrent(window);
        glewExperimental=GL_TRUE;
        if(glewInit()!=GLEW_OK){
            std::cout<<"Failed to initilize GLEW"<<std::endl;
            glfwTerminate();
            return -1;
        }
        Shader shader=Shader("res/shaders/core.vs","rex/shaders/core.fs");
        GLfloat vertices[]={
            -0.5f,-0.5f,0.0f,
            0.5f,-0.5f,0.0f,
            0.0f,0.5f,0.0f
        }
        GLuint VAO,VBO;
        glGenVertexArrays(1,&VAO);//VAO相当于说明书
        glGenBuffers(1,&VBO);//VBO表示数据
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferDate(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);//每读一次下一次
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid *)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_)

        while(!glfwWindowShouldClose(window)){
            glViewport(0,0,screenWidth,screenHeight);
            glfwPollEvent();
            glClearColor(0.2f,0.3f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
        }

    }
};*/
/*测试代码
    #include <iostream>
    #include <GL/gl.h>
    #include "glfw3.h"
 
    int main()
    {
        GLFWwindow* window;
 
        if (!glfwInit()) return -1;
 
        window = glfwCreateWindow(480, 320, "TestOpenGL", NULL ,NULL);
 
        if (!window)
        {
            glfwTerminate();
            return -1;
        }
 
        glfwMakeContextCurrent(window);
 
        while (!glfwWindowShouldClose(window))
        {
            glBegin(GL_TRIANGLES);
 
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.0, 1.0 ,0.0);
 
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-1.0, -1.0 ,0.0);
 
            glColor3f(1.0, 0.0, 1.0);
            glVertex3f(1.0, -1.0 ,0.0);
 
            glEnd();
 
            glfwSwapBuffers(window);
 
            glfwPollEvents();
        }
 
        glfwTerminate();
        
        return 0;
 
    }
    */