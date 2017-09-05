#include<stdlib.h>
#include<GL/glut.h>
#include<string.h>
#include<stdio.h>
int scr=0;
int rvehicleX=200,rvehicleY=430;
int rovehicleX[4], rovehicleY[4];
float total=0;
int i,ri,q;

int score = 0;//for score counting
int screen = 0;
bool collide = false;//check if car collide to make game over

char buffer[10];
int vehicleX = 200, vehicleY = 70;   
int ovehicleX[4], ovehicleY[4];
int divx = 250, divy = 4, movd,rmovd;

void drawText(char ch[],int xpos, int ypos)//draw the text for score and game over
{
    int numofchar = strlen(ch),i;
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <= numofchar - 1; i++)
    {     
		  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
    }
}
 
 
void drawTextNum(char ch[],int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k,i;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <=numtext - 1; i++)
    {
		  if ( i < len )
				 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
		  else
		 {
				 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
				 k++;
		 }
     
    }
}
void ovpos() //calculate positions of other cars
{
    glClearColor(0,0,1,0);
		for(i = 0; i < 4; i++)
			{
				  if(rand() % 2 == 0)
					 {
						  ovehicleX[i] = 200;
					 }
				 else
					 {
						 ovehicleX[i] = 300;
					 }  
				ovehicleY[i] = 1000- i * 160;
			}
}
 void Rovpos() //calculate positions of other cars in reverse mode
{
    glClearColor(0,0,1,0);
	for(i = 0; i < 4; i++)
		{
				 if(rand() % 2 == 0)
				  {
				 	  rovehicleX[i] = 200;
				  }
				  else
				 {
				 	 rovehicleX[i] = 300;
				 }  
		rovehicleY[i] = 0- i * 200;
		}
} 

void drawRoad() //to draw road
{
    glBegin(GL_QUADS); 
        glColor3f(0.5,0.5,0.5);
        glVertex2f(250 - 100, 500);
        glVertex2f(250 - 100, 0);
        glVertex2f(250 + 100, 0);
        glVertex2f(250 + 100, 500);
    glEnd();
}
 
 
void drawDivider()//black patch drawn in middle of road
{
    glLoadIdentity();
   glTranslatef(0, movd, 0);
    for(i = 1; i <= 10; i++)
		{
				 glColor3f(0, 0, 0);
				 glBegin(GL_QUADS);
					 glVertex2f(divx  - 5, divy * 15 * i + 18);
					 glVertex2f(divx  - 5, divy * 15 * i - 18);
					 glVertex2f(divx  + 5, divy * 15 * i - 18);
					 glVertex2f(divx  + 5, divy * 15 * i + 18);
				 glEnd();
    }
    glLoadIdentity();
}
void drawRdivider()//black patch drawn in middle of road for Reverse mode
{
    glLoadIdentity();
    glTranslatef(0, rmovd, 0);
    for(i = 1; i <= 10; i++)
    {
				 glColor3f(0, 0, 0);
				 glBegin(GL_QUADS);
					glVertex2f(divx  - 5, divy * 15 * i + 18);
					glVertex2f(divx  - 5, divy * 15 * i - 18);
					glVertex2f(divx  + 5, divy * 15 * i - 18);
					glVertex2f(divx  + 5, divy * 15 * i + 18);
				 glEnd();
    }
    glLoadIdentity();
}
     
 
void drawVehicle()//car for racing
{
    glPointSize(10.0);
    glBegin(GL_POINTS);//tire
        glColor3f(0,0,0);                     
        glVertex2f(vehicleX - 25, vehicleY + 16); 
        glVertex2f(vehicleX + 25, vehicleY + 16); 
        glVertex2f(vehicleX - 25, vehicleY - 16); 
        glVertex2f(vehicleX + 25, vehicleY - 16);
    glEnd();
     
    glBegin(GL_QUADS);  
        glColor3f(1,0,0);//middle body
        glVertex2f(vehicleX - 25, vehicleY + 20);
        glVertex2f(vehicleX - 25, vehicleY - 20);
        glVertex2f(vehicleX + 25, vehicleY - 20);
        glVertex2f(vehicleX + 25, vehicleY + 20);
    glEnd();
 
    glBegin(GL_QUADS);//up body
        glColor3f(0,0,1);
        glVertex2f(vehicleX - 23, vehicleY + 20);
        glVertex2f(vehicleX - 19, vehicleY + 40);
        glVertex2f(vehicleX + 19, vehicleY + 40);
        glVertex2f(vehicleX + 23, vehicleY + 20);
    glEnd();
 
    glBegin(GL_QUADS);//down body
        glColor3f(0,0,1);
        glVertex2f(vehicleX - 23, vehicleY - 20);
        glVertex2f(vehicleX - 19, vehicleY - 35);
        glVertex2f(vehicleX + 19, vehicleY - 35);
        glVertex2f(vehicleX + 23, vehicleY - 20);
    glEnd();
 } 
