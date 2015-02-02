/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 18:08:18 by jyim              #+#    #+#             */
/*   Updated: 2015/01/29 18:08:19 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include "tools/Vector3.class.hpp"

class Parse
{
   private:
      std::vector<Vector3> *liste;
      Vector3 *borders;
      Vector3 **M;
      int      xMax;
      int      yMax;

      std::string   mitSpace(std::string line);
      Vector3       voxelParse(char *ret);
      void          setBorders();
      int           min(char att);
      int           max(char att);
      void          Tri();
      void          Tri_x();
      void          Tri_y();
      void          FillMatrix(std::vector<float>);
      float        find(Vector3* Mat);

      std::vector<float>          Tri_x(bool swap);

   public:
      Parse(char* av);

      Vector3*     getBorders() const;
      Vector3**    getMatrix() const;
      int          getYMax() const;
      int          getXMax() const;
};

#endif
