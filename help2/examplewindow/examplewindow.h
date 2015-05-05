#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow 
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();
  Gtk::Window win;
  
protected:
  
  //Child widgets:
  Gtk::VBox m_box1;
  Gtk::Label m_Label1;
};

#endif //GTKMM_EXAMPLEWINDOW_H
