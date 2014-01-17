/*
	Program: Body Language
	Authors: Antonio Vassell
			 Mannin Marsh
			 Renae Virgo
			 Hillary Evelyn
	Date:    April 15, 2010

	Purpose: Semester 2 Programming project
			 To stimulate a Program for the body language fitness centre
*/

/*..........................HEADER FILES ...................................*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <process.h>	//Provides the ability for the program to be mulithreaded
#include "Ant_GUI.h"	//These are my header files i made to hold some extra functions, used for GUI, secured input, extra
#include "Database.h"	//This includes more functions such as add member, print member, etc
#include <signal.h>		//This is to provide support to handle ctlr signals
						//Prevent the program from crashing when ctrl+break (etc) key is press

//Constant values
#define Main_BA 	6   //Amount of buttons for the main menu
#define SIGN_IN		0	//Giving the user options a name to make the code more user friendly
#define SIGN_UP		1	
#define ADMIN_AREA	2
#define TRAINERS	3
#define HELP		4
#define EXIT		5	
	
#define SIZE 200
typedef struct 
               {
                  int x1,y1,color,xdir,ydir;
               }PIX;
//Use to collect the time from the user. Only use on place in the program though
typedef struct{
				int day;
				int hour;
				int mins;
				}TIME;
/*...........................FUNCTION PROTOTYPES..........................*/
void Admin_login();									//To allow an administrator to loging
void Admin_Area();									//Admin Options after 
void InitializeMain_Buttons(BUTTON*);				//To initialize main text buttons such as the x1, y1 values
void InitializeGUI(BUTTON*,int*);					//Display the main GUI
void Main_Menu(BUTTON *Button,int *spotlight);		//The main menu options
void Sign_in();										//Allow the user to sign in
void Get_Details(char *username,char * password);	//To get username and password, not in use no
void Member_Status_Report(MEMBER * Member);			//Run the status report for the user/member
void Member_Area(MEMBER *Member);					//Member options after signing in 
void Member_Payment(MEMBER *Member);				//Allows the user to make a payment
void Display_Reports();								//Admin options to display different reports
void Income_Report();								//Run the income report
void MemberNotification_Report();					//Run the Notification report
void Trainers_Report();								//Run the Trainers report
void Tae_Kwon_do_Report();							//Run the tae kwon do report
void Update_Files();								//Use to update all the records in the database, fees owing..
void Load_Database();								//Use to check if database are created at the start of the program
void About();										//Print information about the gym
void Navigation();									//Information about navigation the system
void Information();									//Options for information about the system
BOOL CtrlHandler( DWORD fdwCtrlType );				//To control ctrl break signals
void Non_members();									//Allows non members to make transactions and enter the gym
void Trainer_Area(TRAINER);							//Options for trainers after signing in 
void Trainer_Sign_up(void);							//To allow a new trainer to sign up
void Trainer_Sign_in(void);							//Allow a trainer to sign in 
void Trainer(void);									//Options for trainers to sign in or sign up
void Display_TrainerMembers(TRAINER Trainer);		//Displays Traineres and thier functions
int correctTime(MEMBER Member);						//Make sure the user signs in the correct time if she is a tae-kwon-do member

int  switch_AdminInput(int index,char *username,char *password);	//Able the user to switch between text boxes and perform actions
void Initialize_Signin_Buttons(BUTTON Textbox[],int);				//Initialize text boxes, x1 and y1 values etc...for signin() function
void display_Signin_sideDetails(BUTTON Textbox[]);					//Display the details at the side of each text box...for sign in() function and others

int	 switch_SigninInput(int index,char *username,char*password);	//Same concepts here
void display_TrainerButtons_Interfaces(BUTTON Textbox[]);
int  switch_TrainerInputDetails(int index,TRAINER *Trainer,char *);


int main()
{
	CtrlHandler( true);								//Called to disabled the control+break signal
	
	//Declarations
	BUTTON Button[Main_BA],*Ptr_Button=Button;		//Declaring text boxes
	int index=0,spotlight=0,direction=0,y1=0,ans=0; //
	
	InitializeGUI(Ptr_Button,&spotlight);			//Draw the GUI on screen such as the textboxes for the main menu..
													//The frame, the color, so forth
	color(10);			
	Load_Database();								//Check in database exist, if not, create them
	
	while(1)								//Creates an infinite loop
	{	
		Main_Menu(Button,&spotlight);		//Gives user options to choose
		
		ShowConsoleCursor(true);			//Show the cursor, It was disable before
		switch(spotlight)					//Switch choice
		{
			case SIGN_IN:	Sign_in();		//If they choose SIGN in then call this function
							break;

			case SIGN_UP:	Add_Member();	//Same concept applices here
							break;

			case ADMIN_AREA:Admin_login();
							break;

			case TRAINERS:	Trainer();
							break;

			case HELP:		Information();
							break;

			case EXIT:		exit(0);		//Exit
							break;
		}
		InitializeGUI(Ptr_Button,&spotlight);	//After functions has run reshow the main interface
	}
	_getch();
    return 0;
}

