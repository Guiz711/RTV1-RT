/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:46:20 by achambon          #+#    #+#             */
/*   Updated: 2018/03/14 17:46:23 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

gchar *file_selected(GtkFileChooser *file_btn)
{
    gchar *file_name;
    GtkBuilder  *builder;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
    gtk_builder_connect_signals(builder, NULL);
    file_name = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(file_btn));
    g_object_unref(builder); 
    printf("RT launched with following path : %s\n", (char*)file_name);
    mainfileselect((char*)file_name);
    return (file_name);
}

void add_objectmenu()
{
    GtkBuilder      *builder; 
    GtkWidget       *win;
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
    win = GTK_WIDGET(gtk_builder_get_object(builder, "object_menu"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder); 
    gtk_widget_show(win);                
    // gtk_main();
 }

void apply_settings(t_ui *ui)
{
    GtkBuilder  *builder;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
    gtk_builder_connect_signals(builder, "appliquer_settings");
    printf("%d\n", ui->gtk.win_height);
    // printf("%d\n", uitest.largeur);
    // printf("%d\n", uitest.pixilation);
    g_object_unref(builder);    
}

void add_scenemenu()
{
    GtkBuilder      *builder; 
    GtkWidget       *win;
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
    win = GTK_WIDGET(gtk_builder_get_object(builder, "scene_menu"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(win);                
    // gtk_main();
}

void on_window_main_destroy()
{
    gtk_main_quit();
}

void add_settingsmenu()
{
	GtkBuilder      *builder; 
    GtkWidget       *win;
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
 
    win = GTK_WIDGET(gtk_builder_get_object(builder, "settings_menu"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder); 
    gtk_widget_show(win);                
    // gtk_main();
    
}
void    wheight_changed(GtkEntry *uiw_height, t_ui *ui)
{
    GtkBuilder  *builder;
    int         wheight;
    // ui = NULL;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
    gtk_builder_connect_signals(builder, "uiw_height");
    wheight = atoi(gtk_entry_get_text(GTK_ENTRY(uiw_height)));
    ui->gtk.win_height = wheight;
    printf("%d\n", wheight);
    printf("%d\n", ui->gtk.win_height);
    g_object_unref(builder); 
}

void wwidth_changed(GtkEntry *uiw_width)
{
    GtkBuilder  *builder;
    const gchar *wwidth;
    t_ui ui;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
    gtk_builder_connect_signals(builder, "uiw_width");
    wwidth = gtk_entry_get_text(GTK_ENTRY(uiw_width));
    ui.largeur = atoi(wwidth);
    printf("%s\n", wwidth);
    printf("%d\n", ui.largeur);
    g_object_unref(builder); 
}

void pxlval_changed(GtkEntry *uipxl_val)
{
    GtkBuilder  *builder;
    const gchar *pxlval;
    t_ui ui;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
    gtk_builder_connect_signals(builder, "uipxl_val");
    pxlval = gtk_entry_get_text(GTK_ENTRY(uipxl_val));
    ui.pixilation = atoi(pxlval);
    printf("%s\n", pxlval);
    printf("%d\n", ui.pixilation);
    g_object_unref(builder); 
}
