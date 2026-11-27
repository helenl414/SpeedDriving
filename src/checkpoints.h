#pragma once
#include "raylib.h"

Model loadCheckpoint();
void drawCheckpoint(Model model, Vector3 position);
bool checkCollision(Vector3 car, Vector3 car_size, Vector3 gem, float yaw);
float dotProduct(Vector3 a, Vector3 b);