void Sign_in()
{
	/*
		Purpose: 	Allows a client to sign in with thier user details
	*/
	//Clear the screen
	color(BACKGROUND_COLOR);
	clearscreen();
	//Declarations
	char username[20]={""},password[20]={""};			//to hold temporary login details
	bool flag=false;									//Signal if access or denied
	FILE *Members_File;									//Members file pointer
	int index=0,key=0,chances=3,time_check=0;
	MEMBER Dummy;										//Use for temporary record
	MEMBER Member;										//Member record
	time_t Current_time;								//Use to store current time
	BUTTON Textbox[5];									//Declare 5 textboxes

	//Open database and check if it is opened properly
	if((Members_File=fopen("Members.DAT","rb"))==NULL)
	{
		//If not then
		aligncenter("ERROR: OPENING DATABASE TO SIGN IN.",29);
		aligncenter("PROGRAM WILL EXIT, PRESS ANY KEY TO CONTINUE",30);
		_getch();
		//and
		exit(0);
	}

	time(&Current_time); 								//Assign current time to the variable...
	Initialize_Signin_Buttons(Textbox,5);				//Initialize signin textboxes...x1 ,y1  values
	
	while(1)		//Infinite loop
	{
		//Clear the screen
		color(BACKGROUND_COLOR);
		clearscreen();

		aligncenter("PLEASE ENTER YOUR LOGIN DETAILS BELOW",10);
		color(FORMTEXT_COLOR);
		display_Signin_sideDetails(Textbox);			//Displays details of button at the side suc as "ENTER PASSWORD HERE"
		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,5);			//Display the textboxes on screen
		flag=false;
		index=0;
		//Set these variables to null
		strcpy(password,"");
		strcpy(username,"");

		while(1)	//Another infinite loop
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");   //This draws the selected text
			
			gotoxy(Textbox[index].x1+1,Textbox[index].y1+1);	//Make any output print 			
															    //inside of the selected textbox
			key=switch_SigninInput(index,username,password);
			
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 2:		Non_members();		//Call non-members function
								flag=true;
								break;
					case 3:		//If user selected enter then check if username and password exist
								fseek(Members_File,0L,SEEK_SET);	//Set file pointer at the begining of the file
								//Then loop throug the file "Members databa"
								do{
									//Reading one record at a time
									//And checking if its empty are not
						           	if((fread(&Member,sizeof(MEMBER),1,Members_File))==0)
						           	{
										//If so then break out of the loop
						             	break;
						           	}
						         	//ELSE
									//Check the record if it has the clients username and password if they are correct
						           	if((strcmp(Member.Username,username)==0) && (strcmp(Member.Password,password))==0)
						           	{
									   //If so then chekc if member type is a tae-kwon-do member
						               if(Member.Member_type==2)
											time_check=correctTime(Member);		//If so then check if user is logining the correct time
									   else
										    time_check=1;						//Else set this variable to one and skip all of the below code to give user access
									  
									   clearscreen();
									   //Base on the values receive from the function correctTime
									   //And return to time_check
									   if(time_check==-1)			
									   {
										   //Means its a child trying to login at the wrong time
										   aligncenter("YOU CANNOT ENTER THE GYM NOW BECAUSE THERE ARE NOW CLASS GOING ON",5);
										   aligncenter("CLASSES FOR YOU ARE ON THE FOLLOWIND DAYS",8);
										   aligncenter("MONDAYS & WEDNESDAYS @    5:00-6:00pm",10);
										   aligncenter("FRIDAYS              @    4:30-5:30pm",12);
										   aligncenter("Press any key to continue",14);
										   _getch();
									   }
									   else
									   if(time_check==-2)
									   {
										   //Means its an adult trying to sign in at the wrong time
										   aligncenter("YOU CANNOT ENTER THE GYM NOW BECAUSE THERE ARE NOW CLASS GOING ON",5);
										   aligncenter("CLASSES FOR YOU ARE ON THE FOLLOWIND DAYS",8);
										   aligncenter("MONDAYS & WEDNESDAYS @    7:00-8:00pm",10);
										   aligncenter("SATURDAYS            @    7:00-8:00pm",12);
										   aligncenter("Press any key to continue",14);
										   _getch();
									   }
									   else
									   if(time_check==1)
									   {
										   //Means user is logining in at the correct time 
										   //Or its other member type
										   //Check if user is a regular member interms of attending the gym in a month
										   //And if thier fees have been opened
										   if((((int)Current_time-(int)Member.Signed_in)<=120)&&(((int)Current_time-Member.Last_Update>=120)))
										   {
											   //If up date over due
											   //Then update fees owing base on member type
											   switch(Member.Member_type)
											   {
											   	   case 0: Member.Fees_Owing+=3500;
														   break;
												   case 1: Member.Fees_Owing+=2000;
														   break;
												   case 2: Member.Fees_Owing+=1500;
														   break;
											   }
										   }
										   //If member type is a regular member and 1year has passed since they have joined then update fees owing
										   if(((int)(Current_time-Member.Date_Joined)>500)&&(Member.Member_type==0))
										   {
											   Member.Fees_Owing+=500;
										   }

										   //After all that then assign the current time to thier sign in
										   Member.Signed_in=Current_time;
										   //Rewrite record to update database
										   fseek(Members_File,(long)((-1)*((int)sizeof(MEMBER))),SEEK_CUR);
										   fwrite(&Member,sizeof(MEMBER),1,Members_File);
										   //fread(&Dummy,sizeof(MEMBER),1,Members_File);
										   //Then call te member area funciton to give member options
										   Member_Area(&Member);
									   }
									   //This is to signal access granted
									   flag=true;
						               break;		//Break out of the loop
						           	}
						          }while(!feof(Members_File));	//REading through the file until end of file reached
								if(flag==false)		//Flag will remain false if access was not granted
								{
									//If so update chances and let the user know it was incorrect (login details)
									chances--;
									aligncenter("INVALID USERNAME OR PASSWORD, CHANCES LEFT:",40);printf("%d",chances);
									aligncenter("PRESS ANYKEY TO CONTINUE",42);
									_getch();
									aligncenter("                                                ",40);
									aligncenter("                             ",42);
								}
								break;
					case 4: 	fclose(Members_File);	//If they chose to leave then close the file and return back to main
								return;
								break;
				}
			}
			if(flag==true)		//Break of of loop
				break;
			if(chances==0)		//If user spent all thier chances then 
			{
				clearscreen();
				aligncenter("YOU HAVE ENTERED INCORRECT USERNAME OR PASSWORD TOO MANY TIMES",10);
				aligncenter("THE SYSTEM WILL CLOSE DOWN, PLEASE CONTACT THE ADMINISTRATOR",12);
				_getch();
				fclose(Members_File);
				//and
				exit(0);
			}
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,5);				//up or down
			}
			else
			    _getch();
		}
	}
	fclose(Members_File);
}
void Member_Area(MEMBER *Member)
{
	/*
		Purpose:	This provides functions for the member after they have succesfully loged in
	*/
	//Declarations
	time_t Current_time;
	MEMBER Dummy;
	FILE *Members_File;
	bool flag=false;
	int index=0,key=0;

	BUTTON Textbox[3];		//Declaring 3 text boxes
	//Puting labels in each textbox
	strcpy(Textbox[0].label,"FEE PAYMENT");
	strcpy(Textbox[1].label,"STATUS REPORT");
	strcpy(Textbox[2].label,"SIGN OUT");
	//Initailizing values of the text boxes (the coordinates)
	for(index=0;index<3;index++)
	{
     	Textbox[index].x1=(159/2) - (15);			//Produce a value to set the the x1 value in the middle of the screen
		Textbox[index].x2=Textbox[index].x1+30;
		Textbox[index].y1=10 +((index+1)*3);
		Textbox[index].y2=Textbox[index].y1 +2;
	}
	
	//Same concept applies here as in the Signin() function
	while(1)
	{
		//Clear the screen
		color(BACKGROUND_COLOR);
		clearscreen();

		aligncenter("WELCOME TO THE MEMBERS AREA",10);
		aligncenter("PLEASE SELECT THE OPTION THAT YOU WANT TO DO",12);
		
		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,3);	//Display the textboxes on the screen
		flag=false;
		index=0;
		while(1)
		{	
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			key=Function_button();	
			
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 0:	Member_Payment(Member);			//If the person choose to make a payment
							break;
					case 1:	Member_Status_Report(Member);	//If choice is to run report
							break;
					case 2:	time(&Member->Time_Exit);		//If they choose to log-out
							//Find members record in file and update wat time they exited
							if((Members_File=fopen("Members.DAT","rb"))==NULL)
							{
								aligncenter("ERROR: OPENING DATABASE TO SIGN IN.",29);
								aligncenter("PROGRAM WILL EXIT, PRESS ANY KEY TO CONTINUE",30);
								_getch();
								exit(0);
							}
							do{
					           if((fread(&Dummy,sizeof(struct MEMBER),1,Members_File))==0)
					             break;
							   if(Member->Acount_Number==Dummy.Acount_Number)
					           {
								   //When record is found rewrite record
								   fseek(Members_File,(long)((-1)*((int)sizeof(MEMBER))),SEEK_CUR);
					               fwrite(Member,sizeof(MEMBER),1,Members_File);
								   break;
					           }
					     	}while(!feof(Members_File));
					 		//Close file and exit
							fclose(Members_File);
							return;
							break;
					default:break;
				}
				flag=true;
			}
			if(flag==true)
				break;
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,3);				//up or down
			}
			else
			    _getch();
		}
	}
}
void Member_Payment(MEMBER *Member)
{
	/*
		Purpose:	To allow member to make payments to thier account
	*/
	int index=0,key=0;
	float cash,change,temp_fees_owed=0;
	bool flag=false;
	char cashs[6]={""};			//This will hold user input then convert it to a float
	FILE *Members_File;
	MEMBER Dummy;
	BUTTON Textbox[2];			//Declaring only two buttons
	time_t Current_time;

	//Same concept here as the above functions
	strcpy(Textbox[0].label,"MAKE PAYMENT NOW");
	strcpy(Textbox[1].label,"NO PAYMENT");
	for(index=0;index<2;index++)
	{
     	Textbox[index].x1=(159/2) - (((strlen(Textbox[index].label))/2)+2);	
		Textbox[index].x2=Textbox[index].x1+(strlen(Textbox[index].label));
		Textbox[index].y1=15 +(index*3);
		Textbox[index].y2=Textbox[index].y1 +2;
	}
	//Same concept here as the above functions
	while(1)
	{
		color(BACKGROUND_COLOR);
		clearscreen();
		aligncenter("THE FEE YOU OWING NOW IS: ",8); printf("%.2f",Member->Fees_Owing);
		aligncenter("DO YOU WANT TO PAY NOW?",10);
		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,2);	
		flag=false;
		index=0;
		while(1)
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			key=Function_button();	
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 0:	flag=true;	//Set flag to true if they choose to make payment
							break;
					case 1:	return;		//Exit the function....NOT the program
							break;
					default:break;
				}
			}
			if(flag==true)
				break;	//Break out of the loop
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,2);				//up or down
			}
			else
			    _getch();
	}
	//Clear the screen
	color(BACKGROUND_COLOR);
	clearscreen();
	//Accept the payment
	aligncenter("THE FEE YOU OWING NOW IS: ",8); printf("%.2f",Member->Fees_Owing);
	aligncenter("ENTER THE AMOUNT OF CASH YOU ARE SUPPOSE TO PAY",10);
	/*
		Here draws a text box, put the cursor inside it, and allows the user to input a value
		represent cash,
		The loop runs unitl they press the return key
	*/
	drawtextbox(75,85,22,24,"");
	gotoxy(76,23);
	while(Form_reads(cashs,4)!=D_ARROW_KEY)	//Just make the user input until they press the enter key
		gotoxy(76,23);
	cash=(float)atof(cashs);				//After accepting input as a string convert it to float 
											//And assign it to the variable cash
	//Clear the screen again
	color(BACKGROUND_COLOR);
	clearscreen();
	//Store the fees owing now
	temp_fees_owed=Member->Fees_Owing;
	//If cash his more than the fees owing
	if(cash>Member->Fees_Owing)
	{
		//Then assign all fees owing to fees paid
		Member->Fees_Paid+=Member->Fees_Owing;
		//And calculate change
		change=cash-Member->Fees_Owing;
		Member->Fees_Owing=0;				//Put fees owing to 0
	}
	else
	{
		Member->Fees_Owing-=cash;
		Member->Fees_Paid+=cash;
		change=0;
	}
	//Open members file
	if((Members_File=fopen("Members.DAT","rb+"))==NULL)
	{
		aligncenter("ERROR: OPENING DATABASE FOR PAYMENT",23);
		_getch();
		return;
	}
	else
	{
		//Find the members record
		do{
	           if((fread(&Dummy,sizeof(struct MEMBER),1,Members_File))==0)
	             break;
			   if(Member->Acount_Number==Dummy.Acount_Number)
	           {
				   //When found update the record
				   fseek(Members_File,(long)((-1)*((int)sizeof(MEMBER))),SEEK_CUR);
	               fwrite(Member,sizeof(MEMBER),1,Members_File);
				   break;
	           }
	     }while(!feof(Members_File));
		 fclose(Members_File);
	}
	time(&Current_time);		//Store the current time
	time(&Member->Last_Paid);	//Store the current time in members last paid
	//Print reciept
	aligncenter("TRANSACTION RECIEPT",20);
	gotoxy(65,23);
	printf("ACCOUNT NUMBER: %d",Member->Acount_Number);
	gotoxy(65,24);
	printf("MEMBER NAME: %s %s",Member->F_Name,Member->L_Name);
	gotoxy(65,25);
	printf("DATE: %s",ctime(&Current_time));
	gotoxy(65,26);
	printf("FEES OWED: %.2f",temp_fees_owed);
	gotoxy(65,27);
	printf("CASH PAID: %.2f",cash);
	gotoxy(65,28);
	printf("CHANGE: %.2f",change);
	gotoxy(65,29);
	printf("FEES OWING NOW: %.2f",Member->Fees_Owing);

	aligncenter("YOU NOW OWE: $",30);printf("%.2f",Member->Fees_Owing);
	aligncenter("Press any key to continue",31);
	_getch();
	break;	//Break out of loop
	}
}
void Member_Status_Report(MEMBER *Member)
{
	/*
		Purpose:	To run status report for the member personal use
	*/
	float New_Weight;
	bool flag=false;
	char Weight_s[4]={""};		//This is a string because all inputs are in string 
	time_t Current_time;
	time_t Date_Joined;
	time_t LastSigned_in;
	TRAINER Trainer;
	FILE* Trainers_File;
	//Clear the screen
	color(BACKGROUND_COLOR);
	clearscreen();
	aligncenter("ENTER YOUR CURRENT WEIGHT",20);

	/*
		Here draws a text box, put the cursor inside it, and allows the user to input a value
		represent their weight,
		The loop runs unitl they press the return key
	*/
	drawtextbox(75,85,22,24,"");
	gotoxy(76,23);
	while((Form_reads(Weight_s,4)!=D_ARROW_KEY))	//Just make the user input until they press the enter key
		gotoxy(76,23);														//the "isDigit" checks if the input is in digit
	
	New_Weight=(float)atof(Weight_s);			//Convert the string to a float
	//Time calculations
	LastSigned_in=Member->Signed_in;
	Date_Joined=Member->Date_Joined;
	time(&Current_time);
	
	//If member is a personal trainer
	//Then find that trainer in the trainer database
	//To be able to print the trainer name in the report
	
	if((Trainers_File=fopen("Trainers.DAT","rb"))==NULL)
	{
		printf("Cannot open database");
		return;
	}
	if(Member->Member_type==1)
	{
       do  
	   {	
           	if((fread(&Trainer,sizeof(TRAINER),1,Trainers_File))==0)
           	{
             	break;
           	}
			if(Trainer.Acount_Number==Member->Trainer_Account_Number)
			{
				flag=true;
				break;
			}
        }while(!feof(Trainers_File));
	   if(flag==false)
		   aligncenter("COULDNT FIND YOUR TRAINER",50);
	}
	//Clear the screen 
	color(BACKGROUND_COLOR);
	clearscreen();
	//And do the print outs
	aligncenter("MEMBER STATUS REPORT",20);

	gotoxy(65,25);
	printf("NAME:                   %s %s",Member->F_Name,Member->L_Name);
	gotoxy(65,26);
	printf("ADDRESS:                %s",Member->Address);
	gotoxy(65,27);
	printf("DATE STARTED:           %s",ctime(&Date_Joined));
	gotoxy(65,28);
	printf("WEIGHT AT START:        %.2flb",Member->Weight);
	gotoxy(65,29);
	printf("BMI AT START:           %.2f",Member->BMI);
	gotoxy(65,30);
	printf("TODAY IS:               %s",ctime(&Current_time));
	gotoxy(65,31);
	printf("CURRENT WEIGHT:         %.2flb",New_Weight);
	gotoxy(65,32);
	printf("YOUR NEW BMI IS:        %.2f",(New_Weight/(Member->Height*Member->Height)*703));
	gotoxy(65,33);
	//Check wat member type to decide if to print a personal trainer are not
	if(Member->Member_type==1 &&flag ==true)
	{
		printf("TRAINER'S NAME:         %s  %s",Trainer.F_Name,Trainer.L_Name);
	}
	else
	{
		printf("TRAINER'S NAME:         NO TRAINER");
	}
	gotoxy(65,34);
	printf("LAST SIGN IN DATE:      %s",ctime(&LastSigned_in));
	gotoxy(65,35);
	printf("AMOUNT OWING:           %.2f",Member->Fees_Owing);
	gotoxy(65,36);
	printf("END OF REPORT");
	aligncenter("Press any key to continue",40);
	_getch();
}
void Main_Menu(BUTTON *Button,int *spotlight)
{
    /*
		Purpose:	Main menu interface
					Allows the user to switch between textboxes and returns the index
					of that text box representing thier selected option
	*/
	//Hide the cursor for now
	ShowConsoleCursor(false);
	int key;
	while(1)		
       {
             key=(int)_getch();		//Accept the key from the user
             switch(key)				//Check the key
             {
                  case U_ARROW_KEY:   scrollboxes(Button,spotlight,1);    break;
                  case D_ARROW_KEY:   scrollboxes(Button,spotlight,-1);   break;
                  case ESC_KEY:       exit(0);                            break;
                  case R_ARROW_KEY:                                       break;
                  case L_ARROW_KEY:                                       break;
                  case RETURN_KEY:    return;					            break;
             } 
       }
}
void Admin_login()
{
	/*
		Purpose:	To accept admin login details and give acces to system
	*/
	//Clear the screen and make declarations
	color(BACKGROUND_COLOR);
	clearscreen();
	char username[21]={""},password[21]={""};	//Hold the inputed username and password
	bool flag=false;
	int index=0,key=0,chances=3;

	BUTTON Textbox[5];							//Declare five textboxes

	Initialize_Signin_Buttons(Textbox,5);		//and initialize them
	//Label the two last buttons to give options to actions
	strcpy(Textbox[2].label,"     ENTER    ");
	strcpy(Textbox[3].label,"      BACK    ");
	while(1)
	{
		//Clear screen
		color(BACKGROUND_COLOR);
		clearscreen();
		aligncenter("ENTER YOUR LOGIN DETAILS IN THE BOX PROVIDED BELOW",10);

		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,4);	
		flag=false;
		index=0;
		strcpy(password,"");
		strcpy(username,"");
		
		color(FORMTEXT_COLOR);
		gotoxy(Textbox[0].x1-30,Textbox[0].y1+1);
		printf("ENTER YOUR USERNAME:");
		gotoxy(Textbox[1].x1-30,Textbox[1].y1+1);
		printf("ENTER YOUR PASSORD:");

		while(1)
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			
			gotoxy(Textbox[index].x1+1,Textbox[index].y1+1);	//Make any output print 
						 								    	//inside of the selected textbox
			key=switch_AdminInput(index,username,password);
			
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 2:			//If user pres enter then check login details
								if((strcmp(username,"administrator")==0) && (strcmp(password,"bodylanguage2010"))==0)
						        {
						          	flag=true;   
									//Give the user access
									Admin_Area();
									return;
						        }
								if(flag==false)
								{
									//else update chances and display invalid
									chances--;
									aligncenter("INVALID USERNAME OR PASSWORD, CHANCES LEFT:",30);printf("%d",chances);
									aligncenter("Press any key to continue",32);
									_getch();
									aligncenter("                                                   ",30);
									aligncenter("                               ",32);
								}
								break;
					case 3: 	return;			//End function if they choose to exit
								break;
				}
			}
			if(flag==true)
				break;			//Break out of the loop
			if(chances==0)
			{
				//If their chances are out
				clearscreen();
				aligncenter("YOU HAVE ENTERED INCORRECT PASSWORD TOO MANY TIMES",10);
				aligncenter("THE SYSTEM WILL CLOSE DOWN, PLEASE CONTACT ADMINISTRATOR",12);
				_getch();
				exit(0);
			}
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,4);				//up or down
			}
			else
			    _getch();
		}
	}
}
void Admin_Area()
{
	/*
		Purpose:	Give administrative options after they have succesffully logined
	*/
	Update_Files();		//Update the fees of the user records
	//Clear the screen
	color(BACKGROUND_COLOR);
	clearscreen();
	//Regular declarations
	int choice=0;
	bool flag=false;
	int index=0,key=0;

	BUTTON Textbox[5];	//Declaring five textboxes

	Initialize_Signin_Buttons(Textbox,5);		//Initialize the x1,y1 values of the textboxes
	//Give the textboxes labels to be displayed
	strcpy(Textbox[0].label,"DISPLAY REPORTS ");
	strcpy(Textbox[1].label,"SEARCH FOR MEMBER ");
	strcpy(Textbox[2].label,"VIEW TRAINERS");
	strcpy(Textbox[3].label,"VIEW MEMBERS ");
	strcpy(Textbox[4].label,"BACK");

	while(1)
	{
		//Clear the screen
		color(BACKGROUND_COLOR);
		clearscreen();
		aligncenter("WELCOME TO THE ADMINISTRATIVE AREA.",10);
		aligncenter("WHAT DO YOU WANT TO DO?",12);

		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,5);	
		flag=false;
		index=0;
		while(1)
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			
			gotoxy(Textbox[index].x1+1,Textbox[index].y1+1);	//Make any output print 
						 								    //inside of the selected textbox
			key=Function_button();	
			
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
			
					case 0: Display_Reports();
							flag=true;
							break;
					case 1: Search();
							flag=true;
							break;
					case 2: aligncenter("A FUNCTION IS DISABLED HERE",40);
							flag=true;
							break;
					case 3: Print_Members();
							flag=true;
							break;
					case 4:	return;
							break;
				}
			}
			if(flag==true)
				break;
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,5);				//up or down
			}
			else
			    _getch();
		}
	}
}
void Display_Reports()
{
	/*
		Purpose:	Provide options for the administrator to display different reports
	*/
	//Clearing the screen
	color(BACKGROUND_COLOR);
	clearscreen();
	//Regual declarations
	int choice=0;
	bool flag=false;
	int index=0,key=0,chances=3;

	BUTTON Textbox[5];

	Initialize_Signin_Buttons(Textbox,5);			//Initializing the values of the textboxes,the coordinates
	strcpy(Textbox[0].label,"INCOME REPORT");
	strcpy(Textbox[1].label,"NOTIFICATION REPORT");
	strcpy(Textbox[2].label,"TRAINERS REPORT");
	strcpy(Textbox[3].label,"TAE-KWON-DO REPORT");
	strcpy(Textbox[4].label,"BACK");
	//Same initializing here, why i do it two times?...hmmm....
	for(index=0;index<5;index++)
	{
     	Textbox[index].x1=(159/2)-(15);	
		Textbox[index].x2=Textbox[index].x1+30;
	}
	while(1)
	{
		color(BACKGROUND_COLOR);
		clearscreen();
		aligncenter("PLEASE SELECT BELOW THE REPORT THAT YOU WANT TO DISPLAY",10);
		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,5);	
		flag=false;
		index=0;
		while(1)
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			
			gotoxy(Textbox[index].x1+1,Textbox[index].y1+1);	//Make any output print 
						 								    //inside of the selected textbox
			key=Function_button();	
			
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 0: Income_Report();
							break;
					case 1: MemberNotification_Report();
							break;
					case 2: Trainers_Report();
							break;
					case 3: Tae_Kwon_do_Report();
							break;
					case 4: return;
							break;
					default:break;
				}
				flag=true;
			}
			if(flag==true)
				break;
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,5);				//up or down
			}
			else
			    _getch();
		}
	}
}
void Income_Report()
{
	/*
		Purpose:	To run the income report.
					Display the total income from members, non members, etc
	*/
	//Clear the screen
	color(BACKGROUND_COLOR);
	clearscreen();
	aligncenter("DISPLAYING INCOME REPORT",3);
	//Regular declarations
	int Members_amount=0;
	float total_Member_fees=0,temp_cashfees=0,total_fees=0;
	MEMBER Member;   
	FILE *Members_File;
	FILE *Cash_File;

	//Open the members file
	if((Members_File=fopen("Members.DAT","rb"))==NULL)
	{
		aligncenter("ERROR: MEMBERS.DAT CANNOT BE OPEN FOR INCOME REPORT",5);
		_getch();
		return;
	}
	else
	{
		//Loop through each record getting the fees paid and add it to the variable total_member_fees paid
	    do{
	        if((fread(&Member,sizeof(struct MEMBER),1,Members_File))==0)
	             break;      	
			Members_amount++;
			total_Member_fees+=Member.Fees_Paid;
	     }while(!feof(Members_File));
		fclose(Members_File);
	}
	//Try to open the non-members file to check for cash paid from them
	if((Cash_File=fopen("Cash_File.txt","r+"))==NULL)
	{
		aligncenter("NO CASH FROM MEMBERS",6);
	}
	else
	{
		fscanf(Cash_File,"%f",&temp_cashfees);
		aligncenter("THE FEES FROM NON-MEMBERS: ",10);printf("%d",temp_cashfees);
		fclose(Cash_File);
	}
	total_fees=total_Member_fees + temp_cashfees;
	aligncenter("THE AMOUNT OF NON-MEMBERS IS:      ",11);printf("%d",Members_amount);
	aligncenter("THE TOTAL FEES FROM MEMBERS IS:    ",13);printf("$%.2f",total_Member_fees);
	aligncenter("THE TOTAL GYM FEES IS:             ",15);printf("$%.2f",total_fees);
	aligncenter("THE TOTAL FEES FROM NON-MEMBERS:   ",17);printf("$%.2f",temp_cashfees);
	aligncenter("END OF REPORT",20);
	_getch();
}
void MemberNotification_Report()
{
	int y1=15;
	color(BACKGROUND_COLOR);
	clearscreen();
	aligncenter("DISPLAYING MEMBER NOTIFICATION REPORT",10);
	/*
	  Main purpose of this function is to find out who dont sign in for a long time.
	*/
	MEMBER Member;   
	FILE *Members_File=fopen("Members.DAT","rb");
   	time_t Current_time;

	time(&Current_time);

	/*
		here loops through each record checking persons who haven't signed in long time
		and havent paid their fees
	*/
   	do{
        if((fread(&Member,sizeof(struct MEMBER),1,Members_File))==0)
        {
             break;
        }
       	//The checking is done here
		if((((int)Current_time-(int)Member.Signed_in)>120) || (((int)Current_time-Member.Last_Paid>120)))//
		{
			gotoxy(10,y1);
			printf("%d",Member.Acount_Number);
			gotoxy(20,y1);
			printf("%s",Member.F_Name);
			gotoxy(40,y1);
			printf("%s",Member.L_Name);
			gotoxy(60,y1);
			printf("%s",Member.Tele_Num);
			gotoxy(70,y1);
			printf("%s",Member.Address);
			gotoxy(100,y1);
			printf("%s",Member.Email_Address);
			gotoxy(120,y1);
			printf("%s",ctime(&Member.Signed_in));

			y1++;
		}  
      }while(!feof(Members_File));
   
   	aligncenter("END OF REPORT",y1+3);
   
   	_getch();
   fclose(Members_File);
}
void Trainers_Report()
{
	/*
		Purpose:	To run the trainers report and display the members under those trainers
	*/
	//Clear the screen
	color(BACKGROUND_COLOR);
	clearscreen();
	aligncenter("DISPLAYING TRAINERS REPORT WITH THEIR MEMBERS",3);
	//Regular declarations
	int y1=4,total_mem=0;
	MEMBER Member;
	TRAINER Trainer;
	FILE *Members_File;
	FILE *Trainers_File;
	//Open the members database
	if((Members_File=fopen("Members.DAT","rb+"))==NULL)
	{
		aligncenter("ERROR: CANNOT OPEN TRAINER DATABASE TO FIND TRAINEE",28);
		_getch();
		return;
	}
	//Open the trainers database
	if((Trainers_File=fopen("Trainers.DAT","rb+"))==NULL)
	{
		aligncenter("ERROR: CANNOT OPEN TRAINER DATABASE TO FIND TRAINEE",28);
		_getch();
		return;
	}
	//Loop through each record of the trainer database
	do
	{
       	if((fread(&Trainer,sizeof(TRAINER),1,Trainers_File))==0)
         	break;
		//Display the record of the trainer
		gotoxy(10,y1);
		printf("TRAINER NAME: %s %s",Trainer.F_Name,Trainer.L_Name);
		y1+=1;
		gotoxy(20,y1);
		printf("MEMBERS NAME");
		//Then find members who are associated with that trainer and display them
		fseek(Members_File,0,SEEK_SET);
		do{
			//Looping through the members database
			//Reading a record at a time
	        if((fread(&Member,sizeof(struct MEMBER),1,Members_File))==0)
	        {
	             break;
	        }
			if(Member.Trainer_Account_Number==Trainer.Acount_Number)
			{
				total_mem++;
				y1++;
				gotoxy(20,y1);
				printf("%s  %s",Member.F_Name,Member.L_Name);
			} 
		}while(!feof(Members_File));
		y1++;
		gotoxy(20,y1);
		printf("TOTAL MEMBERS: %d",total_mem);
		total_mem=0;
		y1+=3;
    }while(!feof(Trainers_File));

	fclose(Trainers_File);
	fclose(Members_File);
	_getch();
}
void Tae_Kwon_do_Report()
{
	/*
		Purpose:	 To display tae kwon do report
					 The total adult members
					 The total children members
					 The master....etc
	*/
	//Clear the screen
	color(BACKGROUND_COLOR);
	clearscreen();
	aligncenter("DISPLAYING TAE-KWON-DO REPORT",10);
	//The regular declarations
	int y1=17;
	MEMBER Member;
	FILE *Members_File;
	int Num_adults=0;
	int Num_Children=0;
	float total_fees=0;
	//Open the members database
	if((Members_File=fopen("Members.DAT","rb+"))==NULL)
	{
		aligncenter("ERROR: CANNOT OPEN MEMBERS DATABASE",28);
		_getch();
		return;
	}
	//Then loop the database
	do{
		//Reading a record at a time
        if((fread(&Member,sizeof(struct MEMBER),1,Members_File))==0)
        {
             break;
        }
		//Check if its a taekwon do member
		if(Member.Member_type==2)
		{
			//And if its an adult
			if(Member.Age>=12)
				Num_adults++;
			else	//or Child
			if(Member.Age<12)
				Num_Children++;
			if(Member.Acount_Number>0)
				total_fees+=Member.Fees_Paid;	//Calculating the total fees paid of these members
		}
	}while(!feof(Members_File));
	//Doing the print outs
	gotoxy(10,10);
	printf("THE MASTER'S NAME IS: Master Antuan Chung");
	gotoxy(10,11);
	printf("TOTAL NUMBER OF ADULTS ARE: %d",Num_adults);
	gotoxy(10,12);
	printf("TOTAL NUMBER OF CHILDREN ARE: %d",Num_Children);
	gotoxy(10,13);
	printf("TOTAL NUMBER OF MEMBERS IS: %d",Num_adults+Num_Children);
	gotoxy(10,14);
	printf("TOTAL INCOME IS %.2f",total_fees);
	gotoxy(10,15);
	printf("MEMBERS NAMES ARE");
	gotoxy(10,16);
	printf("CHILDREN");
	//Going back through the members database again to display members (tae-kwon-do)
	fseek(Members_File,0,SEEK_SET);
	do{
		//Read a record at a time
        if((fread(&Member,sizeof(struct MEMBER),1,Members_File))==0)
        {
             break;
        }
		//Checking again if its a tae kwon do member
		if(Member.Member_type==2)
		{
			//Check if its a child
			if(Member.Age<12)
			{
				y1++;
				gotoxy(20,y1);
				//Display the name
				printf("%s  %s",Member.F_Name,Member.L_Name);
			}
		}
	}while(!feof(Members_File));
	
	y1+=2;
	gotoxy(10,y1);
	printf("ADULTS");
	//Going back through the database again to find the adults and display them
	fseek(Members_File,0,SEEK_SET);
	do{
        if((fread(&Member,sizeof(struct MEMBER),1,Members_File))==0)
        {
             break;
        }
		if(Member.Member_type==2)
		{
			if(Member.Age>=12)
			{
				y1++;
				gotoxy(20,y1);
				printf("%s  %s",Member.F_Name,Member.L_Name);
			}
		}
	}while(!feof(Members_File));
	
	fclose(Members_File);
	_getch();
	aligncenter("END OF REPORT",y1);
	aligncenter("Press any key to continue",y1+1);
	_getch();
}
void Update_Files()
{
	/*
		Purpose:	To update the record of each member
					If the person attends the gym regularly 
					and the fees need to update
					then it is updated
	*/
	FILE *Members_File;
	MEMBER Member;
	MEMBER Dummy;
	time_t Current_time;

	time(&Current_time);
	//Open the members database
	if((Members_File=fopen("Members.DAT","rb+"))==NULL)
	{
		aligncenter("ERROR: MEMBERS DATABASE COULD NOT BE OPENED",60);
		_getch();
	}
	else
	{
		do{//Loop through the database record by record and check if update is needed
        	if((fread(&Member,sizeof(MEMBER),1,Members_File))==0)
        	{
             	break;
        	}
			//The checking is here
			//if the difference between the current time and the last sign in time is less 
			//than a month and their fees hasn't been updated in a month then
			if((((int)Current_time-(int)Member.Signed_in)<=120)&&(((int)Current_time-Member.Last_Update>=120)))	//2678400
			{
				//Then update the record base on the member type
				switch(Member.Member_type)
				{
					case 0:		if(((int)Current_time-Member.Date_Joined)<=1000)
									Member.Fees_Owing+=500;
								Member.Fees_Owing+=3500;
								break;
					case 1:		Member.Fees_Owing+=1500;
								break;
					case 2:		Member.Fees_Owing+=2000;
								break;
					default: 	aligncenter("ERROR: MEMBER DOES NOT HAVE A MEMBER TYPE ASSIGNED",60);
								printf("%d",Member.Member_type);
								break;
				}
				//And rewrite the record back in the database
				Member.Last_Update=Current_time;
				fseek(Members_File,(long)((-1)*((int)sizeof(MEMBER))),SEEK_CUR);
				fwrite(&Member,sizeof(MEMBER),1,Members_File);
				fseek(Members_File,(long)((-1)*((int)sizeof(MEMBER))),SEEK_CUR);
				fread(&Dummy,sizeof(MEMBER),1,Members_File);
			}
     	  }while(!feof(Members_File));
		fclose(Members_File);
	}
}
void Load_Database()
{
	/*
		Purpose:	 This just try to open the databases, if they cannot be open then 
					 It creates them
	*/
	FILE * Members_File;
	FILE * Trainers_File;
	//Opening the members file
	if((Members_File=fopen("Members.DAT","rb"))==NULL)
		{
			//printf("\nThere isn't a database: Gonna create a new one");
			Sleep(1000);
			if ((Members_File=fopen("Members.DAT","wb"))==NULL)
			{
				printf("\nError creating database");
				printf("\nProgram will exit...");
				_getch();
				exit(0);
			}
		}
	//Opening the trainers file
	if((Trainers_File=fopen("Trainers.DAT","rb"))==NULL)
		{
			Sleep(1000);
			if ((Trainers_File=fopen("Trainers.DAT","wb"))==NULL)
			{
				printf("\nError creating database");
				printf("\nProgram will exit...");
				_getch();
				exit(0);
			}
		}
}
void Trainer(void)
{
	/*
		Purpose: To provide options for trainers
	*/
	
	int ans;

	bool flag=false;
	int index=0,key=0;

	BUTTON Textbox[3];

	strcpy(Textbox[0].label,"SIGN IN");
	strcpy(Textbox[1].label,"SIGN UP");
	strcpy(Textbox[2].label,"BACK");

	for(index=0;index<3;index++)
	{
     	Textbox[index].x1=(159/2)-(15);	//Dont mind the calculation, was lazy 
		Textbox[index].x2=Textbox[index].x1+30;
		Textbox[index].y1=10 +((index+1)*3);
		Textbox[index].y2=Textbox[index].y1 +2;
	}

	while(1)
	{
		color(BACKGROUND_COLOR);
		clearscreen();
		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,3);	
		flag=false;
		index=0;
		aligncenter("WELCOME TO THE TRAINERS AREA.",10);
		aligncenter("WHAT DO YOU WANT TO DO?",12);
		while(1)
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			key=Function_button();	
			
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 0:	Trainer_Sign_in();
							break;
					case 1:	Trainer_Sign_up();
							break;
					case 2:	return;
							break;
					default:break;
				}
				flag=true;
			}
			if(flag==true)
				break;
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,3);				//up or down
			}
			else
			    _getch();
		}
	}
}
void Trainer_Sign_in(void)
{
	/*
		Purpose: Allows the trainer to sign in
	*/
	
	color(BACKGROUND_COLOR);
	clearscreen();

	char username[21]={""},password[21]={""};
	bool flag=false;
	FILE *Trainers_File;
	int index=0,key=0,chances=3;
	BUTTON Textbox[4];
	TRAINER Trainer;

	if((Trainers_File=fopen("Trainers.DAT","rb"))==NULL)
	{
		aligncenter("ERROR: OPENING DATABASE TO SIGN IN.",29);
		aligncenter("PROGRAM WILL EXIT, PRESS ANY KEY TO CONTINUE",30);
		_getch();
		exit(0);
	}
	for(index=0;index<4;index++)
	{
		Textbox[index].x1=(159/2)-(15);
		Textbox[index].x2=Textbox[index].x1+30;
		Textbox[index].y1=20 +(index * 3);
		Textbox[index].y2=Textbox[index].y1 +2;
		strcpy(Textbox[index].label,"");
	}
	strcpy(Textbox[2].label,"ENTER");
	strcpy(Textbox[3].label,"CANCEL");

	while(1)
	{
		color(BACKGROUND_COLOR);
		clearscreen();
		//display enter username and password
		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,4);	
		flag=false;
		index=0;
		strcpy(password,"");
		strcpy(username,"");
		aligncenter("ENTER YOUR LOGIN DETAILS IN THE BOX PROVIDED BELOW",10);
		
		gotoxy(Textbox[0].x1-30,Textbox[0].y1+1);
		printf("ENTER YOUR USERNAME ==>");

		gotoxy(Textbox[1].x1-30,Textbox[1].y1+1);
		printf("ENTER YOUR PASSORD  ==>");
		while(1)
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			gotoxy(Textbox[index].x1+1,Textbox[index].y1+1);	//Make any output print 
															    //inside of the selected textbox
			key=switch_AdminInput(index,username,password);
			
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 2:		fseek(Trainers_File,0L,SEEK_SET);
								do{
						           	if((fread(&Trainer,sizeof(TRAINER),1,Trainers_File))==0)
						           	{
						             	break;
						           	}
						         
						           	if((strcmp(Trainer.Username,username)==0) && (strcmp(Trainer.Password,password))==0)
						           	{
									    flag=true;
										Trainer_Area(Trainer);
						               break;
						           	}
						        }while(!feof(Trainers_File));
								
								if(flag==false)
								{
									chances--;
									aligncenter("INVALID USERNAME OR PASSWORD, CHANCES LEFT:",40);printf("%d",chances);
									aligncenter("Press any key to continue",42);
									_getch();
									aligncenter("                                                    ",40);
									aligncenter("                             ",42);
								}
								break;
					case 3: 	fclose(Trainers_File);
								return;
								break;
				}
			}
			if(flag==true)
				break;
			if(chances==0)
			{
				clearscreen();
				aligncenter("YOU HAVE ENTERED INCORRECT USERNAME OR PASSWORD TOO MANY TIMES",10);
				aligncenter("THE SYSTEM WILL CLOSE DOWN, PLEASE CONTACT THE ADMINISTRATOR",12);
				_getch();
				fclose(Trainers_File);
				exit(0);
			}
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,4);				//up or down
			}
			else
			    _getch();
		}
	}
 	fclose(Trainers_File);
}
void Trainer_Sign_up(void)
{
	/*
		Purpose:	This allows a new trainer to sign up
	*/
	
	TRAINER Trainer={0},Dummy;
	char cost[5]={""};
	int key=0, direction=0,index=0,flag=0;
	FILE *Trainers_File;

	color(BACKGROUND_COLOR);	//Set background color
	clearscreen();				//Clear the screen to set the background color
	
    BUTTON Textbox[10];	//Creating an Array of buttons
   
	for(index=0;index<10;index++)
	{
		Textbox[index].x1=(159/2)-(15);
		Textbox[index].x2=Textbox[index].x1+30;
		Textbox[index].y1=10 +(index * 3);
		Textbox[index].y2=Textbox[index].y1 +2;
		strcpy(Textbox[index].label,"");
	}
	strcpy(Textbox[8].label,"CONTINUE");
	strcpy(Textbox[9].label,"CANCEL");

	color(FORMTEXT_COLOR);
	display_TrainerButtons_Interfaces(Textbox);
	color(TEXTBOX_COLOR);
	show_InputDetails_Buttons(Textbox,10);

	index=0;
	char str[]={"PLEASE FILL OUT THE FORM BELOW TO BECOME A NEW TRAINER"};
	char str2[70]={""};
	for(index=0;index < (strlen(str));index++)
	{
		str2[index]=str[index];
		aligncenter(str2,5);
		Sleep(10);
		aligncenter("                                                          ",5);
	}
	aligncenter(str2,5);
	index=0;
	while(1)
	{
		color(HIGHLIGHTED_TEXTBOX);
		//This will draw the selected textbox, or highlight it
		drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
		
		gotoxy(Textbox[index].x1+1,Textbox[index].y1+1);	//Make any output print 
														    //inside of the selected textbox
		key=switch_TrainerInputDetails(index,&Trainer,cost);
		
		if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
		{						//When that happens let us see what its suppose to do!
			switch(index)		//As said before, each index represents each button
			{
				case 8: 	flag=1;
							break;
				case 9:		return;
							break;
				default:	printf("\nERROR: A FUNCTION IS RETURNING A RETURN VALUE BUT IT IS NOT REGISTERED");
							break;
			}
		}
		if(flag==1)
		{
			if((strcmp(cost,"")==0)||(strcmp(Trainer.Username,"")==0) ||(strcmp(Trainer.Password,"")==0)||(strcmp(Trainer.F_Name,"")==0)||(strcmp(Trainer.L_Name,"")==0)||(strcmp(Trainer.Level,"")==0)||(strlen(Trainer.Tele_Num)<7))
			{
				aligncenter("FORM IS INCOMPLETE, NO FIELD SHOULD BE LEFT BLANK",40);
				aligncenter("Press any key to continue",42);
				_getch();
				aligncenter("                                                   ",40);
				aligncenter("                                      ",42);
				flag=0;
			}
			else
			{
				break;
			}
		}
		if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
		{													//Then she can make the textbox move
			color(TEXTBOX_COLOR);
			Move_textbox(Textbox,key,&index,10);				//up or down
		}
		else
		    _getch();
	}
	Trainer.Cost_per_hour=(float)atof(cost);
	if((Trainers_File=fopen("Trainers.DAT","ab+"))==NULL)
	{
		aligncenter("ERROR: CANNOT OPEN DATABASE TO ADD MEMBER",28);
		_getch();
		return;
	}
    fread(&Dummy,sizeof(struct TRAINER),1,Trainers_File);
    if((feof(Trainers_File)))		//To check if file is empty
	{
		Trainer.Acount_Number=10000;		//Start from 10000
	}
    else
    {
	   fseek(Trainers_File,(long)((-1)*((int)sizeof(TRAINER))),SEEK_END);
	   fread(&Dummy,sizeof(TRAINER),1,Trainers_File);
	   Dummy.Acount_Number++;
	   Trainer.Acount_Number=Dummy.Acount_Number;
    }

	fseek(Trainers_File,0L,SEEK_END);
    fwrite(&Trainer,sizeof(struct TRAINER),1,Trainers_File);
	fclose(Trainers_File);
	
	color(BACKGROUND_COLOR);
	clearscreen();
	aligncenter("NEW TRAINER ADDED!",30);
	aligncenter("Press any key to continue",33);
	_getch();
}
void Trainer_Area(TRAINER Trainer)
{
	/*
		Purpose: This provides options to the user after they have succesfully signed in
	*/
	int index=0,key=0;
	bool flag=false;
	BUTTON Textbox[2];

	strcpy(Textbox[0].label,"DISPLAY YOUR MEMBERS");
	strcpy(Textbox[1].label,"EXIT");
	for(index=0;index<2;index++)
	{
     	Textbox[index].x1=(159/2) - (15);	
		Textbox[index].x2=Textbox[index].x1+30;
		Textbox[index].y1=15 +(index*3);
		Textbox[index].y2=Textbox[index].y1 +2;
	}
	while(1)
	{
		color(BACKGROUND_COLOR);
		clearscreen();
		aligncenter("WHAT DO YOU WANT TO DO?",10);
		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,2);	
		flag=false;
		index=0;
		while(1)
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			key=Function_button();	
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 0:	Display_TrainerMembers(Trainer);
							flag=true;
							break;
					case 1:	return;
							break;
					default:break;
				}
			}
			if(flag==true)
				break;
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,2);				//up or down
			}
			else
			    _getch();
		}
	}
}
void Display_TrainerMembers(TRAINER Trainer)
{
	/*
		Purpose:	This displays the members for each trainer
	*/
	color(BACKGROUND_COLOR);
	clearscreen();
	aligncenter("DISPLAYING YOUR MEMBERS",10);
	MEMBER Member;

	FILE *Members_File;
	int Total_Members=0,y1=11;

	//Open the members file
	if((Members_File=fopen("Members.DAT","rb+"))==NULL)
	{
		aligncenter("ERROR: OPENING DATABASE FOR TRAINER REPORT",23);
		_getch();
		return;
	}
	else
	{
		//Loops through the members database
		do{
			   //Rea a record at a time
	           if((fread(&Member,sizeof(struct MEMBER),1,Members_File))==0)
	             break;
			   //If the member is associated with the trainer 
			   if(Member.Trainer_Account_Number==Trainer.Acount_Number)
	           {
				   //Then 
				   Total_Members++;
				   y1++;
				   gotoxy(40,y1);
				   //And
				   //Print the members
				   printf("%s %s",Member.F_Name,Member.L_Name);
				   break;
	           }
	     }while(!feof(Members_File));
		 fclose(Members_File);
		if(Total_Members==0)
			aligncenter("SORRY BUT YOU HAVE NO MEMBERS",10);
		else
			aligncenter("END OF REPORT",y1);
		 
		_getch();
	}
}
/*
	The functions are use to initialize the textboxes of the above functions
	Meaning initiaize the x1,y1,x2,y2 values (coordinates)
	Of where they should be displayed on the screen
*/
void InitializeGUI(BUTTON *Button,int *spotlight)
{
	/*
		Purpose:	Use for the
	*/
	int index=0;
	Maximize_Window();							//This is to maximize the window
	ShowConsoleCursor(false);					//Hide the cursor
	HANDLE hconsole;							//Declare a handle
    hconsole=GetStdHandle(STD_OUTPUT_HANDLE);	//Assign the handle to point to the console application
												//Windows programming
	color(BG);									//Change the background color
    clearscreen();								//Clear the screen
	color(7);									//Change color again
	drawmainframe();							//Draw the frame
    SetConsoleTextAttribute(hconsole, SCROLL_AREA);	//Change the color
	clearbox(72,89,3,36);						//Clear the specified area

	InitializeMain_Buttons(Button);	
	
	//Display all the textboxes on the screen
	for(index=0;index<Main_BA;index++)
	{
		showbox(Button[index]);
	}
	
	color(BG);
	drawbox( Button[0].x1-1,Button[0].x1+17,12,16,"");
	SetConsoleTextAttribute(hconsole, SCROLL_AREA);

	*spotlight =2;
}
void InitializeMain_Buttons(struct BUTTON *Button)
{
	int y1=3,index=0;
	
	for(index=0;index<Main_BA;index++)
	{
		Button[index].y1=y1;
		Button[index].x1=73;
		y1+=5;
	}

	strcpy(Button[0].label,"SIGN IN");
	strcpy(Button[1].label,"SIGN UP");
	strcpy(Button[2].label,"ADMIN AREA");
	strcpy(Button[3].label,"TRAINERS");
	strcpy(Button[4].label,"INFORMATION");
	strcpy(Button[5].label,"EXIT");
}
/*
	These are GUI functions for the sign in function
*/
void Initialize_Signin_Buttons(BUTTON Textbox[],int size)
{
	int index=0;
	Textbox[0].x1=(159/2)-(15);
	Textbox[0].x2=Textbox[0].x1+30;
	Textbox[0].y1=15;
	Textbox[0].y2=Textbox[0].y1+2;
	strcpy(Textbox[0].label,"");

	for(index=1;index<size;index++)
	{
		Textbox[index].x1=(159/2)-(15);
		Textbox[index].x2=Textbox[index].x1+30;
		Textbox[index].y1=Textbox[index-1].y1+3;
		Textbox[index].y2=Textbox[index].y1+2;
		strcpy(Textbox[index].label,"");
	}

	strcpy(Textbox[2].label,"NONMEMBER");
	strcpy(Textbox[3].label,"ENTER");
	strcpy(Textbox[4].label,"BACK");
}
void display_Signin_sideDetails(BUTTON Textbox[])
{
	gotoxy(Textbox[0].x1-30,Textbox[0].y1+1);
	printf("ENTER YOUR USERNAME:");

	gotoxy(Textbox[1].x1-30,Textbox[1].y1+1);
	printf("ENTER YOUR PASSORD:");

	gotoxy(Textbox[2].x1-30,Textbox[2].y1+1);
	printf("NON MEMBERS SELECT HERE ==>");

	gotoxy(Textbox[4].x1-30,Textbox[4].y1+1);
	printf("SELECT TO CANCEL");

}
int	 switch_SigninInput(int index,char *username,char*password)
{
	int key=0;
	switch(index)
	{
		case 0: 	key=Form_reads(username,15);	//This is a little complicated function
					break;							//Wont explain here but its use for input 
		case 1:		key=Form_reads_mask(password,15);	//Rather than "scanf" and the "others"
					break;			
		case 2:
		case 3:		
		case 4:		key=Function_button();				
					break;
		default: break;
	}
	return key;
}
/*
	Admin GUI functions
*/
int  switch_AdminInput(int index,char *username,char *password)
{
	int key=0;
	switch(index)
	{
		case 0: 	key=Form_reads(username,20);	//This is a little complicated function
					break;							//Wont explain here but its use for input 
		case 1:		key=Form_reads_mask(password,20);	//Rather than "scanf" and the "others"
					break;			
		case 2:
		case 3:  	key=Function_button();				
					break;
		default: 	break;
	}
	return key;
}
int  switch_TrainerInputDetails(int index,TRAINER *Trainer,char *cost)
{
	int key=0;
	switch(index)
		{
			case 0: 	key=Form_reads(Trainer->Username,15);	//This is a little complicated function
						break;								//Wont explain here but its use for input 
			case 1:		key=Form_reads_mask(Trainer->Password,15);	//Rather than "scanf" and the "others"
						break;
			case 2:		key=Form_reads(Trainer->F_Name,15);
						break;
			case 3:		key=Form_reads(Trainer->L_Name,15);
						break;
			case 4:		key=Form_reads(Trainer->Address,29);
						break;
			case 5:		key=Form_reads(Trainer->Tele_Num,9);
						break;
			case 6:		key=Form_reads(Trainer->Level,19);
						break;
			case 7:		key=Form_reads(cost,5);
						break;
			case 8:
			case 9:		key=Function_button();				//
						break;
			default: 	break;
		}
	return key;
}
void display_TrainerButtons_Interfaces(BUTTON Textbox[])
{
	gotoxy(Textbox[0].x1-30,Textbox[0].y1+1);
	printf("ENTER A USERNAME");
	gotoxy(Textbox[1].x1-30,Textbox[1].y1+1);
	printf("ENTER A PASSWORD");
	gotoxy(Textbox[2].x1-30,Textbox[2].y1+1);
	printf("ENTER YOUR FIRST NAME");
	gotoxy(Textbox[3].x1-30,Textbox[3].y1+1);
	printf("ENTER YOUR LAST NAME");
	gotoxy(Textbox[4].x1-30,Textbox[4].y1+1);
	printf("ENTER YOUR ADDRESS");
	gotoxy(Textbox[5].x1-30,Textbox[5].y1+1);
	printf("ENTER YOUR TELE# ==>");
	gotoxy(Textbox[6].x1-30,Textbox[6].y1+1);
	printf("ENTER YOUR CERTIFICATION LEVEL");
	gotoxy(Textbox[7].x1-30,Textbox[7].y1+1);
	printf("ENTER COST PER HOUR");
}
BOOL CtrlHandler( DWORD fdwCtrlType ) 
{ 
  switch( fdwCtrlType ) 
  { 
    case CTRL_C_EVENT: 
    return TRUE;
 
    case CTRL_BREAK_EVENT: 
    return TRUE; 
 
    default: 
    return TRUE; 
  } 
} 
int  correctTime(MEMBER Member)
{
	/*
		Purpose:	This function allows a tae kwon do member to input the time
					and it checkks if the time login in is correct are not interms
					of if any class are going on at that time
	*/
	TIME time;		//Declaring a TIME structure i created at the top 
	color(BACKGROUND_COLOR);
	clearscreen();

	gotoxy(1,1);

	printf("\nPlease enter the time:");
	
	printf("\n1: Sunday");
	printf("\n2: Monday");
	printf("\n3: Tuesday");
	printf("\n4: Wednesday");
	printf("\n5: Thursday");
	printf("\n6: Friday");
	printf("\n7: Saturday");
	
	//Let the user input the day, hour , min
	//The loops are their for validity of the inputed values
	do{
		printf("\nEnter the Day (The number representation above):\n==>");
		scanf("%d",&time.day);

		if(time.day<=0||time.day>7)
		{
			printf("\nInvalid Day");
		}
	}while(time.day<0||time.day>7);

	do
	{
	printf("\nEnter the hour:\n==>");
	scanf("%d",&time.hour);
	
		if(time.hour<0||time.hour>24)
		{
			printf("\nInvalid hour");
		}
	}while(time.hour<0||time.hour>=24);

	do
	{
	printf("\nEnter the miniutes:\n==>");
	scanf("%d",&time.mins);
	
		if(time.mins<0||time.mins>=60)
		{
			printf("\nInvalid min");
		}
	}while(time.hour<0||time.mins>=60);
	//if member is  a child then check if they are logining the correct time
	if(Member.Age<12)
	{
		if((time.day==2 && time.hour==5 && time.mins>=00 && time.mins<60)||(time.day==4 && time.hour==5 && time.mins>=00 && time.mins<60) ||(time.day==6 && ((time.hour==4 && time.mins>=30 && time.mins<60)||(time.hour==5 && time.mins<=30 && time.mins>=0))))
		{
			//If so then
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	//if member is  an adult then check if they are logining the correct time
	if(Member.Age>=12)
	{
		if((time.day==2 && time.hour==7 && time.mins>=00 && time.mins<60)||(time.day==4 && time.hour==7 && time.mins>=00 && time.mins<60) || (time.day==7 && time.hour==7 && time.mins>=0 && time.mins<60))
		{
			return 1;
		}
		else
		{
			return -2;
		}
	}

}
void Non_members()
{
	/*
		Purpose:   To allow transaction for non members
	*/
	MEMBER Member;

	float cash=0;
	float temp_totalcash=0;
	char cashs[6]={""};

	FILE *Cash_file;
	color(BACKGROUND_COLOR);	//Set background color
	clearscreen();				//Clear the screen to set the background color
	correctTime(Member);
	aligncenter("YOU MUST PAY THIS FEE BEFORE ENTERING THE CLASS AS A NON MEMBER",10);
	aligncenter("THE FEE IS $2500",12);

	aligncenter("ENTER THE CASH TO BE PAID BELOW",15);
	
	//Ask the user to input the cash to be payed
	drawtextbox(75,85,22,24,"");
	gotoxy(76,23);
	while((Form_reads(cashs,5)!=D_ARROW_KEY))	//Just start over
		gotoxy(76,23);
	cash=(float)atof(cashs);

	//if cash over 2500 then allow transaction to occur
	if(cash>=2500)
	{
		//And print a receipt
		aligncenter("HERE IS YOUR RECEIPT",30);
		
		aligncenter("BODY LANGUAGE RECEIPT      ",33);
		aligncenter("SERVICICES FOR: TAE-KWON-DO",35);
		aligncenter("FEE IS                     ",36);printf("$2500");
		aligncenter("CASH ENTERED               ",37);printf("%.2f",cash);
		aligncenter("HERE IS YOUR CHANGE        ",38);printf("%.2f",cash-2500);
	    aligncenter("Press any key to continue",40);
		_getch();
		if((Cash_file=fopen("Cash_File.txt","r+"))==NULL)
		{
			Cash_file=fopen("Cash_File.txt","w+");
		}
		fscanf(Cash_file,"%f",&temp_totalcash);
		cash+=temp_totalcash;
		fclose(Cash_file);
		Cash_file=fopen("Cash_File.txt","r+");

		fprintf(Cash_file,"%f",cash);
		fclose(Cash_file);
	}
	else
	{
		printf("\nInsufficient Funds. You cannot enter this gym");
		aligncenter("INSUFFICIENT FUNDS. YOU CANNOT ENTER THE GYM",30);
	}
	_getch();
}

void Information()
{
	/*
		Purpose:	To provide user with options for information
					Navigation information
					and about bodylanguage
	*/
	//Regular information
	int index=0,key=0;
	BUTTON Textbox[3];
	bool flag=false;

	strcpy(Textbox[0].label,"HOW TO NAVIGATE");
	strcpy(Textbox[1].label,"ABOUT BODY LANGUAGE");
	strcpy(Textbox[2].label,"BACK");
	for(index=0;index<3;index++)
	{
     	Textbox[index].x1=(159/2) - 15;	
		Textbox[index].x2=Textbox[index].x1+30;
		Textbox[index].y1=15 +(index*3);
		Textbox[index].y2=Textbox[index].y1 +2;
	}
	while(1)
	{
		color(BACKGROUND_COLOR);
		clearscreen();
		aligncenter("WHAT DO YOU NEED INFORMATION ABOUT?",10);
		color(TEXTBOX_COLOR);
		show_InputDetails_Buttons(Textbox,3);	
		flag=false;
		index=0;
		while(1)
		{
			color(HIGHLIGHTED_TEXTBOX);
			//This will draw the selected textbox, or highlight it
			drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
			key=Function_button();	
			if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
			{						//When that happens let us see what its suppose to do!
				switch(index)		//As said before, each index represents each button
				{
					case 0:	Navigation();
							flag=true;
							break;
					case 1:	About();
							flag=true;
							break;
					case 2: return;
							break;
					default:break;
				}
			}
			if(flag==true)
				break;
			if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
			{													//Then she can make the textbox move
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,3);				//up or down
			}
			else
			    _getch();
		}
	}
}
void Navigation()
{
   color(BACKGROUND_COLOR);
   clearscreen();
	
   aligncenter("To Navigate throughout the system simply use the ARROW keys",8);
   aligncenter("Use the ENTER key to select you appropriate option",10);
   _getch();
}
void About()
{
	color(BACKGROUND_COLOR);
	clearscreen();

   aligncenter("Here at Body langauge Fitness is our priority.",6);
   aligncenter("A comfortable environment is our main focus",8);
   aligncenter("We ensure our members are comfortably fit and healthy",10);
   aligncenter("Enjoy the experience of our professional Trainers",12);

   aligncenter("CLASSES FOR CHILDREN ARE ON THE FOLLOWING DAYS",15);
   aligncenter("MONDAYS & WEDNESDAYS @    5:00-6:00pm",17);
   aligncenter("FRIDAYS              @    4:30-5:30pm",19);

   aligncenter("CLASSES FOR ADULTS ARE ON THE FOLLOWING DAYS",21);
   aligncenter("MONDAYS & WEDNESDAYS @    7:00-8:00pm",23);
   aligncenter("SATURDAYS            @    7:00-8:00pm",25);
   aligncenter("Press any key to continue",27);
   _getch();
}
