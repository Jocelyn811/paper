#include  <iostream>
#include  "Shader.h"
#include  "Camera.h"
//GLEW
#define GLEW_STATIC
#include <glew.h>
//GLFW
#include <glfw3.h>
using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
#include"SOIL2.h"
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void DoMovement();
bool keys[1024];		//��¼����
GLfloat lastX=0.0f, lastY=0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
bool firstMouse = true;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//for mac
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
	GLfloat lastX = 0.0f;
	GLfloat lastY = 0.0f;

	// retina display
	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, ScrollCallback);
	

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	//��ƬԪ����
	glEnable(GL_BLEND);//͸����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//������Ȳ��ԣ���Ȳ��Է���, z����С���ܸ���֮ǰ��
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Shader shader1 = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	Shader shader2 = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	Shader shader3 = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	Shader shader4 = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	Shader shader5 = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	Shader shader6 = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	Shader shader7 = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	Shader shader8 = Shader("res/shaders/core.vs", "res/shaders/core.fs");

	//����������cube,  x��yƽ���ڵ���ƽ���ڣ�z��ֱָ����
	//������
	GLfloat vertices[] = {
		//position			  //color
		//back
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		//��
		0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,//�м��Ǹ�
		//һ�����еľŸ�С��//
		/*
		0.5f, -0.5f, -1.5f,  1.0f, 0.0f, 0.0f,		
		1.5f, -0.5f, -1.5f,   1.0f, 0.0f, 0.0f,
		1.5f, 0.5f, -1.5f,    1.0f, 0.0f, 0.0f,
		1.5f, 0.5f, -1.5f,    1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -1.5f,   1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -1.5f,  1.0f, 0.0f, 0.0f,//2,3
		//
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		
		-1.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		-1.5f, 0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		-1.5f, 0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		//
		-0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-1.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		-1.5f, 0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		-1.5f, 0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		*/
		////

		//front
		-0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,		//��
		0.5f, -0.5f, 0.5f,	  0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,	  0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,	  0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,	  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,

		//left
		-0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     //��
		-0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,

		//right
		0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 1.0f,    //����
		0.5f, 0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 1.0f,

		//bottom 
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,    //�ۺ�
		0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,

		//up
		-0.5f, 0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   //��ɫ
		0.5f, 0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,   1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,   1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,   1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,   1.0f, 1.0f, 0.0f,


	};

	// VBO ���㻺����� �洢�������� ��ɫ����
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);     // ��VBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//ͨ��ѡ��core.vs�е�location��  ȡ���������� ������������ȡ��һ������  ��ʼλ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	/*
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	*/
	//���
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint VAO1, VBO1;
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glBindVertexArray(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);     
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//ͨ��ѡ��core.vs�е�location��  ȡ���������� ������������ȡ��һ������  ��ʼλ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//���
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();
		DoMovement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);			//�������ɫ����,����ʼ����Ȼ���
		// glUseProgram(shaderProgram);
		shader1.Use();

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 
			static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight), 0.1f, 100.0f);

		//1����ʼ��һ����λ����
		glm::mat4 transform = glm::mat4(1.0f);

		transform = glm::rotate(transform, glm::radians(500.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));//��ת
		transform = glm::scale(transform, glm::vec3(0.49f, 0.49f, 0.49f));//����
		transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, -0.5f));//ƽ��

		
		GLuint transLoc = glGetUniformLocation(shader1.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		GLuint viewLoc = glGetUniformLocation(shader1.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLuint proLoc = glGetUniformLocation(shader1.Program, "projection");
		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//n����
		glBindVertexArray(0);
		


		shader2.Use();
		transform = glm::mat4(1.0f);
		
		transform = glm::rotate(transform, glm::radians(500.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));//��ת
		transform = glm::scale(transform, glm::vec3(0.49f, 0.49f, 0.49f));//����
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, -0.5f));//ƽ��

		transLoc = glGetUniformLocation(shader2.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		viewLoc = glGetUniformLocation(shader2.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		proLoc = glGetUniformLocation(shader2.Program, "projection");
		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//n����
		glBindVertexArray(0);

		shader3.Use();
		transform = glm::mat4(1.0f);


		transform = glm::rotate(transform, glm::radians(500.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));//��ת
		transform = glm::scale(transform, glm::vec3(0.49f, 0.49f, 0.49f));//����
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.5f));//ƽ��


		transLoc = glGetUniformLocation(shader3.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		viewLoc = glGetUniformLocation(shader3.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		proLoc = glGetUniformLocation(shader3.Program, "projection");
		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//n����
		glBindVertexArray(0);

		shader4.Use();
		transform = glm::mat4(1.0f);



		transform = glm::rotate(transform, glm::radians(500.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));//��ת
		transform = glm::scale(transform, glm::vec3(0.49f, 0.49f, 0.49f));//����
		transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.5f));//ƽ��

		transLoc = glGetUniformLocation(shader4.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		viewLoc = glGetUniformLocation(shader4.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		proLoc = glGetUniformLocation(shader4.Program, "projection");
		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//n����
		glBindVertexArray(0);


		shader5.Use();
		transform = glm::mat4(1.0f);



		//transform = glm::rotate(transform, glm::radians(500.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));//��ת
		transform = glm::scale(transform, glm::vec3(0.49f, 0.49f, 0.49f));//����
		transform = glm::translate(transform, glm::vec3(-0.5f, -0.5f, -0.5f));//ƽ��

		transLoc = glGetUniformLocation(shader5.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		viewLoc = glGetUniformLocation(shader5.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		proLoc = glGetUniformLocation(shader5.Program, "projection");
		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//n����
		glBindVertexArray(0);


		shader6.Use();
		transform = glm::mat4(1.0f);



		//transform = glm::rotate(transform, glm::radians(500.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));//��ת
		transform = glm::scale(transform, glm::vec3(0.49f, 0.49f, 0.49f));//����
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, -0.5f));//ƽ��

		transLoc = glGetUniformLocation(shader6.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		viewLoc = glGetUniformLocation(shader6.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		proLoc = glGetUniformLocation(shader6.Program, "projection");
		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//n����
		glBindVertexArray(0);


		shader7.Use();
		transform = glm::mat4(1.0f);



		//transform = glm::rotate(transform, glm::radians(500.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));//��ת
		transform = glm::scale(transform, glm::vec3(0.49f, 0.49f, 0.49f));//����
		transform = glm::translate(transform, glm::vec3(-0.5f, -0.5f, 0.5f));//ƽ��

		transLoc = glGetUniformLocation(shader7.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		viewLoc = glGetUniformLocation(shader7.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		proLoc = glGetUniformLocation(shader7.Program, "projection");
		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//n����
		glBindVertexArray(0);

		shader8.Use();
		transform = glm::mat4(1.0f);



		//transform = glm::rotate(transform, glm::radians(500.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));//��ת
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));//����
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.5f));//ƽ��

		transLoc = glGetUniformLocation(shader8.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		viewLoc = glGetUniformLocation(shader8.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		proLoc = glGetUniformLocation(shader8.Program, "projection");
		glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//n����
		glBindVertexArray(0);


		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO); 
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(xOffset, yOffset);
}

void DoMovement() {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		camera.ProcessKeyboard(FOWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.ProcessScroll(yOffset);
}