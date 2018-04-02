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

GtkWidget *blue;
GtkWidget *lblue;
GtkWidget *red;
GtkWidget *green;
GtkWidget *purple;
GtkWidget *yellow;
GtkWidget *orange;

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
  for(int y = state->board->height - 1; y >= 0; y--) // +108 + 30 * x
  {
    for(int x = state->board->width - 1; x >= 0; x--) // + 30 * y
    {
      switch(board_at(state->board, x, y)){ 
        case CELL_CYAN:
            //gtk_fixed_put(space, lblue, x * 30, y * 30);
            break;
        case CELL_BLUE:
            //gtk_fixed_put(space, blue, x * 30, y * 30);
            break;
        case CELL_RED:
            //gtk_fixed_put(space, red, x * 30, y * 30);
            break;
        case CELL_YELLOW:
            //gtk_fixed_put(space, yellow, x * 30, y * 30);
            break;
        case CELL_ORANGE:
            //gtk_fixed_put(space, orange, x * 30, y * 30);
            break;
        case CELL_GREEN:
            //gtk_fixed_put(space, green, x * 30, y * 30);
            break;
        case CELL_PURPLE:
           //gtk_fixed_put(space, purple, x * 30, y * 30);
            break;
    }
}
}
update(state);
GList *children, *iter;
children = gtk_container_get_children(space);
for(iter = children; iter != NULL; iter = g_list_next(iter))
    gtk_widget_destroy(GTK_WIDGET(iter->data));
g_list_free(children);
state_step(state);
gtk_widget_show_all(window);
debug_state_print(state);
//  Piece *pc = genetic_best(state);
//  piece_free(state->current_piece);
//  state->current_piece = pc;

//  state_apply_input(state, INPUT_HARD_DROP);
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
  
   /* Initialisation de GTK+ */
  gtk_init (NULL, NULL);



  blue = gtk_image_new_from_file("./res/pieces/blue.jpg");
  lblue = gtk_image_new_from_file("./res/pieces/lblue.jpg");
  red = gtk_image_new_from_file("./res/pieces/red.jpg");
  green = gtk_image_new_from_file("./res/pieces/green.jpg");
  purple =  gtk_image_new_from_file("./res/pieces/purple.jpg");
  yellow =  gtk_image_new_from_file("./res/pieces/yellow.jpg");
  orange = gtk_image_new_from_file("./res/pieces/orange.jpg");


   /* Creation d'un nouveau GtkBuilder */
  p_builder = gtk_builder_new ();
  space = gtk_builder_get_object(p_builder, "space");

  update(state);
  

  debug_state_print(state);

  if (p_builder != NULL)
  {
      /* Chargement du XML dans p_builder */
    gtk_builder_add_from_file (p_builder, "./res/Gamespace.glade", & p_err);

    if (p_err == NULL)
    {
       debug_state_print(state);
         /* 1.- Recuparation d'un pointeur sur la fenetre. */
       GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
          p_builder, "window1"
          );
       gtk_widget_add_events(p_win, GDK_KEY_PRESS_MASK);
       space = gtk_builder_get_object(p_builder, "space");

       g_signal_connect(G_OBJECT (p_win), "key-press-event", G_CALLBACK (on_key_press), state);

        g_timeout_add(1000, step, state);

       gtk_widget_show_all (p_win);
       update(state);
       debug_state_print(state);
       gtk_main();

   }
   else
   {
         /* Affichage du message d'erreur de GTK+ */
       g_error ("%s", p_err->message);
       g_error_free (p_err);
   }
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


   /* Initialisation de GTK+ */
   gtk_init (& argc, & argv);




   /* Creation d'un nouveau GtkBuilder */
   p_builder = gtk_builder_new ();


   if (p_builder != NULL)
   {
      /* Chargement du XML dans p_builder */
      gtk_builder_add_from_file (p_builder, "./res/Menu.glade", & p_err);

      if (p_err == NULL)
      {
         /* 1.- Recuparation d'un pointeur sur la fenetre. */
         GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
            p_builder, "window1"
            );


         /* 2.- */
         /* Signal du bouton Ok */
         g_signal_connect (
            gtk_builder_get_object (p_builder, "start"),
            "clicked", G_CALLBACK (cb_ok), p_win
            );

         /* Signal du bouton Annuler */
         g_signal_connect (
            gtk_builder_get_object (p_builder, "quit"),
            "clicked", G_CALLBACK (gtk_main_quit), NULL
            );

         g_signal_connect(window, "delete_event",
            G_CALLBACK(gtk_main_quit), NULL);


         gtk_widget_show_all (p_win);
         gtk_main ();
     }
     else
     {
         /* Affichage du message d'erreur de GTK+ */
         g_error ("%s", p_err->message);
         g_error_free (p_err);
     }
 }


 return EXIT_SUCCESS;
}

