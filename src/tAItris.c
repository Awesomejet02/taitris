/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Main file
 */

#include "utils/random.h"

#include "ui/ui.h"
#include "ui/ui_menu.h"

int main(int argc, char *argv[]) {
  random_init();

  ui_init(argc, argv);
  ui_menu_init();
  ui_gamespace_init();

  ui_menu_show();
  gtk_main();

  return 0;
}