#include "my_conscr.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*GLOBAL VARIABLES*/
//x is marginLeft of frame  
//y is marginTop of frame 
//w is width of frame 
//h is height of frame
int x=2,y=5,w=40,h=20;

typedef struct MyCoord{
	int x;
	int y;	
}MyCoord;


typedef struct Snake
{
	int x;
	int y;
	int score;
	int len;
	MyCoord* body;
}Snake;



	int Move(Snake* s,int dx,int dy)
	{
		int i,len;
		int isGameOver=0;

		//if length of snake <=3 then snake can't crash itself. 
		if(s->len>3){
			
			//check whether snake crash itself. 
			for(i=1;i<=s->len;i++){
				if(s->body[0].x==s->body[i].x && s->body[0].y==s->body[i].y){
					isGameOver=1; 
					
					//crash effect :)
					gotoxy(s->body[0].x,s->body[0].y);
					settextattr(15*16+4);
					putchar('x');
					break;
				}
			}
			if(isGameOver==1){
				
				char message[]={"Game Over"};
				int j;
				//writing message to center of frame.
				gotoxy(x+w/2-(strlen(message)/2),y+h/2);
				settextattr(15*16+4);
				for(j=0;j<strlen(message);j++)
					putchar(message[j]);
				return 1;
			}
		}


		len=s->len;
		for(i=len;i>=0;i--)
		{
			s->body[i] = s->body[i-1]; 	
		}
		
		gotoxy(s->body[len].x,s->body[len].y);
		printf(" ");
		if(s->x+dx<=x) s->x=x+w;
		if(s->x+dx>=x+w) s->x=x;
		if(s->y+dy<=y) s->y=y+h;
		if(s->y+dy>=y+h) s->y=y;
		s->x+=dx;
		s->y+=dy;
		
		s->body[0].x=s->x;
		s->body[0].y=s->y;
		for(i=0;i<len;i++)
		{	
			gotoxy(s->body[i].x,s->body[i].y);
			printf("o");
		}
		return 0;

	}
	
	void CreateFrame(int x,int y,int w,int h)
	{
		int i,frameCell=219;
		for(i=x;i<w+x+1;i++)
		{
			gotoxy(i,y);
			putchar(frameCell);
			gotoxy(i,h+y);
			putchar(frameCell);
		}
		
		for(i=y;i<h+y;i++)
		{
			gotoxy(x,i+1);
			putchar(frameCell);
			gotoxy(w+x,i);
			putchar(frameCell);
			
		}
		
	}
	
	
	MyCoord * CreateFood(Snake * s,int x,int y,int w , int h)
	{
		srand(time(NULL));	
		int flag=1;
		MyCoord * foodCoord=(MyCoord*)malloc(sizeof(MyCoord));
		do
		{
			flag=1;
			
			//random point in frame
			foodCoord->x=(x+1)+rand()%(w-1);
			foodCoord->y=(y+1)+rand()%(h-1);
			
			//check whether is it over the snake.
			int i,len;
			len=s->len;
			for(i=len;i>=0;i--)
			{
				//If there is any point that coincides with even one of the snake's body coordinates then flag=0
				//So we should create new random point.
				if(s->body[i].x==foodCoord->x && s->body[i].y==foodCoord->y){
					flag=0;
					break; 
				} 	
			}
			

		} while (flag==0);
		
		
		gotoxy(foodCoord->x,foodCoord->y);
		putchar('*');
		return foodCoord;
	}


	Snake GetSnakeInstance(){
		Snake s;
		s.len = 1;
		s.score=0;
		s.x=x+w/2;
		s.y=y+h/2;
		s.body = (MyCoord*)malloc((w-2)*(h-2)*sizeof(MyCoord));//max dimension of snake 
		s.body[0].x=s.x;
		s.body[0].y=s.y;

		return s;
	}

	int main()
	{
		
		
		int dx=0,dy=0;
		//agent location setted as center of frame
		int xp=(w+x)/2;
		int yp=(y+h)/2;
		char c;//input character
		short up=1,down=1,right=1,left=1;
		
		CreateFrame(x,y,w,h);
		
		Snake s=GetSnakeInstance();
		
		MyCoord * temp=(MyCoord*)malloc(sizeof(MyCoord));
		temp=CreateFood(&s, x,y,w,h);
		
		cursorvisible(0);//invisible
		
		do
		{
			
			gotoxy(x,y-1);printf("SCORE : %d ",s.score); 
			gotoxy(xp,yp);//go to center


			//catching first keyDown event (up,down,left,right)
			if(kbhit()) c=getch();
			if(kbhit()) c=getch();

			pivotPoint :

			//if the direction is up
			if(down==0 && up!=0)
			{
				
				if(kbhit()) c=getch();
				if(kbhit()) c=getch();
				//agent should not go down directly
				if(c==80) c=72;

				switch(c)
				{
					case 72 : dx=0; dy=-1;  break;
					case 75 : dx=-1; dy=0; down=1; break;
					case 77 : dx=1; dy=0; down=1; break;
				}
			}

			//if the direction is down
			if(up==0 && down!=0)
			{
				
				if(kbhit()) c=getch();
				if(kbhit()) c=getch();
				//agent shouldn't go up directly
				if(c==72) c=80;

				switch(c)
				{
					case 75 : dx=-1; dy=0; up=1; break;
					case 77 : dx=1; dy=0; up=1;  break;
					case 80 : dx=0; dy=1;   break;
				}
			}

			//if the direction is left 
			if(right==0 && left!=0)
			{
				
				if(kbhit()) c=getch();
				if(kbhit()) c=getch();
				//agent shouldn't turn right directly
				if(c==77) c=75;

				switch(c)
				{
					case 75 : dx=-1; dy=0;  break;
					case 72 : dx=0; dy=-1; right=1;  break;
					case 80 : dx=0; dy=1; right=1;   break;
				}
					
			}

			//if the direction is right
			if(left==0 && right!=0)
			{
				
				if(kbhit()) c=getch();
				if(kbhit()) c=getch();
				//agent shouldn't turn left directly
				if(c==75) c=77;

				switch(c)
				{
					case 72 : dx=0; dy=-1; left=1;  break;
					case 80 : dx=0; dy=1; left=1;   break;
					case 77 : dx=1; dy=0; break; 	down=1;
				}
					
			}
			
			//direction key controls
			switch(c)
			{
				case 72 : dx=0; dy=-1;if(up==0){ goto pivotPoint;} down=0;  break;
				case 75 : dx=-1; dy=0;if(left==0){ goto pivotPoint;} right=0; break;
				case 77 : dx=1; dy=0; if(right==0){ goto pivotPoint;}left=0;  break;
				case 80 : dx=0; dy=1; if(down==0){ goto pivotPoint;}up=0;   break;
				case 'k': gotoxy(x+3,h+y+3); settextattr(15*16+4); printf("OYUN BITTI !");  return 0;
			}
			
				int isGameOver=Move(&s,dx,dy);
				//MESSAGE AND FINISH
				if(isGameOver==1){
					gotoxy(x,h+y+3);
					printf("END OF GAME");
					getch();
					return 0;
				}
				 
				//Snake eat food and grow
				if(s.x==temp->x && s.y==temp->y ) 
				{ 	
					s.score++;	s.len++; 
					temp=CreateFood(&s,x,y,w,h);//create new food
				}


				//going through the walls
				if(xp<= x)  xp=x+w-1;//from far left to far right 
				if(xp>= x+w ) xp=x+1;//from far rigth to far left
				if(yp<= y )   yp=y+h-1;//from far top to far bottom
				if(yp>= y+h ) yp=y+1;//from far bottom to far top
			
				Sleep(100);
		}while(1);

		return 0;
	}
