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
#ifndef AHOTESCHEME_H
#define AHOTESCHEME_H

#include <vector>

#include <ahote/hsb.h>

namespace ahote
  {

  typedef std::vector<HSB> Colors;

  Colors primary_colors(double saturation=1.0, double brightness=1.0);

  Colors secondary_colors(double saturation=1.0, double brightness=1.0);

  Colors primary_secondary_colors(double saturation=1.0, double brightness=1.0);

  Colors tertiary_colors(double saturation=1.0, double brightness=1.0);

  Colors rgb_color_wheel(unsigned bands=24, double saturation=1.0, double brightness=1.0);

  Colors complements(const HSB& color);

  Colors complements(const Colors& colors);

  Colors split_complements(const HSB& color, double split=24.0);

  Colors split_complements(const Colors& colors, double split=24.0);

  Colors triads(const HSB& color);

  Colors triads(const Colors& colors);

  Colors tetrads(const HSB& color, double offset=-60.0);

  Colors tetrads(const Colors& colors, double offset=-60.0);

  Colors analogous(const HSB& color, unsigned size=3, double offset=-30.0);

  Colors analogous(const Colors& colors, unsigned size=3, double offset=-30.0);

  /** Adjusting the white level (saturation) */
  Colors tints(const HSB& color,
                                  unsigned size=5,
                                  double offset=-0.2,
                                  double start=1.0
                                 );

  Colors tints(const Colors& colors,
               unsigned size=5,
               double offset=-0.2,
               double start=1.0
              );

  /** Adjusting the black level (brightness) */
  Colors shades(const HSB& color,
                                  unsigned size=5,
                                  double offset=-0.2,
                                  double start=1.0
                                 );

  Colors shades(const Colors& colors,
                unsigned size=5,
                double offset=-0.2,
                double start=1.0
               );

  /** Adjusting the gray level (brightness and saturation) */
  Colors tones(const HSB& color,
               unsigned size=5,
               double offset=-0.2,
               double start=1.0
              );

  Colors tones(const Colors& colors,
               unsigned size=5,
               double offset=-0.2,
               double start=1.0
              );

  /** Tints and shades */
  Colors monochromatic(const HSB& color,
                          unsigned size=3,
                          double offset=-0.5,
                          double start=1.0
                         );

  Colors monochromatic(const Colors& colors,
                       unsigned size=3,
                       double offset=-0.5,
                       double start=1.0
                      );


  HSB complement(const HSB& color, double offset);

  HSB hue_offset(const HSB& color, double offset);


}

#endif
