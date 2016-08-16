/* *****************************************************************************
 * 
 * Name:    atlasbuilder.h
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The application builder for Atlas. In charge of maintaining all
 *              Atlas application builders.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_BUILDER_H
#define ATLAS_BUILDER_H

/* Includes */
#include "atlasapp.h"

/* Typedefs */
typedef  AtlasApp& (*AtlasBuilder)(void);

/* Public functions */
AtlasBuilder * app_builder(void);

#endif /* ATLAS_BUILDER_H */
