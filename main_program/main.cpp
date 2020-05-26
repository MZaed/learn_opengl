#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const float vertices[] = {
        +0.5f, +0.5f, 0.0f,
        +0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, +0.5f, 0.0f,
};

unsigned int indices[] = {
        0U, 1U, 3U,
        1U, 2U, 3U
};

const char* vertexShaderSource =
"#version 330 core                          \n"
"                                           \n"
"layout (location = 0) in vec3 aVertices;   \n"
"void main()                                \n"
"{                                          \n"
"   gl_Position = vec4(aVertices.xyz, 1.0); \n"
"}                                          \n"
"                                           \n";

const char* fragmentShaderSource =
"#version 330 core                          \n"
"                                           \n"
"out vec4 FragColor;                        \n"
"void main()                                \n"
"{                                          \n"
"   FragColor = vec4(1.0, 0.5, 0.2, 1.0);   \n"
"}                                          \n"
"                                           \n";

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

    //Create and setup Vertex Array Object
    GLuint vertexArrayObject = 0U;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //Create and Setup Vertex Buffer
    GLuint vertexBufferId = 0U;
    glGenBuffers(1, &vertexBufferId); //Generate buffer id
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId); //Link buffer to vertex buffer and activate the buffer
    //Allocates memory, fills the selected buffer type with given data, size
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Create and Setup Index Buffer
    GLuint indexBufferId = 0U;
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices, GL_STATIC_DRAW);

    //Tell opengl how to make sense of data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)NULL);
    glEnableVertexAttribArray(0);

    //Create vertex shader
    GLuint vertexShaderId = 0;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER); //Generate ShaderId for a given shader type
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL); //Update shader source program
    glCompileShader(vertexShaderId); //Compile shader with given shaderId
    int success = 0;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        int shaderLength = 0;
        char compilationLog[512] = {0};
        glGetShaderInfoLog(vertexShaderId, sizeof(compilationLog), &shaderLength, compilationLog);
        std::cout << "Shader Length = " << shaderLength << std::endl;
        std::cout << compilationLog << std::endl;
    }

    //Create fragment shader
    GLuint fragmentShaderId = 0;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        int shaderLength = 0;
        char compilationLog[512] = {0};
        glGetShaderInfoLog(fragmentShaderId, sizeof(compilationLog), &shaderLength, compilationLog);
        std::cout << "Shader Length = " << shaderLength << std::endl;
        std::cout << compilationLog << std::endl;
    }

    //Create program object
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        unsigned int bufferSize = 512U;
        int bufferLength = 0U;
        char infoLog[512] = {0};

        glGetShaderInfoLog(shaderProgram, bufferSize, &bufferLength, infoLog);
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArrayObject);
        //Wire frame mode, Default is GL_FILL
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
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


