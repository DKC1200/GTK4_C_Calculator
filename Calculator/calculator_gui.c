#include "calculator.h"
#include <stdio.h>

void on_button_clicked(GtkButton *button, gpointer user_data) {
    Calculator *calc = (Calculator *)user_data;
    const char *value = gtk_button_get_label(button);
    
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(calc->entry));
    const char *current_text = gtk_entry_buffer_get_text(buffer);
    
    char *new_text = g_strdup_printf("%s%s", current_text, value);
    gtk_entry_buffer_set_text(buffer, new_text, -1);
    g_free(new_text);
}

void on_del_clicked(GtkButton *button, gpointer user_data) {
    Calculator *calc = (Calculator *)user_data;
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(calc->entry));
    const char *current_text = gtk_entry_buffer_get_text(buffer);
    
    if (current_text && strlen(current_text) > 0) {
        char *new_text = g_strdup(current_text);
        new_text[strlen(new_text) - 1] = '\0';
        gtk_entry_buffer_set_text(buffer, new_text, -1);
        g_free(new_text);
    }
}

void on_equals_clicked(GtkButton *button, gpointer user_data) {
    Calculator *calc = (Calculator *)user_data;
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(calc->entry));
    const char *current_text = gtk_entry_buffer_get_text(buffer);
    
    if (current_text && strlen(current_text) > 0) {
        char *text = g_strdup(current_text);

        if (text[strlen(text) - 1] == '=') {
            text[strlen(text) - 1] = '\0';
            gtk_entry_buffer_set_text(buffer, text, -1);
        }
        
        const char *problem_text = gtk_entry_buffer_get_text(buffer);
        char *result = solve_problem(problem_text);
        gtk_entry_buffer_set_text(buffer, result, -1);
        
        gtk_editable_set_position(GTK_EDITABLE(calc->entry), -1);
        
        g_free(text);
        g_free(result);
    }
}

Calculator* calculator_new(GtkApplication *app) {
    Calculator *calc = g_malloc(sizeof(Calculator));
    
    calc->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(calc->window), "GTK Calculator");
    gtk_window_set_default_size(GTK_WINDOW(calc->window), 250, 350);
    
    calc->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    calc->label = gtk_label_new("Calculator");
    
    calc->entry = gtk_entry_new();

    gtk_widget_set_margin_start(calc->entry, 10);
    gtk_widget_set_margin_end(calc->entry, 10);
    gtk_widget_set_margin_top(calc->entry, 10);
    gtk_widget_set_margin_bottom(calc->entry, 10);

    gtk_entry_set_alignment(GTK_ENTRY(calc->entry), 1.0);
 
    g_signal_connect(calc->entry, "activate", G_CALLBACK(on_equals_clicked), calc);

    calc->grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(calc->grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(calc->grid), 5);

    gtk_widget_set_margin_start(calc->grid, 10);
    gtk_widget_set_margin_end(calc->grid, 10);
    gtk_widget_set_margin_top(calc->grid, 10);
    gtk_widget_set_margin_bottom(calc->grid, 10);
    
    const char *labels[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };
    
    int pos = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            GtkWidget *button = gtk_button_new_with_label(labels[pos]);
            
            if (strcmp(labels[pos], "C") == 0) {
                g_signal_connect(button, "clicked", G_CALLBACK(on_del_clicked), calc);
            }
            else if (strcmp(labels[pos], "=") == 0) {
                g_signal_connect(button, "clicked", G_CALLBACK(on_equals_clicked), calc);
            }
            else {
                g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), calc);
            }
            
            gtk_grid_attach(GTK_GRID(calc->grid), button, col, row, 1, 1);
            pos++;
        }
    }
    
    gtk_window_set_child(GTK_WINDOW(calc->window), calc->box);

    gtk_box_append(GTK_BOX(calc->box), calc->label);
    gtk_box_append(GTK_BOX(calc->box), calc->entry);
    gtk_box_append(GTK_BOX(calc->box), calc->grid);
    
    return calc;
}