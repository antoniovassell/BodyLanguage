#define _WIN32_WINNT 0x500
#include "Ant_GUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>


#pragma comment(lib,"Winmm.lib")

void Maximize_Window()
{
	HANDLE hconsole;
	hconsole=GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord={159,59};

	SetConsoleScreenBufferSize(hconsole,coord);
    ShowWindow( GetConsoleWindow() , SW_MAXIMIZE);
}

void drawmainframe()
{
    gotoxy(0,2);
    for(int i=0;i<159;i++)
       printf("%c",(unsigned char)220);
    //BUTTOM LINE
    gotoxy(0,37);
    for(int i=0;i<159;i++)
       printf("%c",(unsigned char)220);
    //VERTICAL LEFT
    for(int i=1;i<35;i++)
   	{
   	   gotoxy(70,i+2);
       printf("%c\n",(unsigned char)221); //222
    }
    //VERTICAL RIGHT
    for(int i=1;i<35;i++)
   	{
   	   gotoxy(89,i+2);
       printf("%c\n",(unsigned char)221); //222
    }
}
void changeWindowSize(int x1,int y1,int TOP,int BOTTOM)
{
  HWND console = GetConsoleWindow();     //Creates a handle and assigns it to the consoles windows
  RECT r;        //hmmmm....ask me later
  GetWindowRect(console, &r); //stores the console's current dimensions

  MoveWindow(console, x1, y1, TOP, BOTTOM, TRUE);
}
void drawselector()
{
//220 horzontal
//221 vertical
//254 vertical
  int i;
//  int x1,y1;
  
  gotoxy(1,20);
  for(i=0;i<15;i++)
     printf("%c",(unsigned char)220);
  
  gotoxy(1,23);
  for(i=0;i<15;i++)   
     printf("%c",(unsigned char)220);
  
  for(i=1;i<=3;i++)
   	{
   	   gotoxy(15,i+20);
       printf("%c\n",(unsigned char)223);
    }
  
  gotoxy(16,23);
  for(i=0;i<10;i++)
   	{
   		printf("%c",(unsigned char)220);
    }
}
void showbox(BUTTON Button)
{    
    drawtextbox(Button.x1,Button.x1+13,Button.y1,Button.y1+2,Button.label);
}
//void Fullscreen()
//{
//     HWND hWnd;                                                    //Creating a new handle for a window
//     
//	   SetConsoleTitle("TUAN");                          //Changes the title of the window......
//     hWnd = FindWindow(NULL, "TUAN");                  //Assigns this window to the handle we created....Something like that
//
//     SendMessage(hWnd, WM_SYSKEYDOWN, VK_RETURN, 0xFF000000);      //Passed the boring stuff, this is the nice part,puts the window in fullscreen
//}
   
//void clearboxstatic(int x1,int x2,int y1,int y2)
//{
//     int x=0;
//     int y=0;
//     
//     for(y=1;y<=(y2-y1)+1;y++)
//     {
//         gotoxy(x1-1,(y1+y)-1);
//         printf
//("                                                                                                                                                                                                 ");
//     }
//}

