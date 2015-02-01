/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 18:08:24 by jyim              #+#    #+#             */
/*   Updated: 2015/01/29 18:08:25 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

std::string	Parse::mitSpace(std::string line) {

   size_t	index = 0;

   while (true)
   {
      index = line.find(")", index);
      if (index == std::string::npos) break;

      line.replace(index, 1, ") ");
      index += 1;
   }
   return line;
}

Vector3	 Parse::voxelParse(char *ret) {

   int x = 0;
   int y = 0;
   int z = 0;
   int i = 0;
   int index = 0;
   std::string line = ret;

   while (i < 3) {
      if (i == 0) {x = atoi(&ret[1]);}
      else if (i == 1) {
         index = line.find(",", index);
         y = atoi(&ret[index + 1]);
      }
      else {
         index = line.find(",", index);
         z = atoi(&ret[index + 1]);
      }
      i++;
   }

   Vector3  vox = Vector3(x, y, z);
   return (vox);
}

Parse::Parse(char *av) {

   std::string	line;
   std::string line2;

   liste = new std::vector<Vector3>();
   std::ifstream ifin (av, std::ifstream::in);
   if (!ifin.good())
   {
      std::string av3 = av;
      std::cout << "You dont Have rights to read from file" + av3 +"!! cheak rights" << std::endl;
      ifin.close();
      return ;
   }
   else
   {
      while (getline(ifin, line))
         line2 += line;
      line2 = mitSpace(line2);
      char* pute = &*line2.begin();
      char* ret = strtok(pute, " ");
      while (ret)
      {
         Vector3 voxel = voxelParse(ret);
         liste->push_back(voxel);
         ret = strtok(NULL, " ");
      }
      setBorders();
   }
}

int    Parse::max(int att) {

   int max = 0;

   if (att == 0)
   {
      max = this->liste->at(0).getX();
      for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      {
         if (max < it->getX())
            max = it->getX();
      }
   }
   else if (att == 1)
   {
      max = this->liste->at(0).getY();
      for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      {
         if (max < it->getY())
            max = it->getY();
      }
   }
   else
   {
      max = this->liste->at(0).getZ();
      for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      {
         if (max < it->getZ())
            max = it->getZ();
      }
   }
  return max;
}

int    Parse::min(int att) {

   int min;

   if (att == 0)
   {
      min = this->liste->at(0).getX();
      for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      {
         if (min > it->getX())
            min = it->getX();
      }
   }
   else if (att == 1)
   {
      min = this->liste->at(0).getY();
      for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      {
         if (min > it->getY())
            min = it->getY();
      }
   }
   else
   {
      min = this->liste->at(0).getZ();
      for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      {
         if (min > it->getZ())
            min = it->getZ();
      }
   }
   return min;
}

void   Parse::setBorders() {

   this->borders = new Vector3[5];

   int minX = this->min(0);
   int maxX = this->max(0);
   int minY = this->min(1);
   int maxY = this->max(1);
   int xProp = round(maxX / 3);
   int yProp = round(maxY / 3);

   this->borders[0] = Vector3(minX - xProp, minY - yProp, 0);
   this->borders[1] = Vector3(minX - xProp, maxY + yProp, 0);
   this->borders[2] = Vector3(maxX + xProp, minY - yProp, 0);
   this->borders[3] = Vector3(maxX + xProp, maxY + yProp, 0);

   for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      *it -= this->borders[0];

   for (int i=3; i>=0; i--)
      this->borders[i] -= this->borders[0];

   this->borders[4] = this->borders[3] / 2;
   this->borders[4].setZ(this->max(2));

   std::cout << "Points Nb => " << liste->size() << std::endl;

   this->Tri();
   this->FillMatrix();

   std::cout << "Points Nb => " << liste->size() << std::endl;

   for (int y=0; y<yMax; y++)
   {
      for (int x=0; x<xMax; x++)
      {
         if (M[y][x] != Vector3())
            std::cout << M[y][x] << "   ";
         else
            std::cout << "0   ";
      }
      std::cout << std::endl;
   }
}

std::vector<Vector3>*   Parse::getListe() const {return this->liste;}
Vector3*   Parse::getBorders() const {return this->borders;}
Vector3**   Parse::getMatrix() const {return this->M;}

void      Parse::Tri() {

   Tri_y();
   Tri_x();
   float  tmp = liste->at(0).getX();
   int    ret = 1;
   xMax = 0;
   yMax = 0;
   for (int i = 0; i < liste->size(); i++)
   {
      if (tmp != liste->at(i).getX())
      {
         ret++;
         tmp = liste->at(i).getX();
      }
   }
   xMax = ret + 2;
   ret = 1;
   tmp = liste->at(0).getY();
   for (int i = 0; i < liste->size(); i++)
   {
      if (tmp != liste->at(i).getY())
      {
         ret++;
         tmp = liste->at(i).getY();
      }
   }
   yMax = ret + 2;
}

void      Parse::Tri_y() {

   bool      swap = true;
   Vector3   tmp;

   while (swap)
   {
      swap = false;
      for (int i=0; i<liste->size() - 1; i++)
      {
         if (liste->at(i).getY() < liste->at(i + 1).getY())
         {
            swap = true;
            tmp = liste->at(i);
            liste->at(i) = liste->at(i+1);
            liste->at(i+1) = tmp;
         }
      }
   }
}

void   Parse::Tri_x() {

   bool      swap = true;
   Vector3   tmp;

   while (swap)
   {
      swap = false;
      for (int i=0; i<liste->size() - 1; i++)
      {
         if (liste->at(i).getY() == liste->at(i + 1).getY())
         {
            if (liste->at(i).getX() > liste->at(i + 1).getX())
            {
               swap = true;
               tmp = liste->at(i);
               liste->at(i) = liste->at(i+1);
               liste->at(i+1) = tmp;
            }
         }
      }
   }
}

void   Parse::FillMatrix() {

   M = new Vector3*[yMax];
   for(int i = 0; i < yMax; i++)
      M[i] = new Vector3[xMax];
   M[0][0] = borders[1];
   M[0][xMax - 1] = borders[3];
   M[yMax - 1][xMax - 1] = borders[2];
   M[yMax - 1][0] = borders[0];
   for (int y = 0; y < yMax - 1 ; y++)
   {
      float ret = liste->at(0).getY();
      for (int x = 0; x < xMax - 1; x++)
      {
         if ((x == 0 && y == 0) || (x == 0 && y == yMax - 1) || (x == xMax - 1 && y == 0) || (x == xMax - 1 && y == yMax - 1))
            continue;

         if (((y == 0) || (y == yMax - 1)) || ((x == xMax - 1) || x == 0))
               M[y][x] = Vector3();
         else if (liste->size() > 0)
         {
            if (ret != liste->at(0).getY())
               M[y][x] = Vector3();
            else
            {
               M[y][x] = liste->at(0);
               liste->erase(liste->begin());
            }
         }
      }
   }
}
