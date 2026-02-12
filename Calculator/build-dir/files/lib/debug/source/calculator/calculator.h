#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <gtk/gtk.h>
#include <string.h>

char* solve_problem(const char* problem);

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *entry;
} Calculator;

Calculator* calculator_new(GtkApplication *app);

void on_button_clicked(GtkButton *button, gpointer user_data);
void on_equals_clicked(GtkButton *button, gpointer user_data);
void on_del_clicked(GtkButton *button, gpointer user_data);

#endif