/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Main file
 */

#include <gtk/gtk.h>

#include <SDL_image.h>
#include <SDL2/SDL.h>

#include "utils/random.h"

#include "engine/piece/piece_queue.h"
#include "engine/state.h"
#include "ai/genetic/engine.h"

#include "debug/engine/debug_state.h"

SDL_Surface *blue;
SDL_Surface *lblue;
SDL_Surface *red;
SDL_Surface *green;
SDL_Surface *purple;
SDL_Surface *yellow;
SDL_Surface *orange;

SDL_Window *pWindow = NULL;

GtkBuilder *p_builder;
GtkWidget *space;

/*int main() {
  random_init();

  unsigned int seed = (unsigned int) time(NULL);
  PieceQueue *q = piece_queue_create(seed);

  State *state = state_create();
  state_init(state, q);

  size_t i = 0;

  do {
    //Piece *pc = genetic_best(state);

    //piece_free(state->current_piece);
    //state->current_piece = pc;

    //state_apply_input(state, INPUT_HARD_DROP);

    debug_state_print(state);

    ++i;
  } while (i < 200000 && state_step(state));

  debug_state_print(state);

  //genetic_aicoefs_free(genetic_aicoefs_get());
  state_free(state);
  piece_queue_free(q);

  return 0;
}*/

GtkWidget *window, *bg;
GtkWidget *quit, *start;

void step(State *state)
{
 SDL_Renderer *renderer = NULL;
 SDL_Texture *texture = NULL;

 renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

for (int x = 0; x < 10; x++)
{
    for(int y = 0; y < 20; y++)
    {
        SDL_Rect dest = {y * 30, x * 30, 30, 30};
        switch (state_at(state, x, y)) {
            case CELL_EMPTY:
                break;
            case CELL_BLUE:
                texture = SDL_CreateTextureFromSurface(renderer, blue);
                SDL_RenderCopy(renderer, texture, NULL, &dest);
                break;
            case CELL_CYAN:
                texture = SDL_CreateTextureFromSurface(renderer, lblue);
                SDL_RenderCopy(renderer, texture, NULL, &dest);
                break;
            case CELL_GREEN:
                texture = SDL_CreateTextureFromSurface(renderer, green);
                SDL_RenderCopy(renderer, texture, NULL, &dest);
                break;
            case CELL_YELLOW:
                texture = SDL_CreateTextureFromSurface(renderer, yellow);
                SDL_RenderCopy(renderer, texture, NULL, &dest);
                break;
            case CELL_RED:
                texture = SDL_CreateTextureFromSurface(renderer, red);
                SDL_RenderCopy(renderer, texture, NULL, &dest);
                break;
            case CELL_ORANGE:
                texture = SDL_CreateTextureFromSurface(renderer, orange);
                SDL_RenderCopy(renderer, texture, NULL, &dest);
                break;
            case CELL_PURPLE:
                texture = SDL_CreateTextureFromSurface(renderer, purple);
                SDL_RenderCopy(renderer, texture, NULL, &dest);
                break;
    }
    }
}
// METTRE SCREEN SUR GTK
update(state);
state_step(state);
debug_state_print(state);
//  Piece *pc = genetic_best(state);
//  piece_free(state->current_piece);
//  state->current_piece = pc;

//  state_apply_input(state, INPUT_HARD_DROP);
 SDL_RenderPresent(renderer);
 SDL_DestroyTexture(texture);
 SDL_DestroyRenderer(renderer);
}

static void menu (GtkWidget * p_wid, gpointer p_data)
{
 gtk_window_close(p_data);
 main();
}

void update(State *state)
{
  char temp[20];
  sprintf(temp, "%u", state->score);
  gtk_label_set_text(gtk_builder_get_object(p_builder, "score"), temp);
  sprintf(temp, "%u", state->level);
  gtk_label_set_text(gtk_builder_get_object(p_builder, "lvl"), temp);
  sprintf(temp, "%u", state->broken_lines);
  gtk_label_set_text(gtk_builder_get_object(p_builder, "line"), temp);
}

