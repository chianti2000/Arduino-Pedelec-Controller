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
  m_active_components_ids[0] = COMP_ID_SEP;
  m_active_components_ids[1] = COMP_ID_ICON;
  m_active_components_ids[2] = COMP_ID_SEP;
  m_active_components_ids[3] = COMP_ID_DIAG;
  m_active_components_ids[4] = COMP_ID_SEP;
  m_active_components_ids[5] = COMP_ID_BAT_MAH;
  m_active_components_ids[6] = COMP_ID_ODO_TOTAL;
  m_active_components_ids[7] = COMP_ID_REMAINING;
  m_active_components_ids[8] = COMP_ID_MOTOR_CURRENT;
  m_active_components_ids[9] = COMP_ID_MOTOR_RPM;
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
  return g_components[m_active_components_ids[index]];
}

//! remove the element at index, but does not delete it
void Components::remove(uint8_t index) {
  if (!m_active_components_ids[index] == COMP_ID_SEP)
    g_components[m_active_components_ids[index]]->setActive(false);

  m_active_components_ids[index] = COMP_ID_NONE;

  updatePositionAndRemoveInvisible();
}

//! Draw all components
void Components::draw() {
  uint16_t y = 95;

  for (uint8_t i = 0; i < MAX_COMP_ACTIVE; i++) {
    if (m_active_components_ids[i] == COMP_ID_NONE) {
      continue;
    }
    g_components[m_active_components_ids[i]]->setY(y);
    y += g_components[m_active_components_ids[i]]->getHeight();
    y += 2;
    g_components[m_active_components_ids[i]]->draw();
  }
}
