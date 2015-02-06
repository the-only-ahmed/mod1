// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/06 19:38:03 by ael-kadh          #+#    #+#             //
/*   Updated: 2015/01/28 21:24:54 by jyim             ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#include "Parse.hpp"
#include "SceneOpenGL.h"

int		main(int ac, char **av) {

	std::vector<Vector3>* liste;

	if (ac != 2) {
		std::cout << "Use <filename>." << std::endl;
		std::cout << "Please Give one Argument!!" << std::endl;
		return (-1);
	}

	Parse parsing = Parse(av[1]);
	Vector3 **M = parsing.getMatrix();
	int yMax = parsing.getYMax();
	int xMax = parsing.getXMax();
	SceneOpenGL scene("OpenGL", 800, 600);
	if(scene.initialiserFenetre() == false)
		return -1;
	if(scene.initGL() == false)
		return -1;
/*
	for(int y=0; y<yMax; y++)
	{
		for(int x=0; x<xMax; x++)
		{
			// if (M[y][x].getZ() > 15)
				// continue;
			std::cout << M[y][x].getZ() << " ";
		}
		std::cout << std::endl;
	}*/

	scene.bouclePrincipale(M, xMax, yMax);

	for(int i = 0; i < yMax; i++)
		delete [] M[i];
	delete [] M;
	return (0);
}