void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data) {
  switch (event->keyval){
    case GDK_KEY_Down:
    state_apply_input(data, INPUT_HARD_DROP);
    printf("down!\n");
    debug_state_print(data); break;
    case GDK_KEY_Right:
    state_apply_input(data, INPUT_MOVE_RIGHT);
    printf("right!\n"); 
    debug_state_print(data); break;
    case GDK_KEY_Left: 
    state_apply_input(data, INPUT_MOVE_LEFT);
    printf("left!\n");
    debug_state_print(data); break;
    case GDK_KEY_Up:
    state_apply_input(data, INPUT_ROTATE_RIGHT);
    printf("rotation!\n");
    debug_state_print(data); break;
    case GDK_KEY_Escape:
    gtk_main_quit();
    gtk_window_close(widget);
    main(); break;
}
}

int game()
{
  GError      *  p_err       = NULL;
  size_t i = 0;

  random_init();

  unsigned int seed = (unsigned int) time(NULL);
  PieceQueue *q = piece_queue_create(seed);

  State *state = state_create();
  state_init(state, q);
  
  gtk_init (NULL, NULL);

  p_builder = gtk_builder_new ();
  space = gtk_builder_get_object(p_builder, "space");

  update(state);

 IMG_Init(IMG_INIT_JPG);

   blue = IMG_Load("./res/pieces/blue.jpg");
 lblue = IMG_Load("./res/pieces/lblue.jpg");
 green = IMG_Load("./res/pieces/green.jpg");
 red = IMG_Load("./res/pieces/red.jpg");
 purple = IMG_Load("./res/pieces/purple.jpg");
 orange = IMG_Load("./res/pieces/orange.jpg");
 yellow = IMG_Load("./res/pieces/yellow.jpg");


  

  debug_state_print(state);

  if (p_builder != NULL)
  {
      gtk_builder_add_from_file (p_builder, "./res/Gamespace.glade", & p_err);

    if (p_err == NULL)
    {
      debug_state_print(state);

    pWindow = SDL_CreateWindow("tAItris", SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED, 300, 600, SDL_WINDOW_SHOWN);

      GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
          p_builder, "window1"
          );
      gtk_widget_add_events(p_win, GDK_KEY_PRESS_MASK);
      space = gtk_builder_get_object(p_builder, "space");

      g_signal_connect(G_OBJECT (p_win), "key-press-event", G_CALLBACK (on_key_press), state);

      g_timeout_add(200, step, state);

      gtk_widget_show_all (p_win);
      update(state);
      debug_state_print(state);
      gtk_main();


  }
  else
  {

     g_error ("%s", p_err->message);
     g_error_free (p_err);
 }
  SDL_FreeSurface(blue);
 SDL_FreeSurface(lblue);
 SDL_FreeSurface(yellow);
 SDL_FreeSurface(red);
 SDL_FreeSurface(purple);
 SDL_FreeSurface(orange);
 SDL_FreeSurface(green);

      IMG_Quit();
      SDL_Quit();
}


return EXIT_SUCCESS;
}

static void cb_ok (GtkWidget * p_wid, gpointer p_data)
{
 gtk_window_close(p_data);
 gtk_widget_destroy(p_wid);
 game();
}


int main (int argc, char ** argv)
{
 GtkBuilder  *  p_builder   = NULL;
 GError      *  p_err       = NULL;

 gtk_init (& argc, & argv);

 p_builder = gtk_builder_new ();


 if (p_builder != NULL)
 {
  gtk_builder_add_from_file (p_builder, "./res/Menu.glade", & p_err);

  if (p_err == NULL)
  {
   GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
    p_builder, "window1"
    );

   g_signal_connect (
    gtk_builder_get_object (p_builder, "start"),
    "clicked", G_CALLBACK (cb_ok), p_win
    );

   g_signal_connect (
    gtk_builder_get_object (p_builder, "quit"),
    "clicked", G_CALLBACK (gtk_main_quit), NULL
    );

   g_signal_connect(window, "delete_event",
    G_CALLBACK(gtk_main_quit), NULL);


   gtk_widget_show_all (p_win);
   gtk_main();
}
else
{
   g_error ("%s", p_err->message);
   g_error_free (p_err);
}
}


return EXIT_SUCCESS;
}

