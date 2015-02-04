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

/*Vector3**	SceneOpenGL::CreateTable(Vector3 **M, int xMax, int yMax)
{
	Vector3 **table = new Vector3*[yMax];
	for (int i=0; i<yMax; i++)
		table[i] = new Vector3[100];

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
	return table;
}*/

Vector3**	SceneOpenGL::CreateTable(std::vector<Vector3>* points, int yMax)
{
	Vector3 **table = new Vector3*[yMax];
	for (int i=0; i<yMax; i++)
		table[i] = new Vector3[100];

	for (int y=0; y<yMax; y++)
	{
		if (points[y].size() > 0)
		{
			for (float t=0; t<1; t+=0.01f)
			{
				Vector3 p = this->getCasteljau(points[y], points[y].size()-1, 0, t);
				table[y][static_cast<int>(round(t * 100))] = p;
			}
		}
	}

	return table;
}

bool	SceneOpenGL::isLast(Vector3** M, int x, int y, int xMax, int yMax, bool vertical) {

	if (vertical)
	{
		for(; x<xMax; x++)
		{
			if (M[y][x] != Vector3())
				return false;
		}
	}
	else
	{
		for(; y<yMax; y++)
		{
			if (M[y][x] != Vector3())
				return false;
		}
	}
	return true;
}

void	SceneOpenGL::algo_bezier(Vector3 **M, int xMax, int yMax) {

	int BigY = yMax - 2;
	int BigX = xMax - 2;
	points_high = new std::vector<Vector3>[BigY];
	points_down = new std::vector<Vector3>[BigY];
	points_left = new std::vector<Vector3>[BigX];
	points_right = new std::vector<Vector3>[BigX];

	int a = 0;
	for(int y=1; y<=BigY; y++)
	{
		int i=0;
		for(int x=1; x<xMax; x++)
		{
			if (this->isLast(M, x, y, xMax, yMax, true))
			{
				if (M[y-1][x] != Vector3())
					points_high[a].push_back(M[y-1][x]);
			}
			if (M[y][x] == Vector3())
				continue;
			if (i == 0)
			{
				if (M[y-1][x-1] != Vector3())
					points_high[a].push_back(M[y-1][x-1]);
			}
			points_high[a].push_back(M[y][x]);
			i++;
		}
		a++;
	}

	a = 0;
	for(int y=BigY; y>0; y--)
	{
		int i=0;
		for(int x=1; x<xMax; x++)
		{
			if (this->isLast(M, x, y, xMax, yMax, true))
			{
				if (M[y+1][x] != Vector3())
					points_down[a].push_back(M[y+1][x]);
			}
			if (M[y][x] == Vector3())
				continue;
			if (i == 0)
			{
				if (M[y+1][x-1] != Vector3() || y == BigY)
					points_down[a].push_back(M[y+1][x-1]);
			}
			points_down[a].push_back(M[y][x]);
			i++;
		}
		a++;
	}

	a = 0;
	for(int x=1; x<=BigX; x++)
	{
		int i=0;
		for(int y=1; y<yMax; y++)
		{
			if (this->isLast(M, x, y, yMax, yMax, false))
			{
				if (M[y][x-1] != Vector3() || x == 1)
					points_left[a].push_back(M[y][x-1]);
			}
			if (M[y][x] == Vector3())
				continue;
			if (i == 0)
			{
				if (M[y-1][x-1] != Vector3())
					points_left[a].push_back(M[y-1][x-1]);
			}
			points_left[a].push_back(M[y][x]);
			i++;
		}
		a++;
	}

	a = 0;
	for(int x=BigX; x>0; x--)
	{
		int i=0;
		for(int y=1; y<yMax; y++)
		{
			if (this->isLast(M, x, y, yMax, yMax, false))
			{
				if (M[y][x+1] != Vector3())
					points_right[a].push_back(M[y][x+1]);
			}
			if (M[y][x] == Vector3())
				continue;
			if (i == 0)
			{
				if (M[y-1][x+1] != Vector3())
					points_right[a].push_back(M[y-1][x+1]);
			}
			points_right[a].push_back(M[y][x]);
			i++;
		}
		a++;
	}
}

void SceneOpenGL::bouclePrincipale(Vector3 **M, int xMax, int yMax) {

	// Variables

	bool terminer(false);
	// Vector3 **table = this->CreateTable(M, xMax, yMax);

	// Boucle principale

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 1, 0, 1, 0, 3);
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0.5, 0.3, -2.);
		glRotatef(60, 1, 0, 0);
		glRotatef(45, 0, 0 , 1);
		glScalef(0.5/this->scale.getX(), 0.5/this->scale.getY(), 0.5/this->scale.getZ());

	algo_bezier(M, xMax, yMax);

	Vector3 **table1 = CreateTable(points_high, yMax-2);
	Vector3 **table2 = CreateTable(points_down, yMax-2);
	Vector3 **table3 = CreateTable(points_left, xMax-2);
	Vector3 **table4 = CreateTable(points_right, xMax-2);