void clearboxstatic(int x1,int x2,int y1,int y2)
{
     int x=0;
     int y=0;
     
     for(y=1;y<=(y2-y1)+1;y++)
     {
         gotoxy(x1-1,(y1+y)-1);
         printf("                ");
     }
}
void clearbox(int x1,int x2,int y1,int y2)
{
     int x=0;
     int y=0;
     
     for(y=1;y<=(y2-y1)+1;y++)
     {
         gotoxy(x1-1,(y1+y)-1);
         x=0;
         for(x=0;x<=(x2-x1);x++)
         {
                printf(" ");    
         }
     }
}
void drawbox(int x1,int x2,int y1,int y2,char *str)
{
    int i;
    gotoxy(x1-1,y1);
 //Top line   
    for(i=0;i<(x2-x1);i++)
   	{
   		printf("%c",(unsigned char)220);
    }

//Left vertical line
    gotoxy(x1,y1+1);

    for(i=0;i<(y2-y1);i++)
   	{
   	   gotoxy(x1-1,i+y1+1);
       printf("%c\n",(unsigned char)221);
    }

    gotoxy(x1-1,y2);

//Bottom line
    for(i=0;i<(x2-x1);i++)
   	{
   		printf("%c",(unsigned char)223);
    }

//Right veritcal
  	for(i=1;i<(y2-y1);i++)                  //4
   	{
        gotoxy(x2-2,(y2)-i);
   		printf("%c",(unsigned char)222);
    }
    
    gotoxy(x1,y1+1);
    printf("%s",str);
}
void drawtextbox(int x1,int x2,int y1,int y2,char *str)
{    
    int i;
    gotoxy(x1-1,y1);
	
    printf("%c",(unsigned char)201);    //169
	
    for(i=0;i<(x2-x1);i++)
   	{
   		printf("%c",(unsigned char)196);
    }
    printf("%c\n",(unsigned char)187);  //191

    gotoxy(x1,y1+1);

    for(i=0;i<(y2-y1-1);i++)
   	{
   	   gotoxy(x1-1,i+y1+1);
       printf("%c\n",(unsigned char)179);
    }

    gotoxy(x1-1,y2);
    printf("%c",(unsigned char)200);     //192

    for(i=0;i<(x2-x1);i++)
   	{
   		printf("%c",(unsigned char)196);
    }
    printf("%c",(unsigned char)188);    //217

  	for(i=1;i<=(y2-y1-1);i++)                  //4
   	{
        gotoxy(x2,(y2)-i);
   		printf("%c",(unsigned char)179);
    }
    gotoxy(x1+(((x2-x1)/2)-(strlen(str)/2)),y1+1);
    printf("%s",str);
}
void ShowConsoleCursor( bool bShow ) //Not define in dev but in VC, hmmm....i could easily discard this when i switch
{
	static HANDLE		hOut;
	static BOOL		    firstTime = TRUE;
	CONSOLE_CURSOR_INFO cursorInfo;

	if(firstTime)
	{
		hOut		= GetStdHandle( STD_OUTPUT_HANDLE );
		firstTime	= FALSE;
	}

	cursorInfo.dwSize	= 10;
	cursorInfo.bVisible 	= bShow;

	SetConsoleCursorInfo( hOut,
                              &cursorInfo );
}
/******************************************/
void color(int color)
{
      static HANDLE hconsole;
      hconsole = GetStdHandle(STD_OUTPUT_HANDLE); 
      SetConsoleTextAttribute(hconsole,color);
}
/**********************************/

