#include "car.h"

#include <cmath>
#include <iostream>

void updateCarPosition(Vector3& carPosition, float& yaw, float speed, float turnSpeed, float dt) {
    // Move car
    if (IsKeyDown(KEY_RIGHT)) yaw -= turnSpeed * dt;
    if (IsKeyDown(KEY_LEFT)) yaw += turnSpeed * dt;

    Vector3 forward = getForward(yaw);

    if (IsKeyDown(KEY_UP)) {
        carPosition.x += forward.x * speed * dt;
        carPosition.z += forward.z * speed * dt;
    }
    if (IsKeyDown(KEY_DOWN)) {
        carPosition.x -= forward.x * speed * dt;
        carPosition.z -= forward.z * speed * dt;
    }
}

void drawCar(Model& car, Vector3& carPosition, float yaw, Color carColor) {
    DrawModelEx(
        car,
        carPosition,
        {0.0f, 1.0f, 0.0f},
        yaw * 180.0 / PI,
        {1.0f, 1.0f, 1.0f},
        carColor
    );
}

Vector3 getForward(float yaw) {
    return  {sinf(yaw), 0, cosf(yaw)};
}

Vector3 getSideway(float yaw) {
    return  {cosf(yaw), 0, -sinf(yaw)};
}

