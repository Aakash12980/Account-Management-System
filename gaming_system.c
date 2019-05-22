/*
	Final Project of C Programmng
	Title: Gaming System v2
	Authors: Aakash Bhandari (703)
			 Abhishek Pandey (706)
			 Anjit Sibakoti (708)
			 Shubham Joshi (737)
			 
	Submitted to : Milan Lamichhane
	Date: 3/19/2018
*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct{
		char u_name[20], passwd[33], name[30];
	}login;

typedef struct
	{
		int s_no;
		char game_name[20];
		int game_price;
	}game;
	
void check_user(login, FILE*);
void check_passwd(login, char[]);	
void sign_in(int);
void admin();
void user();
void new_user(int);
void game_edit();
void admin_settings();
int read_choice(int);
void game_entry(FILE *,game []);
void game_list(FILE *, game[],int);
void game_search(FILE *, game[]);
void delete_game();
void remove_game(char[]);
void update_price();
void set_price(char[]);
void list_members(int);
void delete_user(int);
void change_passwd(int);
void add_admin();
void delete_record(char[],int);
void update_record(char[],int);
login new_account(login, FILE*);
login encrypt(login, char[], int);


int main()
{	
	system("cls");
	int token,cho,choice;
	printf("\n\n\n\n\t\t\t\t\t  ||>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<||\n");
	printf("\t\t\t\t\t   || Welcome to Gaming System v2 ||\n");
	printf("\t\t\t\t\t  ||>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<||\n\n\n");
	printf("\t\t\t\t\t   ||----------------------------||\n");
	printf("\t\t\t\t\t  ||\t      1. Admin            ||\n");
	printf("\t\t\t\t\t  ||\t      2. User             ||\n");
	printf("\t\t\t\t\t   ||----------------------------||\n\n");
	printf("\t\t\t\t\tAre you a user or admin? \n");
	cho = read_choice(choice);
	

	switch(cho)
	{
		case 1:
			token = 0;
			sign_in(token);
			admin();
							
		case 2:
			token = 1;
			sign_in(token);
			user();
			
		default:
			printf("Invalid Choice:\n");
			main();	
	}
	

}

void sign_in( int token)
{
	login record;
	int choice;
	FILE *ptvar;
  	if(token == 0)
	  	ptvar = fopen("admin.bat", "r");
  	else
  		ptvar = fopen("user.bat", "r");
	
	check_user(record, ptvar);
	fclose(ptvar);
}

void admin()
{	
	system("cls");
	int cho,choice,token;
	printf("\n\n\n\n\t\t\t\t\t    <||>>>>>>> <<<<<<<||>\n");
	printf("\t\t\t\t\t    ||  Welcome Admin  ||\n");
	printf("\t\t\t\t\t    <||>>>>>>> <<<<<<<||>\n\n\n");
	printf("\t\t\t\t\t=----------------------------=\n");
	printf("\t\t\t\t\t||   1.  Add a new user     ||\n");
	printf("\t\t\t\t\t||   2. View list of users  ||\n");
	printf("\t\t\t\t\t||   3.   Game data -->     ||\n");
	printf("\t\t\t\t\t||   4. Admin Settings -->  ||\n");
	printf("\t\t\t\t\t||   5.      Logout         ||\n");
	printf("\t\t\t\t\t=----------------------------=\n\n\n");
	printf("\t\t\t\t\t   What do you want to do\n");
	cho = read_choice(choice);
	
	switch(cho)
	{
		case 1:
			token = 1;
			new_user(token);
		
		case 2:
			token=1;
			list_members(token);
		
		case 3:
			game_edit();
		
		case 4:
			admin_settings();
			
		case 5:
			main();
			
		default:
			printf("Invalid Choice:\n");
			admin();
	}
}

void list_members(int token)
{
	system("cls");
	login record;
	int flag,counter=0;
	char temp,name[20];
	
	FILE *fvar;
	if(token==0)
		fvar = fopen("admin.bat", "r");
	
	else
		fvar = fopen("user.bat", "r");
	
	printf("\n\n\n\n\t\t\t\t\t }}>>>>>>>>>>>>>><<<<<<<<<<<<<<{{\n");
	printf("\t\t\t\t\t  ||     List of Members      ||\n");
	printf("\t\t\t\t\t }}>>>>>>>>>>>>>><<<<<<<<<<<<<<{{\n\n");
	
	printf("\t\t\t\t\tName\t\t\tUsername\n\n");
	
	fread(&record, sizeof(login), 1, fvar);
	while(!feof(fvar))
	{
		printf("\t\t\t\t\t|%s\t", record.name);
		printf("\t\t%s\n", record.u_name);
		fread(&record, sizeof(login), 1, fvar);
		counter++;
	}
	fclose(fvar);
	printf("\n\n\t\t\t\t\tTotal no of data: %d\n\n",counter);
	if(token == 0)
	{
		printf("Press any key to go back..");
		fflush(stdin);
		temp = getchar();
		admin_settings();
	}
	else
	{	
		printf("Press any key to go back..");
		fflush(stdin);
		temp = getchar();
		admin();
	}
}

void new_user(token)
{
	system("cls");
	login record;
	char temp;
	int cho=0,choice=0;
	FILE *fvar;
  	if(token == 1)
  		fvar = fopen("user.bat", "a+");
	else
		fvar = fopen("admin.bat", "a+");

	printf("\n\n\n\n\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n");
	printf("\t\t\t\t\t ||   Create a New Account!!   ||\n");
	printf("\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n\n\n");
	printf("\t\t\t\t\tPress 1 to continue or 0 to back: \n");
	cho = read_choice(choice);
	
	switch (cho)
	{
		case 1:
			record = new_account(record, fvar);
			fwrite(&record, sizeof(login), 1, fvar);
			fclose(fvar);
			printf("\n\n\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n");                                                                        
			printf("\t\t\t\t\t  |      CONGRATULATIONS!      |\n");
			printf("\t\t\t\t\t  |Your acount has been created|\n");
			printf("\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n\n\n");
			printf("Press any key to continue...");      

			temp = getchar();
		case 0:
			admin();
	}
	
}

int read_choice(int choice)
{
	
	printf("Enter your Choice: ");
	
	scanf("%d",&choice);
	return choice;
}

void game_edit()
{
	system("cls");
	game game_data[50];
	int token,cho, choice;
	FILE *fptr;
	printf("\n\n\n\n\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n");
	printf("\t\t\t\t\t  ||   	    Game data         ||\n");
	printf("\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n\n\n");
	printf("\t\t\t\t\t<>|----------------------------|<>\n");
	printf("\t\t\t\t\t  ||  1. Enter new game entry ||\n");
	printf("\t\t\t\t\t  ||  2. View all game entry  ||\n");
	printf("\t\t\t\t\t  ||  3.  Search for a game   ||\n");
	printf("\t\t\t\t\t  ||  4.   Update price       ||\n");
	printf("\t\t\t\t\t  ||  5.     Delete game      ||\n");
	printf("\t\t\t\t\t  ||  6.        Back          ||\n");
	printf("\t\t\t\t\t<>|----------------------------|<>\n"); 

	cho = read_choice(choice);
	

	switch(cho)
	{
		case 1:
			game_entry(fptr,game_data);
			break;
			
		case 2:
			token = 0;
			game_list(fptr, game_data,token);
			break;
			
		case 3:
			game_search(fptr,game_data);
			break;
			
		case 4:
			token = 5;
			game_list(fptr, game_data,token);
			
		case 5:
			token = 4;
			game_list(fptr, game_data,token);
		case 6:
			admin();
				
		default:
			printf("Invalid Choice:\n");
			game_edit();

		}
	


}

void admin_settings()
{
	system("cls");
	int token,cho,choice;
	
	printf("\n\n\n\n\t\t\t\t\t }}>>>>>>>>>>>>>><<<<<<<<<<<<<<{{\n");
	printf("\t\t\t\t\t  ||  Administrator Settings  ||\n");
	printf("\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n\n\n");
	printf("\t\t\t\t\t []|^^^^^^^^^^^^^^^^^^^^^^^^^^^|[]\n");
	printf("\t\t\t\t\t  [] 1.      Delete user       []\n");
	printf("\t\t\t\t\t  [] 2.   Add another admin    []\n");
	printf("\t\t\t\t\t  [] 3.  View list of admins   []\n");
	printf("\t\t\t\t\t  [] 4. Delete existing admin  []\n");
	printf("\t\t\t\t\t  [] 5.  Change your password  []\n");
	printf("\t\t\t\t\t  [] 6.         Back           []\n");
	printf("\t\t\t\t\t []|^^^^^^^^^^^^^^^^^^^^^^^^^^^|[]\n"); 
	cho = read_choice(choice);
	
	switch(cho)
	{
		case 1:
			token = 1;
			delete_user(token);
		
		case 2:
			add_admin();
		
		case 3:
			token =0;
			list_members(token);			
		case 4:
			token = 0;
			delete_user(token);
			
		case 5:
			token = 0;
			change_passwd(token);
		case 6:
			admin();
			
		default:
			printf("Invalid Choice:\n");
			admin_settings();	
			
	}
	
}

void delete_user(int token)
{
	login record;
	int flag;
	char temp,name[20];
	
	FILE *fvar;
	if(token == 0)
		fvar = fopen("admin.bat", "r");
	
	else
		fvar = fopen("user.bat","r");
	
	
	printf("\n\n\t\t\t\tEnter Username to delete: ");
	fflush(stdin);
	gets(name);
	fread(&record, sizeof(login), 1, fvar);

	while(!feof(fvar))
	{
	
		flag=0;
		if(strcmp(name, record.u_name)==0)
		{
			delete_record(name,token);
			break;
		}
		
		flag++;
		
		fread(&record, sizeof(login), 1, fvar);
	}
	if(flag!=0)
		printf("\t\t\t\tRecord not found for %s.\n", name);
		
	else
		printf("\t\t\t\tDelete Successful!\n");

	fclose(fvar);
	
	if(flag==0 && token == 0)
	{
		remove("admin.bat");
		rename("updated.bat", "admin.bat");
	}
	else if(flag == 0 && token != 0)
	{
		remove("user.bat");
		rename("updated.bat", "user.bat");
	}
	printf("Press any key to go back..");
	fflush(stdin);
	temp = getchar();
	admin_settings();
		
}

void add_admin()
{
	system("cls");
	login record;
	int choice;
	char temp;
	FILE *fvar;
  	fvar = fopen("admin.bat", "a+");
  	printf("\n\n\n\n\t\t\t\t\t {|>>>>>>>>>>>>>><<<<<<<<<<<<<<|}\n");
	printf("\t\t\t\t\t {}       Add a new Admin!     {}\n");
	printf("\t\t\t\t\t {|>>>>>>>>>>>>>><<<<<<<<<<<<<<|}\n\n\n");

	printf("\t\t\t\t\tPress 1 to continue and 0 to exit: ");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
			record = new_account(record, fvar);
			fwrite(&record, sizeof(login), 1, fvar);
			fclose(fvar);
			printf("\n\n\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n");                                                                        
			printf("\t\t\t\t\t  |      CONGRATULATIONS!      |\n");
			printf("\t\t\t\t\t  |Your acount has been created|\n");
			printf("\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n\n\n");
			printf("Press any key to continue..."); 
			temp = getchar();
		case 0:
			break;
	}
	admin_settings();
}

void change_passwd(int token)
{
	system("cls");
	login record;
	int flag;
	char temp,name[20];
	
	FILE *fvar;
	
	if(token == 0)
		fvar = fopen("admin.bat", "r");
	
	else
		fvar = fopen("user.bat", "r");
	printf("\n\n\n\n\t\t\t\t\t {|>>>>>>>>>>>>>><<<<<<<<<<<<<<|}\n");
	printf("\t\t\t\t\t{}     Change Your Password     {}\n");
	printf("\t\t\t\t\t {|>>>>>>>>>>>>>><<<<<<<<<<<<<<|}\n\n\n");	
	printf("\t\t\t\tEnter Username: ");
	fflush(stdin);
	gets(name);
	fread(&record, sizeof(login), 1, fvar);

	while(!feof(fvar))
	{
	
		flag=0;
		if(strcmp(name, record.u_name)==0)
		{
			update_record(name,token);
			break;
		}
		flag++;
		
		fread(&record, sizeof(login), 1, fvar);
	}
	if(flag!=0)
		printf("\t\t\t\tRecord not found for %s.\n", name);
		
	else
		{
			printf("\n\n\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n");                                                                        
			printf("\t\t\t\t\t  |      CONGRATULATIONS!      |\n");
			printf("\t\t\t\t\t  |Password Succesfully Updated|\n");
			printf("\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n\n\n");
			
		}
	fclose(fvar);
	fclose(fvar);
	if(flag==0 && token == 0)
	{
		remove("admin.bat");
		rename("updated.bat", "admin.bat");
		printf("Press any key to continue..."); 
		fflush(stdin);
		temp = getchar();
		admin_settings();
	}
	else if(flag == 0 && token != 0)
	{
		remove("user.bat");
		rename("updated.bat", "user.bat");
		printf("Press any key to continue..."); 
		fflush(stdin);
		temp = getchar();
		user();
		
	}
			
	
}

void update_record(char name[],int token)
{
	login record, change;
	char  new_passwd[33],temp_passwd[33];
	int len;
	FILE *ptvar, *fvar;
	ptvar = fopen("updated.bat", "w");
	
	if(token == 0)
		fvar = fopen("admin.bat", "r");
	else
		fvar = fopen("user.bat", "r");

	fread(&record, sizeof(login), 1, fvar);
	while(!feof(fvar))
	{
		if(strcmp(name, record.u_name)!=0)
		{
			fwrite(&record, sizeof(login), 1, ptvar);
		}
		else
		{
			fflush(stdin);
			printf("\n\t\t\t\t\tEnter your old password: ");
			gets(temp_passwd);
			len = strlen(temp_passwd);
			
			change = encrypt(change, temp_passwd,len);
			
			if(strcmp(change.passwd, record.passwd)==0)
			{
				fflush(stdin);
				printf("\t\t\t\t\tEnter New password: ");
				gets(new_passwd);
				len = strlen(new_passwd);
				record = encrypt(record, new_passwd, len);
				
				fwrite(&record, sizeof(login), 1, ptvar);
			}
			
			else
			{
				printf("\t\t\t\t\tWrong password!! Try Again\n");
				continue;
			}
			
			
		}
		fread(&record, sizeof(login), 1, fvar);
	}
	fclose(fvar);
	fclose(ptvar);
	return;
}

void game_entry(FILE *fptr,game game_data[])
{
	system("cls");
	char choice ;
	int i=0;
	fptr=fopen("game_record.bat","a");
	game_data[i].s_no=0;
    printf("\n\n\n\n\t\t\t\t\t !!>>>>>>>>>>>>>><<<<<<<<<<<<<<!!\n");
	printf("\t\t\t\t\t  ||       New Game Entry     ||\n");
	printf("\t\t\t\t\t !!>>>>>>>>>>>>>><<<<<<<<<<<<<<!!\n\n\n");
	
	do
	{
		game_data[i].s_no=game_data[i].s_no+1;
	  printf("\t\t\t\tEnter Name of the Game: ");
      
	  fflush(stdin);
	  
	  gets(game_data[i].game_name);

	  printf ("\n\t\t\t\tEnter the game price:");
	  scanf("%d",&game_data[i].game_price);

	  fwrite(&game_data[i],sizeof(game),1,fptr);
	printf("\nDo you want to enter more data? (Y for yes // any key to go back)\n\n");
	choice=getch();
	i++;
	}while(choice=='Y'|| choice=='y');


	fclose(fptr);
	game_edit();
}

void select_game()
{
	
	game game_data;
	int flag;
	float price,time;
	char temp,name[20];
	FILE *fvar;
	fvar = fopen ("game_record.bat","r");

	fflush(stdin);
	printf("\t\t\tEnter the game you want to play: ");
	gets(name);

	fread(&game_data, sizeof(game),1,fvar);
	
	while(!feof(fvar))
	{
		flag=0;
		if(strcmp(name, game_data.game_name)==0)
		{	
			printf("\n\t\t\tHow many hours you want to play: ");
			scanf("%f",&time);
			price = time * game_data.game_price-15;
			printf("\n\t\t\tTotal Price = %f\n", price);
			
			break;
				
		}
		fread(&game_data, sizeof(game),1,fvar);
		
		flag++; 
		
		
	}
	if(flag != 0)
	{
		printf("Game not Found :(  .. Try again!!\n");
		select_game();
	
	}
	printf("\n\n\n\n\t\t\t\t\t {|>>>>>>>>>>>>>><<<<<<<<<<<<<<|}\n");
	printf("\t\t\t\t\t  {}       Thank You!!!       {}\n");
	printf("\t\t\t\t\t  {}       Come Again :D      {}\n");
	printf("\t\t\t\t\t {|>>>>>>>>>>>>>><<<<<<<<<<<<<<|}\n\n\n");	
	printf("Press any key to go back..");
		fflush(stdin);
		temp = getchar();
		user();	
}

void game_list(FILE *fptr, game game_data[],int token)
{
	system("cls");
	int i=0,counter = 0;
	char temp;
	fptr=fopen("game_record.bat","r");
	printf("\n\n\n\n\t\t\t\t\t }}>>>>>>>>>>>>>><<<<<<<<<<<<<<{{\n");
	printf("\t\t\t\t\t  ||      List of Games      ||\n");
	printf("\t\t\t\t\t }}>>>>>>>>>>>>>><<<<<<<<<<<<<<{{\n\n");

	fread(&game_data[i],sizeof(game),1,fptr);
	while(!feof(fptr))
	{
		printf("\t\t\t\t\t  Name:     ");
		puts(game_data[i].game_name);
		
		printf("\t\t\t\t\t  Price: %d \n",game_data[i].game_price);
		printf("\t\t\t\t\t |..............................|\n\n");
		i++;
		fread(&game_data[i],sizeof(game),1,fptr);
		counter++;
	}

	fclose(fptr);
	
	
	if(token==0)
	{
		printf("\n\n\t\t\t\t\tTotal no of data: %d\n\n",counter);
		printf("Press any key to go back..");
		fflush(stdin);
		temp = getchar();
		game_edit();
	}
	
	else if (token == 5)
		update_price();
	
	else if (token == 4)
		delete_game();
	else
		select_game();	
}

void game_search(FILE *fptr,game game_data[])
{
	int i=0;
	char temp,s_name[15];
	
	printf("\n\t\t\t\tEnter the name of game: ");
	fflush(stdin);
	gets(s_name);
	
	fptr=fopen("game_record.bat","r");


	do 
	{
	
		fread(&game_data[i],sizeof(game),1,fptr);
	
		if (strcmp(game_data[i].game_name,s_name)==0)
		{
			printf("Name: ");
			puts(game_data[i].game_name);

			printf("Price: %d \n\n",game_data[i].game_price);
			break;
		}

	i++;

   	}while(!feof(fptr));
   	
	fclose(fptr);
	printf("Press any key to go back..");
	temp = getchar();
	game_edit();
}

void update_price()
{
	game game_data;
	int flag;
	char temp,name[20];
	
	FILE *fvar;
	fvar = fopen("game_record.bat", "r");
	fflush(stdin);
	printf("\n\n\t\t\tUpdate price of the game");
	printf("\n\t\t\t\tEnter Game Name: ");
	gets(name);
	fread(&game_data, sizeof(game), 1, fvar);

	while(!feof(fvar))
	{
	
		flag=0;
		if(strcmp(name, game_data.game_name)==0)
		{
			set_price(name);
			break;
		}
		flag++;
		
		fread(&game_data, sizeof(game), 1, fvar);
	}
	if(flag!=0)
		printf("\n\t\t\t\tRecord not found for %s.\n", name);
		
	else
			printf("\n\n\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n");                                                                        
			printf("\t\t\t\t\t  |      CONGRATULATIONS!      |\n");
			printf("\t\t\t\t\t  | The Price has been updated |\n");
			printf("\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n\n\n");

	fclose(fvar);
	if (flag==0)
	{
		remove("game_record.bat");
		rename("test.bat", "game_record.bat");
	}
	printf("Press any key to go back..");
	fflush(stdin);
	temp = getchar();
	game_edit();		
	
}

void set_price(char name[])
{
	game game_data;

	FILE *ptvar, *fvar;
	ptvar = fopen("test.bat", "w");
	fvar = fopen("game_record.bat", "r");

	fread(&game_data, sizeof(game), 1, fvar);
	while(!feof(fvar))
	{
		if(strcmp(name, game_data.game_name)!=0)
		{
			
			fwrite(&game_data, sizeof(game), 1, ptvar);
		}
		else
		{
			
			printf("Enter New Price: ");
			scanf("%d", &game_data.game_price);
		
			fwrite(&game_data, sizeof(game), 1, ptvar);
			
		}
		fread(&game_data, sizeof(game), 1, fvar);
	}
	fclose(fvar);
	fclose(ptvar);
	return;
}

void delete_game()
{
	game game_data;
	int flag;
	char temp,name[20];
	
	FILE *fvar;
	fvar = fopen("game_record.bat", "r");
	fflush(stdin);
	printf("\n\nEnter Game Name to delete: ");
	gets(name);
	fread(&game_data, sizeof(game), 1, fvar);

	while(!feof(fvar))
	{
	
		flag=0;
		if(strcmp(name, game_data.game_name)==0)
		{
			remove_game(name);
			break;
		}
		
		flag++;
		
		fread(&game_data, sizeof(game), 1, fvar);
	}
	if(flag!=0)
		printf("Record not found for %s.\n", name);
		
	else
		printf("\n\n\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n");                                                                        
			printf("\t\t\t\t\t  |      CONGRATULATIONS!      |\n");
			printf("\t\t\t\t\t  |  Game Succesfully Deleted  |\n");
			printf("\t\t\t\t\t ||>>>>>>>>>>>>>><<<<<<<<<<<<<<||\n\n\n");

	fclose(fvar);
	if(flag == 0)
	{
		remove("game_record.bat");
		rename("test.bat", "game_record.bat");		
	}
	printf("Press any key to go back..");
	fflush(stdin);
	temp = getchar();
	game_edit();
}

void remove_game(char name[])
{
	game game_data;
	FILE *ptvar, *fvar;
	ptvar = fopen("test.bat", "w");
	fvar = fopen("game_record.bat", "r");

	fread(&game_data, sizeof(game), 1, fvar);
	while(!feof(fvar))
	{
		if(strcmp(name, game_data.game_name)!=0)
		{
			fwrite(&game_data, sizeof(game), 1, ptvar);
		}

		fread(&game_data, sizeof(game), 1, fvar);
	}
	fclose(fvar);
	fclose(ptvar);
	return;
}

void delete_record(char name[], int token)
{
	login record;
	FILE *ptvar, *fvar;
	ptvar = fopen("updated.bat", "w");
	
	if(token == 0)
		fvar = fopen("admin.bat", "r");
	else
		fvar = fopen("user.bat","r");

	fread(&record, sizeof(login), 1, fvar);
	while(!feof(fvar))
	{
		if(strcmp(name, record.u_name)!=0)
		{
			fwrite(&record, sizeof(login), 1, ptvar);
		}

		fread(&record, sizeof(login), 1, fvar);
	}
	fclose(fvar);
	fclose(ptvar);
	return;
}

void user()
{
	system("cls");
	game game_data[50];
	int token,cho,choice;
	FILE *fptr;
	
	printf("\n\n\n\n\t\t\t\t\t    <||>>>>>>> <<<<<<<||>\n");
	printf("\t\t\t\t\t    ||  Welcome User   ||\n");
	printf("\t\t\t\t\t    <||>>>>>>> <<<<<<<||>\n\n\n");
	printf("\t\t\t\t\t=----------------------------=\n");
	printf("\t\t\t\t\t||   1. View List of Games  ||\n");
	printf("\t\t\t\t\t||   2.  Change Password    ||\n");
	printf("\t\t\t\t\t||   3.      Logout         ||\n");
	printf("\t\t\t\t\t=----------------------------=\n\n\n");
		
	cho = read_choice(choice);
	
	switch(cho)
	{
		case 1:
			token = 1;
			game_list(fptr, game_data,token);
		case 2:
			token = 1;
			change_passwd(token);
			
		case 3:
			main();
		
		default:
			printf("Invalid Choice:\n");
			user();
	}
	
}

login new_account(login record, FILE *fvar)
{
  	int i=0, flag, len;
  	char temp[20], temp_passwd[33], pcode[33];
  
  	while (i==0)
  	{
  		flag=0;
  	
  		fflush(stdin);
    	printf("\n\n\t\t\t\tEnter Username for your account: ");
    	gets(temp);
    	rewind(fvar);
    
    	fread(&record, sizeof(login), 1, fvar);
		while(!feof(fvar))
    	{
    		if(strcmp(temp, record.u_name)==0)
    		{
    		  printf("\t\t\t\tThis user already exists. Please try another!\n");
    	  		flag++;
			}
		
   			fread(&record, sizeof(login), 1, fvar);
		}
		if (flag!=0)
			continue;
    
    	i++;
  	}
  	strcpy(record.u_name, temp);
  
  	printf("\t\t\t\tEnter your Name: ");
	gets(record.name);

  	while(i==1)
  	{
  		fflush(stdin);
  		printf("\t\t\t\tEnter password: ");
  		gets(pcode);
  		len=strlen(pcode);
  		
  		fflush(stdin);
  		printf("\t\t\t\tConfirm password: ");
  		gets(temp_passwd);
  	
  		if (strcmp(pcode, temp_passwd)!=0)
  		{
  		  printf("\t\t\t\tDifferent Passwords. Please Try again!\n");
  	  	continue;
  		}
  		i++;
  	}
  	
  	record = encrypt(record, pcode, len);
	return (record);
 	
}

login encrypt(login record, char pcode[], int len)
{
	int j, num[33];
	 char check[33];
	for (j=2; j<len; j++)
		num[j] = toascii(pcode[j-2])*len;

	num[0]=len;
	num[1] = (toascii(pcode[j]) + toascii(pcode[len]))*len;
	num[len] = (toascii(pcode[0])+toascii(pcode[len/2])+toascii(pcode[len]))*len*len;
	
	itoa(num[0], record.passwd, 16);

	for (j=1; j<=len; j++)
	{
		itoa(num[j], check, 16);
		strcat(record.passwd, check);
	}
	return (record);
}

void check_user(login record, FILE *ptvar)
{
	char name[20], raw_passwd[33];
	int i=0, flag;
	
	while (i==0)
	{
		fflush(stdin);
		printf("\n\n\t\t\tEnter Username: ");
		gets(name);
		rewind(ptvar);
		
		fread(&record, sizeof(login), 1, ptvar);
		while(!feof(ptvar))
		{
			flag=0;
			if(strcmp(name, record.u_name)==0)
				break;
			
			flag++;	
			fread(&record, sizeof(login), 1, ptvar);	
		}
		
		strcpy(raw_passwd, record.passwd);
		
		if (flag!=0)
		{
			printf("\t\t\tSorry! Incorrect Username. Try Again!\n");
			continue;
		}		
		i++;	
	}
	check_passwd(record, raw_passwd);
	return;
}

void check_passwd(login record, char raw_passwd[])
{
	int i=0, len;
	char passwd[33];
	while(i==0)
	{
		printf("\t\t\tEnter Password: ");
		gets(passwd);
		len = strlen(passwd);
		record = encrypt(record, passwd, len);
		
		if(strcmp(raw_passwd, record.passwd)!=0)
		{
			printf("\t\t\tSorry! Incorrect Password. Please Try Again!\n");
				continue;
		}
		printf("You are logged in!\n");
		i++;
	}
	return;
}
