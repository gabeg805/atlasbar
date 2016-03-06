#ifndef ATLAS_USER_APP_H
#define ATLAS_USER_APP_H

#include <gdkmm.h>
#include <string>

std::string get_battery_icon(void);
std::string get_wifi_icon(void);
std::string get_volume_icon(void);
std::string get_brightness_icon(void);
std::string get_date_text(void);
int         wifi_event(void *event);
int         volume_signal(unsigned int key);
int         brightness_signal(unsigned int key);
std::string get_workspace_text(void);
int         workspace_signal(unsigned int key);

#endif
