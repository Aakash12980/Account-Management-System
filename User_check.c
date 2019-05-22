#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct{
		char u_name[20], passwd[33], name[30];
	}login;
	
login new_account(login, FILE*);
login encrypt(login, char[], int);
void check_user(login, FILE*);
void check_passwd(login, char[]);

void main()
{
	login record;
	int choice;
	FILE *ptvar;
  	ptvar = fopen("test.bat", "r");
  	
	check_user(record, ptvar);
	fclose(ptvar);
}

void check_user(login record, FILE *ptvar)
{
	char name[20], raw_passwd[33];
	int i=0, flag;
	
	while (i==0)
	{
		fflush(stdin);
		printf("Enter Username: ");
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
			printf("Sorry! Incorrect Username. Try Again!\n");
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
		printf("Enter Password: ");
		gets(passwd);
		len = strlen(passwd);
		record = encrypt(record, passwd, len);
		
		if(strcmp(raw_passwd, record.passwd)!=0)
		{
			printf("Sorry! Incorrect Password. Please Try Again!\n");
				continue;
		}
		printf("You are logged in!\n");
		i++;
	}
	return;
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
