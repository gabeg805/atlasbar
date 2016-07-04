/* *****************************************************************************
 * 
 * Name:    atlasuser.h
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas User Application handler.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_USER_H
#define ATLAS_USER_H

/* Includes */
#include "atlastypes.h"
#include <stdint.h>
#include <string>

/* Create user apps */
atlas::uapp_t * create_user_apps(void);

/* Battery */
std::string get_battery_info(void);
int         battery_event(void *event);

/* Wifi */
std::string get_wifi_info(void);
int         wifi_event(void *event);

/* Volume */
std::string get_volume_info(void);
int         volume_event(void *event);
int         volume_signal(uint32_t key);

/* Brightness */
std::string get_brightness_info(void);
int         brightness_event(void *event);
int         brightness_signal(uint32_t key);

/* Date */
std::string get_date_info(void);

/* Workspace */
std::string get_workspace_info(void);
int         workspace_signal(uint32_t key);

#endif /* ATLAS_USER_APP_H */
