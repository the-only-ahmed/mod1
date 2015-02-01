#include "SceneOpenGL.h"

// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre, Vector3 middle) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
	m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0) {

		scale = middle / 0.5f;
		scale.setZ(scale.getZ() * -0.5);
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

void drawQuad(Vector3 p1, Vector3 p2, Vector3 p3) {
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	glVertex3f(p3.getX(), p3.getY(), p3.getZ());
	glEnd();
	glFlush();
}

Vector3	SceneOpenGL::getCasteljau(std::vector<Vector3> points, int r, int i, float t) {

	if (r == 0)
		return points[i];

   Vector3 p1 = this->getCasteljau(points, r - 1, i, t);
   Vector3 p2 = this->getCasteljau(points, r - 1, i + 1, t);

	Vector3 p = (p2 * t);
	Vector3 p42 = (p1 * (1 - t));
	return Vector3(p42 + p);
}

void SceneOpenGL::bouclePrincipale(Vector3 **M, int xMax, int yMax) {

	// Variables

	bool terminer(false);

	// Boucle principale

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 1, 0, 1, 0, 3);
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0.5, 0.3, -2.);
		glRotatef(60, 1, 0, 0);
		glRotatef(45, 0, 0, 1);
		glScalef(0.5/this->scale.getX(), 0.5/this->scale.getY(), 0.5/this->scale.getZ());

	while(!terminer)
	{
		// Gestion des evenements

		SDL_WaitEvent(&m_evenements);

		if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			terminer = 1;

		// Nettoyage de l'ecran

		glClear(GL_COLOR_BUFFER_BIT);

		// On remplie puis on active le tableau Vertex Attrib 0

		glColor3f(0, 1, 0);
		drawQuad(M[0][0], M[0][xMax - 1], M[yMax - 1][xMax - 1]);
		drawQuad(M[0][0], M[yMax - 1][xMax - 1], M[yMax - 1][0]);

		Vector3 **table = new Vector3*[yMax];
		for (int i=0; i<yMax; i++)
			table[i] = new Vector3[100];
		glColor3f(1, 0, 0);
		for (int y=0; y<yMax; y++)
		{
			std::vector<Vector3> points;
			for (int x=0; x<xMax; x++)
			{
				if (M[y][x] != Vector3() || (y == yMax - 1 && x == 0) || (y == 0 && x == 0) || (y == 0 && x == xMax - 1) || (y == yMax - 1 && x == xMax - 1))
					points.push_back(M[y][x]);
			}
			if (points.size() > 0)
			{
				for (float t=0; t<1; t+=0.01f)
				{
					Vector3 p = this->getCasteljau(points, points.size()-1, 0, t);
					table[y][static_cast<int>(t * 100)] = p;
				}
			}
		}

		for (int x=0; x<100; x++)
		{
			for (int y=0; y<yMax - 1; y++)
			{
				drawLine(table[y][x], table[y + 1][x]);
			}
		}

		// Actualisation de la fenetre

		SDL_GL_SwapWindow(m_fenetre);
	}
}
