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
	liste = parsing.getListe();
	Vector3 *borders = parsing.getBorders();

	SceneOpenGL scene("OpenGL", 800, 600, borders[4]);
	if(scene.initialiserFenetre() == false)
		return -1;
	if(scene.initGL() == false)
		return -1;

	scene.bouclePrincipale(borders);

	delete [] borders;
	delete liste;
	return (0);
}
