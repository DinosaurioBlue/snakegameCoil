#include "backend.h"
#include <stdlib.h>

// Snake variables
#define WIDTH 20
#define HEIGHT 20
#define SNAKE_MAX_LENGTH 100

typedef struct {
    int x, y;
} Position;

Position snake[SNAKE_MAX_LENGTH];
int snake_length;
Position food;
int direction;  // 0 = up, 1 = right, 2 = down, 3 = left
int game_over;

void initialize_game() {
    // Initialize snake
    snake_length = 3;
    for (int i = 0; i < snake_length; i++) {
        snake[i].x = WIDTH / 2;
        snake[i].y = HEIGHT / 2 + i;
    }

    // Place initial food
    place_food();

    // Initialize direction and game state
    direction = 1;  // Snake starts moving right
    game_over = 0;
}

void place_food() {
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

void update_game_state() {
    // Move the snake by updating the position of each segment
    Position new_head = snake[0];

    if (direction == 0) new_head.y--;
    else if (direction == 1) new_head.x++;
    else if (direction == 2) new_head.y++;
    else if (direction == 3) new_head.x--;

    // Check collisions with walls
    if (new_head.x < 0 || new_head.x >= WIDTH || new_head.y < 0 || new_head.y >= HEIGHT) {
        game_over = 1;
        return;
    }

    // Check collisions with itself
    for (int i = 0; i < snake_length; i++) {
        if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
            game_over = 1;
            return;
        }
    }

    // Move snake's body
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Update the head position
    snake[0] = new_head;

    // Check if the snake has eaten food
    if (snake[0].x == food.x && snake[0].y == food.y) {
        snake_length++;
        increase_score();
        place_food();
    }
}

int check_game_over() {
    return game_over;
}

Position* get_snake() {
    return snake;
}

int get_snake_length() {
    return snake_length;
}

Position get_food() {
    return food;
}
