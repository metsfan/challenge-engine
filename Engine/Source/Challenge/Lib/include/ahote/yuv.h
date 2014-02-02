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
#ifndef AHOTEYUV_H
#define AHOTEYUV_H

namespace ahote {

struct RGB;

  /**
   * A structure containing a YUV value.
   */

struct YUV {
  YUV(double yuv_y=0.0, double yuv_u=0.0, double yuv_v=0.0);

  YUV(const RGB& rgb);

  double y, u, v;

  double operator[](unsigned index);

  YUV& operator=(const RGB& rgb);

  operator RGB();


  };

  void rgb_to_yuv(double rgb_r, double rgb_g, double rgb_b,
                  double& yuv_y, double& yuv_u, double& yuv_v);

  void yuv_to_rgb(double yuv_y, double yuv_u, double yuv_v,
                  double& rgb_r, double& rgb_g, double& rgb_b);


}

#endif
