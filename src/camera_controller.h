#pragma once
#include "raylib.h"

Camera3D cameraController(Vector3 carPosition);
void updateCameraController(Camera3D& camera, Vector3 carPosition, float yaw);