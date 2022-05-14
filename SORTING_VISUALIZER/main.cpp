#include <iostream>
#include "raylib.h"
#include <time.h>


#define HEIGHT 800
#define WIDTH  1200

#define STICK_WIDTH 3.0f
#define STICK_PADDING 20

#define NUMBER_OF_STICKS WIDTH / (int)STICK_WIDTH


struct Stick {
    float x, y;
    float width, height;
    Color color;
    
    Rectangle GetStick() {
        return Rectangle { x, y, width, height };
    }
    
    void DrawStick() {
        DrawRectangleRec(GetStick(), color);
    }
};

Stick Sticks[512];

void InitSticks() {
    srand((unsigned int)time(NULL));

    for(int i = 0; i < NUMBER_OF_STICKS; i++) {
        int h = rand() % HEIGHT + STICK_PADDING;
        Sticks[i] = { .x = i * STICK_WIDTH, .y = 0, \
                      .width = STICK_WIDTH, .height = (float)h, .color = WHITE};
    }
}


void DrawSticks() {
    for(int i = 0; i < NUMBER_OF_STICKS; i++)
        Sticks[i].DrawStick();
}
void BubbleSort() {
    for(int i = 0; i < NUMBER_OF_STICKS; i++) {
        for(int j = 0; j < NUMBER_OF_STICKS - i - 1; j++) {
            if (Sticks[j].height > Sticks[j + 1].height) {
                Sticks[j].color = BLUE;
                std::swap(Sticks[j].height, Sticks[j + 1].height);
            }

        }
        Sticks[NUMBER_OF_STICKS - i - 1].color = GREEN;

    }
}


int main(void) {
    int i = 0;
    int j = 0;
    InitWindow(WIDTH, HEIGHT, "Sorting Visualizer");

    InitSticks();
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        
        for(int k = 0; k < 15; k++) {
        if (i < NUMBER_OF_STICKS) {
            if (Sticks[j].height > Sticks[j + 1].height) {
                    std::swap(Sticks[j].height, Sticks[j + 1].height);
                    //Sticks[j + 1].color = BLUE;
                   // Sticks[j].color = WHITE;

                }
            j++;
            if (j >= NUMBER_OF_STICKS) {
                Sticks[NUMBER_OF_STICKS - i - 1].color = GREEN;
                j = 0;
                i++;
            }
        }
        }
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        for(int i = 0; i < NUMBER_OF_STICKS; i++)
            Sticks[i].DrawStick();
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
