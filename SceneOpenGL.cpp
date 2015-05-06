#include "SceneOpenGL.hpp"

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
	return true;
}

Vector3 setColor(float height, float echelle)
{
	height = (height)/echelle;
	if (height < 0.3f) {
		return Vector3(height, height, height);
	} else if (height < 0.8f) {
		return Vector3(0, height, 0);
	} else {
		return Vector3(height, height, height);
	}
	return Vector3();
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

float *getTheFucknColor(float r, float g, float b, float a)
{
	float *color = new float[120];
	float co[] =
	{
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a
	};
	for (int i = 0; i < 120; i++)
		color[i] = co[i];
	return color;
}

void drawVox(Vector3 p, int porn, int type) {

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


	GLfloat vertices[] =
	{
		// FACE LEFT //
		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pLBD._x, pLBD._y, pLBD._z, /* sommet 1 */
		pLFU._x, pLFU._y, pLFU._z, /* sommet 2 */

		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pLBD._x, pLBD._y, pLBD._z, /* sommet 1 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 2 */

		// FACE RIGHT //
		pRBU._x, pRBU._y, pRBU._z, /* sommet 0 */
		pRBD._x, pRBD._y, pRBD._z, /* sommet 1 */
		pRFU._x, pRFU._y, pRFU._z, /* sommet 2 */

		pRBU._x, pRBU._y, pRBU._z, /* sommet 0 */
		pRBD._x, pRBD._y, pRBD._z, /* sommet 1 */
		pRFD._x, pRFD._y, pRFD._z, /* sommet 2 */

		// FACE UP //
		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pRBU._x, pRBU._y, pRBU._z, /* sommet 1 */
		pLFU._x, pLFU._y, pLFU._z, /* sommet 2 */

		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pRBU._x, pRBU._y, pRBU._z, /* sommet 1 */
		pRFU._x, pRFU._y, pRFU._z, /* sommet 2 */

		// FACE FRONT //
		pLFU._x, pLFU._y, pLFU._z, /* sommet 0 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 1 */
		pRFU._x, pRFU._y, pRFU._z, /* sommet 2 */

		pLFU._x, pLFU._y, pLFU._z, /* sommet 0 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 1 */
		pRFD._x, pRFD._y, pRFD._z, /* sommet 2 */

		// FACE BACK //
		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 1 */
		pRFU._x, pRFU._y, pRFU._z, /* sommet 2 */

		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 1 */
		pRFD._x, pRFD._y, pRFD._z, /* sommet 2 */

	};

	float *color;

	if (type == 4)
		color = getTheFucknColor(1, 0, 0, 1);
	else if (type == 5)
		color = getTheFucknColor(0.2f, 0.2f, 0.2f, 1);
	else
	{
		if (porn >= 0 && porn < 3)
			color = getTheFucknColor(1, 1, 1, 0.5f);
		else if (porn >= 3 && porn <= 30)
				color = getTheFucknColor(0, 0.2, 0.7, 0.4f);
		else
			color = getTheFucknColor(0, 0, 1, 0.7f);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(4, GL_FLOAT, 0, color);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 30);

	delete[] color;

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void drawFace(Vector3 a, Vector3 b, Vector3 c, Vector3 g, Vector3 h, float echelle) {
	GLfloat vertices[] =
	{
		a._x, a._y, a._z, /* sommet 0 */
		b._x, b._y, b._z, /* sommet 1 */
		c._x, c._y, c._z, /* sommet 2 */

		a._x, a._y, a._z, /* sommet 0 */
		g._x, g._y, g._z, /* sommet 1 */
		h._x, h._y, h._z  /* sommet 2 */
	};

	Vector3 cook = setColor(a._z, echelle);
	float color[] = {cook._x, cook._y, cook._z};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_UNSIGNED_BYTE, 0, color);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void SceneOpenGL::bouclePrincipale(Vector3 **M, int xMax, int yMax) {

	// Variables
	Water wat = Water(M, xMax, yMax);
	Volcan vol = Volcan(wat);
	float echelle = (64/15);

	// Boucle principale
	glEnable (GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, 0, 3);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.5, 0.3, -2.); // (0.8, 0.3, -2.)
	glRotatef(180, 0, 1, 0);
	glRotatef(60, 1, 0, 0);
	glScalef(1/this->scale.getX(), 1/this->scale.getY(), 1/this->scale.getZ());

	Vector3 height;
	int pyramide = 0;
	int z = wat.getZ() - 1;
	bool flag = false;

	for (;z > 0; z--)
	{
		if (flag)
			break;
		for (int y=0; y < wat.getY() ; y++)
		{
			if (flag)
				break;
			for (int x=0; x < wat.getX(); x++)
			{
				if (wat._MW[z][y][x].getType() == 1 || wat._MW[z][y][x].getType() == -1)
				{
					height = wat._MW[z][y][x].getV3();
					flag = true;
					break;
				}
			}
		}
	}

	while(1)
	{
		//glRotatef(1, 0, 0, 1);
		// Gestion des evenements

		SDL_PollEvent(&m_evenements);

		if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE || m_evenements.window.event == SDLK_q)
			break;
		if(m_evenements.window.event == SDLK_SPACE)
			wat.AddWater();
		if(m_evenements.window.event == SDLK_r)
			wat.AddRain();
		if(m_evenements.window.event == SDLK_i)
			wat.AddIndia();
		if(m_evenements.window.event == SDLK_v)
			vol.AddLava(wat, height);

		// Nettoyage de l'ecran

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for(int y=0; y<yMax-1; y++)
		{
			for(int x=0; x<xMax-1; x++)
				drawFace(M[y][x], M[y][x+1], M[y+1][x+1], M[y+1][x+1], M[y+1][x], echelle);
		}
		for(int z=0; z<16; z++)
		{
			for(int y=0; y<yMax; y++)
			{
				for(int x=0; x<xMax; x++)
				{
					int type = wat._MW[z][y][x].getType();
					if (type >= 3)
					{
						int porn = wat._MW[z][y][x].getPerc();
						drawVox(wat._MW[z][y][x].getV3(), porn, type);
					}
				}
			}
		}
		wat.MakeFluid();
		if (pyramide >= 10)
		{
			vol.MakeFluid(wat);
			pyramide = 0;
		}
		pyramide++;
		// Actualisation de la fenetre
		glFlush();
		SDL_GL_SwapWindow(m_fenetre);
	}
	wat.KILL();
}
