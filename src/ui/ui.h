/**
 * @file    ui.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   User interface
 */
#ifndef TAITRIS_UI_H
#define TAITRIS_UI_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <err.h>

void ui_init(int argc, char *argv[]);
GtkBuilder* ui_get_builder();
void ui_load_glade(const gchar *filename);
GObject* ui_get_object(const gchar *name);
GtkWidget* ui_get_widget(const gchar *name);

#endif //TAITRIS_UI_H
