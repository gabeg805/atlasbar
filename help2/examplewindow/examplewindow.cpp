#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
{
    win.set_title("Gtk::Box example");
    
    m_Label1.set_text("Gtk::HBox(false, 0);");
    
    m_Label1.set_halign(Gtk::ALIGN_START);
    m_Label1.set_valign(Gtk::ALIGN_START);
    
    m_box1.pack_start(m_Label1, Gtk::PACK_SHRINK);
    win.add(m_box1);
    
    win.show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}
