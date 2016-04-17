/* *****************************************************************************
 * 
 * Name:    AtlasFunc.h
 * Class:   None
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas application function data type.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_FUNC_H
#define ATLAS_FUNC_H

/* Includes */
#include <stdint.h>
#include <string>

/* Structure */
struct AtlasFunc
{
    std::string (*info)(void);
    int         (*event)(void*);
    int         (*signal)(uint8_t);
};

#endif /* ATLAS_FUNC_H */
