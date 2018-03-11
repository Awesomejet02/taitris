/**
 * @file    debug_state.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Debug state
 */
#include "debug_state.h"
#include "../../engine/state.h"
#include "../../engine/piece/piece.h"
#include "../../engine/piece/piece_shape.h"

void debug_state_print_line_number(const Board *brd, int y) {
  printf(ANSI_RESET);

  if (board_is_line_complete(brd, y))
    printf(ANSI_FG_GREEN);

  printf("%2d", y);

  printf(ANSI_RESET);
}

void debug_state_print_cell(Cell c) {
  printf(ANSI_RESET);

  switch (c) {
    case CELL_CYAN:
      printf(ANSI_BG_CYAN); break;
    case CELL_YELLOW:
      printf(ANSI_BG_BYELLOW); break;
    case CELL_PURPLE:
      printf(ANSI_BG_MAGENTA); break;
    case CELL_GREEN:
      printf(ANSI_BG_GREEN); break;
    case CELL_RED:
      printf(ANSI_BG_RED); break;
    case CELL_BLUE:
      printf(ANSI_BG_BLUE); break;
    case CELL_ORANGE:
      printf(ANSI_BG_YELLOW); break;
    default: break;
  }

  printf("  ");

  printf(ANSI_RESET);
}

void debug_state_print_infos(const State *state, int y) {
  printf(ANSI_RESET);

  switch (y) {
    case 0:
      printf("Score: " ANSI_BOLD "%u", state->score); break;
    case 1:
      printf("Level: " ANSI_BOLD "%u", state->level); break;
    case 2:
      printf("Broken lines: " ANSI_BOLD "%u", state->broken_lines); break;
    case 3:
      printf("Step: " ANSI_BOLD "%u", state->step); break;
    case 4:
      printf("Input counts: " ANSI_BOLD "%u", state->input_counts); break;
    default: break;
  }

  printf(ANSI_RESET);
}

void debug_state_print_next_piece(const Piece *pc, int y) {
  printf(ANSI_RESET);

  if (y == 0)
    printf("Next piece:");

  if (y == 1 || y == (PIECE_SHAPE_HEIGHT + 2)) {
    printf("+-");
    for (int x = 0; x < PIECE_SHAPE_WIDTH; x++)
      printf("--");
    printf("-+");
  }

  if (y > 1 && y < (PIECE_SHAPE_HEIGHT + 2)) {
    printf("| ");

    for (int x = 0; x < PIECE_SHAPE_WIDTH; x++) {
      Cell c = CELL_EMPTY;

      if (pc->shape->shape[pc->angle][y - 2][x])
        c = pc->shape->fill;

      debug_state_print_cell(c);
    }

    printf(" |");
  }

  printf(ANSI_RESET);
}

int debug_state_print_current_piece(const Piece *pc, int x, int y) {
  x -= pc->x;
  y = pc->y - y;

  if (x >= 0 && x < PIECE_SHAPE_WIDTH && y >= 0 && y < PIECE_SHAPE_HEIGHT &&
      pc->shape->shape[pc->angle][y][x]) {
    debug_state_print_cell(pc->shape->fill);
    return 1;
  }

  return 0;
}

void debug_state_print(const State *state) {
  printf(DEBUG_STATE_TAG "Printing state ");

  if (state == NULL) {
    printf(ANSI_BOLD ANSI_FG_RED "NULL" ANSI_RESET "\n");
    return;
  }
  else {
    printf(ANSI_BOLD "%p" ANSI_RESET "\n", state);
  }

  printf("\n");

  const Board *brd = state->board;

  for (int y = board_reverse_y(brd, 0); y >= 0; y--) {
    printf(" ");

    debug_state_print_line_number(brd, y);

    printf(" |");

    for (int x = 0; x < brd->width; x++) {
      if (!debug_state_print_current_piece(state->current_piece, x, y)) {
        Cell c = board_at(brd, x, y);
        debug_state_print_cell(c);
      }
    }

    printf("| ");

    debug_state_print_next_piece(state->next_piece, board_reverse_y(brd, y));
    debug_state_print_infos(state, board_reverse_y(brd, y + 8));

    printf("\n");
  }

  printf("    +");
  for (int x = 0; x < brd->width; x++)
    printf("--");
  printf("+");

  printf("\n");

  printf("     ");
  for (int x = 0; x < brd->width; x++)
    printf("%2d", x);

  printf("\n");
  printf("\n");
}