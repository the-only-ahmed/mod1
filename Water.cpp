/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 18:15:53 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/02/13 18:15:56 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Water.hpp"

Water::~Water() {

/*   for(int y=0; y<_yMax; y++)
      delete this->_MW[y];
   delete[] _MW;*/
}

Water::Water(Vector3 **M, int xMax, int yMax) : _yMax(yMax), _xMax(xMax), _zMax(16), tapMax(300) {

   _MW = new Vector4**[_zMax];
   for(int i=0; i<_zMax; i++)
   {
      _MW[i] = new Vector4*[yMax];
      for(int j=0; j<yMax; j++)
         _MW[i][j] = new Vector4[xMax];
   }

   for(int z=0; z<_zMax; z++)
   {
      for(int y=0; y<yMax; y++)
      {
         for(int x=0; x<xMax; x++)
         {
            int w = 0;
            if (M[y][x].getZ() == z)
               w = 1;
            else if (M[y][x].getZ() > z)
               w = -1;
            _MW[z][y][x] = Vector4(M[y][x].getX(), M[y][x].getY(), z, w);
         }
      }
   }
}

void  Water::MakeFluid() {

   int i =0;
   for(int z=0; z<_zMax-1; z++)
   {
      for(int y=0; y<_yMax; y++)
      {
         for(int x=0; x<_xMax; x++)
         {
            if (_MW[z+1][y][x].getW() == 3)
            {
               if (_MW[z][y][x].getW() == 0)
               {
                  _MW[z+1][y][x].setW(0);
                  _MW[z][y][x].setW(3);
               }
            }
         }
      }
   }
}

void  Water::AddWater() {

   int drop = static_cast<int>(round(sqrt(tapMax)/2));
   int z = _zMax - 1;
   int middle_y = static_cast<int>(round(_yMax/2));
   int middle_x = static_cast<int>(round(_xMax/2));

   for(int y=(middle_y-drop+1); y<(middle_y+drop); y++)
   {
      for(int x=(middle_x-drop); x<=(middle_x+drop); x++)
         _MW[z][y][x].setW(3);
   }
}
