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
   for(int z=0; z<_zMax; z++)
   {
      for(int y=0; y<_yMax; y++)
      {
         for(int x=0; x<_xMax; x++)
         {
            /*if (_MW[z+1][y][x].getW() == 3)
            {
               if (_MW[z][y][x].getW() == 0)
               {
                  _MW[z+1][y][x].setW(0);
                  _MW[z][y][x].setW(3);
               }
            }*/
            if (_MW[z][y][x].getW() == 3)
               checkWeight(x, y, z);
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

int   Water::maxWeight(int *w, int size) {

   int max = w[0];
   int pos = 0;
   for(int i=1; i<size; i++)
   {
      if (max < w[i])
      {
         max = w[i];
         pos = i;
      }
   }
   return pos;
}

void  Water::checkWeight(int x, int y, int z) {

   if (z>0 && _MW[z-1][y][x].getW() == 0)
   {
         _MW[z-1][y][x].setW(3);
         _MW[z][y][x].setW(0);
   }
   else
   {
      int   w[8];
      w[0] = getWeight(x-1, y, z);
      w[1] = getWeight(x-1, y-1, z);
      w[2] = getWeight(x-1, y+1, z);
      w[3] = getWeight(x+1, y+1, z);
      w[4] = getWeight(x+1, y-1, z);
      w[5] = getWeight(x+1, y, z);
      w[6] = getWeight(x, y-1, z);
      w[7] = getWeight(x, y+1, z);

      int max = maxWeight(w, 8);
      if (w[max] == -1)
         return;
      switch (max)
      {
         case 0:
            _MW[z][y][x-1].setW(3);
            _MW[z][y][x].setW(0);
            break;
         case 1:
            _MW[z][y-1][x-1].setW(3);
            _MW[z][y][x].setW(0);
            break;
         case 2:
            _MW[z][y+1][x-1].setW(3);
            _MW[z][y][x].setW(0);
            break;
         case 3:
            _MW[z][y+1][x+1].setW(3);
            _MW[z][y][x].setW(0);
            break;
         case 4:
            _MW[z][y-1][x+1].setW(3);
            _MW[z][y][x].setW(0);
            break;
         case 5:
            _MW[z][y][x+1].setW(3);
            _MW[z][y][x].setW(0);
            break;
         case 6:
            _MW[z][y-1][x].setW(3);
            _MW[z][y][x].setW(0);
            break;
         case 7:
            _MW[z][y+1][x].setW(3);
            _MW[z][y][x].setW(0);
            break;
      }
   }
}

int   Water::getWeight(int x, int y, int z) {

   int w = 0;
   if ((z<0 || z>=_zMax || y<0 || y>=_yMax || x<0 || x>=_xMax) || _MW[z][y][x].getW() != 0)
      return -1;
   while(true)
   {
      if (z>=0 && _MW[z-w][y][x].getW() == 0)
         w++;
      else
         break;
   }

   return w;
}
