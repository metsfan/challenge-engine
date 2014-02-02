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
#ifndef AHOTEUTILITY_H
#define AHOTEUTILITY_H

namespace ahote {

template <typename T>
inline
void get_min_max(T& min, T& max, const T& first, const T& second, const T& third) {
    if (first > second) {
      if (first > third) {
        max = first;
        min = (third>second)?second:third;
      }
      else {
        max = third;
        min = second;
      }
    }
    else {
      if (first < third) {
        min = first;
        max = (third>second)?third:second;
      }
      else {
        min = third;
        max = second;
      }
    }
}

}

#endif

