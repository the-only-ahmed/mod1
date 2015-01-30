#include "SceneOpenGL.h"

// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre, Vector3 middle) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
	m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0) {

		scale = middle / 0.5f;
	}

	SceneOpenGL::~SceneOpenGL() {

		SDL_GL_DeleteContext(m_contexteOpenGL);
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();
	}

// Méthodes

bool SceneOpenGL::initialiserFenetre() {

	// Initialisation de la SDL

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}

	// Version d'OpenGL

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Double Buffer

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Création de la fenêtre

	m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(m_fenetre == 0)
	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}

	// Création du contexte OpenGL

	m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

	if(m_contexteOpenGL == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}

	return true;
}

bool SceneOpenGL::initGL() {

#ifdef WIN32

	// On initialise GLEW

	GLenum initialisationGLEW( glewInit() );

	// Si l'initialisation a échoué :

	if(initialisationGLEW != GLEW_OK)
	{
		// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

		// On quitte la SDL

		SDL_GL_DeleteContext(m_contexteOpenGL);
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}

#endif

	// Tout s'est bien passé, on retourne true

	return true;
}

void drawDot(Vector3 p) {
	glBegin(GL_POINTS);
	glVertex3f(p.getX(), p.getY(), p.getZ());
	glEnd();
	glFlush();
}

void drawLine(Vector3 p1, Vector3 p2) {
	glBegin(GL_LINES);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	glEnd();
	glFlush();
}

void SceneOpenGL::bouclePrincipale(Vector3 *borders) {

	// Variables

	Vector3 p1 = Vector3(-9999, -9999, 0);
	Vector3 p2 = Vector3(-9999, 10000, 0);
	Vector3 p3 = Vector3(10000, -9999, 0);
	Vector3 p4 = Vector3(10000, 10000, 0);

	bool terminer(false);

	// Boucle principale

	std::cout << this->scale << std::endl;
	// glm::mat4 myScalingMatrix = glm::scale(2.0f, 2.0f ,2.0f);
		glLoadIdentity();
		glOrtho(0, 1, 0, 1, 0, 1);
		glMatrixMode(GL_PROJECTION);
		glScalef(1 / this->scale.getX(), 1 / this->scale.getY(), 1.0);
		// glTranslatef(2, 2, 2);
	while(!terminer)
	{
		// Gestion des évènements


		// glLoadIdentity();
		// glViewport(0, 0, 800, 600);
		// glMatrixMode(GL_MODELVIEW);
		// glLoadIdentity();

		SDL_WaitEvent(&m_evenements);

		if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			terminer = 1;

		// Nettoyage de l'écran

		glClear(GL_COLOR_BUFFER_BIT);

		// drawLine(p1, p2);

		// On remplie puis on active le tableau Vertex Attrib 0
		// gluLookAt(borders[4].getX() * this->scale, borders[4].getY() * this->scale, borders[4].getZ() * this->scale, 0, -1, 0, 0, 0, 1);
		// drawLine(p1, p2);
		// drawDot(p1);
		// drawDot(p2);
		// drawDot(p3);
		// drawDot(p4);

		drawDot(borders[4]);
		// drawDot(borders[4] / this->scale);
/*		std::cout << "first " << borders[0] / this->scale << std::endl;
		std::cout << "second " << borders[1] / this->scale << std::endl;
		std::cout << "third " << borders[2] / this->scale << std::endl;
		std::cout << "fourth " << borders[3] / this->scale << std::endl;
		std::cout << "middle " << borders[4] / this->scale << std::endl;*/
		drawLine(p1, p2);
		drawLine(p1, p3);
		drawLine(p3, p4);
		drawLine(p4, p2);
		// drawLine(borders[0], borders[1]);
		// drawLine(borders[1], borders[2]);
		// drawLine(borders[2], borders[3]);
		// drawLine(borders[3], borders[4]);
		// drawLine(borders[0] / this->scale, borders[1] / this->scale);
		// drawLine(borders[1] / this->scale, borders[2] / this->scale);
		// drawLine(borders[2] / this->scale, borders[3] / this->scale);
		// drawLine(borders[3] / this->scale, borders[4] / this->scale);

		// Actualisation de la fenêtre

		SDL_GL_SwapWindow(m_fenetre);
	}
}
