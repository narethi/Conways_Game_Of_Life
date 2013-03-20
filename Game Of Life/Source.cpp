#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gl/glut.h>
#include <gl/GL.h>


void renderWindow(void);
void buildGrid(void);
void reshapeWindow(int w, int h);
void drawCell(int x, int y);
void initiateWorld(void);
void checkWorld(void);
void checkCell(int x, int y);
void populateWorld(void);
void randomGenerator(void);
void mainMenu(int option);
void speedMenu(int option);
void godMode(int button, int state, int x, int y);

//Global constants for screen size
int WIDTH = 700;
int HEIGHT = 700;

//Speed control for the delay between renderings
int SPEED_CONTROL = 500;

//Menu ids
int MAIN_MENU;
int SPEED_MENU;

//Arrays for tracking cell growth
bool CELL_WORLD[90][90];
bool TEMP_WORLD[90][90];

//boolean for tracking whether or not the world is in progress
bool PAUSE_WORLD = false;

//floats for storing the ccell color
GLfloat RED = 1.0, GREEN = 1.0, BLUE = 1.0;


/****************************

godMode takes the mouse input and checks if the cell is active
if the cell is active turn it off and if the cell is inactive
inputs:
	Button: takes the button input
	State: checks to see status of the button
	x: checks the x position of mouse
	y: checks the y position of the mouse
outputs:
	none
prints:
	Draws cells

****************************/
void godMode(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (CELL_WORLD[x/10 + 10][y/10 + 10] == true) TEMP_WORLD[x/10 + 10][y/10 + 10] = false;
		else TEMP_WORLD[x/10 + 10][y/10 + 10] = true;
		populateWorld();
		glFlush();
	}
	else;
}

/****************************

Check world checks each cell in the array
inputs:
	none  
outputs:
	none
prints:
	none

****************************/
void checkWorld(void)
{
	for (int i = 0; i<90; i++)
	{
		for (int j = 0; j<90; j++)
		{
			checkCell(i,j);
		}
	}

}

/****************************

populateWorld draws the active cells in black and
all inactive cells in red.
inputs:
	none
outputs:
	none
prints:
	Draws cells

****************************/
void populateWorld(void)
{
	for (int i = 0; i<90; i++)
	{
		for(int j = 0; j<90; j++)
		{
			if(TEMP_WORLD[i][j] == true)
			{
				CELL_WORLD[i][j] = true;
			}
			else
			{
				CELL_WORLD[i][j] = false;
			}
			if(i < 80 && j < 80 && i > 9 && j > 9)
			{
				if(CELL_WORLD[i][j] == true)
				{
				RED = 0.0;
				GREEN = 0.0;
				BLUE = 0.0;
				drawCell(i*10 - 95, j*10 - 95);
				}
				else
				{
				RED = 1.0;
				GREEN = 0.0;
				BLUE = 0.0;
				drawCell(i*10 - 95, j*10 - 95);
				}
			}
			else;
		}
	}
}

/****************************

initiateWorld sets all the cells to inactive
inputs:
	none
outputs:
	none
prints:
	none

****************************/
void initiateWorld(void)
{
	for (int i = 0; i<90; i++)
	{
		for (int j = 0; j<90; j++)
		{
			CELL_WORLD[i][j] = false;
			TEMP_WORLD[i][j] = false;
		}
	}

}

/****************************

checkCell check and individual cell at
x and y in CELL_WORLD
inputs:
	x: x input of the array
	y: y input of the array
outputs:
	none
prints:
	none

****************************/
void checkCell(int x, int y)
{
	int cells = 0;

	for (int i = 0; i<= 2; i++)
	{
		for (int j = 0; j<= 2; j++)
		{
				if (CELL_WORLD[x+i-1][y+j-1] == true) cells++;
				else;
		}
	}

	if(cells == 3) TEMP_WORLD[x][y] = true; 
	else if(cells > 4 || cells < 3) TEMP_WORLD[x][y] = false;
	else;
}

/****************************

renderWindow clears buffers, and sets the clear color
to white
inputs:
	none
outputs:
	none
prints:
	none

****************************/
void renderWindow(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WIDTH,HEIGHT,0);
	buildGrid();

}

