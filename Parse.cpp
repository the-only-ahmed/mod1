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
         index = line.find(",", index + 1);
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
      std::cout << "You dont Have rights to read from file " + av3 + "!! cheak rights" << std::endl;
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

int    Parse::max(char att) {

   int max = 0;

   if (att == 'x')
   {
      max = this->liste->at(0).getX();
      for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      {
         if (max < it->getX())
            max = it->getX();
      }
   }
   else if (att == 'y')
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

int    Parse::min(char att) {

   int min;

   if (att == 'x')
   {
      min = this->liste->at(0).getX();
      for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      {
         if (min > it->getX())
            min = it->getX();
      }
   }
   else if (att == 'y')
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

std::vector<float>    Parse::Tri_x(bool swap) {

   float   tmp;

   std::vector<float> sorted;
   sorted.push_back(0);
   for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      sorted.push_back(it->getX());

   while (swap)
   {
      swap = false;
      for (int i=0; i<liste->size() - 1; i++)
      {
         if (sorted[i] > sorted[i + 1])
         {
            swap = true;
            tmp = sorted[i];
            sorted[i] = sorted[i+1];
            sorted[i+1] = tmp;
         }
      }
   }

   sort(sorted.begin(), sorted.end());
   sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
   return sorted;
}

void   Parse::setBorders() {

   this->borders = new Vector3[5];

   int minX = this->min('x');
   int maxX = this->max('x');
   int minY = this->min('y');
   int maxY = this->max('y');
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

   this->Tri();
   std::vector<float> sorted = this->Tri_x(true);
   this->FillMatrix(sorted);
   delete this->liste;
}

int         Parse::getXMax() const {return this->xMax;}
int         Parse::getYMax() const {return this->yMax;}
Vector3*    Parse::getBorders() const {return this->borders;}
Vector3**   Parse::getMatrix() const {return this->M;}

void      Parse::Tri() {

   Tri_y();
   Tri_x();

   std::vector<float> sorted;
   for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
      sorted.push_back(it->getX());

   sort(sorted.begin(), sorted.end());
   sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());

   int    ret = sorted.size();

   xMax = 0;
   yMax = 0;

   xMax = ret + 2;
   ret = 1;
   float tmp = liste->at(0).getY();
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

float  Parse::find(Vector3* Mat) {

   float res = 0;

   for(int x=0; x<xMax; x++)
   {
      if (Mat[x] != Vector3())
      {
         res = Mat[x].getY();
         break;
      }
   }
   return res;
}

void   Parse::FillMatrix(std::vector<float> sorted) {

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
            if (ret != liste->at(0).getY() || liste->at(0).getX() != sorted[x])
               M[y][x] = Vector3();
            else
            {
               M[y][x] = liste->at(0);
               liste->erase(liste->begin());
            }
         }
      }
   }/*
   for (int y = 1; y < yMax - 1 ; y++)
   {
      float yo = this->find(M[y]);
      M[y][0] = Vector3(0, yo, 0);
      M[y][xMax - 1] = Vector3(M[0][xMax - 1].getX(), yo, 0);
   }
   for (int x = 1; x < xMax - 1 ; x++)
   {
      M[0][x] = Vector3(sorted[x], M[0][0].getY(), 0);
      M[yMax - 1][x] = Vector3(sorted[x], 0, 0);
   }*/
}
