/**
 * @file    ui_gamespace.c
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Gamespace
 */
#include "ui_gamespace.h"
#include "../engine/state.h"

void ui_gamespace_init() {
    ui_load_glade(UI_GAMESPACE_GLADE);
}

static void cb_quit(GtkWidget *widget, gpointer data) {
    UNUSED(data);
    gtk_widget_destroy(widget);
    gtk_main_quit();
}

static void update(const State *state)
{
    char temp[20];
    sprintf(temp, "%u", state->score);
    gtk_label_set_text(GTK_LABEL(ui_get_object("score")), temp);
    sprintf(temp, "%u", state->level);
    gtk_label_set_text(GTK_LABEL(ui_get_object("lvl")), temp);
    sprintf(temp, "%u", state->broken_lines);
    gtk_label_set_text(GTK_LABEL(ui_get_object("line")), temp);
}

static void stepwithouttime(gpointer ps) {
    State *state = (State *)ps;

    gtk_widget_queue_draw(ui_get_widget("NextP"));

    update(state);
    debug_state_print(state);

    if (state_step(state)) {
        gtk_widget_queue_draw(ui_get_widget("NextP"));
    } else {
        gtk_main_quit();
    }
}

static void on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval){
        case GDK_KEY_space:
            state_apply_input(data, INPUT_HARD_DROP);
            stepwithouttime(data);
            break;
        case GDK_KEY_Down:
            state_apply_input(data, INPUT_SOFT_DROP);
            break;
        case GDK_KEY_Right:
            state_apply_input(data, INPUT_MOVE_RIGHT);
            break;
        case GDK_KEY_Left:
            state_apply_input(data, INPUT_MOVE_LEFT);
            break;
        case GDK_KEY_Up:
            state_apply_input(data, INPUT_ROTATE_RIGHT);
            break;
        case GDK_KEY_Escape:
            cb_quit(widget, widget);
            break;
        default: break;
    }
}

static gboolean on_draw_event(GtkWidget* widget, cairo_t *cr, gpointer ps)
{
    UNUSED(widget);
    State *state = (State *)ps;

    cairo_surface_t *lblue = cairo_image_surface_create_from_png("res/pieces/lblue.png");
    cairo_surface_t *blue = cairo_image_surface_create_from_png("res/pieces/blue.png");
    cairo_surface_t *red = cairo_image_surface_create_from_png("res/pieces/red.png");
    cairo_surface_t *green = cairo_image_surface_create_from_png("res/pieces/green.png");
    cairo_surface_t *purple = cairo_image_surface_create_from_png("res/pieces/purple.png");
    cairo_surface_t *yellow = cairo_image_surface_create_from_png("res/pieces/yellow.png");
    cairo_surface_t *orange = cairo_image_surface_create_from_png("res/pieces/orange.png");
    cairo_surface_t *empty = cairo_image_surface_create_from_png("res/pieces/vide.png");


    for (int x = 0; x < 10; x++)
    {
        for(int y = 19; y >= 0; y--)
        {
            switch (state_at(state, x, y)) {
                case CELL_EMPTY:
                    cairo_set_source_surface(cr, empty, x * 30, 570 - y * 30+ 1);
                    break;
                case CELL_BLUE:
                    cairo_set_source_surface(cr, blue, x * 30, 570 - y * 30+ 1);
                    break;
                case CELL_CYAN:
                    cairo_set_source_surface(cr, lblue, x * 30, 570 - y * 30+ 1);
                    break;
                case CELL_GREEN:
                    cairo_set_source_surface(cr, green, x * 30, 570 - y * 30+ 1);
                    break;
                case CELL_YELLOW:
                    cairo_set_source_surface(cr, yellow, x * 30, 570 - y * 30+ 1);
                    break;
                case CELL_RED:
                    cairo_set_source_surface(cr, red, x * 30, 570 - y * 30+ 1);
                    break;
                case CELL_ORANGE:
                    cairo_set_source_surface(cr, orange, x * 30, 570 - y * 30+ 1);
                    break;
                case CELL_PURPLE:
                    cairo_set_source_surface(cr, purple, x * 30, 570 - y * 30+ 1);
                    break;
            }
            cairo_paint_with_alpha (cr, 1);

        }
    }
    return FALSE;
}

static gboolean nextpiece(GtkWidget* widget, cairo_t *cr, gpointer ps)
{
    UNUSED(widget);
    State *state = (State *)ps;

    int array[2][4] = {
            {0,0,0,0},
            {0,0,0,0}
    };

    // cairo_set_source_rgb(cr, 0, 0, 0);
    // cairo_rectangle(cr, 0, 0, 85, 45);
    // cairo_fill(cr);
    switch((Cell)state->next_piece->shape->fill) {
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
            cairo_set_source_rgb(cr, 1, 1, 0);
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
            cairo_set_source_rgb(cr, 1, 0.5, 0.25);
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

static int redraw(gpointer ps) {
    State *state = (State *)ps;
    UNUSED(state);
    gtk_widget_queue_draw(ui_get_widget("DrawGame"));
    return 1;
}

static int step(gpointer ps) {
    State *state = (State *)ps;

    gtk_widget_queue_draw(ui_get_widget("NextP"));

    update(state);
    debug_state_print(state);

    //TODO call co genetic_best(state) ui_gamespace.c
    AiCoefs *coefs = genetic_aicoefs_get();
    Piece *pc = genetic_best(state, coefs);
    Input next_input = delta_piece(state->current_piece, pc);
    piece_free(pc);

    state_apply_input(state, next_input);

    int interval = 100;
    interval -= 20 * state->level;
    interval = interval < 1 ? 1 : interval;

    if (state_step(state)) {
        gtk_widget_queue_draw(ui_get_widget("NextP"));
        g_timeout_add((guint)interval, step, ps);
    } else {
        gtk_main_quit();
    }

    return 0;
}

static int stepmanual(gpointer ps) {
    State *state = (State *)ps;

    gtk_widget_queue_draw(ui_get_widget("NextP"));

    update(state);
    debug_state_print(state);

    int interval = 750;
    interval -= 20 * state->level;
    interval = interval < 1 ? 1 : interval;

    if (state_step(state)) {
        gtk_widget_queue_draw(ui_get_widget("NextP"));
        g_timeout_add((guint)interval, stepmanual, ps);
    } else {
        gtk_main_quit();
    }

    return 0;
}

void game(GtkWidget *win, int mode) {
    unsigned int seed = (unsigned int) time(NULL);
    PieceQueue *q = piece_queue_create(seed);

    State *state = state_create();
    state_init(state, q);


    update(state);

    g_signal_connect(
            ui_get_object("DrawGame"),
            "draw",
            G_CALLBACK(on_draw_event),
            state
    );

    g_signal_connect(
            ui_get_object("NextP"),
            "draw",
            G_CALLBACK(nextpiece),
            state
    );

    if (mode == 0) {
        g_signal_connect(
                G_OBJECT(win),
                "key-press-event",
                G_CALLBACK(on_key_press),
                state
        );

        g_timeout_add(750, stepmanual, state);
    } else {
        g_timeout_add(400, step, state);
    }

    g_timeout_add(50, redraw, state);
}

void ui_gamespace_show(int mode) {
    GtkWidget *win = ui_get_widget("gamespace");

    gtk_widget_add_events(win, GDK_KEY_PRESS_MASK);

    g_signal_connect(
            win,
            "delete-event",
            G_CALLBACK(cb_quit),
            NULL
    );

    gtk_widget_show_all(win);
    game(win, mode);
}
