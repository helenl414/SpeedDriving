#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "camera_controller.h"
#include "raylib.h"
#include "car.h"
#include "checkpoints.h"

int main() {
    const int SCREENWIDTH = 1024;
    const int SCREENHEIGHT = 768;
    const int ENDMESSAGEWIDTH = 600;
    const int ENDMESSAGEHEIGHT = 300;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Car Racer");

    float yaw = 0.0f;
    float turn_speed = 1.5f; // radians per second
    float speed = 5.0f;
    int score = 0;
    float time = 0.0f;
    float best_time = INFINITY;
    bool started = false;
    bool new_record = false;

    Vector3 car_position = {0.0f, 1.0f, -25.0f};
    Vector3 car_size = {1.0f, 1.0f, 2.0f};
    Color car_color = PURPLE;

    std::vector<Vector3> gems_position = {
        {0.0f, 1.0f, -20.0f},
        {5.0f, 1.0f, -15.0f},
        {0.0f, 1.0f, -10.0f},
        {-5.0f, 1.0f, -5.0f},
        {-5.0f, 1.0f, 0.0f},
    };
    std::vector<bool> gems_collected = {false, false, false, false, false};

    Camera3D camera = cameraController(car_position);

    Model car = LoadModelFromMesh(GenMeshCube(car_size.x, car_size.y, car_size.z));
    Model gem = loadCheckpoint();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (score == gems_position.size()) {
            started = false;
            if (time < best_time) {
                best_time = time;
                new_record = true;
            }
            if (IsKeyPressed(KEY_R)) {
                gems_collected = {false, false, false, false, false};
                car_position = {0.0f, 1.0f, -25.0f};
                time = 0.0f;
                yaw = 0.0f;
                score = 0;
                new_record = false;
            }
        }
        else {
            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)){
                started = true;
            }
        }

        if (started) {
            time += GetFrameTime();
        }

        updateCameraController(camera, car_position, yaw);

        updateCarPosition(car_position, yaw, speed, turn_speed, GetFrameTime());

        for (int i = 0; i < gems_collected.size(); i++) {
            if (!gems_collected[i]) {
                if (checkCollision(car_position, car_size, gems_position[i], yaw)) {
                    gems_collected[i] = true;
                    score += 1;
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                drawCar(car, car_position, yaw, car_color);
                for (int i = 0; i < gems_position.size(); i++) {
                    if (!gems_collected[i]) {
                        drawCheckpoint(gem, gems_position[i]);
                    }
                }
                DrawGrid(50, 1.0f);
            EndMode3D();

            if (started) {
                DrawText(TextFormat("Time: %.2f", time), 10, 40, 20, DARKGRAY);
            }
            else {
                if (score == gems_position.size()) {
                    DrawRectangle(
                        (SCREENWIDTH - ENDMESSAGEWIDTH) / 2,
                        (SCREENHEIGHT - ENDMESSAGEHEIGHT) / 2,
                        ENDMESSAGEWIDTH,
                        ENDMESSAGEHEIGHT,
                        Fade(SKYBLUE, 0.6f)
                    );
                    if (new_record) {
                        DrawText(
                            "A new record!",
                            (SCREENWIDTH - ENDMESSAGEWIDTH) / 2 + 100,
                            (SCREENHEIGHT - ENDMESSAGEHEIGHT) / 2 + 40,
                            60,
                            DARKGRAY);
                        DrawText(
                            TextFormat("Time: %.2f", time),
                            (SCREENWIDTH - ENDMESSAGEWIDTH) / 2 + 200,
                            (SCREENHEIGHT - ENDMESSAGEHEIGHT) / 2 + 120,
                            40,
                            DARKGRAY);
                        DrawText(
                            "Press R to replay",
                            (SCREENWIDTH - ENDMESSAGEWIDTH) / 2 + 120,
                            (SCREENHEIGHT - ENDMESSAGEHEIGHT) / 2 + 180,
                            40,
                            DARKGRAY);
                    }
                    else {
                        DrawText(
                            "All gems collected!",
                            (SCREENWIDTH - ENDMESSAGEWIDTH) / 2 + 20,
                            (SCREENHEIGHT - ENDMESSAGEHEIGHT) / 2 + 20,
                            60,
                            DARKGRAY);
                        DrawText(
                            TextFormat("Time: %.2f", time),
                            (SCREENWIDTH - ENDMESSAGEWIDTH) / 2 + 160,
                            (SCREENHEIGHT - ENDMESSAGEHEIGHT) / 2 + 100,
                            40,
                            DARKGRAY);
                        DrawText(
                            TextFormat("Best Time: %.2f", best_time),
                            (SCREENWIDTH - ENDMESSAGEWIDTH) / 2 + 160,
                            (SCREENHEIGHT - ENDMESSAGEHEIGHT) / 2 + 140,
                            40,
                            DARKGRAY);
                        DrawText(
                            "Press R to replay",
                            (SCREENWIDTH - ENDMESSAGEWIDTH) / 2 + 120,
                            (SCREENHEIGHT - ENDMESSAGEHEIGHT) / 2 + 200,
                            40,
                            DARKGRAY);
                    }
                }
            }

        EndDrawing();
    }

    UnloadModel(car);
    UnloadModel(gem);

    CloseWindow();
    return 0;
}