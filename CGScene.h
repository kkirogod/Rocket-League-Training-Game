#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"
#include "CGLight.h"
#include "CGMaterial.h"
#include "CGFigure.h"
#include "CGObject.h"

class CGScene {
public:
    CGScene();
    ~CGScene();
    void Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 shadowViewMatrix);
    void DrawShadow(CGShaderProgram* program, glm::mat4 shadowMatrix);
    glm::mat4 GetLightViewMatrix();
    CGObject* getCoche();
    CGFigure* getBalon();

private:
    CGFigure* ground;
    CGFigure* paredIzq;
    CGFigure* paredDer;
    CGFigure* paredNorteDer;
    CGFigure* paredNorteIzq;
    CGFigure* paredNorteArriba;
    CGFigure* paredSur;
    CGFigure* figBalon;
    CGFigure* figPorteria;
    CGObject* coche;
    CGMaterial* matb;
    CGMaterial* matg;
    CGMaterial* matPorteria;
    CGMaterial* mat0;
    CGMaterial* matPared;
    CGMaterial* matBalon;
    CGLight* light;
};
