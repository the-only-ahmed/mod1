/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Volcan.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 18:23:31 by jyim              #+#    #+#             */
/*   Updated: 2015/03/09 18:23:33 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOLCAN_HPP
# define VOLCAN_HPP

#include "Water.hpp"

class Volcan
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

      void  DoFluid(Water wat, int x, int y, int z);

   public:
      Volcan(Water wat);
      ~Volcan();
      void MakeFluid(Water wat);
      void AddLava(Water wat, Vector3 height);
};

#endif
