#pragma once

#include <GL/glew.h>
#include "CGShaderProgram.h"
#include "CGScene.h"
#include "CGSkybox.h"
#include "CGCamera.h"

class CGModel
{
public:
	void initialize(int w, int h);
	void finalize();
	void render();
	void update();
	void key_pressed(int key);
	void mouse_button(int button, int action);
	void mouse_move(double xpos, double ypos);
	void resize(int w, int h);

private:
	bool fueraCoche = false;
	bool fueraBalon = false;

	void colocarCamara();

	CGShaderProgram* sceneProgram;
	CGShaderProgram* skyboxProgram;
	CGShaderProgram* shadowProgram;
	CGScene* scene;
	CGCamera* camera;
	CGSkybox* skybox;
	glm::mat4 projection;

	GLsizei wndWidth;
	GLsizei wndHeight;
	GLuint shadowFBO;
	GLuint depthTexId;
	GLuint offsetTexId;

	bool InitShadowMap();
	void CarBallImpact();
	void GoalDetection();
	void CameraConstraints();
	void CarConstraints();
	void BallConstraints();
	void BuildOffsetTex(int texSize, int samplesU, int samplesV);
	float jitter();
};
