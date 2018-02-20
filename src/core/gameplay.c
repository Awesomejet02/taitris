/**
 * @file    gameplay.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "gameplay.h"

void handleInput(int *proceed, int *x, int *y, int *r) {
  SDL_Event event;
  // Take an event
  while (SDL_PollEvent(&event) != 0) {
    // Switch on event type
    switch (event.type) {
      // Someone pressed a key -> leave the function
      case SDL_QUIT: /* Quit */
        *proceed = 0;
        break;
      case SDL_KEYDOWN: /* Si appui sur une touche */
        switch (event.key.keysym.sym) {
          case SDLK_SPACE: // key_space : launch the recognition
            *r += 1;
            break;
          case SDLK_UP:
            //TODO down bottom
            break;
          case SDLK_DOWN:*y += 1;
            break;
          case SDLK_RIGHT:*x += 1;
            break;
          case SDLK_LEFT:*x -= 1;
            break;
          case SDLK_ESCAPE:*proceed = 0;
            break;
          default: break;
        }
        break;
      default: break;
    }
  }
}

void handleMovement(board *board, piece *p, int *currentScore,
                    int dx, int dy, int dr) {
  if (dy == 1)
    softDrop(currentScore);
  else if (dy > 1)
    hardDrop(currentScore, dy);

  p->c_i += dr;
  if (p->c_i >= p->n)
    p->c_i = 0;
  if (!checkPosition(board, p)) {
    p->c_i -= dr;
    if (p->c_i >= (size_t) -1)
      p->c_i = p->n - 1;
    warnx("position %ld\n", p->c_i);
    //	return;//Can't rotate so return;
  }

  p->x += dx;
  p->y += dy;

  if (!checkPosition(board, p)) {
    p->x -= dx;
    p->y -= dy;
    return;
  }
}

void checkGravity(board *b, piece *p, int *currentScore) {
  static time_t lastTime = -1;
  if (lastTime == -1)
    time(&lastTime);

  shape *shape = p->shapes_[p->c_i];

  double sec = difftime(time(NULL), lastTime);
  //printf("%lf \n", sec);
  if (sec >= 2) {
    //printf("BADDDD");
    p->y += 1;

    if (!checkPosition(b, p)) {
      p->y -= 1;
      fixPosition(b, p);

      size_t nbLine = 0;
      for (size_t y = p->y; y < p->y + shape->w; y++) {
        if (isLineFull(b, y)) {
          nbLine++;
          removeLine(b, y);//TODO opti remove
        }
      }
      computeScore(currentScore, (int) nbLine, (int) b->lvl);
      free(p);
      b->piece_ = init_piece((size_t) getRandom(), 1);
    }
    time(&lastTime);
  }
}

void play(SDL_Surface *screen) {
  board *board = init_board(20, 10, 0);
  board->piece_ = init_piece((size_t) getRandom(), 1);//TODO dynamic x
  int *currentScore = malloc(sizeof(int));
  *currentScore = 0;

  int proceed = 1;
  createWindow(screen);
  SDL_Surface **sp = load_sprites();

  while (proceed) {
    int dx = 0, dy = 0, dr = 0;

    handleInput(&proceed, &dx, &dy, &dr);

    //printf("%d %d %d\n", dx, dy, dr);

    handleMovement(board, board->piece_, currentScore, dx, dy, dr);

    checkGravity(board, board->piece_, currentScore);

    //printf("%ld %ld\n", board->piece_->x, board->piece_->y);

    displayBoard(screen, board, sp);//TODO show piece

    usleep(200);
  }
}