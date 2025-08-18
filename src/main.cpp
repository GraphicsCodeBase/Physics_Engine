#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "headers/Shader.hpp" 
#include "headers/Shapes.hpp"
#include "headers/Camera.hpp"
//shader path globals
std::string shader_VS = "../src/Shaders/main.vert";
std::string shader_FS = "../src/Shaders/main.frag";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version to 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS fix
#endif

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Physics Engine", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL functions via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Set viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //setup Shaders
    Shader mainShader;
    mainShader.setUpShader(shader_VS,shader_FS);

    //object creation
    Shapes object_1(
        Shapes::shapeType::CUBE,            // type
        glm::vec3(0.0f, 0.0f, 0.0f),        // position
        glm::vec3(1.0f, 1.0f, 1.0f),        // scale
        0.0f,                               // rotation in degrees
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // color RGBA
    Shapes object_2(Shapes::shapeType::PYRAMID,            // type
                    glm::vec3(3.0f, 0.0f, 0.0f),        // position
                    glm::vec3(1.0f, 1.0f, 1.0f),        // scale
                    0.0f,                               // rotation in degrees
                    glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)); // color RGBA
    //initialize camera object.
    camera main_camera;
    //get window params.
    // Get actual framebuffer size
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    // Set OpenGL viewport
    glViewport(0, 0, windowWidth, windowHeight);

    float lastFrame = 0.0f;//initalise last frame time.
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //calculate delta time
        float currentFrame = static_cast<float>(glfwGetTime());
        float dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Render (clear to teal color)
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //update camera.
        main_camera.update(dt, window, windowWidth, windowHeight);
        //bind Shader
        mainShader.use();
        object_1.update(dt);
        object_2.update(dt);
        //pass in uniforms.
        //passing in global shaders.
        mainShader.setVec3("lightDir",glm::vec3(1.0f, 1.0f, 0.0f));
        mainShader.setVec3("lightColor", glm::vec3(1.0f));

        object_1.render(mainShader, main_camera.getViewProj());
        object_2.render(mainShader, main_camera.getViewProj());
        //unbind shaders.
        mainShader.unUse();
        // Swap buffers + poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
