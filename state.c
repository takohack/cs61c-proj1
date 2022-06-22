#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake_utils.h"
#include "state.h"

/* Helper function definitions */
static char get_board_at(game_state_t* state, int x, int y);
static void set_board_at(game_state_t* state, int x, int y, char ch);
static bool is_tail(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static int incr_x(char c);
static int incr_y(char c);
static void find_head(game_state_t* state, int snum);
static char next_square(game_state_t* state, int snum);
static void update_tail(game_state_t* state, int snum);
static void update_head(game_state_t* state, int snum);

/* Helper function to get a character from the board (already implemented for you). */
static char get_board_at(game_state_t* state, int x, int y) {
  return state->board[y][x];
}

/* Helper function to set a character on the board (already implemented for you). */
static void set_board_at(game_state_t* state, int x, int y, char ch) {
  // printf("%p\n",state->board[y]);
  state->board[y][x] = ch;
}

/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function.
  game_state_t * ptr = (game_state_t *)malloc(sizeof(game_state_t));
  ptr->x_size = 14;
  ptr->y_size = 10;
  char **board = (char **)malloc(sizeof(char *)*ptr->y_size);
  for(int i = 0;i<ptr->y_size;i++){
    board[i] = (char *)malloc(sizeof(char)*ptr->x_size);
    memset(board[i],32,ptr->x_size);
  }
  ptr->board = board;
  for (int y = 0; y < ptr->y_size; y++) {
    for (int x = 0; x < ptr->x_size; x++) {
      if (x == 0 || y == 0 || x == (ptr->x_size -1) || y == (ptr->y_size - 1)) {
        set_board_at(ptr,x,y,'#');
      }
    }
  }
  set_board_at(ptr,9,2,'*');
  set_board_at(ptr,4,4,'d');
  set_board_at(ptr,5,4,'>');
  ptr->num_snakes = 1;
  snake_t * snake = (snake_t *)malloc(sizeof(snake_t) * ptr->num_snakes);
  snake[0].head_x = 5;
  snake[0].head_y = 4;
  snake[0].tail_x = 4;
  snake[0].tail_y = 4;
  snake->live = true;
  ptr->snakes = snake;
  return ptr;
}

/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function.
  for(int i = 0;i<state->x_size;i++){
    free(state->board[i]);
  }
  free(state->board);
  for(int j = 0;j<state->num_snakes;j++){
    free(state->snakes);
  }
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
  for (int y = 0; y < state->y_size; y++) {
    for (int x = 0; x < state->x_size; x++) {
      fprintf(fp,"%c",state->board[y][x]);
      //printf("%c",state->board[y][x]);
    }
    //printf("\n");
    fprintf(fp,"\n");
  }
  return;
}

/* Saves the current state into filename (already implemented for you). */
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */
static bool is_tail(char c) {
  // TODO: Implement this function.
  return c == 'w' || c == 'a' || c == 's' || c == 'd';
}

static bool is_snake(char c) {
  // TODO: Implement this function.
  if (c == '^' || c == '<' || c == '>' || c == 'v' || c == 'x'){
    return true;
  }else{
    return is_tail(c);
  }
}

static char body_to_tail(char c) {
  if (c == '^'){
    return 'w';
  }else if (c == '<'){
    return 'a';
  }else if (c == 'v'){
    return 's';
  }else if (c == '>'){
    return 'd';
  }else{
    return '?';
  }
}

static int incr_x(char c) {
  if (c == '>' || c == 'd'){
    return 1;
  }else if (c == '<' || c == 'a'){
    return -1;
  }else{
    return 0;
  }
}

static int incr_y(char c) {
  if(c == 'v' || c == 's'){
    return 1;
  }else if (c == '^' || c == 'w'){
    return -1;
  }else{
    return 0;
  }
}

/* Task 4.2 */
static char next_square(game_state_t* state, int snum) {
  // TODO: Implement this function.
  int x = state->snakes[snum].head_x;
  int y = state->snakes[snum].head_y;
  //printf("%c\n",get_board_at(state,x,y));
  x += incr_x(get_board_at(state,x,y));
  y += incr_y(get_board_at(state,x,y));
  return get_board_at(state,x,y);
}

/* Task 4.3 */
static void update_head(game_state_t* state, int snum) {
  // TODO: Implement this function
  int x = state->snakes[snum].head_x;
  int y = state->snakes[snum].head_y;
  //printf("%c\n",get_board_at(state,x,y));
  set_board_at(state,x + incr_x(get_board_at(state,x,y)),
              y + incr_y(get_board_at(state,x,y)),get_board_at(state,x,y));
  state->snakes[snum].head_x += incr_x(get_board_at(state,x,y));
  state->snakes[snum].head_y += incr_y(get_board_at(state,x,y));
  return;
}

/* Task 4.4 */
static void update_tail(game_state_t* state, int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  return;
}

/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  return NULL;
}

/* Task 6.1 */
static void find_head(game_state_t* state, int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  return NULL;
}
