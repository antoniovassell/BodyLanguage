#include "Database.h"
#include "Ant_GUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define TEXTBOX 	13

void Initialize_InputDetails_Buttons(int,int,BUTTON *);
void Display_InputDetails_SideDetails(BUTTON[]);
int  switch_InputDetails(int,MEMBER*,char *,char *,char *);
int  do_dropdown_menu();
void Initialize_DropDownMenu(BUTTON *,int);
void show_DropDownMenu(BUTTON *,int);

void Add_Member()
{
	/*
	   Purpose: To provide the user with a form to fill out their details
	*/
	//Delcarations
	int key=0, direction=0,index=0,flag=0,y1=0,trainer_num=0,trainer_num_input=0,taekwondo_amt=0;
	char Age[5]={""},Height[5]={""},Wieght[5]={""},input_num[2]={""};
	MEMBER Member={0,"","","","",0,"","","",0,0,0,0,0,0,0,0,0,0,0};
	MEMBER Dummy={0,"","","","",0,"","","",0,0,0,0,0,0,0,0,0,0,0};
	TRAINER Trainer_Dummy;
	TRAINER Trainer;
	FILE *Members_File;
	FILE *Trainers_File;
    BUTTON Textbox[TEXTBOX];	//Creating an Array of buttons
    
	//GUI Functions
	color(BACKGROUND_COLOR);	//Set background color
	clearscreen();				//Clear the screen to set the background color
	aligncenter("PLEASE ENTER YOUR DETAILS BELOW TO BECOME A NEW MEMBER",1);
	color(TEXTBOX_COLOR);
    Initialize_InputDetails_Buttons(SPACE,ALIGN,Textbox);
	show_InputDetails_Buttons(Textbox,TEXTBOX);

	color(FORMTEXT_COLOR);
	Display_InputDetails_SideDetails(Textbox);

	index=0;
	//This loop is to calculate how much tae-kwon-do members are in the file already
	if((Members_File=fopen("Members.DAT","rb"))==NULL)
	{
		aligncenter("ERROR: OPENING DATABASE TO SIGN IN.",29);
		aligncenter("PROGRAM WILL EXIT, PRESS ANY KEY TO CONTINUE",30);
		_getch();
		exit(0);
	}
	do{
        if((fread(&Dummy,sizeof(struct MEMBER),1,Members_File))==0)
        {
             break;
        }
		if(Dummy.Member_type==2)
		{
			taekwondo_amt++;
		}
	}while(!feof(Members_File));
	fclose(Members_File);

	while(1)   //This is a infinite loop that provides the user to switch between options
	{
		color(HIGHLIGHTED_TEXTBOX);
		//This will draw the selected textbox, or highlight it
		drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
		
		gotoxy(Textbox[index].x1+1,Textbox[index].y1+1);	//Make any output print 
														    //inside of the selected textbox
		key=switch_InputDetails(index,&Member,Age,Wieght,Height);
		
		if(key==RETURN_KEY)		//Only a function button returns a RETURN_KEY value, 
		{						//When that happens let us see what its suppose to do!
			switch(index)		
			{
				case 10:	Member.Member_type = do_dropdown_menu();	//This provides the option for the user to select a member type
							if(Member.Member_type>=0)
							{
								switch(Member.Member_type)
								{
									case 0:	strcpy(Textbox[10].label,"Regular Member      ");
											break;
									case 1:	strcpy(Textbox[10].label,"Personal Trainer    ");
											break;
									case 2:	strcpy(Textbox[10].label,"Tae-Kwon-Do Member  ");
											break;
								}
								drawtextbox(Textbox[10].x1,Textbox[10].x2,Textbox[10].y1,Textbox[10].y2,Textbox[10].label);
							}
							break;
				case 11: 	if(taekwondo_amt==20)
							{
								aligncenter("TAE KWON CLASSES ARE FULL, PLEASE CHOOSE ANOTHER MEMBER TYPE",50);
								_getch();
								aligncenter("                                                             ",50);
							}
							else
							{
								flag=1;
							}
							break;
				case 12:	return;
							break;
				default:	printf("\nERROR: A FUNCTION IS RETURNING A RETURN VALUE BUT IT IS NOT REGISTERED");
							break;
			}
		}
		if(flag==1)
			break;
		if(key ==U_ARROW_KEY||key ==D_ARROW_KEY)			//If the user presses up or down
		{													//Then she can make the textbox move
			color(TEXTBOX_COLOR);
			Move_textbox(Textbox,key,&index,TEXTBOX);		//up or down
		}
		else
		    _getch();
	}
   
	/*
		This switch statement is to calculate the initial fees
		for the member base on the member type

	*/
	switch(Member.Member_type)
	{
		case 0:	Member.Fees_Owing=500;
				break;
				/*
					If the member type is "personal trainer"
					Then make the user choose which trainer they want
				*/
		case 1:	Member.Fees_Owing=0;	
				y1=10;
				trainer_num=1;
				color(BACKGROUND_COLOR);
				clearscreen();

				aligncenter("PLEASE CHOOSE YOUR TRAINER FROM THE LIST OF AVAILABLE TRAINERS",5);
				aligncenter("TRAINER DETAILS",10);
				gotoxy(30,y1);
				printf("NUMBER");
				gotoxy(40,y1);
				printf("ID #");
				gotoxy(50,y1);
				printf("FIRST NAME");
				gotoxy(70,y1);
				printf("LAST NAME");
				gotoxy(90,y1);
				printf("CERTIFICATION LEVEL");
				
				y1+=5;
				if((Trainers_File=fopen("Trainers.DAT","ab+"))==NULL)
				{
					aligncenter("ERROR: CANNOT OPEN DATABASE TO ADD MEMBER",28);
					_getch();
					return;
				}
				do  //This loops through the trainers database to print out the trainers
				{	
		           	if((fread(&Trainer_Dummy,sizeof(TRAINER),1,Trainers_File))==0)
		           	{
		             	break;
		           	}
					
					if(Trainer_Dummy.Acount_Number!=0)
					{
						gotoxy(30,y1);
						printf("%d",trainer_num);
						gotoxy(40,y1);
						printf("%d",Trainer_Dummy.Acount_Number);
						gotoxy(50,y1);
						printf("%s",Trainer_Dummy.F_Name);
						gotoxy(70,y1);
						printf("%s",Trainer_Dummy.L_Name);
						gotoxy(90,y1);
						printf("%s",Trainer_Dummy.Level);
						
						trainer_num++;
						y1++;
					}
		        }while(!feof(Trainers_File));
				fclose(Trainers_File);
			
				aligncenter("ENTER THE TRAINER NUMBER YOU WANT FOR YOUR TRAINER",40);
				drawtextbox(75,85,22,24,"");
				gotoxy(76,23);
				while(Form_reads(input_num,5)!=D_ARROW_KEY )	//Here is just to receive an input in a text box
					gotoxy(76,23);								//For the user to select which trainer they want
				trainer_num_input=(int)atoi(input_num);
				printf("TRAINER INPUT %d",trainer_num_input);
				if((Trainers_File=fopen("Trainers.DAT","ab+"))==NULL)
				{
					aligncenter("ERROR: CANNOT OPEN TRAINER DATABASE TO FIND TRAINEE",28);
					_getch();
					return;
				}
				fseek(Trainers_File,0,SEEK_SET);
				do	//Go back through the trainer database to find the selected trainer
				{	//and assign thier account number the the members structure
		           	if((fread(&Trainer,sizeof(TRAINER),1,Trainers_File))==0)
		             	break;
					if(Trainer.Acount_Number!=0)
					{
						trainer_num_input--;
					}
					if(trainer_num_input==0)
						break;
						
		        }while(!feof(Trainers_File) && (trainer_num_input>=0));
				
				fclose(Trainers_File);
				break;
		case 2:	Member.Fees_Owing=0;
				break;
	}
	//Assign the selected trainer account number to the member record
	if(Member.Member_type==1)
	{
		Member.Trainer_Account_Number=Trainer.Acount_Number;
	}
	else
	{
		Member.Trainer_Account_Number=0; //Assigns 0 If member is a other members
	}
	Member.Age=(int)atoi(Age);			//These codes just converts any string variables to digits/numbers/intergers
	Member.Height=(float)atof(Height);	//Floats....
	Member.Weight=(float)atof(Wieght);   
    Member.BMI=((Member.Weight/(Member.Height *Member.Height)) * 703);   //This is to calculate BMI
    
	/**********All of here is to write the data to file*****************/
	//This is to open the Members database
	if((Members_File=fopen("Members.DAT","ab+"))==NULL)
	{
		printf("\nError: Opening Database to save file");
		_getch();
		return;
	}
	//Just checking if the file is empty
    fread(&Dummy,sizeof(struct MEMBER),1,Members_File);
    if((feof(Members_File)))	
	{
		Member.Acount_Number=1000;		//Start from 1000 if file is empty
	}
    else
	//Read the last record in the database to get the previous account number
    {
	   fseek(Members_File,(long)((-1)*((int)sizeof(MEMBER))),SEEK_END);
	   fread(&Dummy,sizeof(MEMBER),1,Members_File);
	   Member.Acount_Number=Dummy.Acount_Number+1; //Increment that value and assign it to 
													//The new members record
    }
	//Assign the current time to all time variables of the record
    time(&Member.Date_Joined);
    time(&Member.Signed_in);
    time(&Member.Last_Update);
	time(&Member.Last_Paid);
	time(&Member.Time_Exit);
    Member.Fees_Paid=0;
	Member.Class=0;
	//Put the file pointer to the end of file and add the new record
    fseek(Members_File,0L,SEEK_END);
    fwrite(&Member,sizeof(struct MEMBER),1,Members_File);
    fclose(Members_File);
	
	color(BACKGROUND_COLOR);
	clearscreen();

	aligncenter("NEW MEMBER ADD!",20);
	aligncenter("Press any key to continue",23);
	_getch();
}
void Print_Members()
{
	/*
		Purpose:  This is to print out the members in the database
	*/
	color(BACKGROUND_COLOR);
	clearscreen();
	aligncenter("DISPLAYING ALL MEMBERS",10);

	int y1=15;
	MEMBER Member;   
	FILE *Members_File;
    if((Members_File=fopen("Members.DAT","rb"))==NULL)
	{
		aligncenter("ERROR: COULDN'T OPEN DATABASE TO PRINT MEMBERS",10);
		aligncenter("Press any key to continue",12);
		_getch();
		return;
	}

   	do{
        if((fread(&Member,sizeof(struct MEMBER),1,Members_File))==0)
        {
             break;
        }
		if(Member.Acount_Number>0)
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
   
   	aligncenter("NO MORE MEMBERS IN DATABASE",y1+3);
   
   	_getch();
   	fclose(Members_File);
}
void Search()
{
      /*
		Purpose: To allow admin to search for a member by Account number
				 And print the detail
	  */
	  color(BACKGROUND_COLOR);
	  clearscreen();
	  aligncenter("SEARCH FUNCTION (NEEDS SOME ADJUSTMENTS)",5);

	  MEMBER Member;
	  FILE *Members_File=fopen("Members.DAT","rb");
      int  Flag=0;
      int  Request;
      
      aligncenter("\nEnter the Acount number you want to search for==> ",10);
      scanf("%d",&Request);
        
      do{
           if((fread(&Member,sizeof(MEMBER),1,Members_File))==0)
           {
             break;
           }
           
           if(Member.Acount_Number==Request)
           {
               aligncenter("MEMBER FOUND",15);
			   printf("\n%d %s %s",Member.Acount_Number,Member.F_Name,Member.L_Name);
               Flag=1;
			   break;
           }
        }while(!feof(Members_File));
   
   if(!Flag)
     aligncenter("Account Number not found",10);
   
   _getch();
   
   fclose(Members_File); 
}
void Initialize_InputDetails_Buttons(int space,int align,BUTTON *Textbox)
{
	int index=0;

	Textbox[index].y1=space;	
    Textbox[index].x1=align;
	Textbox[index].x2=Textbox[0].x1+25;
	Textbox[index].y2=Textbox[0].y1+2;

	strcpy(Textbox[index].label,"");

    for(index=1;index<TEXTBOX;index++)
    {
			   Textbox[index].y1=Textbox[index-1].y1+space;
               Textbox[index].x1=align;
			   Textbox[index].x2=Textbox[index].x1+25;
			   Textbox[index].y2=Textbox[index].y1+2;
			   
			   strcpy(Textbox[index].label,"");
    }
    strcpy(Textbox[10].label,"Member Type");
	strcpy(Textbox[11].label,"  CONTINUE ");
	strcpy(Textbox[12].label,"  CANCEL   ");
}
void Display_InputDetails_SideDetails(BUTTON Textbox[])
{
	gotoxy(Textbox[0].x1-30,Textbox[0].y1+1);
	printf("ENTER A USERNAME:");

	gotoxy(Textbox[1].x1-30,Textbox[1].y1+1);
	printf("ENTER A PASSORD:");

	gotoxy(Textbox[2].x1-30,Textbox[2].y1+1);
	printf("ENTER YOUR FIRST NAME:");

	gotoxy(Textbox[3].x1-30,Textbox[3].y1+1);
	printf("ENTER YOUR SURNAME");

	gotoxy(Textbox[4].x1-30,Textbox[4].y1+1);
	printf("ENTER YOUR HOME ADDRESS");

	gotoxy(Textbox[5].x1-30,Textbox[5].y1+1);
	printf("ENTER YOUR PHONE NUMBER:");

	gotoxy(Textbox[6].x1-30,Textbox[6].y1+1);
	printf("ENTER YOUR EMAIL ADDRESS");

	gotoxy(Textbox[7].x1-30,Textbox[7].y1+1);
	printf("ENTER YOUR AGE: ");

	gotoxy(Textbox[8].x1-30,Textbox[8].y1+1);
	printf("ENTER YOUR HEIGHT IN INCHES:");

	gotoxy(Textbox[9].x1-30,Textbox[9].y1+1);
	printf("ENTER YOUR WIEGHT IN POUNDS:");

	gotoxy(Textbox[10].x1-30,Textbox[10].y1+1);
	printf("SELECT BOX TO SELECT MEMBER");
}
int  switch_InputDetails(int index,MEMBER *Member,char *Age,char *Wieght,char *Height)
{
	int key=0;
	switch(index)
		{
			case 0: 	key=Form_reads(Member->Username,10);	//This is a little complicated function
						break;								//Wont explain here but its use for input 
			case 1:		key=Form_reads_mask(Member->Password,10);	//Rather than "scanf" and the "others"
						break;
			case 2:		key=Form_reads(Member->F_Name,14);
						break;
			case 3:		key=Form_reads(Member->L_Name,14);
						break;
			case 4:		key=Form_reads(Member->Address,30);
						break;
			case 5:		key=Form_reads(Member->Tele_Num,9);
						break;
			case 6:		key=Form_reads(Member->Email_Address,29);
						break;
			case 7:		key=Form_reads(Age,4);
						break;
			case 8:		key=Form_reads(Height,4);	
						break;
			case 9:		key=Form_reads(Wieght,4);
						break;
			case 10:										//These are cases for the function buttons
			case 11:
			case 12:	key=Function_button();				//
						break;
			default: break;
		}
	return key;
}
//Drop down menu functions
int  do_dropdown_menu()
{
	char key=NULL;
	int index=0;
	int clearIndex=0;
	const int size=3;
	BUTTON Textbox[size];
	
	Initialize_DropDownMenu(Textbox,3);
	
	color(TEXTBOX_COLOR);
	show_DropDownMenu(Textbox,3);

	while(1)
	{
		color(HIGHLIGHTED_TEXTBOX);
		//This will draw the selected textbox, or highlight it
		drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,"");
		key=(char)_getch();
		
		if(key==RETURN_KEY)
				break;

		if(key<=0)
		{
			key=(char)_getch();
			if(key==L_ARROW_KEY && index==0)
				break;
			else
			{
				color(TEXTBOX_COLOR);
				Move_textbox(Textbox,key,&index,3);
			}
		}
	}
	for(clearIndex=0;clearIndex<size;clearIndex++)
		clearbox(Textbox[clearIndex].x1,Textbox[clearIndex].x2+1,Textbox[clearIndex].y1,Textbox[clearIndex].y2);
	
	if(key==L_ARROW_KEY)
			return -1;
	else
	if(key==RETURN_KEY)
	{
		return index;
	}
}
void Initialize_DropDownMenu(BUTTON *Textbox,int size)
{
	int index=0;
	strcpy(Textbox[0].label,"Regular");
	strcpy(Textbox[1].label,"Personal Trainer");
	strcpy(Textbox[2].label,"Tae-Kwon-Do");

	Textbox[0].x1=97;
	Textbox[0].y1=33;
	Textbox[0].x2=Textbox[index].x1+((strlen(Textbox[index].label))+2);
	Textbox[0].y2=Textbox[0].y1+2;

	for(index=1;index<size;index++)
	{
		Textbox[index].x1=Textbox[index-1].x2+2;
		Textbox[index].y1=Textbox[0].y1;
		Textbox[index].x2=Textbox[index].x1+((strlen(Textbox[index].label))+2);
		Textbox[index].y2=Textbox[0].y1+2;
	}
}
void show_DropDownMenu(BUTTON *Textbox,int size)
{
	int index=0;

	for(index=0;index<size;index++)
		 drawtextbox(Textbox[index].x1,Textbox[index].x2,Textbox[index].y1,Textbox[index].y2,Textbox[index].label);
}
