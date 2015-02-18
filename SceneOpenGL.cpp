#include "SceneOpenGL.h"

// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
	m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0) {

		scale = Vector3(64, 64, 32) / 0.5f;
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

	GLenum initialisationGLEW(glewInit());

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
	initShaders();
	// glEnable(GL_DEPTH_TEST);
	return true;
}

void setColor(float height, float echelle)
{
	height = (height)/echelle;
	if (height < 0.3f) {
		glColor3f(height, height, height);
	} else if (height < 0.8f) {
		glColor3f(0, height, 0);
	} else {
		glColor3f(height, height, height);
	}
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

void drawTriangles(Vector3 p1, Vector3 p2, Vector3 p3, float echelle) {
	glBegin(GL_TRIANGLE_STRIP);
	setColor(p1.getZ(), echelle);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	setColor(p2.getZ(), echelle);
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	setColor(p3.getZ(), echelle);
	glVertex3f(p3.getX(), p3.getY(), p3.getZ());
	glEnd();
	glFlush();
}

void drawQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) {
	glBegin(GL_QUADS);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	glVertex3f(p3.getX(), p3.getY(), p3.getZ());
	glVertex3f(p4.getX(), p4.getY(), p4.getZ());
	glEnd();
	glFlush();
}

void drawVox(Vector3 p) {

	float x0 = p.getX() - 0.5f;
	float x1 = p.getX() + 0.5f;
	float y0 = p.getY() - 0.5f;
	float y1 = p.getY() + 0.5f;
	float z0 = p.getZ() - 0.5f;
	float z1 = p.getZ() + 0.5f;

	Vector3 pLBU = Vector3(x0, y0, z0);
	Vector3 pLBD = Vector3(x0, y0, z1);
	Vector3 pRBD = Vector3(x1, y0, z1);
	Vector3 pRBU = Vector3(x1, y0, z0);

	Vector3 pLFU = Vector3(x0, y1, z0);
	Vector3 pLFD = Vector3(x0, y1, z1);
	Vector3 pRFD = Vector3(x1, y1, z1);
	Vector3 pRFU = Vector3(x1, y1, z0);

	drawQuad(pLBU, pLBD, pLFU, pLFU);

	drawQuad(pLBU, pLBD, pRBU, pRBD);

	drawQuad(pLFU, pLFD, pRFU, pRFD);

	drawQuad(pRBU, pRBD, pRFU, pRFU);

	// drawQuad(pLBD, pLFD, pRFD, pRBD);

	drawQuad(pLBU, pRBU, pLFU, pRFU);
}

void SceneOpenGL::bouclePrincipale(Vector3 **M, int xMax, int yMax) {

	// Variables
	Water wat = Water(M, xMax, yMax);

	// Boucle principale

	float echelle = (64/15);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 1, 0, 1, 0, 3);
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0.5, 0.3, -2.); // (0.8, 0.3, -2.)
		glRotatef(60, 1, 0, 0);
		glRotatef(125, 0, 0 , 1); // (45, 0, 0, 1)
		glScalef(1/this->scale.getX(), 1/this->scale.getY(), 1/this->scale.getZ());

	while(1)
	{
		// wat.AddWater();
		glRotatef(1, 0, 0, 1);
		// Gestion des evenements

		SDL_PollEvent(&m_evenements);

		if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			break;

		// Nettoyage de l'ecran

		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

		glClear(GL_COLOR_BUFFER_BIT);

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		_colorProgram.use();
	/*	for(int y=0; y<yMax-1; y++)
		{
			for(int x=0; x<xMax-1; x++)
			{
				drawTriangles(M[y][x], M[y][x+1], M[y+1][x+1], echelle);
				drawTriangles(M[y][x], M[y+1][x+1], M[y+1][x], echelle);
			}
		}/*
		glColor4f(0, 0.5, 1, 0.02f);
		for(int z=0; z<16; z++)
		{
			for(int y=0; y<yMax; y++)
			{
				for(int x=0; x<xMax; x++)
				{
					if (wat._MW[z][y][x].getW() == 3)
						drawVox(wat._MW[z][y][x].getV3());
						// drawDot(wat._MW[z][y][x].getV3());
				}
			}
		}
		wat.MakeFluid();*/
		_colorProgram.unuse();
		// Actualisation de la fenetre
		SDL_GL_SwapWindow(m_fenetre);
	}
}

void SceneOpenGL::initShaders() {
	if (_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag") == -1)
		return;
	_colorProgram.addAttribute("vertexPosition");
	if (_colorProgram.linkShaders() == -1)
		return;
}
