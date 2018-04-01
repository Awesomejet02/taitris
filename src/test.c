/*#include <stdlib.h>
#include <gtk/gtk.h>
#include "src/utils/random.h"

#include "src/engine/piece/piece_queue.h"
#include "src/engine/state.h"
#include "src/ai/genetic/engine.h"

#include "src/debug/engine/debug_state.h"
 
 GtkWidget *window, *bg;
 GtkWidget *quit, *start;


void key (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval){
        case GDK_KEY_Down:
         state_apply_input(data, INPUT_HARD_DROP); break;
        case GDK_KEY_Right:
         state_apply_input(data, INPUT_MOVE_RIGHT); break;
        case GDK_KEY_Left: 
         state_apply_input(data, INPUT_MOVE_LEFT); break;
        case GDK_KEY_Up:
         state_apply_input(data, INPUT_ROTATE_RIGHT); break;
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
 
   gtk_init (NULL, NULL);
 
   p_builder = gtk_builder_new ();
   gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
 
   if (p_builder != NULL)
   {   gtk_builder_add_from_file (p_builder, "Gamespace.glade", & p_err);
 
      if (p_err == NULL)
      {
                GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
            p_builder, "window1"
         );

         if (!state_step(state))
         {
            G_CALLBACK(gtk_window_close);
            main(NULL, NULL);
         }

         g_signal_connect(G_OBJECT (window), "keyboard_press", G_CALLBACK (key), state);

 
         gtk_widget_show_all (p_win);
         gtk_main ();
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
   gtk_window_close(p_data);
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
      gtk_builder_add_from_file (p_builder, "Menu.glade", & p_err);
 
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
         gtk_main ();
      }
      else
      {
         g_error ("%s", p_err->message);
         g_error_free (p_err);
      }
   }
 
 
   return EXIT_SUCCESS;
}

*/