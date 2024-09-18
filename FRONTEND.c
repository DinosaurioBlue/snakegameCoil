void draw(game_settings_t* game,snake_t*snake){
    CLEAR();//erasing screen
    int i;
    //printing borders
    #ifndef WINDOWS
    for (i = 0; i < game->board_width + 2; i++) {
        mvprintw(0, i, "%C",game->board_char);
        mvprintw(game->board_height + 1, i, "%C",game->board_char);
    }
    for (i = 0; i < game->board_height + 2; i++) {
        mvprintw(i, 0, "%C",game->board_char);
        mvprintw(i, game->board_width + 1, "%C",game->board_char);
    }
    //printing score and life
    mvprintw(game->board_height+4,0,"your score is:%d",game->score);
    mvprintw(game->board_height+5,0,"your lifes are:%d",game->life);

    //printing snake
    mvprintw(snake->pos[0].y,snake->pos[0].x,"%C",game->snake_head);
    for(i=1;i<snake->length;++i){
        mvprintw(snake->pos[i].y,snake->pos[i].x,"%C",game->snake_body);
    }

    //printing fruit
    mvprintw(game->fruit_y, game->fruit_x, "%C", game->fruit_ch);



    #else//windows draw's function
    for (i = 0; i < game->board_width + 2; i++) {
        gotoxy(i, 0);
        printf("%C",);
        gotoxy(i, game->board_height + 1);
        printf("%C",game->board_char);
    }
    for (i = 0; i < game->board_height + 2; i++) {
        gotoxy(0, i);
        printf("%C",game->board_char);
        gotoxy(game->board_width + 1, i);
        printf("%C",game->board_char);
    }

    // Printing score and life
    gotoxy(0, game->board_height + 3);
    printf("Score: %d", game->score);
    gotoxy(0, game->board_height + 4);
    printf("Lives: %d", game->life);

    // Printing snake
    gotoxy(snake->pos[0].x, snake->pos[0].y);
    printf("%C", game->snake_head);
    for(i=1; i<snake->length; ++i){
        gotoxy(snake->pos[i].x, snake->pos[i].y);
        printf("%C", game->snake_body);
    }

    // Printing fruit
    gotoxy(game->fruit_x, game->fruit_y);
    printf("%C",game->fruit_ch);
    #endif
}
