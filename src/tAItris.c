/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Main file
 */

#include <gtk/gtk.h>
#include "utils/random.h"

#include "engine/piece/piece_queue.h"
#include "engine/state.h"
#include "ai/genetic/engine.h"

#include "debug/engine/debug_state.h"

int IA_mode;


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

GtkWidget *window;

static gboolean on_draw_event(GtkWidget* widget, cairo_t *cr, gpointer state)
{
    for (int x = 0; x < 10; x++)
    {
        for(int y = 19; y >= 0; y--)
        {
            switch (state_at(state, x, y)) {
                case CELL_EMPTY:
                break;
                case CELL_BLUE:
                cairo_set_source_rgb(cr, 0, 0, 1);
                cairo_rectangle(cr, x * 30+ 2, 570 - y * 30+ 2, 27, 27);
                break;
                case CELL_CYAN:
                cairo_set_source_rgb(cr, 0, 1, 1);
                cairo_rectangle(cr, x * 30 +2, 570 - y * 30+ 2, 27, 27);
                break;
                case CELL_GREEN:
                cairo_set_source_rgb(cr, 0, 1, 0);
                cairo_rectangle(cr, x * 30+ 2, 570 - y * 30+ 2, 27, 27);
                break;
                case CELL_YELLOW:
                cairo_set_source_rgb(cr, 1, 1, 1);
                cairo_rectangle(cr, x * 30+ 2, 570 - y * 30+ 2, 27, 27);
                break;
                case CELL_RED:
                cairo_set_source_rgb(cr, 1, 0, 0);
                cairo_rectangle(cr, x * 30+ 2, 570 - y * 30+ 2, 27, 27);
                break;
                case CELL_ORANGE:
                cairo_set_source_rgb(cr, 1, 1, 0);
                cairo_rectangle(cr, x * 30+ 2, 570 - y * 30+ 2, 27, 27);
                break;
                case CELL_PURPLE:
                cairo_set_source_rgb(cr, 1, 0, 1);
                cairo_rectangle(cr, x * 30+ 2, 570 - y * 30+ 2, 27, 27);
                break;
            }
            cairo_stroke_preserve(cr);
            cairo_fill(cr);

        }
    }
    return FALSE;
}

static gboolean nextpiece(GtkWidget* widget, cairo_t *cr, gpointer cell)
{
    int array[2][4] = {0,0,0,0,0,0,0,0};
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, 80, 40);
    cairo_fill(cr);
    switch((Cell)cell) {
        case CELL_EMPTY:
        break;
        case CELL_CYAN:
        array[0][0] = 0; array[0][1] = 0;
        array[0][2] = 0; array[0][3] = 0;
        array[1][0] = 1; array[1][1] = 1;
        array[1][2] = 1; array[1][3] = 1;
        cairo_set_source_rgb(cr, 0, 1, 1);
        break;
        case CELL_BLUE:
        array[0][0] = 1; array[0][1] = 0;
        array[0][2] = 0; array[0][3] = 0;
        array[1][0] = 1; array[1][1] = 1;
        array[1][2] = 1; array[1][3] = 0;
        cairo_set_source_rgb(cr, 0, 0, 1);
        break;
        case CELL_GREEN:
        array[0][0] = 0; array[0][1] = 1;
        array[0][2] = 1; array[0][3] = 0;
        array[1][0] = 1; array[1][1] = 1;
        array[1][2] = 0; array[1][3] = 0;
        cairo_set_source_rgb(cr, 0, 1, 0);
        break;
        case CELL_YELLOW:
        array[0][0] = 0; array[0][1] = 1;
        array[0][2] = 1; array[0][3] = 0;
        array[1][0] = 0; array[1][1] = 1;
        array[1][2] = 1; array[1][3] = 0;
        cairo_set_source_rgb(cr, 0, 1, 1);
        break;
        case CELL_PURPLE:
        array[0][0] = 0; array[0][1] = 1;
        array[0][2] = 0; array[0][3] = 0;
        array[1][0] = 1; array[1][1] = 1;
        array[1][2] = 1; array[1][3] = 0;
        cairo_set_source_rgb(cr, 1, 0, 1);
        break;
        case CELL_ORANGE:
        array[0][0] = 0; array[0][1] = 0;
        array[0][2] = 1; array[0][3] = 0;
        array[1][0] = 1; array[1][1] = 1;
        array[1][2] = 1; array[1][3] = 0;
        cairo_set_source_rgb(cr, 1, 0.5, 0.5);
        break;
        case CELL_RED:
        array[0][0] = 1; array[0][1] = 1;
        array[0][2] = 0; array[0][3] = 0;
        array[1][0] = 0; array[1][1] = 1;
        array[1][2] = 1; array[1][3] = 0;
        cairo_set_source_rgb(cr, 1, 0, 0);
        break;
    }
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            if (array[y][x] == 1)
            {
                cairo_rectangle(cr, 20*x, 20*y, 20, 20);
                cairo_stroke_preserve(cr);
                cairo_fill(cr);
            }
        }
    }
    return FALSE;
}

