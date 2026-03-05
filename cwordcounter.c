#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

size_t word_count(const char *s) {
  size_t count = 0;
  while(*s) {
    while(isspace((unsigned char)*s)){
      s++;
    }
    if(*s) {
      count++;
      while(*s && !isspace((unsigned char)*s)) {
        s++;
      }
    }
  }
  return count;
}

static void text_updated(GtkTextBuffer *text_buffer, gpointer label) {
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(text_buffer, &start);
    gtk_text_buffer_get_end_iter(text_buffer, &end);
    char *text = gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Word Count: %zu", word_count(text));
    gtk_label_set_text(GTK_LABEL(label), buffer);
    g_free(text);
}

static void activate (GtkApplication* app, gpointer user_data) {
  GtkWidget *window, *vertical_box, *input_box, *status_label, *scrolling_frame;

  window = gtk_application_window_new (app);
  gtk_window_set_title(GTK_WINDOW (window), "VKN's C Word Counter");
  gtk_window_set_default_size(GTK_WINDOW (window), 600, 600);

  vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), vertical_box);

  scrolling_frame = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolling_frame), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start(GTK_BOX(vertical_box), scrolling_frame, TRUE, TRUE, 0);

  input_box = gtk_text_view_new ();
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(input_box), GTK_WRAP_WORD_CHAR);
  gtk_container_add(GTK_CONTAINER(scrolling_frame), input_box);

  status_label = gtk_label_new("Word Count: 0");
  gtk_widget_set_halign(status_label, GTK_ALIGN_START);
  gtk_box_pack_start(GTK_BOX(vertical_box), status_label, FALSE, FALSE, 8);
  
  GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(input_box));
  g_signal_connect(text_buffer, "changed", G_CALLBACK(text_updated), status_label);

  gtk_widget_show_all(window);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  app = gtk_application_new("com.voidkeepernull.wordcounter", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);
}