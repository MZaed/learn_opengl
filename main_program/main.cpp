#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <shader.h>
#include <gl_error_check.h>
#include <vertex_array.h>
#include <vertex_buffer.h>
#include <index_buffer.h>
#include <texture_buffer2D.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastFrameTime = 0;

float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

static glm::vec3 cameraPos(0.0f, 0.0f, 0.0f);
static glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
float Zoom = 45.0f;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetScrollCallback(window, scroll_callback); 
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    VertexArray vertexArray;
    vertexArray.bind();

    VertexBuffer vertexBuffer;
    vertexBuffer.bind();

    vertexBuffer.write(vertices, sizeof(vertices));

    //Tell opengl how to make sense of data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)NULL);
    glEnableVertexAttribArray(0);

    Shader basicShader("shader/basic.shader");
    basicShader.bind();

    int width;
    int height;
    int nrChannels;

    unsigned char *data = stbi_load("texture/wall.jpg", &width, &height, &nrChannels, 0);

    TextureBuffer2D texture0(GL_TEXTURE0);
    texture0.bind();
    texture0.write(width, height, GL_RGB, data);
    texture0.unBind();

    stbi_image_free(data);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("texture/awesomeface.png", &width, &height, &nrChannels, 0);

    TextureBuffer2D texture1(GL_TEXTURE1);
    texture1.bind();
    texture1.write(width, height, GL_RGBA, data);
    texture1.unBind();

    stbi_image_free(data);

    texture0.bind();
    texture1.bind();

    basicShader.setUniform1i("ourTexture0", 0);
    basicShader.setUniform1i("ourTexture1", 1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);


        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos * cameraFront, cameraUp);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(Zoom), static_cast<float>(SCR_WIDTH/SCR_HEIGHT), 0.1f, 100.0f);

        basicShader.SetUniformMat4fv("uView", view);
        basicShader.SetUniformMat4fv("uProjection", projection);

        vertexArray.bind();

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            basicShader.SetUniformMat4fv("uModel", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    const float currentFrameTime = glfwGetTime();
    const float deltaFrameTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    float cameraSpeed = 2.5F * deltaFrameTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static double lastX = xpos;
    static double lastY = ypos;

    static float yaw = -90.0F;
    static float pitch = 0.0F;

    static bool firstMouse = true;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    cameraFront = glm::normalize(cameraFront);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f; 
}

