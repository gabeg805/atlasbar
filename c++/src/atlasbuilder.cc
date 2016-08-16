/* *****************************************************************************
 * 
 * Name:    atlasbuilder.cc
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

/* Includes */
#include "atlasbuilder.h"
#include "battery.h"
#include "brightness.h"
#include "date.h"
#include "volume.h"
#include "wifi.h"
#include "workspace.h"

/* ************************************************************************** */
/* */
AtlasBuilder * app_builder(void)
{
    static AtlasBuilder builder[] = {workspaces, date, battery, wifi, volume,
                                     brightness, NULL};
    return builder;
}
