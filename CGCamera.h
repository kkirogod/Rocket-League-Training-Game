#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGSlotCar.h"

class CGCamera {
public:
    CGCamera();
    glm::mat4 ViewMatrix();

    void SetPosition(GLfloat x, GLfloat y, GLfloat z);
    void SetPosition(glm::vec3 position);
    void SetDirection(GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat xUp, GLfloat yUp, GLfloat zUp);
    void SetDirection(glm::vec3 d, glm::vec3 u);
    void SetDir(glm::vec3 dir);
    void SetMoveStep(GLfloat step);
    void SetTurnStep(GLfloat step);

    glm::vec3 GetPosition();
    glm::vec3 GetDirection();
    glm::vec3 GetUpDirection();
    GLfloat GetMoveStep();
    GLfloat GetTurnStep();

    void MoveFront();
    void MoveBack();
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();

    void TurnRight();
    void TurnLeft();
    void TurnUp();
    void TurnDown();
    void TurnCW();
    void TurnCCW();

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



