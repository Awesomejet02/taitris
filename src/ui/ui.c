/**
 * @file    ui.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   User interface
 */
#include "ui.h"

void ui_init(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
}

GtkBuilder* ui_get_builder() {
  static GtkBuilder *builder = NULL;

  if (!builder)
    builder = gtk_builder_new();

  if (!builder)
    errx(EXIT_FAILURE, "Can't initialize GtkBuilder.");

  return builder;
}

void ui_load_glade(const gchar *filename) {
  GError *err = NULL;

  GtkBuilder *builder = ui_get_builder();

  gtk_builder_add_from_file(builder, filename, &err);

  if (err)
    errx(EXIT_FAILURE, "Can't load glade file %s", filename);
}

GObject* ui_get_object(const gchar *name) {
  GtkBuilder *builder = ui_get_builder();
  GObject *obj = gtk_builder_get_object(builder, name);

  if (!obj)
    errx(EXIT_FAILURE, "Can't load objet %s", name);

  return obj;
}

GtkWidget* ui_get_widget(const gchar *name) {
  return (GtkWidget*) ui_get_object(name);
}