void drawRcar()	//car for racing in reverse mode
{
	glPointSize(10.0);
    glBegin(GL_POINTS);//tire
        glColor3f(0,0,0);                     
        glVertex2f(rvehicleX - 25, rvehicleY + 16); 
        glVertex2f(rvehicleX + 25, rvehicleY + 16); 
        glVertex2f(rvehicleX - 25, rvehicleY - 16); 
        glVertex2f(rvehicleX + 25,rvehicleY - 16);
    glEnd();
	glBegin(GL_QUADS);  
        glColor3f(1,0,0);//middle body
        glVertex2f(rvehicleX - 25, rvehicleY + 20);
        glVertex2f(rvehicleX - 25, rvehicleY - 20);
        glVertex2f(rvehicleX + 25, rvehicleY - 20);
        glVertex2f(rvehicleX + 25, rvehicleY + 20);
    glEnd();
 
    glBegin(GL_QUADS);//up body
        glColor3f(0,0,1);
        glVertex2f(rvehicleX - 23, rvehicleY + 20);
        glVertex2f(rvehicleX - 19, rvehicleY + 40);
        glVertex2f(rvehicleX + 19, rvehicleY + 40);
        glVertex2f(rvehicleX + 23, rvehicleY + 20);
    glEnd();
 
    glBegin(GL_QUADS);//down body
        glColor3f(0,0,1);
        glVertex2f(rvehicleX - 23, rvehicleY - 20);
        glVertex2f(rvehicleX - 19, rvehicleY - 35);
        glVertex2f(rvehicleX + 19, rvehicleY - 35);
        glVertex2f(rvehicleX + 23, rvehicleY - 20);
    glEnd();




}
  
