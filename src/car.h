#pragma once
#include "raylib.h"

void updateCarPosition(Vector3& carPosition, float& yaw, float speed, float turnSpeed, float dt);
void drawCar(Model& car, Vector3& carPosition, float yaw, Color carColor);
Vector3 getForward(float yaw);
Vector3 getSideway(float yaw);