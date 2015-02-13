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

#include "tools/Vector3.class.hpp"
#include "tools/Vector4.class.hpp"

class Water
{
   private:
      int      _xMax;
      int      _yMax;
      int      _zMax;
      int      tapMax;

   public:
      Water(Vector3 **M, int xMax, int yMax);
      ~Water();
      void MakeFluid();
      void AddWater();

      Vector4  ***_MW;
};

#endif
