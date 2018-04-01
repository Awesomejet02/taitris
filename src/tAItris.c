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


void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval){
        case GDK_KEY_Down:
         state_apply_input(data, INPUT_HARD_DROP);
         gtk_window_close(widget); break;
        case GDK_KEY_Right:
         state_apply_input(data, INPUT_MOVE_RIGHT);
         printf("right!\n"); break;
        case GDK_KEY_Left: 
         state_apply_input(data, INPUT_MOVE_LEFT);
         printf("left!\n"); break;
        case GDK_KEY_Up:
         state_apply_input(data, INPUT_ROTATE_RIGHT);
         printf("rotation!\n"); break;
    }
}
 
int game()
{
  GtkBuilder  *  p_builder   = NULL;
  GError      *  p_err       = NULL;
 
  random_init();

  unsigned int seed = (unsigned int) time(NULL);
  PieceQueue *q = piece_queue_create(seed);

  State *state = state_create();
  state_init(state, q);

  size_t i = 0;
 
   /* Initialisation de GTK+ */
   gtk_init (NULL, NULL);
 
 
   /* Creation d'un nouveau GtkBuilder */
   p_builder = gtk_builder_new ();
   
 
   if (p_builder != NULL)
   {
      /* Chargement du XML dans p_builder */
      gtk_builder_add_from_file (p_builder, "Gamespace.glade", & p_err);
 
      if (p_err == NULL)
      {
         
         /* 1.- Recuparation d'un pointeur sur la fenetre. */
         GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
            p_builder, "window1"
         );
         gtk_widget_add_events(p_win, GDK_KEY_PRESS_MASK);

         if (!state_step(state))
         {
            G_CALLBACK(gtk_window_close);
            main(NULL, NULL);
         }

         g_signal_connect(G_OBJECT (p_win), "key-press-event", G_CALLBACK (on_key_press), state);

 
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

static void cb_ok (GtkWidget * p_wid, gpointer p_data)
{
   gtk_window_close(p_data);
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
      gtk_builder_add_from_file (p_builder, "Menu.glade", & p_err);
 
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

