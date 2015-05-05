#include "packbox.h"
#include <cstdio> //For sprintf().

PackBox::PackBox(bool homogeneous, int spacing, Gtk::PackOptions options,
        int padding) :
  Gtk::HBox(homogeneous, spacing),
  m_button1("box.pack_start("),
  m_button2("button,"),
  m_button3((options == Gtk::PACK_SHRINK) ? "Gtk::PACK_SHRINK" :
            ((options == Gtk::PACK_EXPAND_PADDING) ?
             "Gtk::PACK_EXPAND_PADDING" : "Gtk::PACK_EXPAND_WIDGET"))
{
  pack_start(m_button1, options, padding);
  pack_start(m_button2, options, padding);
  pack_start(m_button3, options, padding);

  sprintf(padstr, "%d);", padding);

  m_pbutton4 = new Gtk::Button(padstr);
  pack_start(*m_pbutton4, options, padding);
}

PackBox::~PackBox()
{
  delete m_pbutton4;
}
