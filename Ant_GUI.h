/*
	This file was named wrongly..."Ant_GUI"
	Becuase it contains many other functions such as input functions..etc
*/
#define RETURN_KEY		13
#define BG              172     //78 E
#define TB              30
#define TC              56
#define R_ARROW_KEY		77
#define L_ARROW_KEY		75
#define U_ARROW_KEY		72
#define D_ARROW_KEY		80
#define ESC_KEY			27
#define BA               6

#define TEXTBOX    			   160//15
#define HIGHLIGHTED_TEXTBOX    172//9//251
#define TEXTBOX_COLOR		   175//12//252
#define FORMTEXT_COLOR		   172//12//252
#define BACKGROUND_COLOR	   172//15//250
#define SCROLL_AREA    		   172	

#define ALIGN   70
#define SPACE	3
#define LENGHT  25

typedef struct BUTTON{
                int x1,x2;
                int y1,y2;
                char label[40];
                }BUTTON;
void myPixxy(void *);
void Maximize_Window();
void Menu();
void drawtextbox(int x1,int x2,int y1,int y2,char *);
void gotoxy(int x,int y);
void ShowConsoleCursor(bool);
void color(int color);
void drawbox(int x1,int x2,int y1,int y2,char *);
void clearbox(int,int,int,int);
void clearboxstatic(int x1,int x2,int y1,int y2);
void dotheaction(int spotlight);                     
void scrollboxes(struct BUTTON *Button,int *,int);
void showbox(struct BUTTON Button);
void drawmainframe();
void Fullscreen();
void changeWindowSize(int,int,int,int);
void drawselector();
void scrollboxes(struct BUTTON *Button,int *spotlight,int direction);
void aligncenter(char str[],int y1);
void clearscreen();

void Move_textbox(BUTTON Textbox[],int key,int *index,int size);
void show_InputDetails_Buttons(BUTTON Textbox[],int MAX);
void show_InputDetails_Buttons(BUTTON Textbox[],int MAX);

void showtexbox(BUTTON Button);
int  Form_reads(char *str,int MAX);
int  Function_button();
int  Form_reads_mask(char *input,int MAX);
