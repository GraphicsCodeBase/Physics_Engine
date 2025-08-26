#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "headers/Shader.hpp" 
#include "headers/Shapes.hpp"
#include "headers/Camera.hpp"
#include "headers/MeshLibary.hpp"
#include "headers/physics.hpp"
#include "headers/Renderer.hpp"
//shader path globals
std::string shader_VS = "../src/Shaders/main.vert";
std::string shader_FS = "../src/Shaders/main.frag";
std::string Test_shader_VS = "../src/Shaders/test.vert";
std::string Test_shader_FS = "../src/Shaders/test.frag";

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

    // Set OpenGL version to 4.6 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
    //setup meshes.
    MeshLib resource;
    resource.initalise();

    //initalise mesh instances.
    auto cube = std::make_shared<Shapes>(Shapes::shapeType::CUBE,// type
        glm::vec3(0.0f, 0.0f, 0.0f),      // pos
        glm::vec3(1.0f, 1.0f, 1.0f),      // scale
        0.0f,                             // rot
        glm::vec4(1, 0, 0, 1)             // color (red)
    );

    //setup Shaders
    Shader mainShader;
    mainShader.setUpShader(shader_VS,shader_FS);
    //mainShader.setUpShader(Test_shader_VS,Test_shader_FS);
    //make a physics system
    PhysicsSystem physics_system;
    physics_system.initaliseObjects();
    //make renderer system
    Renderer render_system;
    render_system.initInstanceBuffer(cube->getMesh(),100);
    //initialize camera object.
    camera main_camera;
    //get window params.
    // Get actual framebuffer size


    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    // After creating window + GL context
    glEnable(GL_DEPTH_TEST);

    float lastFrame = 0.0f;//initalise last frame time.
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        //calculate delta time
        float currentFrame = static_cast<float>(glfwGetTime());
        float dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Render (clear to teal color)
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        //update camera.
        main_camera.update(dt, window, windowWidth, windowHeight);
        //bind Shader
        mainShader.use();

        //update the objects 
        physics_system.update(dt);

        //pass into the renderer to be rendered 
        render_system.updateInstanceData(cube->getMesh(),physics_system.getObjects());

        //passing in global shaders.
        mainShader.setMat4("uniform_vp", main_camera.getViewProj());
        mainShader.setVec3("lightPos",glm::vec3(3.0f, 2.0f, 2.0f));
        mainShader.setVec3("lightColor", glm::vec3(1.0f));
        mainShader.setVec4("objectColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        render_system.drawInstanced(cube->getMesh(), physics_system.getObjects().size());
        //unbind shaders.
        mainShader.unUse();
        // Swap buffers + poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
