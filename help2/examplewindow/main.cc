#include <iostream>
#include <cstdlib>
#include <gtkmm/main.h>
#include "examplewindow.h"

using std::atoi;

int main(int argc, char *argv[])
{
  Gtk::Main main_instance(argc, argv);

  if(argc != 2)
  {
    std::cerr << "usage: packbox num, where num is 1, 2, or 3." << std::endl;
    return 1;
  }

  ExampleWindow window;
  Gtk::Main::run(window.win); //Shows the window and returns when it is closed.

  return 0;
}
