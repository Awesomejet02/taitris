/**
 * @file    ui_menu.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Menu
 */
#include "ui_menu.h"

void ui_menu_init() {
  ui_load_glade(UI_MENU_GLADE);
}

static void cb_start(GtkWidget *widget, gpointer data) {
  gtk_window_close(data);
  gtk_widget_destroy(widget);
  ui_gamespace_show(1);
}

static void cb_manual(GtkWidget *widget, gpointer data) {
  gtk_window_close(data);
  gtk_widget_destroy(widget);
  ui_gamespace_show(0);
}

void ui_menu_show() {
  GtkWidget *win = ui_get_widget("menu");

  g_signal_connect(
      ui_get_object("start"),
      "clicked",
      G_CALLBACK(cb_start),
      win
  );

  g_signal_connect(
      ui_get_object("manual"),
      "clicked",
      G_CALLBACK(cb_manual),
      win
  );

  g_signal_connect(
      ui_get_object("quit"),
      "clicked",
      G_CALLBACK(gtk_main_quit),
      NULL
  );

  gtk_widget_show_all(win);
}