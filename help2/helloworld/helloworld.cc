#include "helloworld.h"
#include <iostream>
#include <gtkmm.h>

HelloWorld::HelloWorld()
: m_button1("Button 1"),
  m_button2("Button 2")
{
  // This just sets the title of our new window.
  set_title("Hello Buttons!");

  // sets the border width of the window.
  set_border_width(10);

  // put the box into the main window.
  add(m_box1);

  // Now when the button is clicked, we call the "on_button_clicked" function
  // with a pointer to "button 1" as it's argument
  // m_button1.signal_clicked().connect(sigc::bind<Glib::ustring>(
  //             sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1"));

  // instead of gtk_container_add, we pack this button into the invisible
  // box, which has been packed into the window.
  // note that the pack_start default arguments are Gtk::EXPAND | Gtk::FILL, 0
  m_box1.pack_start(m_button1);
  Gtk::Label label;
  // Gtk::EventBox ploob;
  label.set_text("Hi There!");
  label.set_halign(Gtk::ALIGN_START);
  label.set_valign(Gtk::ALIGN_START);
 // label.set_markup("<span background=\"black\" foreground=\"red\">Gin and Tonic</span>");
  // ploob.add(label);
  
  m_box1.pack_start(label, Gtk::PACK_SHRINK);
  
  // always remember this step, this tells GTK that our preparation
  // for this button is complete, and it can be displayed now.
  m_button1.show();
  label.show();
  // ploob.show();
  
  // call the same signal handler with a different argument,
  // passing a pointer to "button 2" instead.
  // m_button2.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
  //             sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 2"));

  // m_box1.pack_start(m_button2);

  // Show the widgets.
  // They will not really be shown until this Window is shown.
  // m_button2.show();
  m_box1.show();
}

// HelloWorld::~HelloWorld()
// {
// }

// Our new improved signal handler.  The data passed to this method is
// printed to stdout.
void HelloWorld::on_button_clicked(Glib::ustring data)
{
  std::cout << "Hello World - " << data << " was pressed" << std::endl;
}
