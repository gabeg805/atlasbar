#ifndef ATLAS_USER_APP_H
#define ATLAS_USER_APP_H

#include <gdkmm.h>
#include <string>

std::string get_battery_icon(void);
std::string get_wifi_icon(void);
std::string get_volume_icon(void);
std::string get_brightness_icon(void);
std::string get_date_text(void);
bool        wifi_event(void *event);
bool        volume_signal(unsigned int key);
bool        brightness_signal(unsigned int key);

#endif
