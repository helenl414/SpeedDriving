#include "camera_controller.h"
#include "car.h"

float upward_distance = 3.0;
float backward_distance = 8.0;

Camera3D cameraController(Vector3 carPosition) {
    // Define the camera to look into 3D world
    Camera3D camera = { 0 };
    camera.position = Vector3(carPosition.x, carPosition.y + 0.5, carPosition.z - 0.5);
    camera.target = Vector3(carPosition.x, carPosition.y, carPosition.z);
    camera.up = Vector3(0.0f, 1.0f, 0.0f);
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    return camera;
}

void updateCameraController(Camera3D& camera, Vector3 carPosition, float yaw) {
    Vector3 forward = getForward(yaw);
    camera.position = Vector3(
        carPosition.x - forward.x * backward_distance,
        carPosition.y + upward_distance,
        carPosition.z - forward.z * backward_distance);
    camera.target = Vector3(carPosition.x, carPosition.y + 0.5, carPosition.z - 0.5);
}