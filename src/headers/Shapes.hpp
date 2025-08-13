#include <glm/glm.hpp>
using namespace glm;

class Shapes
{
public:
	enum shapeType
	{
		CUBE,
		BALL,
		PYRAMID
	};
	//constructor
	Shapes(shapeType type, glm::vec3 pos = { 0,0,0 }, glm::vec3 scl = { 1,1,1 }, float rot = 0.0f, glm::vec4 col = { 1,1,1,1 });
	~Shapes();//destructor
	//void initalise_shape();
	void set_color(vec4 color);

private:
	//basic attributes to send to the GPU.
	glm::vec3 position;
	glm::vec3 scale;
	float roatation;
	glm::vec4 color;
	glm::mat4 modelMatrix;
	shapeType objectType;
};