void gotoxy(int x,int y)
{
     COORD coord;

     coord.X = x;
     coord.Y = y;

     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
/*************************************/
void scrollboxes(BUTTON *Button,int *spotlight,int direction)
{
	static int index=0;
    static HANDLE hconsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole,SCROLL_AREA);
    for(int moment=1;moment<=5;moment++)
    {
            if(_kbhit())
            {
                _getch();
            }
            for(index=0;index<BA;index++)
            {
                  clearboxstatic(Button[index].x1-1,Button[index].x1+10,Button[index].y1,Button[index].y1+3);
            }
            
			color(BG);
            drawbox( Button[0].x1-1,Button[0].x1+17,12,16,"");
            SetConsoleTextAttribute(hconsole,SCROLL_AREA);

            for(index=0;index<BA;index++)
            {
                  Button[index].y1+=direction;
                  
                  if(direction==-1)
                  {
                       if((Button[index].y1<3))
                       {
                          Button[index].y1=32;
                       }
                  }
                  if(direction==1)
                  {
                       if((Button[index].y1>32))
                       {
                          Button[index].y1=3;
                       }
                  }
            }
            for(index=0;index<BA;index++)
            {
                  //if((Button[index].y1>0) && (Button[index].y1<33))
                       showbox(Button[index]);
                       
					   color(BG);
					   drawbox( Button[0].x1-1,Button[0].x1+17,12,16,"");
					   SetConsoleTextAttribute(hconsole,SCROLL_AREA);
            }      

          //  Sleep(5);
     }
     
     *spotlight+=(direction*-1);
	 
     if((*spotlight)>BA-1)
	 {   
		 (*spotlight) =0;
	 }
     else
     if((*spotlight)<0)
	 {   
		 (*spotlight)=(5);
	 }
}
void aligncenter(char str[],int y1)
{
	int lenght=strlen(str);
	int x1=(159/2) - (lenght/2);

	gotoxy(x1,y1);
	printf("%s",str);
}
void clearscreen()
{
	gotoxy(0,0);

printf("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ");
	gotoxy(0,0);
}
void Move_textbox(BUTTON Textbox[],int key,int *index,int size)
{
	int direction=0;
	//PlaySound(TEXT("nav.WAV"),NULL,SND_ASYNC);
	
	switch(key)
	{
		case U_ARROW_KEY: direction =-1;
						  break;
		case D_ARROW_KEY: direction =1;
						  break;
		case L_ARROW_KEY: direction =-1;
						  break;
		case R_ARROW_KEY: direction =1;
						  break;
		default:		  return;
						  break;
	}
	(*index)+=direction;

	if(*index==size)
	{	
		(*index)=0;
		drawtextbox(Textbox[size-1].x1,Textbox[size-1].x2,Textbox[size-1].y1,Textbox[size-1].y2,"");
	}
	else
	if(*index <0)
	{
		(*index)=size-1;
		drawtextbox(Textbox[0].x1,Textbox[0].x2,Textbox[0].y1,Textbox[0].y2,"");
	}
	else
		drawtextbox(Textbox[(*index)-direction].x1,Textbox[(*index)-direction].x2,Textbox[(*index)-direction].y1,Textbox[(*index)-direction].y2,"");


}
int  Function_button()
{
	ShowConsoleCursor(false);
	char ch;
	while(1)
	{
		ch=(char)_getch();
		if(ch<=0)
		{
		      ch=(char)_getch();
		      if(ch==U_ARROW_KEY)
		             return U_ARROW_KEY;
		      if(ch==D_ARROW_KEY)
		             return D_ARROW_KEY;
		      else
		          continue;
		}
		else
		if(ch==13)
		      return RETURN_KEY;
	}
}
void show_InputDetails_Buttons(BUTTON Textbox[],int MAX)
{
	int index=0;

	for(index=0;index<MAX;index++)
    {
               showtexbox(Textbox[index]);
    }
}
void reads(char *input,int MAX)
{
   int i=0;   
   char ch=0;

   while(1)
        {
           ch=(char)_getch();
           fflush(stdin);

           if(ch<=0)
              {
                  ch=(char)_getch();
                  continue;
              }
           else
           if(ch==13)
              {
                  if(i>0)
                    {break;}
              }
           else
           if(ch==8)
  	          {
       	          if(i>0)
                    {
                       printf("\b \b");
                 	   i--;
                 	   continue;
         	 	    }
              }
           else
           if((ch>=65 && ch<=90) || (ch>=97 && ch<=122) || (ch>=48 && ch<=57) || ch==32)
              {
                  if(i<MAX)
                    {
                       input[i]=ch;
  		               printf("%c",input[i]);
                       i++;
                    }
              }
        }
    for(i=i;i<MAX;i++)
    	{
         input[i]='\0';
        }
}
int  Form_reads(char *input,int MAX)
{
   ShowConsoleCursor(true);
	int i=strlen(input); 
   printf(" %s",input);
   char ch='\0';
   
   while(1)
        {
           ch=(char)_getch();
           fflush(stdin);

           if(ch<=0)
              {
                  ch=(char)_getch();
                                   
                  if(ch==U_ARROW_KEY)
                     {
                         for(i=i;i<MAX;i++)
    	          		 {
                      		input[i]='\0';
                  		 }
						 	return U_ARROW_KEY;
                     }
                  if(ch==D_ARROW_KEY)
                     {
						 for(i=i;i<MAX;i++)
    	          		 {
                      		input[i]='\0';
                  		 }
                         	return D_ARROW_KEY;
                     }
                  else
                      continue;
              }
           else
           if(ch==13)
              {
                  if(i>0)
                    {
						for(i=i;i<MAX;i++)
    					{
         					input[i]='\0';
        				}
						return D_ARROW_KEY;
				  	}
              }
           else
           if(ch==8)
  	          {
       	          if(i>0)
                    {
                       printf("\b \b");
                 	   i--;
                 	   continue;
         	 	    }
              }
           else
           if((ch>=65 && ch<=90) || (ch>=97 && ch<=122) || (ch>=48 && ch<=57) || ch==32 ||ch==46||ch==64)
              {
                  if(i<MAX)
                    {
                       input[i]=ch;
  		               printf("%c",input[i]);
                       i++;
                    }
              }
        }
    for(i=i;i<MAX;i++)
    	{
         input[i]='\0';
        }
}
void showtexbox(BUTTON Button)
{    
    drawtextbox(Button.x1,Button.x2,Button.y1,Button.y2,Button.label);
}
int  Form_reads_mask(char *input,int MAX)
{
   ShowConsoleCursor(true);
   int i=strlen(input); 
   for(int x=0;x<i;x++)
	   printf("*");
   
   char ch='\0';
   
   while(1)
        {
           ch=(char)_getch();
           fflush(stdin);

           if(ch<=0)
              {
                  ch=(char)_getch();
                                   
                  if(ch==U_ARROW_KEY)
                     {
                         for(i=i;i<MAX;i++)
    	          		 {
                      		input[i]='\0';
                  		 }
						 	return U_ARROW_KEY;
                     }
                  if(ch==D_ARROW_KEY)
                     {
						 for(i=i;i<MAX;i++)
    	          		 {
                      		input[i]='\0';
                  		 }
                         	return D_ARROW_KEY;
                     }
                  else
                      continue;
              }
           else
           if(ch==13)
              {
                  if(i>0)
                    {
						for(i=i;i<MAX;i++)
    					{
         					input[i]='\0';
        				}
						return D_ARROW_KEY;
				  	}
              }
           else
           if(ch==8)
  	          {
       	          if(i>0)
                    {
                       printf("\b \b");
                 	   i--;
                 	   continue;
         	 	    }
              }
           else
           if((ch>=65 && ch<=90) || (ch>=97 && ch<=122) || (ch>=48 && ch<=57) || ch==32)
              {
                  if(i<MAX)
                    {
                       input[i]=ch;
  		               printf("*");
                       i++;
                    }
              }
        }
    for(i=i;i<MAX;i++)
    	{
         input[i]='\0';
        }
}


