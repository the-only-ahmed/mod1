#ifndef SCENEOPENGL_HPP
#define SCENEOPENGL_HPP

// Includes

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include "glm/glm.hpp"
#include "Parse.hpp"

#include "tools/Vector3.class.hpp"
#include "GLSLProgram.h"
#include "Water.hpp"

// Classe

class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale(Vector3 **M, int xMax, int yMax);

   private:
      void initShaders();

   GLSLProgram _colorProgram;

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
};

#endif
