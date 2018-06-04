/**
 * @file    tAItris.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Main file
 */

#include "utils/random.h"

#include "ui/ui.h"
#include "ui/ui_menu.h"
#include "ai/genetic/candidate.h"
#include "ai/genetic/engine.h"

int main(int argc, char *argv[]) {
    random_init();

    if(argc > 1){
        Candidate * best = learn();
        AiCoefs *c = best->coefs;
        printf("\n\nfitness: %f\nholes: %f\nclears: %f\nbumpiness: %f\nagg_height: %f\n",
               best->fitness,
               c->holes,
               c->clears,
               c->bumpiness,
               c->agg_height);
        genetic_candidate_free(best);
        return 0;
    }

    ui_init(argc, argv);
    ui_menu_init();
    ui_gamespace_init();

    ui_menu_show();
    gtk_main();

    return 0;
}