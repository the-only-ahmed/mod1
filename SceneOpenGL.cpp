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

// Methodes

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

	// Creation de la fenetre

	m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(m_fenetre == 0)
	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}

	// Creation du contexte OpenGL

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

	// Si l'initialisation a echoue :

	if(initialisationGLEW != GLEW_OK)
	{
		// On affiche l'erreur grace a la fonction : glewGetErrorString(GLenum code)

		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

		// On quitte la SDL

		SDL_GL_DeleteContext(m_contexteOpenGL);
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}

#endif

	// Tout s'est bien passe, on retourne true

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

void SceneOpenGL::bouclePrincipale(Vector3 *borders, std::vector<Vector3> *liste) {

	// Variables

	Vector3 p = Vector3(0.1f, 0.1f, 0);

	bool terminer(false);

	// Boucle principale

		glLoadIdentity();
		glOrtho(0, 1, 0, 1, 0, 1);
		glMatrixMode(GL_MODELVIEW_MATRIX);
		glTranslatef(0.5, 0.3, 0);
		glScalef(0.1/this->scale.getX(), 0.1/this->scale.getY(), 1);
		glRotatef(90, 1, 0, 1);
	while(!terminer)
	{
		// Gestion des evenements


		// glLoadIdentity();
		// glViewport(0, 0, 800, 600);
		// glMatrixMode(GL_MODELVIEW);
		// glLoadIdentity();

		SDL_WaitEvent(&m_evenements);

		if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			terminer = 1;

		// Nettoyage de l'ecran

		glClear(GL_COLOR_BUFFER_BIT);

		// On remplie puis on active le tableau Vertex Attrib 0

		// for(std::vector<Vector3>::iterator it = liste->begin(); it != liste->end(); ++it)
			// drawDot(*it);

		drawDot(borders[4]);
		drawLine(borders[0], borders[1]);
		drawLine(borders[0], borders[2]);
		drawLine(borders[1], borders[3]);
		drawLine(borders[2], borders[3]);
		// drawLine(borders[0], borders[3]);
		// drawLine(borders[1], borders[2]);

		// Actualisation de la fenetre

		SDL_GL_SwapWindow(m_fenetre);
	}
}
