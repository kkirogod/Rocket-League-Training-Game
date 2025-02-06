#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGMaterial.h"
#include "CGShaderProgram.h"

#define VERTEX_DATA 0
#define INDEX_DATA 1
#define NORMAL_DATA 2
#define TEXTURE_DATA 3

//
// CLASE: CGFigure
//
// DESCRIPCIÓN: Clase abstracta que representa un objeto descrito mediante
// VAO para su renderizado mediante shaders
// 
class CGFigure {
protected:
	GLushort* indexes; // Array of indexes 
	GLfloat* vertices; // Array of vertices
	GLfloat* normals;  // Array of normals
	GLfloat* textures; // Array of texture coordinates

	GLuint numFaces; // Number of faces
	GLuint numVertices; // Number of vertices
	GLuint VBO[4];
	GLuint VAO;

	glm::mat4 location; // Model matrix
	CGMaterial* material;

public:
	~CGFigure();
	void InitBuffers();
	void SetMaterial(CGMaterial* mat);
	void ResetLocation();
	void SetLocation(glm::mat4 l);
	glm::mat4 GetLocation();
	glm::vec3 GetRealPosition();
	void Translate(glm::vec3 t);
	void Rotate(GLfloat angle, glm::vec3 axis);
	void Draw(CGShaderProgram* program, glm::mat4 projection, glm::mat4 view, glm::mat4 shadowViewMatrix);
	void DrawShadow(CGShaderProgram* program, glm::mat4 shadowMatrix);

    // MANEJO DEL BALON:

    CGFigure();
    glm::mat4 ViewMatrix();

    void SetPosition(GLfloat x, GLfloat y, GLfloat z);
    void SetDirection(GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat xUp, GLfloat yUp, GLfloat zUp);
    void SetDirection(glm::vec3 d, glm::vec3 u);
    void SetMoveStep(GLfloat step);
    void SetUpStep(GLfloat step);
    void SetTurnStep(GLfloat step);

    glm::vec3 GetPosition();
    glm::vec3 GetDirection();
    glm::vec3 GetUpDirection();
    GLfloat GetMoveStep();
    GLfloat GetUpStep();
    GLfloat GetTurnStep();

    void MoveFront();
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();

private:
    glm::vec3 Pos;
    glm::vec3 Dir;
    glm::vec3 Up;
    glm::vec3 Right;

    GLfloat moveStep;
    GLfloat upStep;
    GLfloat turnStep;
    GLfloat cosAngle;
    GLfloat sinAngle;
};



