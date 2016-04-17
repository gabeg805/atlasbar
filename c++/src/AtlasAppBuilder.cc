/* *****************************************************************************
 * 
 * Name:    AtlasAppBuilder.h
 * Class:   <AtlasAppBuilder>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Application builder. Creates an Atlas App by reading
 *              information in the configuration file.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasAppBuilder.h"
#include "AtlasFunc.h"
#include "AtlasAppUtil.h"
#include "atlasio.h"
#include <string>

/* ************************************************************************** */
/* Constructor */
AtlasAppBuilder::AtlasAppBuilder()
{
    this->app = NULL;
}

/* ************************************************************************** */
/* Create an application (event and signal) */
void AtlasAppBuilder::create(std::string name, AtlasFunc *func)
{
    if ( !AtlasAppUtil::is_app(name) )
        return;
    AtlasAppUtil::new_app(&this->app);
    AtlasAppUtil::set_name(this->app, name);
    AtlasAppUtil::set_func(this->app, func);
    AtlasAppUtil::set_type(this->app);
    AtlasAppUtil::set_length(this->app);
    AtlasAppUtil::set_focus(this->app);
    AtlasAppUtil::set_align(this->app);
    AtlasAppUtil::set_widget(this->app);
    AtlasAppUtil::set_update(this->app);
    atlasio::debug("Created application '"+name+"'.");
}
