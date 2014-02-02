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
#ifndef AHOTERYB_H
#define AHOTERYB_H

namespace ahote {

struct RGB;

struct RYB {
  RYB(double r=0.0, double y=0.0, double b=0.0);
  
  RYB(const RGB& rgb);
  
  double red, yellow, blue;
  
  double operator[](unsigned index);

  RYB& operator=(const RGB& rgb);

  operator RGB();


  };

  void rgb_to_ryb(double rgb_r, double rgb_g, double rgb_b,
                  double& ryb_r, double& ryb_y, double& ryb_b);

  void ryb_to_rgb(double ryb_r, double ryb_y, double ryb_b,
                  double& rgb_r, double& rgb_g, double& rgb_b);


}

#endif
