#include <iostream>
#include "raylib.h"
#include <time.h>
#include <stack>


#define HEIGHT 800
#define WIDTH  1200

#define STICK_WIDTH 3.0f
#define STICK_PADDING 20
#define NUMBER_OF_STICKS WIDTH / (int)STICK_WIDTH

#define SPEED 100

struct Stick {
    float x, y;
    float width, height;
    Color color;
    
    Rectangle GetStick() {
        return Rectangle { x, y + HEIGHT - height, width, height };
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
                      .width = STICK_WIDTH, .height = (float)h, .color = WHITE };
    }
}


void DrawSticks() {
    for(int i = 0; i < NUMBER_OF_STICKS; i++)
        Sticks[i].DrawStick();
}

void BubbleSort(int i, int j) {
    while (!WindowShouldClose()) {
        
        for(int k = 0; k < SPEED; k++) {
            
        if (i < NUMBER_OF_STICKS) {
            Sticks[j].color = BLUE;
            
            if (Sticks[j].height > Sticks[j + 1].height) {
                Sticks[j].color = WHITE;
                Sticks[j + 1].color = BLUE;
                std::swap(Sticks[j].height, Sticks[j + 1].height);
                
            } else {
                Sticks[j].color = WHITE;
            }
            j++;
            if (j >= NUMBER_OF_STICKS - i - 1) {
                Sticks[NUMBER_OF_STICKS - i - 1].color = GREEN;
                j = 0;
                i++;
            }
          }
        }
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        DrawSticks();
            
        EndDrawing();
    }
}

void SelectionSort(int i, int j) {
    int min_id = 0;
    
    while(!WindowShouldClose()) {
        
        if (i < NUMBER_OF_STICKS - 1) {
            
            Sticks[min_id].color = WHITE;
            Sticks[i - 1].color = GREEN;
            
            min_id = i;
            for (int j = i + 1; j < NUMBER_OF_STICKS; j++) {
                if (Sticks[j].height < Sticks[min_id].height) {
                    min_id = j;
                }
                
            }
            Sticks[min_id].color = BLUE;
            std::swap(Sticks[i].height, Sticks[min_id].height);
            i++;

        }
        Sticks[i].color = GREEN;
        Sticks[i - 1].color = GREEN;
            
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        DrawSticks();
        
        EndDrawing();
    }
    
}

int partition(int start, int end) {
    
    int pivot_idx = start - 1;
    
    int pivot = Sticks[end].height;
    
    
    for (int j = start; j < end; j++) {
        if (pivot >= Sticks[j].height) {
            pivot_idx++;
            std::swap(Sticks[j].height, Sticks[pivot_idx].height);
        }
    }
    
    std::swap(Sticks[pivot_idx + 1].height, Sticks[end].height);
        
    
    return pivot_idx + 1;
}

void quickSort(int start, int end) {
    
    if (start >= end) return;
    
    int pivot = partition(start, end);
    
    quickSort(start, pivot - 1);
    quickSort(pivot + 1, end);
}

void quickSortVisualizeResult() {
    while(!WindowShouldClose()) {
        
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        quickSort(0, NUMBER_OF_STICKS - 1);
        DrawSticks();
        
        EndDrawing();
        
    }
}

void quickSortIterative() {
    
    int start = 0;
    int end = NUMBER_OF_STICKS - 1;
    std::stack<int> s;
    s.push(start);
    s.push(end);
    
    int i = 0;
    
    while(!WindowShouldClose()) {
        if (!s.empty()) {
            end = s.top();
            s.pop();
            start = s.top();
            s.pop();
            
            int pivot_idx = partition(start, end);
            
            if (pivot_idx + 1 < end) {
                s.push(pivot_idx + 1);
                s.push(end);
            }
            
            if (pivot_idx - 1 > start) {
                s.push(start);
                s.push(pivot_idx - 1);
                
            }
        
            
        } else {
            Sticks[i++].color = GREEN;
        }
        
        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawSticks();
        
        EndDrawing();
    }
    
}

void merge(int left, int middle, int right) {
    int leftSize = middle - left + 1;
    float A[leftSize];
    
    int rightSize = right - middle;
    float B[rightSize];
    
    for (int i = left; i <= middle; i++)
        A[i - left] = Sticks[i].height;
    
    for (int i = middle + 1; i <= right; i++)
        B[i - middle - 1] = Sticks[i].height;
    
    int i = 0, j = 0;
    int k = left;
    
    while (i < leftSize && j < rightSize) {
        if (A[i] < B[j]) {
            Sticks[k++].height = A[i++];
        } else {
            Sticks[k++].height = B[j++];
        }
    }
    
    while (i < leftSize) {
        Sticks[k++].height = A[i++];
    }
    
    while (j < rightSize) {
        Sticks[k++].height = B[j++];
    }
    
}


void mergeSortIterative() {
    int i = 1, j = 0;
    
    while(!WindowShouldClose()) {
        
        if (i <= NUMBER_OF_STICKS) {
            int l = j;
            int m = j + i - 1;
            int r;
            
            if (j + 2 * i - 1 < NUMBER_OF_STICKS - 1) {
                r = j + 2 * i - 1;
            } else {
                r = NUMBER_OF_STICKS - 1;
            }
            merge(l, m, r);
            
            j += 2 * i;
            
            if (j >= NUMBER_OF_STICKS - i + 1) {
                j = 0;
                i *= 2;
            }

        }
                
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        DrawSticks();
        
        EndDrawing();
    }
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Sorting Visualizer");

    InitSticks();
    
    SetTargetFPS(60);
    
    mergeSortIterative();
    //quickSortIterative();
    //quickSortVisualizeResult();
    //BubbleSort(0, 0);
    //SelectionSort(0, 0);
    CloseWindow();

    return 0;
}
