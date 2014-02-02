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
#ifndef AHOTEHSB_H
#define AHOTEHSB_H

namespace ahote {

#undef RGB;
struct RGB;

  /**
   * A structure containing a HSB value.
   */

struct HSB {
  HSB(double h=0.0, double s=0.0, double b=0.0);

  HSB(const RGB& rgb);

  double hue, saturation, brightness;

  double operator[](unsigned index);

  HSB& operator=(const RGB& rgb);

  operator RGB();

  };

  void rgb_to_hsb(double rgb_r, double rgb_g, double rgb_b,
                  double& hsb_h, double& hsb_s, double& hsb_b);

  void hsb_to_rgb(double hsb_h, double hsb_s, double hsb_b,
                  double& rgb_r, double& rgb_g, double& rgb_b);


}

#endif
