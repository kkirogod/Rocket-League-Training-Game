#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"
#include "CGPiece.h"

//
// CLASE: CGObject
//
// DESCRIPCIÓN: Clase abstracta que representa un objeto formado por varias piezas
// 
class CGObject
{
protected:
	glm::mat4 model;  // Model matrix

public:
	void ResetLocation();
	void Translate(glm::vec3 t);
	void Rotate(GLfloat angle, glm::vec3 axis);
	void SetLocation(glm::mat4 loc);
	glm::mat4 GetLocation();
	void Draw(CGShaderProgram* program, glm::mat4 projection, glm::mat4 view);
    void DrawShadow(CGShaderProgram* program, glm::mat4 shadowMatrix);

    virtual int GetNumPieces() = 0;
	virtual CGPiece* GetPiece(int i) = 0;

    // MANEJO DEL COCHE:

    CGObject();
    glm::mat4 ViewMatrix();

    void SetPosition(GLfloat x, GLfloat y, GLfloat z);
    void SetDirection(GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat xUp, GLfloat yUp, GLfloat zUp);
    void SetMoveStep(GLfloat step);
    void SetTurnStep(GLfloat step);

    glm::vec3 GetPosition();
    glm::vec3 GetRealPosition();
    glm::vec3 GetDirection();
    glm::vec3 getForwardDirection();
    glm::vec3 getUpDirection();
    glm::vec3 getRightDirection();
    glm::vec3 GetUpDirection();
    GLfloat GetMoveStep();
    GLfloat GetTurnStep();

    void MoveFront();

    void TurnRight();
    void TurnLeft();

private:
    glm::vec3 Pos;
    glm::vec3 Dir;
    glm::vec3 Up;
    glm::vec3 Right;

    GLfloat moveStep;
    GLfloat turnStep;
    GLfloat cosAngle;
    GLfloat sinAngle;
};

