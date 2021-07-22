#include "Player.h"
#include <math.h>
#include <stdio.h>

#define PI 3.141592

void Player::DrawLocalAxis()
{
	int axisLength = 5;
	// XYZ˛Ě`ć
	glBegin(GL_LINES);
	{
		Position3D<float> position;
		position = transform->GetPosition();
		float axisMtr[3][4] = {
			{1.0,1.0,0.0,0.0},
			{1.0,0.0,0.0,0.0},
			{0.0,0.0,1.0,0.0}
		};
		glColor3d(1.0, 1.0, 0.0);	// yellow
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, axisMtr[0]);
		glVertex3d(0, 0, 0); glVertex3d(position.x + axisLength, 0, 0);	//x-axis
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, axisMtr[1]);
		glVertex3d(0, 0, 0); glVertex3d(0, position.y + axisLength, 0);	//y-axis
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, axisMtr[2]);
		glVertex3d(0, 0, 0); glVertex3d(0, 0, position.z + axisLength);	//z-axis
	}
	glEnd();
}

// vC[Ěf`ć
void Player::DrawPlayer()
{
	ChangeObjectSize(2);
	glPushMatrix();
	{
		head.Draw(0, 4.575 + 0.5, 0);
		armLeft.Draw(1, 4.175, 0);
		armRight.Draw(-1, 4.175, 0);
		waist.Draw(0, 2.325, 0);
		legLeft.Draw(0.5, 0, 0);
		legRight.Draw(-0.5, 0, 0);
	}
	glPopMatrix();
	glTranslated(0, (2.325 + 1 + 0.25) * size, 0);
	glScaled(1.5 * size, 2 * size, 0.5 * size);
	glutWireCube(1);
}

Player::Player(bool b)
{
	transform = nullptr;
	objSize.depth = objSize.height = objSize.width = 2;
	size = 1;
	myPlayer = b;
}

Player::~Player()
{
	delete transform;
}

void Player::Update()
{
}

void Player::Draw()
{
	Position3D<float> position;
	position = transform->GetPosition();
	RotateAngle3D<float> rotateAngle;
	rotateAngle = transform->GetRotateAngle();

	Vector3D forward;
	forward.x = 1 * sin(rotateAngle.y * PI / 180.0);
	forward.y = 1 * sin(rotateAngle.x * PI / 180.0);
	forward.z = 1 * cos(rotateAngle.y * PI / 180.0);

	if (myPlayer) {
		//camera.SetPosition(position.x - forward.x * 10, position.y + 5, position.z - forward.z * 10);
		//camera.SetViewPosition(position.x + forward.x * 10, position.y + 5, position.z + forward.z * 10);
		camera.SetPosition(position.x - forward.x * 1, position.y + 2, position.z - forward.z * 1);
		camera.SetViewPosition(position.x + forward.x * 10, position.y + 2, position.z + forward.z * 10);
		camera.Draw();
	}
	if (!myPlayer) {
		glPushMatrix();
		{
			glTranslated(position.x, position.y + objSize.height / 2, position.z);
			glRotated(rotateAngle.x, 1, 0, 0);
			glRotated(rotateAngle.y, 0, 1, 0);
			glRotated(rotateAngle.z, 0, 0, 1);
			DrawPlayer();
			DrawLocalAxis();
		}
		glPopMatrix();
	}
}

void Player::SetParentObject(Object& obj)
{
	parent = &obj;
	transform = parent->GetComponent<Transform>();
}

void Player::MoveForward(float dist)
{
	Position3D<float> position;
	position = transform->GetPosition();
	RotateAngle3D<float> angle;
	angle = transform->GetRotateAngle();

	Vector3D forward;

	forward.x = 1 * sin(angle.y * PI / 180.0);
	forward.y = 1 * sin(angle.x * PI / 180.0);
	forward.z = 1 * cos(angle.y * PI / 180.0);

	//printf("x:%f,y:%f,z:%f\n", forward.x, forward.y, forward.z);
	//printf("x:%f,y:%f,z:%f\n", angle.x, angle.y, angle.z);
	//printf("--------------\n");

	position.x += forward.x * dist;
	position.y += 0;
	position.z += forward.z * dist;

	transform->SetPosition(position);
}

void Player::MoveRight(float dist)
{
	Position3D<float> position;
	position = transform->GetPosition();
	RotateAngle3D<float> angle;
	angle = transform->GetRotateAngle();

	Vector3D right;
	right.x = 1 * cos(angle.y * PI / 180.0);

}

void Player::MoveUP(float dist) {
	Position3D<float> position;
	position = transform->GetPosition();
	position.y += dist;
	transform->SetPosition(position);
}

void Player::Rotate(float angle)
{

}

void Player::ChangeObjectSize(int value)
{
	size = value;
	head.ChangeObjSize(size);
	armRight.ChangeObjSize(size);
	armLeft.ChangeObjSize(size);
	waist.ChangeObjSize(size);
	legRight.ChangeObjSize(size);
	legLeft.ChangeObjSize(size);
}
