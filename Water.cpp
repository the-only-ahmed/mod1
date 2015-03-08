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

Water::Water(Vector3 **M, int xMax, int yMax) : _xMax(xMax), _yMax(yMax), _zMax(16), tapMax(300) {

   _MW = new gougoutte_glass**[_zMax];
   for(int i=0; i<_zMax; i++)
   {
      _MW[i] = new gougoutte_glass*[yMax];
      for(int j=0; j<yMax; j++)
         _MW[i][j] = new gougoutte_glass[xMax];
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
            _MW[z][y][x] = gougoutte_glass(Vector3(M[y][x].getX(), M[y][x].getY(), z), w);
         }
      }
   }

   xStart = round(M[0][0].getX());
   yStart = round(M[0][0].getY());

   xEnd = round(M[0][_xMax-1].getX());
   yEnd = round(M[_yMax-1][0].getY());

   std::cout << "xStart : " << xStart << "   |  xEnd : " << xEnd << std::endl;
   std::cout << "yStart : " << yStart << "   |  yEnd : " << yEnd << std::endl;
}

void  Water::MakeFluid() {

   for(int z=0; z<_zMax; z++)
      for(int y=0; y<_yMax; y++)
         for(int x=0; x<_xMax; x++)
            if (_MW[z][y][x].getType() == 3)
               DoFluid(x, y, z);
}

void  Water::AddWater() {

   /*int drop = static_cast<int>(round(sqrt(tapMax)/2));
   int z = _zMax - 1;
   int middle_y = static_cast<int>(round(_yMax/2));
   int middle_x = static_cast<int>(round(_xMax/2));

   for(int y=(middle_y-drop+1); y<(middle_y+drop); y++)
   {
      for(int x=(middle_x-drop); x<=(middle_x+drop); x++)
      {
         _MW[z][y][x].setType(3);
         _MW[z][y][x].setPerc(100);
      }
   }*/

   for(int y=0; y<_yMax; y++)
   {
      for(int z=10; z>0; z--)
      {
         _MW[z][y][0].setType(3);
         _MW[z][y][0].setPerc(100);
      }
   }
}

void  Water::DoFluid(int x, int y, int z) {

   Vector3 p[9];
   p[0] = Vector3(x, y, z-1);
   p[1] = Vector3(x, y-1, z);
   p[2] = Vector3(x, y+1, z);
   p[3] = Vector3(x-1, y, z);
   p[4] = Vector3(x-1, y-1, z);
   p[5] = Vector3(x-1, y+1, z);
   p[6] = Vector3(x+1, y+1, z);
   p[7] = Vector3(x+1, y-1, z);
   p[8] = Vector3(x+1, y, z);

   int V = _MW[z][y][x].getPerc();
   int porn;
   if(z>0)
   {
      porn = _MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].getPerc();
      if (porn < 100)
      {
         int ret  = 100 - porn;
         if (ret <= V)
         {
            _MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].addPerc(ret);
            _MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].setType(3);
            _MW[z][y][x].addPerc(-ret);
         }
         else
         {
            _MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].addPerc(V);
            _MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].setType(3);
            _MW[z][y][x].addPerc(-V);
         }
      }
   }

   V = _MW[z][y][x].getPerc();
   if (V <= 0)
      return;

   std::vector<gougoutte_glass> liste;
  for(int i=1; i<9; i++)
   {
      int x0 = static_cast<int>(p[i]._x);
      int y0 = static_cast<int>(p[i]._y);
      int z0 = static_cast<int>(p[i]._z);

      if(x0==0 && (i==3 || i==4 || i==5))
         continue;
      if(x==_xMax-1 && (i==6 || i==7 || i==8))
         continue;
      if(y==0 && (i==1 || i==4 || i==7))
         continue;
      if(y==_yMax-1 && (i==2 || i==5 || i==6))
         continue;

      if (_MW[z0][y0][x0].getPerc() < V)
         liste.push_back(_MW[z0][y0][x0]);
   }
   if(liste.empty())
      return;
   std::sort(liste.begin(), liste.end());

   while(!liste.empty())
   {
      V = _MW[z][y][x].getPerc();
      porn = ceil(V/8);
      unsigned int i = 0;
      for(; i<liste.size(); i++)
      {
         if (porn<=0 || liste[i].getPerc()+porn > V-porn)
            break;
         V -= porn;
         liste[i].addPerc(porn);
         liste[i].setType(3);
      }
      if (liste.size() == 1)
      {
         if (V > liste[0].getPerc())
         {
            int alpha = V-liste[0].getPerc();
            alpha = floor(alpha/2);
            liste[0].addPerc(alpha);
            V -= alpha;
         }
      }
      while(i<liste.size())
      {
         int gega = liste.size()-1;
         int x1 = static_cast<int>(round(liste[gega].getV3()._x) - xStart);
         int y1 = static_cast<int>(round(liste[gega].getV3()._y) - yStart);
         int z1 = static_cast<int>(round(liste[gega].getV3()._z));

         _MW[z1][y1][x1].setPerc(liste[gega].getPerc());
         _MW[z1][y1][x1].setType(liste[gega].getType());
         liste.pop_back();
      }
      _MW[z][y][x].setPerc(V);
   }


   while (_MW[z][y][x].getPerc() > 0)
   {
      V = _MW[z][y][x].getPerc();
      for(int i=1; i<9; i++)
      {
         int x0 = static_cast<int>(p[i]._x);
         int y0 = static_cast<int>(p[i]._y);
         int z0 = static_cast<int>(p[i]._z);

         if(x0==0 && (i==3 || i==4 || i==5))
            continue;
         if(x==_xMax-1 && (i==6 || i==7 || i==8))
            continue;
         if(y==0 && (i==1 || i==4 || i==7))
            continue;
         if(y==_yMax-1 && (i==2 || i==5 || i==6))
            continue;

         if (_MW[z0][y0][x0].getPerc() <= V-1)
            liste.push_back(_MW[z0][y0][x0]);
      }
      if(liste.empty())
         break;
      std::sort(liste.begin(), liste.end());
      unsigned int i=0;
      for(; i<liste.size(); i++)
      {
         //if (liste[i].getPerc()+1 > V-1)
         if(V-1<0)
            break;
         V -= 1;
         liste[i].addPerc(1);
         liste[i].setType(3);
      }
      _MW[z][y][x].setPerc(V);
      while(!liste.empty())
      {
         int gega = liste.size()-1;
         int x1 = static_cast<int>(round(liste[gega].getV3()._x) - xStart);
         int y1 = static_cast<int>(round(liste[gega].getV3()._y) - yStart);
         int z1 = static_cast<int>(round(liste[gega].getV3()._z));

         _MW[z1][y1][x1].setPerc(liste[gega].getPerc());
         _MW[z1][y1][x1].setType(liste[gega].getType());
         liste.pop_back();
      }
      if(i==0)
         break;
   }
}
