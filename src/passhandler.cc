#include <gtkmm.h>

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
  auto builder = Gtk::Builder::create_from_file("src/window.glade");

  Gtk::Window *pWindow = nullptr;
  builder->get_widget("MainWindow", pWindow);

  return app->run(*pWindow);
}
