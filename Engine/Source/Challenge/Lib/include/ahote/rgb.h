/***************************************************************************
*   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
*   rvinyard@cs.nmsu.edu                                                  *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU Lesser General Public License as        *
*   published by the Free Software Foundation version 2.1.                *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU Lesser General Public      *
*   License along with this library; if not, write to the                 *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
***************************************************************************/
#ifndef AHOTERGB_H
#define AHOTERGB_H

namespace ahote {

typedef enum COLOR_INDEXES {
  RED=0x00,
  GREEN=0x01,
  BLUE=0x02,
  HUE=0x00,
  SATURATION=0x01,
  BRIGHTNESS=0x02,
  LIGHTNESS=0x02,
  ALPHA=0x03
} COLOR_INDEXES;

/**
 * A structure storing an RGB value.
 */
struct RGB {
  RGB(double r=0.0, double g=0.0, double b=0.0);

  double red, green, blue;

  double operator[](unsigned index);

};

}
#endif
