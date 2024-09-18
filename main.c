#include "backend.h"
#include "frontend.h"
#include <ncurses.h>

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(100); // Set input delay

    // Show the main menu
    show_menu();

    // Initialize the game
    initialize_game();

    // Main game loop
    while (!check_game_over()) {
        handle_input();
        update_game_state();
        render_screen();
    }

    // Show Game Over screen
    display_game_over();

    // End ncurses mode
    endwin();

    return 0;
}
