#include "CGSlotCar.h"
#include "CGSlotCar_pieces.h"
#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

CGSlotCar::CGSlotCar()
{
	model = glm::mat4(1.0f);

	mtl[0] = new CGMaterial();
	mtl[0]->SetAmbientReflect(0.588f, 0.588f, 0.588f);
	mtl[0]->SetDifusseReflect(0.588f, 0.588f, 0.588f);
	mtl[0]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[0]->SetShininess(10.0f);
	mtl[0]->InitTexture("textures/SlotCarRed.jpg");

	mtl[1] = new CGMaterial();
	mtl[1]->SetAmbientReflect(0.588f, 0.588f, 0.588f);
	mtl[1]->SetDifusseReflect(0.588f, 0.588f, 0.588f);
	mtl[1]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[1]->SetShininess(10.0f);

	pieces[0] = new CGSlotCar_0(mtl[0]);
	pieces[1] = new CGSlotCar_1(mtl[1]);
}

CGSlotCar::~CGSlotCar()
{
	for (int i = 0; i < 2; i++) delete pieces[i];
	delete[] pieces;
	for (int i = 0; i < 2; i++) delete mtl[i];
	delete[] mtl;
}

int CGSlotCar::GetNumPieces()
{
	return 2;
}

CGPiece* CGSlotCar::GetPiece(int index)
{
	return pieces[index];
}

