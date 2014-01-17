/*
	This contains some extra functions for the database or bodylanugae cpp file
	such as add member , print,search,etc
*/

#include <time.h>
typedef struct MEMBER{
               int    Acount_Number;
               char   Username[16];
			   char   Password[16];
			   char   F_Name[20];
               char   L_Name[20];
               int    Age;
               char   Address[30];
			   char   Tele_Num[9];
			   char   Email_Address[30];
               float  Weight;
               float  Height;
               int    Member_type;
			   int 	  Trainer_Account_Number;
               int    Class;
               time_t Date_Joined;
			   time_t Signed_in;
			   time_t Last_Update;
			   time_t Last_Paid;
			   time_t Time_Exit;
               float  Fees_Owing;   //This specifies the fee owed.
			   float  Fees_Paid;
			   float  BMI;
             }MEMBER;

typedef struct TRAINER{
               int    Acount_Number;
               char   Username[16];
			   char   Password[16];
			   char   F_Name[16];
               char   L_Name[16];
               char   Address[30];
			   char   Tele_Num[10];
               char   Level[20];
			   float  Cost_per_hour;
               }TRAINER;


void Add_Member();
void Print_Members();
void Search();
void Delete(MEMBER);
void Edit_Member(MEMBER);
void Members_Menu(int*);

//Input details for add member button functions

