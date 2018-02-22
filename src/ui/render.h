/**
 * @file    render.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#ifndef TAITRIS_RENDER_H
#define TAITRIS_RENDER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../core/game_state.h"
#include "gui.h"

#define RENDER_FPS 30
#define RENDER_CELL_SIZE 64

void render_handle(SDL_Surface *screen, const struct game_state *gs);

void render_board(SDL_Surface *screen, const struct board *brd);
void render_piece(SDL_Surface *screen, struct piece pc);
void render_next_piece(SDL_Surface *screen, struct piece pc);
void render_score(SDL_Surface *screen, int score);

#endif //TAITRIS_RENDER_H
