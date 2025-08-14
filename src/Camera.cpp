#include "headers/Camera.hpp"

//basic camera class to be able to move the camera around.
void camera::update(float dt, GLFWwindow* window, int display_w, int display_h)
{
    // Get current cursor position
    double cursor_x = 0.0, cursor_y = 0.0;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);

    // Initialize cursor position only once
    if (!initialized)
    {
        cursor_pos = glm::vec2((float)cursor_x, (float)cursor_y);
        initialized = true;
    }

    // Only update camera if right mouse button is held
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        float speed = 4.0f;

        glm::vec3 side = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
        glm::vec3 up = glm::normalize(glm::cross(side, direction));

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            speed *= 2.0f;

        // Movement controls
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += glm::normalize(direction) * dt * speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= glm::normalize(direction) * dt * speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= glm::normalize(side) * dt * speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += glm::normalize(side) * dt * speed;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            position += up * dt * speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            position -= up * dt * speed;

        // Mouse movement
        glm::vec2 cursor_delta = glm::vec2((float)cursor_x, (float)cursor_y) - cursor_pos;

        direction = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(15.0f) * dt * cursor_delta.y, side) * glm::vec4(direction, 0.0f));
        direction = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(15.0f) * dt * cursor_delta.x, glm::vec3(0, 1, 0)) * glm::vec4(direction, 0.0f));
    }

    // Update projection matrix
    float near = 0.01f;
    float far = 900.0f;
    float aspect = (display_h == 0) ? 1.0f : static_cast<float>(display_w) / static_cast<float>(display_h);
    proj = glm::perspective(glm::radians(70.0f), aspect, near, far);

    // Update view matrix
    view = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
    viewProj = proj * view;

    // Update cursor position for next frame
    cursor_pos = glm::vec2((float)cursor_x, (float)cursor_y);
}

glm::mat4 camera::getViewProj()
{
    return viewProj;
}
