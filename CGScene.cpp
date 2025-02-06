#include "CGScene.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CGShaderProgram.h"
#include "CGFigure.h"
#include "CGLight.h"
#include "CGMaterial.h"
#include "CGSphere.h"
#include "CGGround.h"
#include "resource.h"
#include "CGSlotCar.h"
#include "CGSlotCar_pieces.h"
#include "CGPorteria.h"

//
// FUNCIÓN: CGScene::CGScene()
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CGScene::CGScene()
{
    glm::vec3 Ldir = glm::vec3(1.0f, -0.8f, -1.0f);
    Ldir = glm::normalize(Ldir);
    light = new CGLight();
    light->SetLightDirection(Ldir);
    light->SetAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));
    light->SetDifusseLight(glm::vec3(0.8f, 0.8f, 0.8f));
    light->SetSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

    matg = new CGMaterial();
    matg->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matg->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matg->SetSpecularReflect(0.8f, 0.8f, 0.8f);
    matg->SetShininess(16.0f);
    matg->InitTexture("textures/terrenoDeJuego/field.jpg");
    //matg->InitTexture(IDR_IMAGE2);

    ground = new CGGround(100.0f, 150.0f);
    ground->SetMaterial(matg);

    matPorteria = new CGMaterial();
    matPorteria->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matPorteria->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matPorteria->SetSpecularReflect(0.8f, 0.8f, 0.8f);
    matPorteria->SetShininess(16.0f);
    matPorteria->InitTexture("textures/terrenoDeJuego/goal.jpg");

    mat0 = new CGMaterial();
    mat0->SetAmbientReflect(1.0f, 0.0f, 1.0f);
    mat0->SetDifusseReflect(1.0f, 0.0f, 1.0f);
    mat0->SetSpecularReflect(0.8f, 0.8f, 0.8f);
    mat0->SetShininess(16.0f);
    mat0->InitTexture("textures/terrenoDeJuego/cement.jpg");
    //mat0->InitTexture(IDR_IMAGE1);

    GLuint textureId = mat0->GetTexture();

    matPared = new CGMaterial();
    matPared->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matPared->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matPared->SetSpecularReflect(0.8f, 0.8f, 0.8f);
    matPared->SetShininess(16.0f);
    matPared->SetTexture(textureId);

    paredIzq = new CGGround(20.0f, 150.0f);
    paredIzq->SetMaterial(matPared);
    paredIzq->Translate(glm::vec3(-100.0f, 20.0f, 0.0f));
    paredIzq->Rotate(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    paredDer = new CGGround(20.0f, 150.0f);
    paredDer->SetMaterial(matPared);
    paredDer->Translate(glm::vec3(100.0f, 20.0f, 0.0f));
    paredDer->Rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    paredNorteDer = new CGGround(38.0f, 20.0f);
    paredNorteDer->SetMaterial(matPared);
    paredNorteDer->Translate(glm::vec3(63.0f, 20.0f, -150.0f));
    paredNorteDer->Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    paredNorteIzq = new CGGround(38.0f, 20.0f);
    paredNorteIzq->SetMaterial(matPared);
    paredNorteIzq->Translate(glm::vec3(-63.0f, 20.0f, -150.0f));
    paredNorteIzq->Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    paredNorteArriba = new CGGround(25.0f, 10.0f);
    paredNorteArriba->SetMaterial(matPared);
    paredNorteArriba->Translate(glm::vec3(0.0f, 30.0f, -150.0f));
    paredNorteArriba->Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    paredSur = new CGGround(100.0f, 20.0f);
    paredSur->SetMaterial(matPared);
    paredSur->Translate(glm::vec3(0.0f, 20.0f, 150.0f));
    paredSur->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    matBalon = new CGMaterial();
    matBalon->SetAmbientReflect(1.0f, 1.0f, 1.0f);
    matBalon->SetDifusseReflect(1.0f, 1.0f, 1.0f);
    matBalon->SetSpecularReflect(0.8f, 0.8f, 0.8f);
    matBalon->SetShininess(16.0f);
    matBalon->InitTexture("textures/ball.jpg");
    //mat2->InitTexture(IDR_IMAGE3);

    figBalon = new CGSphere(20, 40, 3.0f);
    figBalon->SetMaterial(matBalon);
    figBalon->Translate(glm::vec3(0.0f, 3.0f, -10.0f));

    figPorteria = new CGPorteria(10.0f, 5.0f);
    figPorteria->SetMaterial(matPorteria);
    figPorteria->Translate(glm::vec3(-15.0f, 10.0f, -155.0f));
    figPorteria->Rotate(180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    coche = new CGSlotCar();
    coche->Translate(glm::vec3(0.0f, 0.0f, 20.0f));
    coche->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

//
// FUNCIÓN: CGScene3:~CGScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CGScene::~CGScene()
{
    delete ground;
    delete paredIzq;
    delete paredDer;
    delete paredNorteDer;
    delete paredNorteIzq;
    delete paredNorteArriba;
    delete paredSur;
    delete figBalon;
    delete figPorteria;
    delete light;
    delete matg;
    delete mat0;
    delete matPared;
    delete matBalon;
    delete coche;
}

//
// FUNCIÓN: CGScene::Draw()
//
// PROPÓSITO: Dibuja la escena
//
void CGScene::Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 shadowViewMatrix)
{
    light->SetUniforms(program);

    ground->Draw(program, proj, view, shadowViewMatrix);
    paredIzq->Draw(program, proj, view, shadowViewMatrix);
    paredDer->Draw(program, proj, view, shadowViewMatrix);
    paredNorteDer->Draw(program, proj, view, shadowViewMatrix);
    paredNorteIzq->Draw(program, proj, view, shadowViewMatrix);
    paredNorteArriba->Draw(program, proj, view, shadowViewMatrix);
    paredSur->Draw(program, proj, view, shadowViewMatrix);
    figBalon->Draw(program, proj, view, shadowViewMatrix);
    figPorteria->Draw(program, proj, view, shadowViewMatrix);
    coche->Draw(program, proj, view);
}

//
// FUNCIÓN: CGScene::DrawShadow()
//
// PROPÓSITO: Dibuja las sombras de la escena
//
void CGScene::DrawShadow(CGShaderProgram* program, glm::mat4 shadowMatrix)
{
    coche->DrawShadow(program, shadowMatrix);
    paredIzq->DrawShadow(program, shadowMatrix);
    paredDer->DrawShadow(program, shadowMatrix);
    paredNorteDer->DrawShadow(program, shadowMatrix);
    paredNorteIzq->DrawShadow(program, shadowMatrix);
    paredNorteArriba->DrawShadow(program, shadowMatrix);
    paredSur->DrawShadow(program, shadowMatrix);
    figBalon->DrawShadow(program, shadowMatrix);
    figPorteria->DrawShadow(program, shadowMatrix);
}

//
// FUNCIÓN: CGScene::GetLightViewMatrix()
//
// PROPÓSITO: Obtiene la matriz de posicionamiento de la luz
//
glm::mat4 CGScene::GetLightViewMatrix()
{
    glm::vec3 Zdir = -(light->GetLightDirection());
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Xdir = glm::normalize(glm::cross(Up, Zdir));
    glm::vec3 Ydir = glm::cross(Zdir, Xdir);
    glm::vec3 Zpos = 150.0f * Zdir;
    glm::vec3 Center = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 view = glm::lookAt(Zpos, Center, Ydir);
    return view;
}

CGObject* CGScene::getCoche()
{
    return coche;
}

CGFigure* CGScene::getBalon()
{
    return figBalon;
}