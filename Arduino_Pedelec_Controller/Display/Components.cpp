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

/**
 * List with the customized components
 */

#include "Components.h"

//! Constructor

Components::Components()
{
  g_components[COMP_ID_SEP] = new SeparatorComponent();
  g_components[COMP_ID_ICON] = new IconComponent();
  g_components[COMP_ID_DIAG] = new DiagramComponent("Throttle", VALUE_ID_THROTTLE_POTI, 0, 1023);
  g_components[COMP_ID_BAT_MAH] = new TextComponent("Batterie mAh", VALUE_ID_BATTERY_MAH_USED, 0);
  g_components[COMP_ID_BAT_VOLT] = new TextComponent("Volt", VALUE_ID_BATTERY_VOLTAGE_CURRENT, 1);
  g_components[COMP_ID_ODO_TOTAL] = new TextComponent("Total km", VALUE_ID_ODO_TOTAL, 0);
  g_components[COMP_ID_REMAINING] = new TextComponent("Reichweite", VALUE_ID_REMAINING, 1);
  g_components[COMP_ID_TIME_DRIVEN] = new TextComponent("Fahrzeit", VALUE_ID_TIME_DRIVEN, 2);
  g_components[COMP_ID_VESC_TEMP] = new TextComponent("VESC Temp C", VALUE_ID_VESC_TEMP, 1);
  g_components[COMP_ID_MOTOR_CURRENT] = new TextComponent("Motor Strom", VALUE_ID_MOTOR_CURRENT, 1);
  g_components[COMP_ID_MOTOR_RPM] = new TextComponent("Motor RPM", VALUE_ID_MOTOR_RPM, 0);
  g_components[COMP_ID_THROTTLE_POTI] = new TextComponent("Throttle", VALUE_ID_THROTTLE_POTI, 0);
  g_components[COMP_ID_THROTTLE_WRITE] = new TextComponent("Throttle out", VALUE_ID_THROTTLE_WRITE, 1);
  g_components[COMP_ID_SUPPORT_POTI] = new TextComponent("Support W", VALUE_ID_SUPPORT_POTI, 0);

  int8_t i = 0;
  m_active_components_ids[i++] = COMP_ID_SEP;
  m_active_components_ids[i++] = COMP_ID_ICON;
  m_active_components_ids[i++] = COMP_ID_SEP;
  m_active_components_ids[i++] = COMP_ID_DIAG;
  m_active_components_ids[i++] = COMP_ID_SEP;
  m_active_components_ids[i++] = COMP_ID_BAT_VOLT;
  m_active_components_ids[i++] = COMP_ID_THROTTLE_WRITE;
  m_active_components_ids[i++] = COMP_ID_VESC_TEMP;
  m_active_components_ids[i++] = COMP_ID_SUPPORT_POTI;
  m_active_components_ids[i++] = COMP_ID_MOTOR_RPM;
  updatePositionAndRemoveInvisible();
}

//! Destructor
Components::~Components() {
}

//! Activate / Deactivate children
void Components::deActivateChilren(bool enabled) {
  for (uint8_t i = 0; i < MAX_COMP_ACTIVE; i++) {
    if (m_active_components_ids[i] != COMP_ID_NONE) {
      g_components[m_active_components_ids[i]]->setActive(enabled);
    }
  }
}

//! Update the Y position of all elements, and remove invisible elements from the list
void Components::updatePositionAndRemoveInvisible() {
  uint16_t y = 95;
  uint8_t i = 0;
  for (; i < MAX_COMP_ACTIVE; i++) {
    if (m_active_components_ids[i] == COMP_ID_NONE) {
      continue;
    }
    m_y_top[i] = y;
    g_components[m_active_components_ids[i]]->setY(m_y_top[i]);
    g_components[m_active_components_ids[i]]->setActive(true);
    y += g_components[m_active_components_ids[i]]->getHeight();
    if (y > 320) {
      // Not fully visible, the next will be invisible
      break;
    }
    y += 2;
  }

  for (; i < MAX_COMP_ACTIVE; i++) {
    if (!m_active_components_ids[i] == COMP_ID_SEP || !m_active_components_ids[i==COMP_ID_NONE])
      g_components[m_active_components_ids[i]]->setActive(false);
    m_active_components_ids[i] = COMP_ID_NONE;
  }
}

//! Return the component at position index
BaseComponent* Components::get(uint8_t index) {
  if (index >= MAX_COMP_ACTIVE)
    return NULL;
  if (m_active_components_ids[index] == COMP_ID_NONE)
    return NULL;
  return g_components[m_active_components_ids[index]];
}

uint16_t Components::getY(uint8_t index) {
  return m_y_top[index];
}


//! remove the element at index, but does not delete it
void Components::remove(uint8_t index) {
  if (!m_active_components_ids[index] == COMP_ID_SEP)
    g_components[m_active_components_ids[index]]->setActive(false);

  m_active_components_ids[index] = COMP_ID_NONE;

  updatePositionAndRemoveInvisible();
}

//! Draw all components
void Components::draw(bool repaint) {

  for (uint8_t i = 0; i < MAX_COMP_ACTIVE; i++) {
    if (m_active_components_ids[i] == COMP_ID_NONE) {
      continue;
    }
    g_components[m_active_components_ids[i]]->setY(m_y_top[i]);
    g_components[m_active_components_ids[i]]->draw(repaint);
  }
}
