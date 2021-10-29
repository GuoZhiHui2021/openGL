#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include "render/ShaderManager.h"
#include "render/def.h"
#include "render/PanelRender.h"

using namespace _Shader;
GLFWwindow* createWindow();
TextureData createTextureData(const char* src, uint16_t textureUnit, uint16_t wrap_s = GL_REPEAT, uint16_t wrap_t = GL_REPEAT, uint16_t min_filter = GL_NEAREST, uint16_t max_filter = GL_NEAREST);
RenderData* createRenderData(int id, float* vertices, int count, unsigned int *indices, int element_count, TextureData* textureDatas, int texture_count);
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

float alpha = 0.5f;
bool alpha_dirty = true;

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
	//	//±‡“Î¡¥Ω”◊≈…´∆˜

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
	//		// ‰»Î
	//		processInput(window);
	//		//‰÷»æ÷∏¡Ó
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
		/*float vertices[] = {
			-0.8f, -0.4f,0.0f,  1.0f,0.0f,0.0f,    0.5f, 0.5f,
			-0.2f, -0.4f,0.0f,  0.0f,1.0f,0.0f,    1.5f, 0.5f,
			-0.2f, 0.4f, 0.0f,  1.0f,0.0f,0.0f,    1.5f, 1.5f,
			-0.8f, 0.4f, 0.0f,  0.0f,0.0f,1.0f,    0.5f, 1.5f,
			0.2f, -0.4f, 0.0f,  1.0f,0.0f,0.0f,    0.0f, 0.0f,
			0.8f, -0.4f, 0.0f,  0.0f,1.0f,0.0f,    1.0f, 0.0f,
			0.8f, 0.4f, 0.0f,   1.0f,0.0f,0.0f,     1.0f, 1.0f,
			0.2f, 0.4f, 0.0f,   0.0f,0.0f,1.0f,     0.0f, 1.0f,
		};*/
		
		float vertices0[] = {
			-1.0f, 1.0f,0.0f,  1.0f,0.0f,0.0f,    0.0f, 2.0f,
			-1.0f, 0.0f,0.0f,  0.0f,1.0f,0.0f,    0.0f, 1.0f,
			0.0f, 0.0f, 0.0f,  1.0f,0.0f,0.0f,    1.0f, 1.0f,
			0.0f, 1.0f, 0.0f,  0.0f,0.0f,1.0f,    1.0f, 2.0f,
		};
		float vertices1[] = {
			0.0f, 1.0f,0.0f,  1.0f,0.0f,0.0f,    1.0f, 2.0f,
			0.0f, 0.0f,0.0f,  0.0f,1.0f,0.0f,    1.0f, 1.0f,
			1.0f, 0.0f, 0.0f,  1.0f,0.0f,0.0f,    2.0f, 1.0f,
			1.0f, 1.0f, 0.0f,  0.0f,0.0f,1.0f,    2.0f, 2.0f,
		};
		float vertices2[] = {
			-1.0f, 0.0f,0.0f,  1.0f,0.0f,0.0f,    0.0f, 1.0f,
			-1.0f, -1.0f,0.0f,  0.0f,1.0f,0.0f,    0.0f, 0.0f,
			0.0f, -1.0f, 0.0f,  1.0f,0.0f,0.0f,    1.0f, 0.0f,
			0.0f, 0.0f, 0.0f,  0.0f,0.0f,1.0f,    1.0f, 1.0f,
		};
		float vertices3[] = {
			0.0f, 0.0f,0.0f,  1.0f,0.0f,0.0f,    1.0f, 1.0f,
			0.0f, -1.0f,0.0f,  0.0f,1.0f,0.0f,    1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,  1.0f,0.0f,0.0f,    2.0f, 0.0f,
			1.0f, 0.0f, 0.0f,  0.0f,0.0f,1.0f,    2.0f, 1.0f,
		};
		/*float vertices[] = {
			-0.8f, -0.4f,0.0f,  1.0f,0.0f,0.0f,
			-0.2f, -0.4f,0.0f,  0.0f,1.0f,0.0f,
			-0.2f, 0.4f, 0.0f,  1.0f,0.0f,0.0f, 
			-0.8f, 0.4f, 0.0f,  0.0f,0.0f,1.0f,  
			0.2f, -0.4f, 0.0f,  1.0f,0.0f,0.0f,   
			0.8f, -0.4f, 0.0f,  0.0f,1.0f,0.0f,  
			0.8f, 0.4f, 0.0f,   1.0f,0.0f,0.0f,  
			0.2f, 0.4f, 0.0f,   0.0f,0.0f,1.0f,  
		};*/
		/*unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3,
			4, 5, 7,
			5, 6, 7,
		};*/
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
		};
		
		ShaderManager::Instance()->initialize();
		ShaderManager::Instance()->addShader(VERTEXSHADER_TYPE, "shader/texture.vs");
		ShaderManager::Instance()->addShader(FRAGMENTSHADER_TYPE, "shader/texture.fs");
		ShaderManager::Instance()->addShader(FRAGMENTSHADER_TYPE, "shader/texture1.fs");
		PanelRender render1;
		render1.initialize();
		render1.attachShader(VERTEXSHADER_TYPE, "shader/texture.vs");
		render1.attachShader(FRAGMENTSHADER_TYPE, "shader/texture.fs");
		render1.initialized();

		PanelRender render2;
		render2.initialize();
		render2.attachShader(VERTEXSHADER_TYPE, "shader/texture.vs");
		render2.attachShader(FRAGMENTSHADER_TYPE, "shader/texture1.fs");
		render2.initialized();


		TextureData boxTextureData0 = createTextureData("res/texture/container.jpg", GL_TEXTURE0);
		TextureData boxTextureData1 = createTextureData("res/texture/awesomeface.png", GL_TEXTURE1);
		TextureData textureDatas[2];
		memcpy(textureDatas, &boxTextureData0, sizeof(TextureData));
		memcpy(&textureDatas[1], &boxTextureData1, sizeof(TextureData));
		TextureData textureDatas0[2];
		TextureData textureDatas1[2];
		TextureData textureDatas2[2];
		TextureData textureDatas3[2];

		memcpy(textureDatas0, &textureDatas, 2 * sizeof(TextureData));
		memcpy(textureDatas1, &textureDatas, 2 * sizeof(TextureData));
		memcpy(textureDatas2, &textureDatas, 2 * sizeof(TextureData));
		memcpy(textureDatas3, &textureDatas, 2 * sizeof(TextureData));

		textureDatas0[0].options[0] = GL_CLAMP_TO_EDGE;
		textureDatas0[0].options[1] = GL_CLAMP_TO_EDGE;

		textureDatas1[0].options[0] = GL_CLAMP_TO_BORDER;
		textureDatas1[0].options[1] = GL_CLAMP_TO_BORDER;

		textureDatas3[0].options[0] = GL_MIRRORED_REPEAT;
		textureDatas3[0].options[1] = GL_MIRRORED_REPEAT;

		RenderData* renderData0 = createRenderData(1, vertices0, 4, indices, 6, textureDatas0, 2);
		RenderData* renderData1 = createRenderData(2, vertices1, 4, indices, 6, textureDatas1, 2);
		RenderData* renderData2 = createRenderData(3, vertices2, 4, indices, 6, textureDatas2, 2);
		RenderData* renderData3 = createRenderData(4, vertices3, 4, indices, 6, textureDatas3, 2);

		render1.loadData(renderData0);
		render1.loadData(renderData1);
		render1.loadData(renderData2);
		render2.loadData(renderData3);

		
		//render.setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (!glfwWindowShouldClose(window))
		{
			// ‰»Î
			processInput(window);
			//‰÷»æ÷∏¡Ó
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			if (alpha_dirty)
			{
				render2.setUniform("alpha", (void*)&alpha, 1, ShaderParamType::SPT_FLOAT);
				alpha_dirty = false;
			}
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
TextureData createTextureData(const char* src, uint16_t textureUnit, uint16_t wrap_s, uint16_t wrap_t, uint16_t min_filter, uint16_t max_filter)
{
	TextureData data;
	memcpy(&data.texture, src, strlen(src));
	data.texture[strlen(src)] = '\0';
	data.options[0] = wrap_s;
	data.options[1] = wrap_t;
	data.options[2] = min_filter;
	data.options[3] = max_filter;
	data.textureUnit = textureUnit;
	return data;
}
RenderData* createRenderData(int id,float* vertices, int count, unsigned int *indices, int element_count, TextureData* textureDatas,int texture_count)
{
	RenderData* renderData = new RenderData();
	renderData->vertices = (float*)malloc(count * 8 * sizeof(float));
	memcpy(renderData->vertices, vertices, count * 8 * sizeof(float));
	renderData->count = count;
	renderData->element = (unsigned int*)malloc(element_count * sizeof(float));
	memcpy(renderData->element, indices, element_count * sizeof(float));
	renderData->element_count = element_count;
	renderData->useColor = true;
	renderData->useUV[0] = true;
	renderData->id = id;
	renderData->textures = new TextureData[texture_count];
	for (int i = 0; i < texture_count; i++)
	{
		TextureData& textureData = renderData->textures[i];
		memcpy(&textureData, &textureDatas[i], sizeof(TextureData));
	}
	renderData->textureSize = texture_count;
	return renderData;
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
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		alpha = std::min(1.0f, std::max(0.0f, alpha + 0.01f));
		alpha_dirty = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		alpha = std::min(1.0f, std::max(0.0f, alpha - 0.01f));
		alpha_dirty = true;
	}
}