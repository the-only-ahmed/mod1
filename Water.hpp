/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 18:15:48 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/02/13 18:15:49 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATER_HPP
# define WATER_HPP

#include <vector>
#include <algorithm>

#include "tools/Vector3.class.hpp"
#include "tools/Vector4.class.hpp"
#include "gougoutte_glass.hpp"

class Water
{
   private:
      int      _xMax;
      int      _yMax;
      int      _zMax;
      int      tapMax;

      int      xStart;
      int      yStart;
      int      xEnd;
      int      yEnd;

      void  DoFluid(int x, int y, int z);

   public:
      Water(Vector3 **M, int xMax, int yMax);
      ~Water();
      void MakeFluid();
      void AddWater();

      gougoutte_glass  ***_MW;
};

#endif
