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
#include <cmath>
#include "tools/Vector3.class.hpp"

class Parse
{
   private:
      std::vector<Vector3> *liste;
      Vector3 *borders;

      std::string   mitSpace(std::string line);
      Vector3       voxelParse(char *ret);
      void          setBorders();
      int           min(int att);
      int           max(int att);

   public:
      Parse(char* av);

      std::vector<Vector3>*   getListe() const;
      Vector3*                getBorders() const;
};

#endif
