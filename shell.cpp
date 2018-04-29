#include <iostream>
#include <cstdio>
#include <csignal>
#include <cstdlib>
#include <cstring>


using namespace std;

//GLOBAL VARIABLE
char *ip_cmd , *tokens[50];
int no_of_tokens;


//FUNCTIONS DECALARATION
//void intializer();
int tokenizer();
int check_command();
void cmd_inbuit();
//void cmd_usd();
//void parser(int );
//void addtohistory();


int main(int argc , char *argv[])
{

//intializer()

char temp_ip[300];
int i,j,chkcmd;


while(1)		
{
	scanf("%[^\n]",temp_ip);
	getchar();
	ip_cmd=(char *)malloc(strlen(temp_ip)+1);
	strcpy(ip_cmd,temp_ip);

    if (strcmp(ip_cmd,"exit")==0)
	 {   break;}

    else //if (ip_cmd[0]!=0)  //printf("add to history execute\n");//add_history(buf);
	{
		// NOW RUN   CALL TO TOKENIZER		 //for(j=0;j<i;j++) 	{ 	printf("%s\n",tokens[j]);	}
		no_of_tokens =	tokenizer();		
	
		//parser(no_of_tokens);	  /*identify token no that has command and pass it(parser will return the no that has the command pass it using loop)*/
		

//pid_t childpid;
//printf("Before fork\n");
	   
 /*childpid = fork();
	
	if(childpid >= 0)
	{
		if( childpid == 0)
		{	printf("inchild\n");	execvp(tokens[0],tokens);	}
		else
		{printf("in parent\n");}
		cout<<"fork over"<<endl;
	}
	else // fork returns -1 on failure 
   	{
   	    perror("fork"); // display error message 
   	    exit(0); 
   	}*/

		chkcmd = check_command();	/*actually parser checks whole string and its validity and which token is of which command*/
		if(chkcmd == 0)//check if command is inbuilt call execvp //if inbuilt cmd return 0 else 1
		{	cmd_inbuit(); }	
		/*else if(chkcmd == 1)		//or usd function
		{}*/		
		else			//-1 command not found
		{printf("invalid command");}

	}

	free(ip_cmd);		


}
return 0;
}





void cmd_inbuit()
{
pid_t childpid;
printf("Before fork\n");
	   
 childpid = fork();
	
	if(childpid >= 0)
	{
		if( childpid == 0)
		{	printf("inchild\n");	
		execvp(tokens[0],tokens);				
		cout<<"fork over"<<endl;	}
		else
		{printf("in parent\n");}
	}
	else /* fork returns -1 on failure */
   	{
   	    perror("fork"); /* display error message */
   	    exit(0); 
   	}
}





int check_command()
{//check for token of 0 1st

char *temp;
int flag=0;
FILE *file = fopen ( "inbuilt_function.txt" , "r" );

temp =(char*)malloc( (strlen(tokens[0]) + 1 ) * sizeof(char) );

temp = strcat(tokens[0] , "\n");



// inbuilt file
if ( file != NULL )
{
	char line [ 32 ]; 
	while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
	{
		if(strcmp(temp , line)==0)
		{	
			printf("matched\n");
			flag=1;
			return 0;
		}		//fputs ( line, stdout ); /* write the line */
	}	
	fclose ( file );
}
else
{
	perror ( "Error in opening file check file path or name is proper\n" ); 
}



//usd file  
file = fopen ( "usd_function.txt" , "r" );
if ( file != NULL )
{
	char line [ 32 ]; 
	while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
	{
		if(strcmp(temp , line)==0)
		{	
			printf("matched\n");
			flag=1;			
			return 1;
		}		//fputs ( line, stdout ); /* write the line */
	}	
	fclose ( file );
}
else
{
	perror ( "Error in opening file check file path or name is proper\n" ); 
}

if(flag==0)
{
	return -1;
}

return 0;
}

























//***************--------------intializer(){}

int tokenizer()
{

char *pch;
int i=0,j;

pch = strtok (ip_cmd," ");		//  pch = strtok (str," ,.-");
	
while (pch != NULL)
{
	tokens[i]=(char *)malloc(strlen(pch)+1);
	strcpy(tokens[i],pch);
	i++;
    pch = strtok (NULL," ");
}
return i;
/*for(j=0;j<i;j++)
{
	printf("%s\n",tokens[j]);
}*/

}


/*
//***************--------------parser
void parser(int no_of_tokens_inparser)
{
//check validity of input
//if valid //call funtion to check validity 
//if not valid return 
//else
//if it is inbuilt execute
//else call usd
// there should be a facility to call pipe from both function
}
*/

