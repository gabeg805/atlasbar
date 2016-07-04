/* *****************************************************************************
 * 
 * Name:    atlasfunc.h
 * Type:    <_AtlasFuncType>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Function type.
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
struct _AtlasFuncType
{
    std::string (*info)(void);
    int         (*event)(void*);
    int         (*signal)(uint32_t);
};

/* Namespace extension */
namespace atlas
{
    typedef _AtlasFuncType func_t;
};

#endif /* ATLAS_FUNC_H */
