#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <openssl/sha.h>

typedef struct data_fields{
  GtkEntry *entry_base;
  GtkEntry *entry_secret;
}data_fields;

static void print_pass(GtkWidget *widget, gpointer data)
{
  int size;
  const gchar *base, *secret;
  data_fields *entry = data;
  unsigned char *hash, *prehash, *hashstr;

  hash = malloc(SHA_DIGEST_LENGTH);
  hashstr = malloc(SHA_DIGEST_LENGTH*2+1);
  base = gtk_entry_get_text(entry->entry_base);
  secret = gtk_entry_get_text(entry->entry_secret);
  size = strlen(base) + strlen(secret);
  prehash = malloc(size);

  sprintf(prehash, "%s%s", base, secret);
  SHA1(prehash, sizeof(prehash)-1, hash);
  for (size_t i = 0; i < SHA_DIGEST_LENGTH; i++) {
    sprintf((hashstr+i*2), "%02X", hash[i]);
  }
  hashstr[40]=0;
  g_print("Password: %s\n", hashstr);

  // free(hashstr);
  // free(prehash);
  // free(hash);
}
static void activate(GtkApplication* app, gpointer user_data)
{
  data_fields *fd;
  GtkWidget *window, *button, *box, *entry_base, *entry_secret;
  GtkEntryBuffer *buffer_base, *buffer_secret;
  fd = malloc(sizeof(data_fields));

  window = gtk_application_window_new (app);
  button = gtk_button_new_with_label("Compute password");
  box = gtk_list_box_new();
  buffer_base = gtk_entry_buffer_new("Base (hostname)", 16);
  buffer_secret = gtk_entry_buffer_new("Secret key", 11);
  entry_base = gtk_entry_new_with_buffer(buffer_base);
  entry_secret = gtk_entry_new_with_buffer(buffer_secret);

  fd->entry_base = GTK_ENTRY(entry_base);
  fd->entry_secret = GTK_ENTRY(entry_secret);

  gtk_window_set_title (GTK_WINDOW (window), "Password Handler");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_list_box_prepend(GTK_LIST_BOX(box), button);
  gtk_list_box_prepend(GTK_LIST_BOX(box), entry_secret);
  gtk_list_box_prepend(GTK_LIST_BOX(box), entry_base);
  g_signal_connect(button, "clicked", G_CALLBACK(print_pass), fd);
  gtk_widget_show_all (window);
  //free(fd);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.suzukilab.passwordhandler", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}