void drawOVehicle()//other cars
{
     
    for(i = 0; i < 4; i++)
    {
		
				glPointSize(10.0);
				glBegin(GL_POINTS);//tire
					glColor3f(0,0,0);                     
					glVertex2f(ovehicleX[i] - 25, ovehicleY[i] + 16); 
					glVertex2f(ovehicleX[i] + 25, ovehicleY[i] + 16); 
					glVertex2f(ovehicleX[i] - 25, ovehicleY[i] - 16); 
					glVertex2f(ovehicleX[i] + 25, ovehicleY[i] - 16);
				glEnd();
     
				glBegin(GL_QUADS);  
					glColor3f(0.99609, 0.83984, 0);//middle body
					glVertex2f(ovehicleX[i] - 25, ovehicleY[i] + 20);
					glVertex2f(ovehicleX[i] - 25, ovehicleY[i] - 20);
					glVertex2f(ovehicleX[i] + 25, ovehicleY[i] - 20);
					glVertex2f(ovehicleX[i] + 25, ovehicleY[i] + 20);
				glEnd();
 
				glBegin(GL_QUADS);//up body
					glColor3f(0,1,0);
					glVertex2f(ovehicleX[i] - 23, ovehicleY[i] + 20);
					glVertex2f(ovehicleX[i] - 19, ovehicleY[i] + 40);
					glVertex2f(ovehicleX[i] + 19, ovehicleY[i] + 40);
					glVertex2f(ovehicleX[i] + 23, ovehicleY[i] + 20);
				glEnd();
 
				glBegin(GL_QUADS);//down body
					glColor3f(0,1,0);
					glVertex2f(ovehicleX[i] - 23, ovehicleY[i] - 20);
					glVertex2f(ovehicleX[i] - 19, ovehicleY[i] - 35);
					glVertex2f(ovehicleX[i] + 19, ovehicleY[i] - 35);
					glVertex2f(ovehicleX[i] + 23, ovehicleY[i] - 20);
				glEnd();
     
				ovehicleY[i] = ovehicleY[i] - 8; 
     
				if(ovehicleY[i] > vehicleY - 25 - 25 && ovehicleY[i] < vehicleY + 25 + 25 && ovehicleX[i] == vehicleX)
				{
						collide = true;
				}
     
				if(ovehicleY[i] < -25)
				{ 
					if(rand() % 2 == 0)
					{
						ovehicleX[i] = 200;
					}
					else
					{
						ovehicleX[i] = 300;
					}
					ovehicleY[i] = 600; 
				}

				if(vehicleY>ovehicleY[i])
					total+=0.1;
	
    }

}
void drawRocars()
{
	for(ri = 0; ri < 4; ri++)
    {
				glPointSize(10.0);
				glBegin(GL_POINTS);//tire
					glColor3f(0,0,0);                     
					glVertex2f(rovehicleX[ri] - 25, rovehicleY[ri] + 16); 
					glVertex2f(rovehicleX[ri] + 25, rovehicleY[ri] + 16); 
					glVertex2f(rovehicleX[ri] - 25, rovehicleY[ri] - 16); 
					glVertex2f(rovehicleX[ri] + 25, rovehicleY[ri] - 16);
				glEnd();
     
				glBegin(GL_QUADS);  
					glColor3f(0.99609, 0.83984, 0);//middle body
					glVertex2f(rovehicleX[ri] - 25, rovehicleY[ri] + 20);
					glVertex2f(rovehicleX[ri] - 25, rovehicleY[ri] - 20);
					glVertex2f(rovehicleX[ri] + 25, rovehicleY[ri] - 20);
					glVertex2f(rovehicleX[ri] + 25, rovehicleY[ri] + 20);
				glEnd();
 
				glBegin(GL_QUADS);//up body
					glColor3f(0,1,0);
					glVertex2f(rovehicleX[ri] - 23, rovehicleY[ri] + 20);
					glVertex2f(rovehicleX[ri] - 19, rovehicleY[ri] + 40);
					glVertex2f(rovehicleX[ri] + 19, rovehicleY[ri] + 40);
					glVertex2f(rovehicleX[ri] + 23, rovehicleY[ri] + 20);
				glEnd();
 
				glBegin(GL_QUADS);//down body
					glColor3f(0,1,0);
					glVertex2f(rovehicleX[ri] - 23, rovehicleY[ri] - 20);
					glVertex2f(rovehicleX[ri] - 19, rovehicleY[ri] - 35);
					glVertex2f(rovehicleX[ri] + 19, rovehicleY[ri] - 35);
					glVertex2f(rovehicleX[ri] + 23, rovehicleY[ri] - 20);
				glEnd();
				rovehicleY[ri] = rovehicleY[ri] +8;
				if(rovehicleY[ri] > rvehicleY - 25 - 25 && rovehicleY[ri] < rvehicleY + 25 + 25 && rovehicleX[ri] == rvehicleX)
				{
		
					collide = true;
				}
	
				if(rovehicleY[ri] >1024)
				{ 

					if(rand() % 2 == 0)
					{
						rovehicleX[ri] = 200;
					}
					else
					{
						rovehicleX[ri] = 300;
					}
					rovehicleY[ri] =160; 
				} 
				if(vehicleY<ovehicleY[i])
					total+=0.01;
	
	}
	


}
void Specialkey(int key, int x, int y)//allow to use navigation key for movement of car
{
	
		
	switch(key)
		{
				
				 case GLUT_KEY_UP: 
					 		for(i = 0; i <4; i++)
							 {
							   ovehicleY[i] = ovehicleY[i] - 10;  
			 
							 }
							 movd = movd - 20;
							 break;	

				 case GLUT_KEY_DOWN: 
					for(i = 0; i <4; i++)
							 {
							   ovehicleY[i] = ovehicleY[i] + 10;  
							   rovehicleY[ri] = ovehicleY[ri] + 10;  
							 }
							 movd = movd + 20;
							 break;

				 case GLUT_KEY_LEFT:
							   vehicleX = 200;
							   rvehicleX = 200;
				     		   break;

				 case GLUT_KEY_RIGHT:
								vehicleX = 300;
								rvehicleX = 300;
							 break;
			 
		}

	glutPostRedisplay();
}

