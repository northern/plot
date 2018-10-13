// https://developer.gnome.org/gtk2/stable/gtk2-Stock-Items.html

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "resource/icon.h"

void on_new(GtkWidget *button, gpointer data)
{
  printf("New..\n");
}

void on_open(GtkWidget *button, gpointer data)
{
  GSList *filenames;
  GtkWidget *dialog;

  dialog = gtk_file_chooser_dialog_new(
    "Open File ...",
    NULL,
    GTK_FILE_CHOOSER_ACTION_OPEN,
    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
    GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
    NULL
  );

  gint result = gtk_dialog_run (GTK_DIALOG (dialog));

  if (result == GTK_RESPONSE_ACCEPT) {
    filenames = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));

    while (filenames != NULL) {
      gchar *file = (gchar*) filenames->data;
      printf("%s was selected.\n", file);
      filenames = filenames->next;
    }
  }

  gtk_widget_destroy(dialog);
}

void on_save(GtkWidget *button, gpointer data)
{
  printf("Save..\n");
}

void on_saveas(GtkWidget *button, gpointer data)
{
  printf("Save as..\n");
}

void on_preferences(GtkWidget *button, gpointer data)
{
  printf("Preferences..\n");
}

void on_undo(GtkWidget *button, gpointer data)
{
  printf("Undo..\n");
}

void on_redo(GtkWidget *button, gpointer data)
{
  printf("Redo..\n");
}

void on_copy(GtkWidget *button, gpointer data)
{
  printf("Copy..\n");
}

void on_cut(GtkWidget *button, gpointer data)
{
  printf("Cut..\n");
}

void on_paste(GtkWidget *button, gpointer data)
{
  printf("Paste..\n");
}

void on_about(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  GdkPixbuf *icon;

  dialog = gtk_about_dialog_new();

  icon = gdk_pixbuf_new_from_inline(-1, image_icon, FALSE, NULL);
  
  gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Plot");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.9"); 
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(c) Reactik");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "For pixel pushing and level plotting.");
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "http://reactik.com/plot");
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), icon);

  g_object_unref(icon);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

GtkWidget* get_filemenu(GtkWidget *window)
{
  GtkWidget
    *menu,
    *menuitem,
    *item
  ;
  GtkAccelGroup *group;

  menu = gtk_menu_new();
  group = gtk_accel_group_new();

  gtk_menu_set_accel_group(GTK_MENU(menu), group);
  gtk_window_add_accel_group(GTK_WINDOW(window), group);

  menuitem = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_new), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_open), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, group);
  //gtk_widget_set_sensitive(item, FALSE);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_save), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_saveas), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu), gtk_separator_menu_item_new());

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_PREFERENCES, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_preferences), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu), gtk_separator_menu_item_new());
  
  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(gtk_main_quit), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  return menuitem;
}

GtkWidget* get_editmenu(GtkWidget *window)
{
  GtkWidget
    *menu,
    *menuitem,
    *item
  ;
  GtkAccelGroup *group;

  menu = gtk_menu_new();
  group = gtk_accel_group_new();

  gtk_menu_set_accel_group(GTK_MENU(menu), group);
  gtk_window_add_accel_group(GTK_WINDOW(window), group);

  menuitem = gtk_menu_item_new_with_label("Edit");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO, group);
  gtk_widget_add_accelerator(item, "activate", group, GDK_Z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_undo), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_REDO, group);
  gtk_widget_add_accelerator(item, "activate", group, GDK_Z, GDK_CONTROL_MASK | GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_redo), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu), gtk_separator_menu_item_new());

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_COPY, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_copy), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_CUT, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_cut), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_PASTE, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_paste), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  return menuitem;
}

GtkWidget* get_helpmenu(GtkWidget *window)
{
  GtkWidget
    *menu,
    *menuitem,
    *item
  ;
  GtkAccelGroup *group;

  menu = gtk_menu_new();
  group = gtk_accel_group_new();

  gtk_menu_set_accel_group(GTK_MENU(menu), group);
  gtk_window_add_accel_group(GTK_WINDOW(window), group);

  menuitem = gtk_menu_item_new_with_label("Help");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);

  item = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, group);
  g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(on_about), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  return menuitem;
}

GtkWidget* get_menubar(GtkWidget *window)
{
  GtkWidget *menubar;

  menubar = gtk_menu_bar_new();

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), get_filemenu(window));
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), get_editmenu(window));
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), get_helpmenu(window));

  return menubar;
}

GtkWidget* get_main_window(gchar *title, gint width, gint height)
{
  GtkWidget *window;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  gtk_window_set_title(GTK_WINDOW(window), title);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  return window;
}

void set_main_window_icon(GtkWidget *window)
{
  GdkPixbuf *icon;

  icon = gdk_pixbuf_new_from_inline(-1, image_icon, FALSE, NULL);
  gtk_window_set_icon(GTK_WINDOW(window), icon);
}

GtkWidget* get_content()
{
  int i;
  const gchar* names[] = { "Andrew", "Joe", "Samantha", "Jonathan" };
  GtkWidget *box;

  box = gtk_hbox_new (TRUE, 5);

  for (i = 0; i < 4; i++) {
    GtkWidget *button = gtk_button_new_with_label(names[i]);

    gtk_box_pack_start_defaults(GTK_BOX(box), button);
  }

  return box;
}

int main(int argc, char *argv[])
{
  GtkWidget
    *window,
    *vbox,
    *pane
  ;

  gtk_init(&argc, &argv);

  window = get_main_window("Plot", 1024, 768);
  set_main_window_icon(window);

  pane = gtk_vpaned_new();

  gtk_paned_pack1(GTK_PANED(pane), get_content(), TRUE, TRUE);
  gtk_paned_pack2(GTK_PANED(pane), get_content(), TRUE, TRUE);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  gtk_box_pack_start(GTK_BOX(vbox), get_menubar(window), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), pane, TRUE, FALSE, 0);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
