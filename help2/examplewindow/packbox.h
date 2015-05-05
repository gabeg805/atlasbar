#ifndef GTKMM_EXAMPLE_PACKBOX_H
#define GTKMM_EXAMPLE_PACKBOX_H

#include <gtkmm.h>

class PackBox : public Gtk::HBox
{
public:
  PackBox(bool homogeneous, int spacing, Gtk::PackOptions, int padding = 0);
  virtual ~PackBox();

protected:
  Gtk::Button m_button1, m_button2, m_button3;
  Gtk::Button* m_pbutton4;

  char padstr[80];
};

#endif //GTKMM_EXAMPLE_PACKBOX_H