/*
	for (int y = 0; y < yMax - 2; y++)
		for (int x =0; x < 99; x++)
			if (table1[y][x] == Vector3())
				std::cout << x << " && " << y << std::endl;
*/
	while(!terminer)
	{
		glRotatef(1, 0, 0, 1);
		// Gestion des evenements

		SDL_WaitEvent(&m_evenements);

		if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			terminer = 1;

		// Nettoyage de l'ecran

		glClear(GL_COLOR_BUFFER_BIT);

		// On remplie puis on active le tableau Vertex Attrib 0

		glColor3f(0.5, 0.5, 0.5);
		drawQuad(M[0][0], M[0][xMax - 1], M[yMax - 1][xMax - 1]);
		glColor3f(1, 1, 1);
		drawQuad(M[0][0], M[yMax - 1][xMax - 1], M[yMax - 1][0]);
/*
		glColor3f(1, 0, 0);
		for(int y=0; y<yMax - 2; y++)
			for (int x = 0; x < points_high[y].size() - 1; x++)
				drawLine(points_high[y][x], points_high[y][x+1]);

		glColor3f(0, 1, 0);
		for(int y=0; y<yMax - 2; y++)
			for (int x = 0; x < points_down[y].size() - 1; x++)
				drawLine(points_down[y][x], points_down[y][x+1]);


		glColor3f(0, 1, 1);
		for(int x=0; x<xMax - 2; x++)
			for (int y=0; y<points_left[x].size() - 1; y++)
				drawLine(points_left[x][y], points_left[x][y+1]);

		glColor3f(0, 0, 1);
		for(int x=0; x<xMax - 2; x++)
			for (int y=0; y<points_right[x].size() - 1; y++)
				drawLine(points_right[x][y], points_right[x][y+1]);

*/
		glColor3f(1, 0, 0);
		for(int y=0; y<yMax - 3; y++)
		{
			for (int x = 0; x < 99; x++)
			{
				drawLine(table1[y][x], table1[y][x+1]);
				drawQuad(table1[y][x], table1[y + 1][x], table1[y][x + 1]);
				drawQuad(table1[y + 1][x + 1], table1[y + 1][x], table1[y][x + 1]);
			}
		}

		glColor3f(0, 1, 0);
		for(int y=0; y<yMax - 3; y++)
		{
			for (int x = 0; x < 99; x++)
			{
				drawLine(table2[y][x], table2[y][x+1]);
				drawQuad(table2[y][x], table2[y + 1][x], table2[y][x + 1]);
				drawQuad(table2[y + 1][x + 1], table2[y + 1][x], table2[y][x + 1]);
			}
		}

		glColor3f(0, 1, 1);
		for(int x=0; x<xMax - 3; x++)
		{
			for (int y=0; y<99; y++)
			{
				drawLine(table3[x][y], table3[x][y+1]);
				drawQuad(table3[x][y], table3[x + 1][y], table3[x][y + 1]);
				drawQuad(table3[x + 1][y + 1], table3[x + 1][y], table3[x][y + 1]);
			}
		}

		glColor3f(0, 0, 1);
		for(int x=0; x<xMax - 3; x++)
		{
			for (int y=0; y<99; y++)
			{
				// drawLine(table4[x][y], table4[x][y+1]);
				drawQuad(table4[x][y], table4[x + 1][y], table4[x][y + 1]);
				drawQuad(table4[x + 1][y + 1], table4[x + 1][y], table4[x][y + 1]);
			}
		}

				/* TRIANGLES */

				// drawQuad(table[y][x], table[y + 1][x], table[y][x + 1]);
				// drawQuad(table[y + 1][x + 1], table[y + 1][x], table[y][x + 1]);


		// Actualisation de la fenetre

		SDL_GL_SwapWindow(m_fenetre);
	}
	for(int i=0; i<yMax-2; i++)
		delete [] table1[i];
	delete [] table1;
	for(int i=0; i<yMax-2; i++)
		delete [] table2[i];
	delete [] table2;
	for(int i=0; i<xMax-2; i++)
		delete [] table3[i];
	delete [] table3;
	for(int i=0; i<xMax-2; i++)
		delete [] table4[i];
	delete [] table4;
}
