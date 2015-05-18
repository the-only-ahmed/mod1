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

void       Parse::normalize(int base, int height) {

   Vector3 max = Vector3(this->max('x'), this->max('y'), this->max('z'));
   double length = max.Length();

   for(unsigned int i=0; i<liste.size(); i++)
   {
      if (length > 0)
      {
         double inv = base/sqrt(length);

         if (base == height)
            liste[i] *= inv;
         else
         {
            liste[i].setX(liste[i].getX()*inv);
            liste[i].setY(liste[i].getY()*inv);

            inv = height/sqrt(length);
            liste[i].setZ(liste[i].getZ()*inv);
         }
      }
   }
}

int    Parse::max(char att) {

   int max = 0;

   if (att == 'x')
   {
      max = this->liste[0].getX();
      for(std::vector<Vector3>::iterator it = liste.begin(); it != liste.end(); ++it)
      {
         if (max < it->getX())
            max = it->getX();
      }
   }
   else if (att == 'y')
   {
      max = this->liste[0].getY();
      for(std::vector<Vector3>::iterator it = liste.begin(); it != liste.end(); ++it)
      {
         if (max < it->getY())
            max = it->getY();
      }
   }
   else
   {
      max = this->liste[0].getZ();
      for(std::vector<Vector3>::iterator it = liste.begin(); it != liste.end(); ++it)
      {
         if (max < it->getZ())
            max = it->getZ();
      }
   }
  return max;
}


Parse::Parse(char *av) : xMax(64), yMax(64) {

   std::string	line;
   std::string line2;

   std::ifstream ifin (av, std::ifstream::in);
   if (!ifin.good())
   {
      std::string av3 = av;
      std::cout << "You dont Have rights to read from file " + av3 + "!! check rights" << std::endl;
      ifin.close();
      exit(0);
   }
   else
   {
      while (getline(ifin, line))
         line2 += line;
      if (line.empty())
      {
         std::string av3 = av;
         std::cout << "file " + av3 + " empty" << std::endl;
         ifin.close();
         exit(0);
      }   
      line2 = mitSpace(line2);
      char* pute = &*line2.begin();
      char* ret = strtok(pute, " ");
      while (ret)
      {
         Vector3 voxel = voxelParse(ret);
         liste.push_back(voxel);
         ret = strtok(NULL, " ");
      }
   }
   FillMatrix();
}

void  Parse::recenter() {

   for(int y=0; y<yMax; y++)
   {
      for(int x=0; x<xMax; x++)
      {
         M[y][x].setX(M[y][x].getX()-static_cast<int>(round(xMax/2)));
         M[y][x].setY(M[y][x].getY()-static_cast<int>(round(yMax/2)));
      }
   }
}

int         Parse::getXMax() const {return this->xMax;}
int         Parse::getYMax() const {return this->yMax;}
Vector3**   Parse::getMatrix() const {return this->M;}

void   Parse::FillMatrix() {

   M = new Vector3*[yMax];
   for(int i = 0; i < yMax; i++)
      M[i] = new Vector3[xMax];

   for(int y=0; y<yMax; y++)
      for(int x=0; x<xMax; x++)
         M[y][x] = Vector3(x, y, 0);

   this->normalize(64, 32);

   for(unsigned int i=0; i<liste.size(); i++)
   {
      int x = static_cast<int>(round(liste[i].getX()));
      int y = static_cast<int>(round(liste[i].getY()));
      M[y][x].setZ(liste[i].getZ());
   }
   for (int y = 0; y < yMax; y++)
   {
      for (int x = 0; x < xMax; x++)
      {
         if (M[y][x].getZ() != 0)
            continue;
         double z = InverseDistanceWeight(M[y][x]);
         M[y][x].setZ(z);
      }
   }
   recenter();
}

double Parse::Weight(double ret) {return (1/(ret*ret));}

double Parse::InverseDistanceWeight(Vector3 target) {

   double total = 0;
   double sum = 0;
   double distance, weight, value;

   for (unsigned int i = 0; i < liste.size(); i++)
   {
      // Euclidean distance
      distance = sqrt(pow(liste[i].getX() - target.getX(), 2) + pow(liste[i].getY() - target.getY(), 2));
      if (distance == 0)
         weight = 1;
      else
         weight = 1/pow(distance, 2); // the weighting function
      value = weight * liste[i].getZ(); // the adjusted value
      total += value; // sum it all up
      sum += weight;
   }
   sum += Weight(std::min(target.getX(), 64 - target.getX()));
   sum += Weight(std::min(target.getY(), 64 - target.getY()));
   // get the weighted average
   return (total/sum);
}
