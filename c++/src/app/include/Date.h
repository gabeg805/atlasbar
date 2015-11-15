/* *****************************************************************************
 * 
 * Name:    Date.h
 * Class:   <Date>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas date application. Displays the current date and time.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_DATE_H
#define ATLAS_DATE_H

/* Includes */
#include "AtlasApp.h"
#include <gtkmm.h>
#include <string>

/* Classes */
class Date:
    public AtlasApp<Gtk::Label>
{
public:
    void               create(void);
    static bool        update(void *w);
    static std::string get_time(void);
};

#endif /* ATLAS_DATE_H */
