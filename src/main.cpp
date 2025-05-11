#include "config.h"

int main()
{
    std::ifstream file;
    std::string line;

    file.open("src/shaders/vertex.glsl");
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    GLFWwindow *window;

    if (!glfwInit())
    {
        std::cout << "GLFW couldn't start" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640, 640, "My first window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.75f, 0.5f, 0.75f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

unsigned int make_modules(const std::string &filepath, unsigned int module_type)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line))
    {
        bufferedLines << line << "/n";
    }
    std::string shaderSource = bufferedLines.str();

    const char *sharderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &sharderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &status);
    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module compilation error:\n"
                  << errorLog << std::endl;
    }

    return shaderModule;
}