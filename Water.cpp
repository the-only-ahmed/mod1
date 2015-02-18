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

Water::Water(Vector3 **M, int xMax, int yMax) : _yMax(yMax), _xMax(xMax), _zMax(16), tapMax(50) {

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
               DoFluid(x, y, z);
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

int   Water::posWeight(int *w, int size) {

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

int   Water::maxWeight(int *w, int size) {

   int max = w[0];
   for(int i=1; i<size; i++)
   {
      if (max < w[i])
         max = w[i];
   }
   return max;
}

void  Water::DoFluid(int x, int y, int z) {

   if (z>0 && _MW[z-1][y][x].getW() == 0)
   {
      _MW[z-1][y][x].setW(3);
      _MW[z][y][x].setW(0);
   }
   else
   {
      int max = this->checkWeight(x, y, z, 0);
      if (max > 7 || max < -1)
         std::cout << "MAX = " << max << std::endl;
      switch (max)
      {
         case -1:
            break;
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


int  Water::checkWeight(int x, int y, int z, int i) {

   int   w[8];
   Vector3 p[8];
   if (!w)
      return -1;
   p[0] = Vector3(x-1, y, z);
   p[1] = Vector3(x-1, y-1, z);
   p[2] = Vector3(x-1, y+1, z);
   p[3] = Vector3(x+1, y+1, z);
   p[4] = Vector3(x+1, y-1, z);
   p[5] = Vector3(x+1, y, z);
   p[6] = Vector3(x, y-1, z);
   p[7] = Vector3(x, y+1, z);

   if (i>3)
   {
      w[0] = getWeight(p[0]);
      w[1] = getWeight(p[1]);
      w[2] = getWeight(p[2]);
      w[3] = getWeight(p[3]);
      w[4] = getWeight(p[4]);
      w[5] = getWeight(p[5]);
      w[6] = getWeight(p[6]);
      w[7] = getWeight(p[7]);
      if (w[posWeight(w, 8)] == -1)
         return -1;
      return maxWeight(w, 8);
   }


   w[0] = getWeight(p[0]) + checkWeight(p[0].getX(), p[0].getY(), p[0].getZ(), i+1);
   w[1] = getWeight(p[1]) + checkWeight(p[1].getX(), p[1].getY(), p[1].getZ(), i+1);
   w[2] = getWeight(p[2]) + checkWeight(p[2].getX(), p[2].getY(), p[2].getZ(), i+1);
   w[3] = getWeight(p[3]) + checkWeight(p[3].getX(), p[3].getY(), p[3].getZ(), i+1);
   w[4] = getWeight(p[4]) + checkWeight(p[4].getX(), p[4].getY(), p[4].getZ(), i+1);
   w[5] = getWeight(p[5]) + checkWeight(p[5].getX(), p[5].getY(), p[5].getZ(), i+1);
   w[6] = getWeight(p[6]) + checkWeight(p[6].getX(), p[6].getY(), p[6].getZ(), i+1);
   w[7] = getWeight(p[7]) + checkWeight(p[7].getX(), p[7].getY(), p[7].getZ(), i+1);

/*   int pos = posWeight(w, 8);
//  int max = maxWeight(w, 8);
   if (w[pos] == -1)
      return NULL;*/

   if (w[posWeight(w, 8)] == -1)
         return -1;
   if (i == 0)
      return posWeight(w,8);
   return maxWeight(w, 8);
//   if (ahmed == -1)
//      return w;
//   else
//      return w;
}

int   Water::getWeight(Vector3 p) {

   int x = static_cast<int>(p.getX());
   int y = static_cast<int>(p.getY());
   int z = static_cast<int>(p.getZ());

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
