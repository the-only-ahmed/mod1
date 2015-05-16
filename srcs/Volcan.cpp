/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Volcan.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 18:23:27 by jyim              #+#    #+#             */
/*   Updated: 2015/03/09 18:23:28 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Volcan.hpp"

Volcan::~Volcan() {}

Volcan::Volcan(Water wat) : tapMax(50) {

   (void)tapMax;
   _xMax = wat.getX();
   _yMax = wat.getY();
   _zMax = wat.getZ();
   xStart = wat.getXS();
   yStart = wat.getYS();
   xEnd = wat.getXE();
   yEnd = wat.getYE();
}

void  Volcan::MakeFluid(Water wat) {

   for(int z=0; z<_zMax; z++)
      for(int y=0; y<_yMax; y++)
         for(int x=0; x<_xMax; x++)
            if (wat._MW[z][y][x].getType() == 4 && wat._MW[z][y][x].chut < 2)
               DoFluid(wat, x, y, z);
}

void  Volcan::AddLava(Water wat, Vector3 height) {

   int _x = static_cast<int>(height._x) - xStart;
   int _y = static_cast<int>(height._y) - yStart;
   int z = static_cast<int>(height._z) + 1;

   for(int y=_y-1; y<_y+1; y++)
   {
      for(int x=_x-1; x<_x+1; x++)
      {
         if (wat._MW[z][y][x].getType() == 0)
         {
            wat._MW[z][y][x].setType(4);
            wat._MW[z][y][x].setPerc(100);
         }
         else if (wat._MW[z][y][x].getType() == 3)
            wat._MW[z][y][x].setType(5);
         else if (wat._MW[z][y][x].getType() == 1 || wat._MW[z][y][x].getType() == -1)
            continue;
         else if (wat._MW[z][y][x].getType() == 4)
            wat._MW[z][y][x].setPerc(100);
      }
   }
}

void  Volcan::DoFluid(Water wat, int x, int y, int z) {

   if (wat._MW[z][y][x].chut >= 2){
      return;}

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

   int V = wat._MW[z][y][x].getPerc();
   int flag;
   if(z>0)
   {
      flag = wat._MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].getPerc();
      if(wat._MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].getType() == 3)
         wat._MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].setType(5);

      else if (flag < 100)
      {
         int ret  = 100 - flag;
         if (ret <= V)
         {
            wat._MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].addPerc(ret);
            wat._MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].setType(4);
            wat._MW[z][y][x].addPerc(-ret);
         }
         else
         {
            wat._MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].addPerc(V);
            wat._MW[static_cast<int>(p[0]._z)][static_cast<int>(p[0]._y)][static_cast<int>(p[0]._x)].setType(4);
            wat._MW[z][y][x].addPerc(-V);
         }
      }
   }

   V = wat._MW[z][y][x].getPerc();
   if (V <= 0)
      return;

   std::vector<gougoutte_glass> liste;
   for(int i=1; i<9; i++)
   {
      int x0 = static_cast<int>(p[i]._x);
      int y0 = static_cast<int>(p[i]._y);
      int z0 = static_cast<int>(p[i]._z);

      if(x==0 && (i==3 || i==4 || i==5))
         continue;
      if(x==_xMax-1 && (i==6 || i==7 || i==8))
         continue;
      if(y==0 && (i==1 || i==4 || i==7))
         continue;
      if(y==_yMax-1 && (i==2 || i==5 || i==6))
         continue;

      if (wat._MW[z0][y0][x0].getPerc() < V)
         liste.push_back(wat._MW[z0][y0][x0]);
   }
   if(liste.empty())
   {
      if (wat._MW[z][y][x].getPerc() == 100)
         wat._MW[z][y][x].chut++;
      return;
   }
   std::sort(liste.begin(), liste.end());

   while(!liste.empty())
   {
      V = wat._MW[z][y][x].getPerc();
      flag = ceil(V/8);
      unsigned int i = 0;
      for(; i<liste.size(); i++)
      {
         if (flag<=0 || liste[i].getPerc()+flag > V-flag)
            break;

         V -= flag;
         liste[i].addPerc(flag);
         liste[i].setType(4);

         if(liste[i].getType() == 3)
            liste[i].setType(5);
      }
      if (liste.size() == 1)
      {
         if (V > liste[0].getPerc())
         {
            int alpha = V-liste[0].getPerc();
            alpha = floor(alpha/2);
            liste[0].addPerc(alpha);
            V -= alpha;

            if(liste[0].getType() == 3)
               liste[0].setType(5);
         }
      }
      while(i<liste.size())
      {
         int gega = liste.size()-1;
         int x1 = static_cast<int>(round(liste[gega].getV3()._x) - xStart);
         int y1 = static_cast<int>(round(liste[gega].getV3()._y) - yStart);
         int z1 = static_cast<int>(round(liste[gega].getV3()._z));

         wat._MW[z1][y1][x1].setPerc(liste[gega].getPerc());
         wat._MW[z1][y1][x1].setType(liste[gega].getType());
         liste.pop_back();
      }
      wat._MW[z][y][x].setPerc(V);
   }

   while (wat._MW[z][y][x].getPerc() > 0)
   {
      V = wat._MW[z][y][x].getPerc();
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

         if (wat._MW[z0][y0][x0].getPerc() <= V-1)
            liste.push_back(wat._MW[z0][y0][x0]);
      }
      if(liste.empty())
         break;
      std::sort(liste.begin(), liste.end());
      unsigned int i=0;
      for(; i<liste.size(); i++)
      {
         if(V-1<0)
            break;
         V -= 1;
         liste[i].addPerc(1);
         liste[i].setType(4);

         if(liste[i].getType() == 3)
            liste[i].setType(5);
      }
      wat._MW[z][y][x].setPerc(V);
      while(!liste.empty())
      {
         int gega = liste.size()-1;
         int x1 = static_cast<int>(round(liste[gega].getV3()._x) - xStart);
         int y1 = static_cast<int>(round(liste[gega].getV3()._y) - yStart);
         int z1 = static_cast<int>(round(liste[gega].getV3()._z));

         wat._MW[z1][y1][x1].setPerc(liste[gega].getPerc());
         wat._MW[z1][y1][x1].setType(liste[gega].getType());
         liste.pop_back();
      }
      if(i==0)
         break;
   }
   if (wat._MW[z][y][x].getPerc() == 100)
      wat._MW[z][y][x].chut++;
}
