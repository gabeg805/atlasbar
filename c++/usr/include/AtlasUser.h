/* *****************************************************************************
 * 
 * Name:    AtlasUser.h
 * Class:   None
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
#include "AtlasUserApp.h"
#include <stdint.h>
#include <string>

/* Create user apps */
AtlasUserApp* create_user_apps(void);

/* Battery */
std::string get_battery_icon(void);
int         battery_event(void *event);

/* Wifi */
std::string get_wifi_icon(void);
int         wifi_event(void *event);

/* Volume */
std::string get_volume_icon(void);
int         volume_event(void *event);
int         volume_signal(uint8_t key);

/* Brightness */
std::string get_brightness_icon(void);
int         brightness_event(void *event);
int         brightness_signal(uint8_t key);

/* Date */
std::string get_date_text(void);

/* Workspace */
std::string get_workspace_text(void);
int         workspace_signal(uint8_t key);

#endif /* ATLAS_USER_APP_H */