void Normalkey(unsigned char key, int x, int y)
{
    switch(key)
    {
				case '1':if(scr == 0) // screen =0 is WELCOME PAGE
							 scr=1; //Instruction PAGE
						 break;
				case '2':if(scr == 1)
							 scr=2; //NORMAL GAME MODE
						 break;
				case 'r':
				case 'R':if(scr==1)
							 scr=3;//Reverse Mode
						break;
	
				
			
				case 27:exit(0);
	
    }
	glutPostRedisplay();
} 

void display()
{
	int s=0;
	if(scr==0)//welcome
	{
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(1,1,1);
				drawText("Sir M Visvesvaraya Institute of Technology Bengaluru", 170, 450);
				drawText("Computer Graphics And Visualization Mini Project", 170, 400);
				drawText("Under Guidance of:", 170, 350);
				drawText("Monica Rani H.G (Asst. Professor)",190,300);
				drawText("PROJECT MEMBERS:",170,230);
				drawText("Varun Gowda K -1MV14CS118",190,200);
				drawText("Durina V S    -1MV14CS126",190,170);
				drawText("PRESS 1 TO CONTINUE",100,100);
				glutSwapBuffers();
    }
	if(scr==1)//instr
	{
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(1,1,1);
				drawText("Use UP ARROW to accelerate", 170, 290);
				drawText("Use LEFT ARROW to move left", 170, 250);
				drawText("Use RIGHT ARROW to move right", 170, 210);
				drawText("Press 2 to continue", 170, 150);
				drawText("Press R to play in reverse mode",170,130);
				glutSwapBuffers();

	}
	if(scr==2)//GAME MODE
	{
				glClear(GL_COLOR_BUFFER_BIT);
				glClearColor(163.0/255.0,117.0/255.0,73.0/255.0,1.0);
				drawRoad(); 
				drawDivider();
				drawVehicle();
				drawOVehicle();
				movd = movd - 16;
				if(movd < - 60)
				{
					movd = 0;
				}
				score=(int)total;
				glColor3f(1,1,1);
				drawText("Score:", 360,455);
				itoa (score, buffer, 10);
				drawTextNum(buffer, 6, 420,455);
				glutSwapBuffers(); 
				for(q = 0; q<=10000000; q++){;}
				if(collide == true)
				{
					for(double t = 0; t<=100000000; t++){;}
							scr=4;
			
				}

	}
	
	
	if(scr==3)//REVERSE MODE
	{
				glClear(GL_COLOR_BUFFER_BIT);
				glClearColor(163.0/255.0,117.0/255.0,73.0/255.0,1.0);
				drawRoad(); 
				drawRdivider();
				drawRcar();
				drawRocars();
				rmovd = rmovd + 16;
				if(rmovd >  60)
				{
					rmovd = 0;
				}
				score=(int)total;//-1;
				glColor3f(1,1,1);
				drawText("Score:", 360,455);
				itoa (score, buffer, 10);
				drawTextNum(buffer, 6, 420,455);
				glutSwapBuffers(); 
				for(q = 0; q<= 10000000; q++){;}
				if(collide == true)
				{
					for(double t = 0; t<=100000000; t++){;}
							scr=4;
			
				}
		


	}
	if(scr==4)//Exit Screen
	{
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(1,1,1);
				drawText("Game Over",200,250);
				drawText("Score:", 200,200);
				itoa (score, buffer, 10);
				drawTextNum(buffer, 6, 260,200);
				glutSwapBuffers();		

	}


}
void init()
{
				glClearColor(0.0,0.0,1.0,1.0);
				glColor3f(0.0,0.0,1.0);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluOrtho2D(0, 500, 0, 500);
				glMatrixMode(GL_MODELVIEW);
}
void main(int argc, char **argv)
{
				glutInit(&argc,argv);
				glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
				glutInitWindowPosition(100,100);
				glutInitWindowSize(800,500);
				glutCreateWindow("2-D Car Game");
				ovpos();
				Rovpos();
				init();
				glutDisplayFunc(display);	
				glutIdleFunc(display);
				glutKeyboardFunc(Normalkey);
				glutSpecialFunc(Specialkey);
				glutMainLoop();
}
