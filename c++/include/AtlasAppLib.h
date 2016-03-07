/* *****************************************************************************
 * 
 * Name:    AtlasAppLib.h
 * Class:   None
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas application library.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_APP_LIB_H
#define ATLAS_APP_LIB_H

/* Includes */
#include "AtlasAlignType.h"
#include <stdint.h>
#include <string>

/* Typedefs */
typedef std::string (*AtlasGetFunc)(void);
typedef int         (*AtlasEventFunc)(void*);
typedef int         (*AtlasSignalFunc)(unsigned int);

/* Structure */
struct NameApp {
    std::string             name;
    std::string             type;
    AtlasAlign::AlignType   align;
    unsigned int            length;
    int                     focus;
    AtlasGetFunc            getstr;
    AtlasEventFunc          event;
    AtlasSignalFunc         signal;
    void                   *app;
};

#endif /* ATLAS_APP_LIB_H */