void step(State *state)
{

    g_signal_connect(G_OBJECT(gtk_builder_get_object(p_builder, "DrawGame")), "draw", G_CALLBACK(on_draw_event), state);
    gtk_widget_queue_draw(G_OBJECT(gtk_builder_get_object(p_builder, "DrawGame")));
    g_signal_connect(G_OBJECT(gtk_builder_get_object(p_builder, "NextP")), "draw", G_CALLBACK(nextpiece), (gpointer)(state->next_piece->shape->fill));
    gtk_widget_queue_draw(G_OBJECT(gtk_builder_get_object(p_builder, "NextP")));

    update(state);
    debug_state_print(state);
    state_step(state);
    if (IA_mode == 1)
    {
        Piece *pc = genetic_best(state);
        piece_free(state->current_piece);
        state->current_piece = pc;

        state_apply_input(state, INPUT_HARD_DROP);
    }
}

void stepmanual(State *state)
{

    g_signal_connect(G_OBJECT(gtk_builder_get_object(p_builder, "DrawGame")), "draw", G_CALLBACK(on_draw_event), state);
    gtk_widget_queue_draw(G_OBJECT(gtk_builder_get_object(p_builder, "DrawGame")));
    g_signal_connect(G_OBJECT(gtk_builder_get_object(p_builder, "NextP")), "draw", G_CALLBACK(nextpiece), (gpointer)(state->next_piece->shape->fill));
    gtk_widget_queue_draw(G_OBJECT(gtk_builder_get_object(p_builder, "NextP")));

    update(state);
    debug_state_print(state);
    state_step(state);
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
        gtk_widget_destroy(widget);
        gtk_main_quit();
        break;
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


    debug_state_print(state);

    if (p_builder != NULL)
    {
      gtk_builder_add_from_file (p_builder, "./res/Gamespace.glade", & p_err);

      if (p_err == NULL)
      {

    //pWindow = SDL_CreateWindow("tAItris", SDL_WINDOWPOS_UNDEFINED,
      //                                 SDL_WINDOWPOS_UNDEFINED, 300, 600, SDL_WINDOW_SHOWN);

          GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
              p_builder, "window1"
              );
          gtk_widget_add_events(p_win, GDK_KEY_PRESS_MASK);
          space = gtk_builder_get_object(p_builder, "space");

          g_signal_connect(G_OBJECT (p_win), "key-press-event", G_CALLBACK (on_key_press), state);

          if (IA_mode == 1)
            g_timeout_add(750, step, state);
        else
            g_timeout_add(750, stepmanual, state);

          gtk_widget_show_all (p_win);
          update(state);
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

static void cb_ok (GtkWidget * p_wid, gpointer p_data)
{
    IA_mode = 1;
    gtk_window_close(p_data);
    gtk_widget_destroy(p_wid);
    gtk_main_quit();
    game();
}

static void cb_manual (GtkWidget * p_wid, gpointer p_data)
{
    IA_mode = 0;
    gtk_window_close(p_data);
    gtk_widget_destroy(p_wid);
    gtk_main_quit();
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
                gtk_builder_get_object (p_builder, "manual"),
                "clicked", G_CALLBACK (cb_manual), p_win
                );

            g_signal_connect (
                gtk_builder_get_object (p_builder, "quit"),
                "clicked", G_CALLBACK (gtk_main_quit), NULL
                );

            g_signal_connect(window, "delete_event",
                G_CALLBACK(gtk_main_quit), NULL);


            gtk_widget_show_all (p_win);
            gtk_main();
            gtk_widget_destroy(gtk_builder_get_object (p_builder, "quit"));
            gtk_widget_destroy(gtk_builder_get_object (p_builder, "start"));
            gtk_widget_destroy(p_win);
        }
        else
        {
            g_error ("%s", p_err->message);
            g_error_free (p_err);
        }
    }


    return EXIT_SUCCESS;
}

