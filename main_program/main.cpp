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

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const float vertices[] = {
        //Vertices(xyz)     //Color(RGB)     //TextureCoord
        +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, +0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f
};

unsigned int indices[] = {
        0U, 1U, 3U,
        1U, 2U, 3U
};

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

    //Create and Setup Index Buffer
    IndexBuffer indexBuffer;
    indexBuffer.bind();
    indexBuffer.write(indices, sizeof(indices));

    //Tell opengl how to make sense of data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

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

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);


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

    glm::mat4 trans(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    basicShader.SetUniformMat4fv("uTransform", trans);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vertexArray.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


