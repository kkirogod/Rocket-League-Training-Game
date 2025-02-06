#include "CGFigure.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//
// FUNCIÓN: CGFigure::~CGFigure()
//
// PROPÓSITO: Destructor de la figura
//
CGFigure::~CGFigure()
{
	if (vertices != NULL) delete[] vertices;
	if (indexes != NULL) delete[] indexes;
	if (normals != NULL) delete[] normals;
	if (textures != NULL) delete[] textures;

	// Delete vertex buffer objects
	glDeleteBuffers(4, VBO);
	glDeleteVertexArrays(1, &VAO);
}

//
// FUNCIÓN: CGFigure::InitBuffers()
//
// PROPÓSITO: Crea el VAO y los VBO y almacena todos los datos
//            en la GPU.
//
void CGFigure::InitBuffers()
{
	// Create the Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the Vertex Buffer Objects
	glGenBuffers(4, VBO);

	// Copy data to video memory
	// Vertex data
	int buffsize = sizeof(GLfloat) * numVertices * 3;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTEX_DATA]);
	glBufferData(GL_ARRAY_BUFFER, buffsize, vertices, GL_STATIC_DRAW);

	// Normal data
	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_DATA]);
	glBufferData(GL_ARRAY_BUFFER, buffsize, normals, GL_STATIC_DRAW);

	// Texture coordinates
	buffsize = sizeof(GLfloat) * numVertices * 2;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE_DATA]);
	glBufferData(GL_ARRAY_BUFFER, buffsize, textures, GL_STATIC_DRAW);

	// Indexes
	buffsize = sizeof(GLushort) * numFaces * 3;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX_DATA]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffsize, indexes, GL_STATIC_DRAW);

	delete[] vertices;
	delete[] indexes;
	delete[] normals;
	delete[] textures;

	vertices = NULL;
	indexes = NULL;
	normals = NULL;
	textures = NULL;

	glEnableVertexAttribArray(0); // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTEX_DATA]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1); // Vertex normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_DATA]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2); // Vertex textures
	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE_DATA]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	location = glm::mat4(1.0f);
}

//
// FUNCIÓN: CGFigure::SetMaterial(CGMaterial* m)
//
// PROPÓSITO: Asigna el material de la figura
//
void CGFigure::SetMaterial(CGMaterial* mat)
{
	material = mat;
}

//
// FUNCIÓN: CGFigure::ResetLocation()
//
// PROPÓSITO: Asigna la posición inicial de la figura 
//
void CGFigure::ResetLocation()
{
	location = glm::mat4(1.0f);
}

void CGFigure::SetLocation(glm::mat4 l)
{
	location = l;
}

glm::mat4 CGFigure::GetLocation()
{
	return location;
}

glm::vec3 CGFigure::GetRealPosition() {
	return glm::vec3(location[3][0], location[3][1], location[3][2]);
}

//
// FUNCIÓN: CGFigure::Translate(glm::vec3 t)
//
// PROPÓSITO: Añade un desplazamiento a la matriz de posición de la figura 
//
void CGFigure::Translate(glm::vec3 t)
{
	location = glm::translate(location, t);
}

//
// FUNCIÓN: CGFigure::Rotate(GLfloat angle, glm::vec3 axis)
//
// PROPÓSITO: Añade una rotación a la matriz de posición de la figura 
//
void CGFigure::Rotate(GLfloat angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
}

//
// FUNCIÓN: CGFigure::Draw(CGShaderProgram * program, glm::mat4 projection, glm::mat4 view,  glm::mat4 shadowViewMatrix)
//
// PROPÓSITO: Dibuja la figura
//
void CGFigure::Draw(CGShaderProgram* program, glm::mat4 projection, glm::mat4 view, glm::mat4 shadowViewMatrix)
{
	glm::mat4 mvp = projection * view * location;
	program->SetUniformMatrix4("MVP", mvp);
	program->SetUniformMatrix4("ViewMatrix", view);
	program->SetUniformMatrix4("ModelViewMatrix", view * location);
	program->SetUniformMatrix4("ShadowMatrix", shadowViewMatrix * location);
	material->SetUniforms(program);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_SHORT, NULL);
}

//
// FUNCIÓN: CGFigure::DrawShadow(CGShaderProgram * program, glm::mat4 shadowMatrix)
//
// PROPÓSITO: Dibuja la sombra de la figura
//
void CGFigure::DrawShadow(CGShaderProgram* program, glm::mat4 shadowMatrix)
{
	glm::mat4 mvp = shadowMatrix * location;
	program->SetUniformMatrix4("MVP", mvp);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_SHORT, NULL);
}

////////////////////////////////////////////////////////////
/////////////////// MANEJO DEL COCHE ///////////////////////
////////////////////////////////////////////////////////////

CGFigure::CGFigure()
{
	Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	Dir = glm::vec3(0.0f, 0.0f, 1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Right = glm::vec3(1.0f, 0.0f, 0.0f);

	moveStep = 0.0f;
	upStep = 0.0f;
	turnStep = 1.0f;
	cosAngle = (GLfloat)cos(glm::radians(turnStep));
	sinAngle = (GLfloat)sin(glm::radians(turnStep));
}

glm::mat4 CGFigure::ViewMatrix()
{
	return glm::lookAt(Pos, Pos - Dir, Up);
}

void CGFigure::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	Pos = glm::vec3(x, y, z);
}

void CGFigure::SetDirection(GLfloat xD, GLfloat yD, GLfloat zD, GLfloat xU, GLfloat yU, GLfloat zU)
{
	Dir = glm::vec3(xD, yD, zD);
	Up = glm::vec3(xU, yU, zU);
	Right = glm::cross(Up, Dir);
}

void CGFigure::SetDirection(glm::vec3 d, glm::vec3 u)
{
	Dir = glm::vec3(d);
	Up = glm::vec3(u);
	Right = glm::cross(Up, Dir);
}

void CGFigure::SetMoveStep(GLfloat step)
{
	moveStep = step;
}

void CGFigure::SetUpStep(GLfloat step)
{
	upStep = step;
}

void CGFigure::SetTurnStep(GLfloat step)
{
	turnStep = step;
	cosAngle = (GLfloat)cos(glm::radians(turnStep));
	sinAngle = (GLfloat)sin(glm::radians(turnStep));
}

glm::vec3 CGFigure::GetPosition()
{
	return Pos;
}

glm::vec3 CGFigure::GetDirection()
{
	return Dir;
}

glm::vec3 CGFigure::GetUpDirection()
{
	return Up;
}

GLfloat CGFigure::GetMoveStep()
{
	return moveStep;
}

GLfloat CGFigure::GetUpStep()
{
	return upStep;
}

GLfloat CGFigure::GetTurnStep()
{
	return turnStep;
}

void CGFigure::MoveFront()
{
	if (moveStep > 0.0f)
		moveStep -= 0.001f;

	else if (moveStep < 0.0f)
		moveStep += 0.001f;

	if (this->GetRealPosition().y > 3.0f)
		upStep-=0.005f;
	else if (upStep < 0.0f)
		upStep = -upStep * 0.8;

	Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	Pos += glm::vec3(moveStep * Dir.x, upStep, moveStep * Dir.z);
	Translate(Pos);
}

void CGFigure::MoveLeft()
{
	Pos -= moveStep * Right;
}

void CGFigure::MoveRight()
{
	Pos += moveStep * Right;
}

void CGFigure::MoveUp()
{
	Pos += moveStep * Up;
}

void CGFigure::MoveDown()
{
	Pos -= moveStep * Up;
}