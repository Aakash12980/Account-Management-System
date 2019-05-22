#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct{
		char u_name[20], passwd[33], name[30];
	}login;
	
void delete_record(char[]);
login encrypt(login, char[], int);


void main()
{
	login record;
	int flag;
	char name[20];
	
	FILE *fvar;
	fvar = fopen("test.bat", "r");
	
	printf("Enter Username: ");
	gets(name);
	fread(&record, sizeof(login), 1, fvar);

	while(!feof(fvar))
	{
	
		flag=0;
		if(strcmp(name, record.u_name)==0)
		{
			delete_record(name);
			break;
		}
		flag++;
		
		fread(&record, sizeof(login), 1, fvar);
	}
	if(flag!=0)
		printf("Record not found for %s.\n", name);
		
	else
		printf("Password Successfully Updated!\n");

	fclose(fvar);
	if (flag==0)
		remove("test.bat");
	rename("updated.bat", "test.bat");	
	
}

void delete_record(char name[])
{
	login record;
	char new_passwd[33];
	int len;
	FILE *ptvar, *fvar;
	ptvar = fopen("updated.bat", "w");
	fvar = fopen("test.bat", "r");

	fread(&record, sizeof(login), 1, fvar);
	while(!feof(fvar))
	{
		if(strcmp(name, record.u_name)!=0)
		{
			fwrite(&record, sizeof(login), 1, ptvar);
		}
		else
		{
			
			printf("Enter New password: ");
			gets(new_passwd);
			len = strlen(new_passwd);
			record = encrypt(record, new_passwd, len);
			printf("Passwd: %s\n", record.passwd);
			fwrite(&record, sizeof(login), 1, ptvar);
			
		}
		fread(&record, sizeof(login), 1, fvar);
	}
	fclose(fvar);
	fclose(ptvar);
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
