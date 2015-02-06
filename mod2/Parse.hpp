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
      std::vector<Vector3> liste;
      Vector3 **M;
      const int      xMax;
      const int      yMax;

      std::string   mitSpace(std::string line);
      Vector3       voxelParse(char *ret);
      void          FillMatrix();
      void          normalize(int base, int height);
      int           max(char att);
      double        InverseDistanceWeight(Vector3 target);

   public:
      Parse(char* av);

      Vector3**    getMatrix() const;
      int          getYMax() const;
      int          getXMax() const;
};

#endif
