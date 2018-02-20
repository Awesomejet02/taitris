/**
 * @file    gameUI.c
 * @author  S4MasterRace
 * @version 1.0
 * @brief   No description
 */

#include "gameUI.h"

SDL_Surface **load_sprites() {
  SDL_Surface **sp = malloc(7 * sizeof(SDL_Surface *));
  sp[1] = load_image("res/sprites/blue.bmp");
  sp[0] = load_image("res/sprites/cyan.bmp");
  sp[2] = load_image("res/sprites/green.bmp");
  sp[3] = load_image("res/sprites/yellow.bmp");
  sp[4] = load_image("res/sprites/pink.bmp");
  sp[5] = load_image("res/sprites/red.bmp");
  sp[6] = load_image("res/sprites/purple.bmp");
  return sp;
}

SDL_Surface *drawScore(SDL_Surface *screen, int score) {
  SDL_Surface *toBlit = NULL;
  SDL_Rect _score = {20, 20, 0, 0};
  SDL_Rect _text = {35, 35, 0, 0};

  toBlit = SDL_CreateRGBSurface(0, 200, 210, 32, 0, 0, 0, 0);
  SDL_BlitSurface(toBlit, NULL, screen, &_score);
  SDL_FreeSurface(toBlit);

  TTF_Font *font = NULL;
  SDL_Color white_color = {255, 255, 255, 0};
  init_TTF();

  font = load_font("res/font/font.ttf", 40);

  char buffer[128];

  sprintf(buffer, "Score : %d", score);
  toBlit = TTF_RenderText_Blended(font, buffer, white_color);
  SDL_BlitSurface(toBlit, NULL, screen, &_text);
  SDL_FreeSurface(toBlit);

  _text.y += 60;
  sprintf(buffer, "Niveau : 0");
  toBlit = TTF_RenderText_Blended(font, buffer, white_color);
  SDL_BlitSurface(toBlit, NULL, screen, &_text);
  SDL_FreeSurface(toBlit);

  _text.y += 60;
  toBlit = TTF_RenderText_Blended(font, "Ligne(s) : 0", white_color);
  SDL_BlitSurface(toBlit, NULL, screen, &_text);
  SDL_FreeSurface(toBlit);

  SDL_Flip(screen);
  return screen;
}

SDL_Surface *createWindow(SDL_Surface *screen) {
  SDL_Surface *toBlit = NULL;
  SDL_Rect _back = {0, 0, 0, 0};
  SDL_Rect _next = {650, 20, 0, 0};

  toBlit = load_image("res/sprites/game_background.bmp");
  SDL_BlitSurface(toBlit, NULL, screen, &_back);
  SDL_FreeSurface(toBlit);

  toBlit = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
  SDL_BlitSurface(toBlit, NULL, screen, &_next);
  SDL_FreeSurface(toBlit);

  //Text
  TTF_Font *font = NULL;
  SDL_Color white_color = {255, 255, 255, 0};
  init_TTF();

  font = load_font("res/font/font.ttf", 40);

  _next.y += 105;
  _next.x += 17;
  toBlit = TTF_RenderText_Blended(font, "Next", white_color);
  SDL_BlitSurface(toBlit, NULL, screen, &_next);
  SDL_FreeSurface(toBlit);

  SDL_Flip(screen);

  screen = drawScore(screen, 50);

  return screen;
}

SDL_Surface *drawBoard(SDL_Surface *screen, SDL_Rect _board, board *board, SDL_Surface **sp) {
  SDL_Surface *game, *toBlit = NULL;
  //SDL_Rect _board = {355, 20, 0, 0};
  game = SDL_CreateRGBSurface(0, 250, 500, 32, 0, 0, 0, 0);
  SDL_FillRect(game, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(game, NULL, screen, &_board);
  SDL_FreeSurface(game);
  for (size_t i = 0; i < board->w; i++) {
    _board.y = 20;
    for (size_t j = 0; j < board->h; j++) {
      //warnx(j * 10 + i);
      if (board->board_[j * board->w + i] == -1) {
        _board.y += 25;
        continue;
      }

      /*switch (board->board_[j * 10 + i]) {
          case 1:
              toBlit = sp[board->board_[j * 10 + i]];
              break;
          case 2:
              toBlit = sp[board->board_[j * 10 + i]];
              break;
          case 3:
              toBlit = sp[board->board_[j * 10 + i]];
              break;
          case 4:
              toBlit = sp[board->board_[j * 10 + i]];
              break;
          case 5:
              toBlit = sp[board->board_[j * 10 + i]];
              break;
          case 6:
              toBlit = sp[board->board_[j * 10 + i]];
              break;
          default:
              break;
      }*/
      SDL_BlitSurface(sp[board->board_[j * board->w + i]], NULL, screen, &_board);
      _board.y += 25;
    }
    _board.x += 25;
  }
  return screen;
}

SDL_Surface *drawPiece(SDL_Surface *screen, piece *p, SDL_Surface **sp) {
  SDL_Surface *toBlit = NULL;
  SDL_Rect _board;
  _board.x = 355 + 25 * (Sint16) p->x;
  _board.y = 20 + 25 * (Sint16) p->y;
  toBlit = sp[p->id];
  shape *shape_ = p->shapes_[p->c_i];
  for (size_t y = 0; y < shape_->h; y++) {
    _board.x = 355 + 25 * (Sint16) p->x;
    for (size_t x = 0; x < shape_->w; x++) {
      //warnx(j * 10 + i);
      if (shape_->form[y * (shape_->w) + x] == 0) {
        _board.x += 25;
        continue;
      }
      SDL_BlitSurface(toBlit, NULL, screen, &_board);
      _board.x += 25;
    }
    _board.y += 25;
  }

  return screen;
}

SDL_Surface *displayBoard(SDL_Surface *screen, board *board, SDL_Surface **sp) {
  SDL_Rect _board = {355, 20, 0, 0};
  drawBoard(screen, _board, board, sp);
  drawPiece(screen, board->piece_, sp);
  SDL_Flip(screen);
  return screen;
}
