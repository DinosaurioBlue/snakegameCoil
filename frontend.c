#include "frontend.h"
#include "backend.h"
#include <ncurses.h>

// Render the game screen
void render_screen() {
    clear();

    // Get the snake and food positions
    Position* snake = get_snake();
    int snake_length = get_snake_length();
    Position food = get_food();

    // Draw the snake
    for (int i = 0; i < snake_length; i++) {
        mvprintw(snake[i].y, snake[i].x, "O");
    }

    // Draw the food
    mvprintw(food.y, food.x, "X");

    // Draw the border
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT - 1, i, "#");
    }
    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH - 1, "#");
    }

    // Show the score
    mvprintw(HEIGHT, 0, "Score: %d", get_score());

    refresh();
}

// Handle user input for snake movement
void handle_input() {
    int ch = getch();

    switch (ch) {
        case KEY_UP:
            if (direction != 2) direction = 0;  // Up
            break;
        case KEY_RIGHT:
            if (direction != 3) direction = 1;  // Right
            break;
        case KEY_DOWN:
            if (direction != 0) direction = 2;  // Down
            break;
        case KEY_LEFT:
            if (direction != 1) direction = 3;  // Left
            break;
    }
}

// Display the game over screen
void display_game_over() {
    clear();
    mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "GAME OVER");
    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 5, "Final Score: %d", get_score());
    refresh();
    getch();  // Wait for user input
}

// Display the menu
void show_menu() {
    clear();
    mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "SNAKE GAME");
    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 5, "Press any key to start");
    refresh();
    getch();  // Wait for user input
}
