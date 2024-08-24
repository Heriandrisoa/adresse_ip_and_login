#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#define MAX 1000
void login(char* logged);
int is_already_in(char* user);
int check_password(char* user,char* password);
void change_password(char* user);
void deconnect();
void meo();
void adduser();
int getip();
int valid(char* A);
int compare(char* A,char* B);
int main()
{
	char logged[100];
	log:
	while(1)
	{
	login(logged);
	printf("\n\nbienvenu %s\n\n", logged);
	printf("\ntapez deconnection si vous voulez vous deconnecter\n");
	printf("\ntapez ajouter si vous voulez ajouter un login\n");
	getip();
	}

	return 0;
}


void login(char* logged_in)
{
	int repere=0;
	//system("clear");
	sprintf(logged_in," ");
	FILE* log_actual_file=NULL;
	FILE* log_file=NULL;
	char buffer[MAX]=" ";
	char password[MAX];
	log_actual_file=fopen("cache/is_already_logged", "r+");
	log_file=fopen("cache/all_login","r+");
	if(log_actual_file==NULL)
	{
		printf("erreur d'ouverture du fichier is_already loged");
		exit(1);
	}

	if(log_file==NULL)
	{
		printf("erreur d'ouverture du fichier all_login");
		exit(1);
	}

	fgets(logged_in,100,log_actual_file);
	if(strcmp(logged_in," ")==0)
	{
		++repere;
		ask:
		printf("login:");
		meo(logged_in);
		rewind(log_file);
		printf("mot de passe:");
		//getchar();
		meo(password);
		//printf("%s-------", password);
		/*mitady an le login oe misy ao am le fichier ve */
		while(fgets(buffer,150,log_file)!=NULL)
		{
		//printf("%s", buffer);
		/*for(int i=0 ; i<strlen(buffer) ; i++)
		{
			printf("%c--", buffer[i]);
		}*/
		//printf("%ld", strlen(buffer));
		//printf("%s %ld",buffer,strlen(buffer));
		if(!compare(logged_in,buffer))
			goto password;
		}
		printf("login incorect ou invalide\n");
		goto ask;
		password:

		if(!check_password(logged_in,password))
		{
			printf("mot de passe incorect\n");
			goto ask;
		}
		success:
		printf("\t\t");
	//	system("clear");
	}
	if(repere>0)
		fprintf(log_actual_file,"%s",logged_in);
	fclose(log_actual_file);
	fclose(log_file);
}

int is_already_in(char* user)
{
	FILE* A=NULL;
	A=fopen("cache/all_login", "r+");
	if(A==NULL)
	{
		printf("erreur lors de l'ouverture du fichier all_login");
		exit(1);
	}
	char buffer[MAX];
	while(fgets(buffer,150,A)!=NULL)
	{
		//printf("eeto llo %s %s\n",buffer,user);
		if(compare(user,buffer)==0)
		{
			//printf("%s-%s",buffer,user);
			return 1;
		}
	}

	return 0;
}

void change_password(char* user)
{
	printf("");
}

int check_password(char* user,char* passwd)
{

	int c, user_index=0, password_index=0;
	FILE* password_file=NULL;
	char str[MAX];
	char* buffer;
	char user_buffer[MAX];
	char password_buffer[MAX];

	password_file=fopen("cache/all_password","r+");
	if(password_file==NULL)
	{
		printf("erreur lors de la verification des mot de passe");
		exit(1);
	}	
	while(fgets(str,150,password_file))
	{
		buffer=strtok(str,":");
		strcpy(user_buffer,buffer);
		buffer=strtok(NULL,":");
		strcpy(password_buffer,buffer);
		if(strcmp(user_buffer,user)==0)
		{
			//printf("%s %s %s %s", user_buffer,password_buffer,passwd,user);
			if(compare(passwd,password_buffer)==0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	

	
}
void deconnect()
{
	FILE* loggoff=NULL;

	loggoff=fopen("cache/is_already_logged" , "w");

	if(loggoff==NULL)
	{
		printf("probmleme lors de la deconnection");
	}
	getchar();
	fclose(loggoff);
}

void meo(char* str)
{
	int c,index=0;


	while((c=getchar())!='\n')
	{
		str[index]=c;
		index++;
	}
	str[index]='\0';
}

void adduser()
{
	FILE* log_in=NULL;
	FILE* password_file=NULL;
	password_file=fopen("cache/all_password","a+");
	log_in=fopen("cache/all_login","a+");
	if(password_file==NULL)
	{
		printf("erreur d'ouverture du fichier all_password");
		exit(1);
	}
	
	if(log_in==NULL)
	{
		printf("erreur d'ouverture du fichier all_login");
		exit(1);
	}

	char user_name[MAX];
	char user_password[MAX];

	ask:
	printf("nom de l'utilisateur:");
	getchar();
	meo(user_name);
	printf("mot de passe:");
	//getchar();
	meo(user_password);
	if(is_already_in(user_name))
	{
		printf("le nom d'utilisateur est deja pris\n");
		goto ask;
	}
	fprintf(password_file,"%s:%s\n",user_name,user_password);
	//printf("%s %s",user_name,user_password);
	fprintf(log_in,"%s\n", user_name);
	printf("ajout avec succes\n ");
	//system("sleep(2)");
	fclose(log_in);
	fclose(password_file);
}


int getip()
{
	
	char* ip=NULL;
	ip=malloc(MAX*sizeof(char));
	if(ip==NULL)
	{
		printf("erreur allocation");
		exit(1);
	}
	get:
	printf("\nles addresses ip doivent respecter le format a.b.c.d ou a,b,c,d sont des entiers compris entre 0 et 255\n\n");
	printf("ip:");
	scanf("%s", ip);
	if(strcmp(ip,"deconnection")==0)
	{
		printf("deconnection... \n");
		deconnect();
		return 1;
	}
	else if(strcmp(ip,"ajouter")==0)
	{
		adduser();
		return 1;
	}

	else if(strcmp(ip,"clear")==0)
	{
		system("clear");
		return 1;
	}
	if(!valid(ip))
	{
		goto get;
	}
	exit(1);
}

int valid(char* A)
{
	int buff,class;
	char* buffer;
	int count_point=0;
	for(int i=0 ; i<strlen(A) ; i++)
	{
		if(A[i]=='.')
		{
			count_point++;
		}
		else
		{
			if(!strchr("0123456789",A[i]))
			{
				printf("erreur de syntaxe\n");
				return 0;
			}
		}
	}
	if(count_point!=3)
	{
		printf("erreur de syntaxe\n");
		return 0;
	}

	buffer=strtok(A,".");
	class=atoi(buffer);
	while(buffer!=NULL)
	{
		int buff;
		buff=atoi(buffer);
		if(buff>255||buff<0)
		{
			printf("addresse ip non valide sur %d\n",buff);
			return 0;
		}
		buffer=strtok(NULL,".");
	}
	printf("l'adresse ip est de classe:");
	if(class<=128)
	{
		printf("A");
	}
	else if(class<=192)
	{
		printf("B");
	}
	else if(class<=224)
	{
		printf("C");
	}
	else
	{
		printf("D");
	}
	return 1;
}

int compare(char* A,char* B)
{
	if(strlen(A)!=strlen(B)-1)
	{
		return 1;
	}	
	
	B[strlen(B)-1]='\0';
	if(strcmp(A,B)==0)
		return 0;
	else
		return 1;
}