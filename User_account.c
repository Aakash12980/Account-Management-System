#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct{
		char u_name[20], passwd[33], name[30];
	}login;
	
login new_account(login, FILE*);
login encrypt(login, char[], int);
	
void main()
{
	login record;
	int choice;
	FILE *fvar;
  	fvar = fopen("test.bat", "a+");
  	
	printf("Welcome To the System\n\n");
	printf("Press 1 to create new account and 0 to exit: ");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
			record = new_account(record, fvar);
			fwrite(&record, sizeof(login), 1, fvar);
			fclose(fvar);
			printf("\n\n CONGRATULATIONS! Your acount has been created.");
		case 0:
			break;
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
    	printf("Enter Username for your account: ");
    	gets(temp);
    	rewind(fvar);
    
    	fread(&record, sizeof(login), 1, fvar);
		while(!feof(fvar))
    	{
    		if(strcmp(temp, record.u_name)==0)
    		{
    		  printf("This user already exists. Please try another!\n");
    	  		flag++;
			}
		
   			fread(&record, sizeof(login), 1, fvar);
		}
		if (flag!=0)
			continue;
    
    	i++;
  	}
  	strcpy(record.u_name, temp);
  
  	printf("Enter your Name: ");
	gets(record.name);

  	while(i==1)
  	{
  		fflush(stdin);
  		printf("Enter password: ");
  		gets(pcode);
  		len=strlen(pcode);
  		
  		fflush(stdin);
  		printf("Confirm password: ");
  		gets(temp_passwd);
  	
  		if (strcmp(pcode, temp_passwd)!=0)
  		{
  		  printf("Different Passwords. Please Try again!\n");
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