#define SIZE 200

//void myPixxy(void *p)
//{
//	static PIX pix[SIZE]={0,0,0};
//    //srand(time(NULL));
//    static int WIT=150, HEIGHT=58, ySTART=37,xSTART=0,F_R=20;
//
//    int y1=0,x1=0,xdirection=0,ydirection=0,flag=0;
//    int index=0;
//    
//    for(index=0;index<SIZE;index++)
//    {
//        if(index>WIT-1)
//             pix[index].x1=WIT;
//        else
//             pix[index].x1=index;
//    
//        if(index>HEIGHT-1)
//             pix[index].y1=HEIGHT-((index/4));
//        else
//             pix[index].y1=index;
//             
//        pix[index].color=rand()%15+160;
//        pix[index].xdir=1;
//        pix[index].ydir=1;
//    }
//    //while(1)
//    //{             
//       //  ySTART=rand()%10;
//       //  HEIGHT=rand()%10+50;//(ySTART*3);
//       //  xSTART=rand()%50;
//       //  WIT=  rand()%50+100;//(xSTART*3);
//         
//         for(int i=0;i<=1;i++)
//         {
//             for(index=0;index<SIZE;index++)
//             {
//                 gotoxy(pix[index].x1,pix[index].y1);
//                 color(pix[index].color);
//                 putch(42);
//             }
//              Sleep(F_R);
//             for(index=0;index<SIZE;index++)
//             {
//                 gotoxy(pix[index].x1,pix[index].y1);
//                 putch(32);
//             }
//    
//            for(index=0;index<SIZE;index++)
//            {        
//                if(pix[index].x1>=WIT)
//                    pix[index].xdir=-1;
//                if(pix[index].x1<=xSTART)
//                    pix[index].xdir=1;
//                
//                if(pix[index].y1>=HEIGHT)
//                    pix[index].ydir=-1;
//                if(pix[index].y1<=ySTART)
//                    pix[index].ydir=1;
//                
//                pix[index].x1+=pix[index].xdir;
//                pix[index].y1+=pix[index].ydir;
//            }    
//        //}          
//    }
//}
