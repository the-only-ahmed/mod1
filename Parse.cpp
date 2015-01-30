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
   this->borders[4] = this->borders[3] / 2;

   std::cout << "left - down : " << this->borders[0] << std::endl;
   std::cout << "left - up : " << this->borders[1] << std::endl;
   std::cout << "right - down : " << this->borders[2] << std::endl;
   std::cout << "right - up : " << this->borders[3] << std::endl;
   std::cout << "middle : " << this->borders[4] << std::endl;

}

std::vector<Vector3>*   Parse::getListe() const {return this->liste;}
Vector3*   Parse::getBorders() const {return this->borders;}
