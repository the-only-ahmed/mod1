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
#include "SceneOpenGL.hpp"

int		main(int ac, char **av) {

	if (ac != 2) {
		std::cout << "Use <filename>." << std::endl;
		std::cout << "Please Give one Argument!!" << std::endl;
		return (-1);
	}
	srand (time(NULL));
	Parse parsing = Parse(av[1]);
	Vector3 **M = parsing.getMatrix();
	int yMax = parsing.getYMax();
	int xMax = parsing.getXMax();
	SceneOpenGL scene("OpenGL", 800, 600);
	if(scene.initialiserFenetre() == false)
		return -1;
	if(scene.initGL() == false)
		return -1;

	scene.bouclePrincipale(M, xMax, yMax);

	for(int i = 0; i < yMax; i++)
		delete [] M[i];
	delete [] M;
	return (0);
}
