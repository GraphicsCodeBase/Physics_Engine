#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::rotate, glm::perspective, glm::lookAt, etc.
#include <GLFW/glfw3.h>
class camera
{
public:
	//basic camera properties.
	glm::vec3 position = { 0.0f, 0.0f,-1.0f };
	glm::vec3 direction = glm::normalize(glm::vec3(-1, -1, -1));
	glm::vec3 cursor = {};

	//matrices of the camera.
	glm::mat4 view;
	glm::mat4 proj;
	glm::mat4 viewProj;

	//update function to pass into the shaders.
	void update(float dt, GLFWwindow* window, int display_w, int display_h);
	glm::mat4 getViewProj();
private:

	bool initialized = false; // used to set cursor position on first update
	glm::vec2 cursor_pos = { 0.0f, 0.0f };
};