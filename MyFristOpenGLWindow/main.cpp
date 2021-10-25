#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderManager.h"
#include "def.h"
#include "PanelRender.h"

using namespace _Shader;
GLFWwindow* createWindow();
bool initGLAD();
void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
"	vertexColor = vec4(aColor, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"in vec4 vertexColor;\n"
"uniform vec4 outColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vertexColor;\n"
"}\0";
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = createWindow();
	if (window == NULL)
		return -1;
	if (!initGLAD())
		return -1;
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//{
	//	±‡“Î¡¥Ω”◊≈…´∆˜

	//	unsigned int vertexShader;
	//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//	glCompileShader(vertexShader);
	//	int success;
	//	char infoLog[512];
	//	glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//	if (!success)
	//	{
	//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//	}

	//	unsigned int fragShader;
	//	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	//	glCompileShader(fragShader);
	//	glad_glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	//	if (!success)
	//	{
	//		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
	//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//	}

	//	unsigned int shaderProgram;
	//	shaderProgram = glCreateProgram();
	//	glAttachShader(shaderProgram, vertexShader);
	//	glAttachShader(shaderProgram, fragShader);
	//	glLinkProgram(shaderProgram);
	//	glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//	if (!success)
	//	{
	//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	//	}
	//	glDeleteShader(vertexShader);
	//	glDeleteShader(fragShader);

	//	/*float vertices[] =
	//	{
	//		-0.5f,-0.5f,0.0f,
	//		0.5f,-0.5f,0.0f	,
	//		0.0f,0.5f,0.0f
	//	};*/

	//	float vertices[] = {
	//	-0.8f, -0.4f,0.0f,1.0f,0.0f,0.0f,
	//	-0.2f, -0.4f,0.0f,0.0f,1.0f,0.0f,
	//	-0.2f, 0.4f, 0.0f,1.0f,0.0f,0.0f,
	//	-0.8f, 0.4f, 0.0f,0.0f,0.0f,1.0f,
	//	0.2f, -0.4f, 0.0f,1.0f,0.0f,0.0f,
	//	0.8f, -0.4f, 0.0f,0.0f,1.0f,0.0f,
	//	0.8f, 0.4f, 0.0f,1.0f,0.0f,0.0f,
	//	0.2f, 0.4f, 0.0f,0.0f,0.0f,1.0f,
	//	};

	//	unsigned int indices[] = {
	//		0, 1, 3,
	//		1, 2, 3,
	//		4, 5, 7,
	//		5, 6, 7,
	//	};

	//	unsigned int VAO;
	//	unsigned int VBO;
	//	unsigned int EBO;
	//	glGenBuffers(1, &EBO);
	//	glGenBuffers(1, &VBO);
	//	glGenVertexArrays(1, &VAO);
	//	glBindVertexArray(VAO);
	//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//	glEnableVertexAttribArray(0);
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//	glEnableVertexAttribArray(1);

	//	int nrAttributes;
	//	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	//	while (!glfwWindowShouldClose(window))
	//	{
	//		 ‰»Î
	//		processInput(window);
	//		‰÷»æ÷∏¡Ó
	//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//		glClear(GL_COLOR_BUFFER_BIT);

	//		glUseProgram(shaderProgram);

	//		float timeValue = glfwGetTime();
	//		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	//		int vertexColorLoaction = glGetUniformLocation(shaderProgram, "outColor");
	//		std::cout << greenValue << " " << vertexColorLoaction << std::endl;
	//		glUniform4f(vertexColorLoaction, 0.0f, greenValue, 0.0f, 1.0f);
	//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(GL_UNSIGNED_INT) * 6));

	//		glDrawArrays(GL_TRIANGLES, 0, 3);

	//		glfwPollEvents();
	//		glfwSwapBuffers(window);
	//	}
	//	glDeleteVertexArrays(1, &VAO);
	//	glDeleteBuffers(1, &VBO);
	//	glDeleteProgram(shaderProgram);
	//}
	
	{
		float vertices1[] = {
			-0.8f, -0.4f,0.0f,1.0f,0.0f,0.0f,
			-0.2f, -0.4f,0.0f,0.0f,1.0f,0.0f,
			-0.2f, 0.4f, 0.0f,1.0f,0.0f,0.0f,
			-0.8f, 0.4f, 0.0f,0.0f,0.0f,1.0f,
		};
		unsigned int indices1[] = {
			0, 1, 3,
			1, 2, 3,
		};

		float vertices2[] = {
			0.2f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.8f, -0.4f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.8f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
			//0.2f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f,
		};

		unsigned int indices2[] = {
			0, 1, 2,
		};
		
		ShaderManager::Instance()->initialize();
		ShaderManager::Instance()->addShader(VERTEXSHADER_TYPE, "shader/panel.vs");
		ShaderManager::Instance()->addShader(FRAGMENTSHADER_TYPE, "shader/helloTriangle1.fs");
		ShaderManager::Instance()->addShader(FRAGMENTSHADER_TYPE, "shader/helloTriangle2.fs");
		PanelRender render1;
		render1.initialize();
		render1.attachShader(VERTEXSHADER_TYPE, "shader/panel.vs");
		render1.attachShader(FRAGMENTSHADER_TYPE, "shader/helloTriangle1.fs");
		render1.initialized();

		RenderData* renderData = new RenderData();
		renderData->vertices = (float*)malloc(sizeof(vertices1));
		memcpy(renderData->vertices, vertices1, sizeof(vertices1));
		renderData->count = 4;
		renderData->element = (unsigned int*)malloc(sizeof(indices1));
		memcpy(renderData->element, indices1, sizeof(indices1));
		renderData->element_count = 6;
		renderData->useColor = true;
		renderData->id = 1;
		render1.loadData(renderData);

		PanelRender render2;
		render2.initialize();
		render2.attachShader(VERTEXSHADER_TYPE, "shader/panel.vs");
		render2.attachShader(FRAGMENTSHADER_TYPE, "shader/helloTriangle2.fs");
		render2.initialized();

		RenderData* renderData2 = new RenderData();
		renderData2->vertices = (float*)malloc(sizeof(vertices2));
		memcpy(renderData2->vertices, vertices2, sizeof(vertices2));
		renderData2->count = 4;
		renderData2->element = (unsigned int*)malloc(sizeof(indices2));
		memcpy(renderData2->element, indices2, sizeof(indices2));
		renderData2->element_count = 6;
		renderData2->useColor = true;
		renderData2->id = 1;
		render2.loadData(renderData2);

		/*float vertices2[] = {
			-0.5f, 0.2f,0.0f,1.0f,0.0f,0.0f,
			-0.4f, -0.6f,0.0f,0.0f,1.0f,0.0f,
			-0.3f, 0.4f, 0.0f,1.0f,0.0f,0.0f,
		};
		unsigned int indices2[] = {
			0, 1, 2,
		};
		RenderData* renderData2 = new RenderData();
		renderData2->vertices = (float*)malloc(sizeof(vertices2));
		memcpy(renderData2->vertices, vertices2, sizeof(vertices2));
		renderData2->count = 3;
		renderData2->element = (unsigned int*)malloc(sizeof(indices2));
		memcpy(renderData2->element, indices2, sizeof(indices2));
		renderData2->element_count = 3;
		renderData2->useColor = true;
		renderData2->id = 2;*/
		/*render.loadData(renderData2);*/

		//float outColor[] = { 0.2f,0.5f,0.7f,1.0f };
		//render.setUniform("outColor", outColor, 4, ShaderParamType::SPT_VEC4);
		//render.setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (!glfwWindowShouldClose(window))
		{
			// ‰»Î
			processInput(window);
			//‰÷»æ÷∏¡Ó
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			render1.render();
			render2.render();

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}
	glfwTerminate();
	return 0;
}


GLFWwindow* createWindow()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnCreateWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	return window;
}
bool initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
	return true;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}