#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include "packbox.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow(int which);
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_button_quit_clicked();

  //Child widgets:
  Gtk::Button m_button;
  Gtk::VBox m_box1;
  Gtk::HBox m_boxQuit;
  Gtk::Button m_buttonQuit;

  Gtk::Label m_Label1, m_Label2;

  Gtk::HSeparator m_seperator1, m_seperator2, m_seperator3, m_seperator4, m_seperator5;
};

#endif //GTKMM_EXAMPLEWINDOW_H