/****************************

reshapeWindow resets the window dimensions, and the viewport
inputs:
	none
outputs:
	none
prints:
	none

****************************/
void reshapeWindow(int w, int h)
{
	WIDTH = w;
	HEIGHT = h;
	glViewport(0,0,w, h);
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

/****************************

runWorld populates world and then checks each cell
inputs:
	none
outputs:
	none
prints:
	none

****************************/
void runWorld(void)
{

	populateWorld();
	checkWorld();
	glFlush();		
	_sleep(SPEED_CONTROL);
}

/****************************

buildGrid draws the grid that contains all the cells
inputs:
	none
outputs:
	none
prints:
	none

****************************/
void buildGrid(void)
{
	glPointSize(1.0);
	glColor3f(0.5, 0.5, 0.5);
	for (int i = 0; i<=70; i++)
	{
		glBegin(GL_LINES);
		glVertex2i(i*10, 0);
		glVertex2i(i*10,700);
		glEnd();
	}
	for(int j = 0; j<=70; j++)
	{
		glBegin(GL_LINES);
		glVertex2i(0,j*10);
		glVertex2i(700, j*10);
		glEnd();
	}
}

/****************************

randomGenerator uses the computer clock to generate random numbers
between 0 and 10, then if the number is less than or equal to 3
activate the cell otherwise deactivate the cell
inputs:
	none
outputs:
	none
prints:
	none

****************************/
void randomGenerator(void)
{
	int random;
	srand(time(NULL));
	for(int i = 0; i<90; i++)
	{
		for(int j = 0; j<90; j++)
		{
			random = rand() % 10;
			if(random <= 3)
			{
				TEMP_WORLD[i][j] = true;
			}
			else
			{
				TEMP_WORLD[i][j] = false;
			}
		}
	}
}

/****************************

drawCell draws a cell at the x and y coordinates
inputs:
	x: x input that is passed is the coordinate that the cell will appear
	y: y input that is passed is the coordinate that the cell will appear
outputs:
	none
prints:
	none

****************************/
void drawCell(int x, int y)
{
	glPointSize(9.0);
	glColor3f(RED, GREEN, BLUE);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}

/****************************

speedMenu contains all the options for speed selection menu,
the speed is chosen depending on the value
inputs:
	option: menu item choice
outputs:
	none
prints:
	none

****************************/
void speedMenu(int option)
{
	switch (option)
	{
	case 0:
		SPEED_CONTROL = 100;
		break;
	case 1:
		SPEED_CONTROL = 200;
		break;
	case 2:
		SPEED_CONTROL = 300;
		break;
	case 3:
		SPEED_CONTROL = 400;
		break;
	case 4:
		SPEED_CONTROL = 500;
		break;
	}
}

/****************************

mainMenu chooses which action to take
inputs:
	option: Choice of the action to take
outputs:
	none
prints:
	none

****************************/
void mainMenu(int option)
{
	switch(option)
	{
	case 0:
		if(PAUSE_WORLD == false)
		{
			PAUSE_WORLD = true;
			glutIdleFunc(populateWorld);
			checkWorld();
			populateWorld();
			glFlush();
		}
		else
		{
			PAUSE_WORLD = false;
			glutIdleFunc(runWorld);
		}
		break;
	case 1:
		randomGenerator();
		populateWorld();
		glFlush();
		break;
	case 2:
		initiateWorld();
		populateWorld();
		glFlush();
		break;
	case 3:
		exit(0);
		break;
	}
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Conway's Game Of Life");
	glutDisplayFunc(renderWindow);
	glutReshapeFunc(reshapeWindow);
	initiateWorld();
	randomGenerator();
	glutMouseFunc(godMode);

	/*Entryof menus*/
	//Speed selection submenu
	SPEED_MENU = glutCreateMenu(speedMenu);
	glutAddMenuEntry(".1 Seconds", 0);
	glutAddMenuEntry(".2 Seconds", 1);
	glutAddMenuEntry(".3 Seconds", 2);
	glutAddMenuEntry(".4 Seconds", 3);
	glutAddMenuEntry(".5 Seconds", 4);

	//Main menu
	MAIN_MENU = glutCreateMenu(mainMenu);
	glutAddSubMenu("Set delay", SPEED_MENU);
	glutAddMenuEntry("Pause/Resume", 0);
	glutAddMenuEntry("Randomize", 1);
	glutAddMenuEntry("Clear", 2);
	glutAddMenuEntry("Exit", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutIdleFunc(runWorld);
	glutMainLoop();
	return 0;

}