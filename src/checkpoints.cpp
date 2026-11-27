#include "checkpoints.h"
#include "car.h"

#include <iostream>
#include <vector>


float inner_radius = 0.3f;
float outer_radius = 0.5f;
float spin_speed = 100.0f;
float spin_angle = 1.0f;
std::vector<Vector3> checkpoints;

Model loadCheckpoint() {
    return LoadModelFromMesh(GenMeshTorus(inner_radius, outer_radius, 16, 32));
}

void drawCheckpoint(Model checkpoint, Vector3 position) {
    spin_angle = spin_speed * GetTime();

    DrawModelEx(
        checkpoint,
        position,
        {0.0f, 1.0f, 0.0f},
        spin_angle,
        {1.0f, 1.0f, 1.0f},
        GREEN
    );
}

bool checkCollision(Vector3 car, Vector3 car_size, Vector3 gem, float yaw) {
    // Find the arrow from the car to checkpoint
    Vector3 rel = {0.0f, 0.0f, 0.0f};
    rel.x = gem.x - car.x;
    rel.z = gem.z - car.z;

    Vector3 forward = getForward(yaw);
    Vector3 sideway = getSideway(yaw);

    float along = abs(dotProduct(rel, forward));
    float across = abs(dotProduct(rel, sideway));

    float along_limit = abs(car_size.x / 2 + outer_radius);
    float across_limit = abs(car_size.z / 2 + outer_radius);

    if (along < along_limit && across < across_limit)
        return true;
    else
        return false;
}

float dotProduct(Vector3 a, Vector3 b) {
    return a.x * b.x + a.z * b.z;
}