/*
ILI9341 LCD Display controller for Arduino_Pedelec_Controller

Copyright (C) 2016
Andreas Butti, andreas.b242 at gmail dot com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#pragma once

#include "BaseComponent.h"
#include "TextComponent.h"
#include "DiagramComponent.h"
#include "IconComponent.h"
#include "SeparatorComponent.h"

/**
 * List with the customized components
 */

//! Max. 10 Components on the screen (should be enough, there isn't more space)
#define COMPONENT_COUNT 20
#define MAX_COMP_ACTIVE 10

class BaseComponent;


#define COMP_ID_NONE -1

enum {
    COMP_ID_SEP = 0,
    COMP_ID_ICON,
    COMP_ID_DIAG,
    COMP_ID_BAT_MAH,
    COMP_ID_BAT_VOLT,
    COMP_ID_ODO_TOTAL,
    COMP_ID_REMAINING,
    COMP_ID_TIME_DRIVEN,
    COMP_ID_MOTOR_TEMP,
    COMP_ID_MOTOR_CURRENT,
    COMP_ID_MOTOR_RPM,
    COMP_COUNT};

BaseComponent* PROGMEM g_components[] = {
        new SeparatorComponent(),
        new IconComponent(),
        new DiagramComponent(),
        new TextComponent("Batterie mAh", VALUE_ID_BATTERY_MAH_CURRENT, 0),
        new TextComponent("Volt", VALUE_ID_BATTERY_VOLTAGE_CURRENT, 2),
        new TextComponent("Total km", VALUE_ID_ODO_TOTAL, 0),
        new TextComponent("Reichweite", VALUE_ID_REMAINING, 1),
        new TextComponent("Fahrzeit", VALUE_ID_TIME_DRIVEN, 2),
        new TextComponent("Motor Temperatur C", VALUE_ID_MOTOR_TEMP, 1),
        new TextComponent("Motor Strom", VALUE_ID_MOTOR_CURRENT, 1),
        new TextComponent("Motor RPM", VALUE_ID_MOTOR_RPM, 0),
};

class Components {
    // Constructor / Destructor
public:
    //! Constructor
    Components();

    //! Destructor
    virtual ~Components();

    // public API
public:
    //! Draw all components
    void draw();

    //! Return the component at position index
    BaseComponent* get(uint8_t index);

    //! remove the element at index, but does not delete it
    void remove(uint8_t index);

    //! Activate / Deactivate children
    void deActivateChilren(bool enabled);

private:
    //! Update the Y position of all elements, and remove invisible elements from the list
    void updatePositionAndRemoveInvisible();

    // Member
private:
    //! List with the components

//  BaseComponent* m_components[COMP_COUNT];
    int8_t m_active_components_ids[MAX_COMP_ACTIVE];
};
