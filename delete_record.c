#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct{
		char u_name[20], passwd[33], name[30];
	}login;
	
void delete_record(char[]);

void main()
{
	login record;
	int flag;
	char name[20];
	
	FILE *fvar;
	fvar = fopen("test.bat", "r");
	
	printf("Enter Username to delete: ");
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
		printf("Record not found for %s.", name);
		
	else
		printf("Delete Successful!");

	fclose(fvar);
	remove("test.bat");
	rename("updated.bat", "test.bat");	
	
}

void delete_record(char name[])
{
	login record;
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

		fread(&record, sizeof(login), 1, fvar);
	}
	fclose(fvar);
	fclose(ptvar);
	return;
}
