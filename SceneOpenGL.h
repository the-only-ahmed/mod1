#ifndef SCENEOPENGL_HPP
#define SCENEOPENGL_HPP

// Includes

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>

#include "glm/glm.hpp"

#include "tools/Vector3.class.hpp"

// Classe

class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre, Vector3 middle);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale(Vector3 **M, int xMax, int yMax);

   private:

   std::vector<Vector3> * points_high;
   std::vector<Vector3> * points_down;
   std::vector<Vector3> * points_left;
   std::vector<Vector3> * points_right;

	Vector3 scale;

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    SDL_Event m_evenements;

    Vector3       getCasteljau(std::vector<Vector3> points, int r, int i, float t);
   //  Vector3**	  CreateTable(Vector3 **M, int xMax, int yMax);
    Vector3**	  CreateTable(std::vector<Vector3>* points, int yMax);
    void	      algo_bezier(Vector3 **M, int xMax, int yMax);
    bool         isLast(Vector3** M, int x, int y, int xMax, int yMax, bool vertical);
};

#endif
