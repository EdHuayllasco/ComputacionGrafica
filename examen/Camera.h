#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "shaderClass.h"
class Camera {
public:
	//VECTORES DE LA CAMARA
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	int width;
	int height;
	// EVITA QUE LA CAMARA SALTE A UN ESQUINA AL HACER EL CLICK POR PRIMERA VEZ
	// BUG ARREGLADO
	bool firstClick = true;
	// CONTROLAMOS LA SENSIBILIDAD Y LA VELOCIDAD CUANDO MIRAMOS AL ALREDEDOR
	float speed = 0.1f;
	float sensitivity = 100.f;
	//CONSTRUCTOR
	Camera(int width, int height, glm::vec3 position);
	// ACTUALIZAMOS LA MATRIZ DE LA CAMARA AL VERTEX SHADER
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// EXPORTAR LA MATRIZ DE LA CAMARA AL SHADER
	void Matrix(Shader& shader, const char* uniform);
	// MANEJAR LAS ENTRAADAS DE LA CAMARA
	void Inputs(GLFWwindow* window);

};
#endif // !CAMERA_CLASS_H