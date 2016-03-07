/* *****************************************************************************
 * 
 * Name:    AtlasApp.h
 * Class:   <AtlasApp>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas application creater.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_APP_H
#define ATLAS_APP_H

/* Includes */
#include "AtlasAppLib.h"
#include <string>

/* Class */
class AtlasApp
{
public:
    AtlasApp();

    void create(std::string name, AtlasGetFunc getstr);
    void create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event);
    void create(std::string name, AtlasGetFunc getstr, AtlasSignalFunc signal);
    void create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal);

    NameApp *app;
};

#endif /* ATLAS_APP_H */
