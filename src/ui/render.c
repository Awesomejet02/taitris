/**
 * @file    render.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "render.h"

void render_handle(SDL_Surface *screen, const struct game_state *gs) {
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 50, 50, 100));

  render_board(screen, gs->board);
  render_piece(screen, gs->piece_current);
  render_next_piece(screen, gs->piece_next);

  SDL_Flip(screen);
}

void render_board(SDL_Surface *screen, const struct board *brd) {
  SDL_Rect rect = {
      0, 0,
      BOARD_WIDTH * RENDER_CELL_SIZE, BOARD_HEIGHT * RENDER_CELL_SIZE
  };

  SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));

  for (size_t y = 0; y < BOARD_HEIGHT; y++) {
    for (size_t x = 0; x < BOARD_WIDTH; x++) {
      int state = board_at(brd, x, y);

      if (state == -1) continue;

      Uint32 color;

      switch (state) {
        case PIECE_I:
          color = SDL_MapRGB(screen->format, 66, 223, 244);
          break;
        case PIECE_O:
          color = SDL_MapRGB(screen->format, 244, 199, 65);
          break;
        case PIECE_T:
          color = SDL_MapRGB(screen->format, 196, 65, 244);
          break;
        case PIECE_L:
          color = SDL_MapRGB(screen->format, 244, 163, 31);
          break;
        case PIECE_J:
          color = SDL_MapRGB(screen->format, 28, 56, 239);
          break;
        case PIECE_Z:
          color = SDL_MapRGB(screen->format, 242, 98, 41);
          break;
        case PIECE_S:
          color = SDL_MapRGB(screen->format, 130, 244, 65);
          break;
        default:
          color = SDL_MapRGB(screen->format, 0, 0, 0);
          break;
      }

      SDL_Rect cell = {
          (Sint16) x * RENDER_CELL_SIZE,
          (Sint16) y * RENDER_CELL_SIZE,
          RENDER_CELL_SIZE,
          RENDER_CELL_SIZE
      };

      SDL_FillRect(screen, &cell, color);
    }
  }
}

void render_piece(SDL_Surface *screen, struct piece pc) {
  for (size_t y = 0; y < PIECE_HEIGHT; y++) {
    for (size_t x = 0; x < PIECE_WIDTH; x++) {
      if (pc.shapes[pc.angle][y][x] == 0) continue;

      Uint32 color;

      switch (pc.id) {
        case PIECE_I:
          color = SDL_MapRGB(screen->format, 66, 223, 244);
          break;
        case PIECE_O:
          color = SDL_MapRGB(screen->format, 244, 199, 65);
          break;
        case PIECE_T:
          color = SDL_MapRGB(screen->format, 196, 65, 244);
          break;
        case PIECE_L:
          color = SDL_MapRGB(screen->format, 244, 163, 31);
          break;
        case PIECE_J:
          color = SDL_MapRGB(screen->format, 28, 56, 239);
          break;
        case PIECE_Z:
          color = SDL_MapRGB(screen->format, 242, 98, 41);
          break;
        case PIECE_S:
          color = SDL_MapRGB(screen->format, 130, 244, 65);
          break;
        default:
          color = SDL_MapRGB(screen->format, 0, 0, 0);
          break;
      }

      SDL_Rect cell = {
          (Sint16) (pc.x + x) * RENDER_CELL_SIZE,
          (Sint16) (pc.y + y) * RENDER_CELL_SIZE,
          RENDER_CELL_SIZE,
          RENDER_CELL_SIZE
      };

      SDL_FillRect(screen, &cell, color);
    }
  }
}

void render_next_piece(SDL_Surface *screen, struct piece pc) {
  SDL_Rect rect = {
      BOARD_WIDTH * RENDER_CELL_SIZE + 20,
      20,
      460,
      460
  };

  SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));

  for (size_t y = 0; y < PIECE_HEIGHT; y++) {
    for (size_t x = 0; x < PIECE_WIDTH; x++) {
      if (pc.shapes[pc.angle][y][x] == 0) continue;

      Uint32 color;

      switch (pc.id) {
        case PIECE_I:
          color = SDL_MapRGB(screen->format, 66, 223, 244);
          break;
        case PIECE_O:
          color = SDL_MapRGB(screen->format, 244, 199, 65);
          break;
        case PIECE_T:
          color = SDL_MapRGB(screen->format, 196, 65, 244);
          break;
        case PIECE_L:
          color = SDL_MapRGB(screen->format, 244, 163, 31);
          break;
        case PIECE_J:
          color = SDL_MapRGB(screen->format, 28, 56, 239);
          break;
        case PIECE_Z:
          color = SDL_MapRGB(screen->format, 242, 98, 41);
          break;
        case PIECE_S:
          color = SDL_MapRGB(screen->format, 130, 244, 65);
          break;
        default:
          color = SDL_MapRGB(screen->format, 0, 0, 0);
          break;
      }

      SDL_Rect cell = {
          rect.x + 50 + (Sint16) x * RENDER_CELL_SIZE,
          rect.y + 50 + (Sint16) y * RENDER_CELL_SIZE,
          RENDER_CELL_SIZE,
          RENDER_CELL_SIZE
      };

      SDL_FillRect(screen, &cell, color);
    }
  }
}