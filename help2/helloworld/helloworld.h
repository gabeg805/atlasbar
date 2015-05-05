#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window
{
public:
  HelloWorld();
  /* virtual ~HelloWorld(); */

protected:

  // Signal handlers:
  // Our new improved on_button_clicked(). (see below)
  void on_button_clicked(Glib::ustring data);

  // Child widgets:
  Gtk::HBox m_box1;
  Gtk::Button m_button1, m_button2;
};

#endif // GTKMM_EXAMPLE_HELLOWORLD_H
