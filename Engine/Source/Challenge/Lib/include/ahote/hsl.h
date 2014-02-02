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
#ifndef AHOTEHSL_H
#define AHOTEHSL_H

namespace ahote
  {

#undef RGB;

  struct RGB;

  /**
   * A structure containing a HSL value.
   */
  struct HSL
    {
      HSL(double h=0.0, double s=0.0, double l=0.0);

      HSL(const RGB& rgb);

      double hue, saturation, lightness;

      double operator[](unsigned index);

      HSL& operator=(const RGB& rgb);

      operator RGB();

    };

    /**
     * Convert RGB color to HSL
     * Given r,g,b, each in [0,1], returns h in [0,360]; s and l in [0,1].
     */
    void rgb_to_hsl(double rgb_r, double rgb_g, double rgb_b,
                  double& h, double& s, double& l);

    /**
     * Convert HSL color to RGB
     * Given h in [0,360]; s and l in [0,1], returns r,g,b each in [0,1].
     */
    void hsl_to_rgb(double hsl_h, double hsl_s, double hsl_l,
                    double& rgb_r, double& rgb_g, double& rgb_b);

}

#endif
