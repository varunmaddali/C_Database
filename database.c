#include <stdio.h>
#include <string.h>
//*****************************+++++++++++++++++**********            Increase the array sizes after the completion***********************
int hash1(char *a, int n);
int p_N = 0;
int t_N = 0;
void setP_N(int v)
{
	p_N = v;
}
struct pkmn
{
	char ID[20];
	char NAME[25],TYPE[150],STRONG_TO[150],WEAK_TO[100];
}pkmn_array[50];

void setT_N(int v)
{
	t_N = v;
}

struct train
{
	char FIRSTNAME[30],LASTNAME[50],BADGES_HELD[100],POKEMON_OWNED[500];
	char AGE[10];
}train_array[100];



int main(int argc, char* argv[])
{
	int num = 0,count,count1,il = 0,insert = 0,update = 0,delete = 0,select = 0,write = 0,linecount=1;
	char str[999],* pch,t[100],*pch1,*check,rowsArray[100][999],command[100][1000];
	FILE *fptr;
	//fptr = fopen( "input1.txt" , "r");
	fptr = fopen(argv[1] , "r");
	if (fptr)
	{
		printf("\ndatabase created awaiting to create tables in it\n");
		while (fscanf(fptr, "%s", str)!=EOF)
		{
			num++;
			if((strcmp("pokemon.txt",str))==0)
			{
				pokemon();		
			}
			if((strcmp("trainers.txt",str))==0)
			{
				trainers();//*****************************************************************************   Uncomment it later//
			}
								
			if(num > 4)
			{
				//printf("\n%s\n",str);
				strcpy(rowsArray[il], str);
				strcat(rowsArray[il],"\0");
				//printf("\n%s\n",rowsArray[il]);
			}
			il++;
		}
		il = il-1;
		printf("----------------------------------------updating tables---------------------------------\n");
		printf("number of operations on the tables :%d\n",il-3);
		
		
		//Displaying the lines with commands
		/*for(int i = 0;i<il+1;i++)
		{
			printf("\n%s\n",rowsArray[i]);
		}*/
		
		for(int i = 0;i<100;i++)
		{
			strcpy(command[i],"o");
		}
		
		
		for(int i = 0;i<il+1;i++)
		{	
			if(i>3)
			{
				printf("-----------------------------------------------------------------------------------\n");
				printf(" %d.\n ",i-3);
				if(rowsArray[i][0] == 'I')
				{
					insert = 1;
					for(int j = 0;rowsArray[i][j] != '\0';j++)
					{
						if(rowsArray[i][j] == ')' && rowsArray[i][j+2] == 'p')
						{
							//printf("\ninserting into pokemons\n");
							linecount = 1;
							for(int u =1;rowsArray[i][u]!='\0';u++)
							{
								linecount++;
							}
							//printf("\nline count: %d",linecount);
							strncpy(command[i],rowsArray[i]+8,linecount-18);
							strcat(command[i],"\0");
							//printf("\n Inserting into pokemons \n---%s\n",command[i]);
							insert_into('p',command[i]);
						}
						else if(rowsArray[i][j] == ')' && rowsArray[i][j+2] == 't')
						{
							//printf("\ninsert into trainers\n");
							linecount = 1;
							for(int u =1;rowsArray[i][u]!='\0';u++)
							{
								linecount++;
							}
							//printf("\n\n*****line count: %d",linecount);
							strncpy(command[i],rowsArray[i]+8,linecount-19);
							strcat(command[i],"\0");
							//printf("\n inserting into trainers \n---%s\n",command[i]);
							insert_into('t',command[i]);
						}
					}
				}
				
				else if(rowsArray[i][0] == 'U')
				{
					update = 1;
					for(int j = 0;rowsArray[i][j] != '\0';j++)
					{
						if(rowsArray[i][j] == ')' && rowsArray[i][j+2] == 'p')
						{
							//printf("\n Updating into pokemons\n");
							linecount = 1;
							for(int u =1;rowsArray[i][u]!='\0';u++)
							{
								linecount++;
							}
							//printf("\nline count: %d",linecount);
							strncpy(command[i],rowsArray[i]+8,linecount-18);
							strcat(command[i],"\0");
							//printf("\n Updating into pokemons \n---%s",command[i]);
							update_into('p',command[i]);
						}
						else if(rowsArray[i][j] == ')' && rowsArray[i][j+2] == 't')
						{
							//printf("\nupdate into trainers\n");
							linecount = 1;
							for(int u =1;rowsArray[i][u]!='\0';u++)
							{
								linecount++;
							}
							//printf("\n\n*****line count: %d",linecount);
							strncpy(command[i],rowsArray[i]+8,linecount-19);
							strcat(command[i],"\0");
							//printf("\n Updating into trainers \n---%s\n",command[i]);
							update_into('t',command[i]);
						}
					}
				}
				
				
				else if(rowsArray[i][0] == 'D')
				{
					delete = 1;
					for(int j = 0;rowsArray[i][j] != '\0';j++)
					{
						if(rowsArray[i][j] == ')' && rowsArray[i][j+2] == 'p')
						{
							linecount = 1;
							for(int u =1;rowsArray[i][u]!='\0';u++)
							{
								linecount++;
							}
							//printf("\nline count: %d",linecount);
							strncpy(command[i],rowsArray[i]+8,linecount-18);
							strcat(command[i],"\0");
							//printf("varun -----%s\n",command[i]);
							//printf("\ndelete into pokemons\n");
							delete_into('p',command[i]);
						}
						if(rowsArray[i][j] == ')' && rowsArray[i][j+2] == 't')
						{
							linecount = 1;
							for(int u =1;rowsArray[i][u]!='\0';u++)
							{
								linecount++;
							}
							//printf("\nline count: %d",linecount);
							strncpy(command[i],rowsArray[i]+8,linecount-19);
							strcat(command[i],"\0");
							//printf("v---%s\n",command[i]);
							delete_into('t',command[i]);
							//printf("\n delete from trainers\n");
						}
					}
				}
				else if(rowsArray[i][0] == 'S')
				{
					//printf("select");
					select = 1;
					for(int j = 0;rowsArray[i][j] != '\0';j++)
					{
						if(rowsArray[i][j] == ')' && rowsArray[i][j+2] == 'p')
						{
							linecount = 1;
							for(int u =1;rowsArray[i][u]!='\0';u++)
							{
								linecount++;
							}
							strncpy(command[i],rowsArray[i]+8,linecount-18);
							strcat(command[i],"\0");
							sel('p',command[i]);
						}
						if(rowsArray[i][j] == ')' && rowsArray[i][j+2] == 't')
						{
							linecount = 1;
							for(int u =1;rowsArray[i][u]!='\0';u++)
							{
								linecount++;
							}
							strncpy(command[i],rowsArray[i]+8,linecount-19);
							strcat(command[i],"\0");
							sel('t',command[i]);
						}
					}
				}
				else if(rowsArray[i][0] == 'W')
				{
					w();
					printf("%s\n",rowsArray[i]);
					printf("write to file\n");
				}
				else
				{
					printf("\nnothig to do\n");
				}
			}	
		}
	}
	else
	{  
		printf("Error opening the FILE!");   
	}
	fclose(fptr);
	//printf("\n------------------------------------------------------------finally displaying the records---------------------------\n");
	//printf("\t\tFinal pokemons table\n\n");
	//display_pokemon();
	//printf("\t\tFinal trainers table\n\n");
	//display_trainers();
	return 0;
}


//Modulo hash function for pokemon table
int hash1(char *a, int n)
{
	int num = atoi(a);
	int remainder;
	remainder = num%n;
	//printf("\n\n remainder is :%d\n",remainder);
	return remainder;;
}


int hash2(int n, int index)
{
	int number = index;
	int mul = 2;
	number = ((number * mul) + n);
	//printf("****\n%d\n",index);
	return number;
}


pokemon()
{
	//printf("\n\n------------Pokemon----------------------\n\n");
	FILE *fptr;
	char str[999],temp_str[999],*token,temporary[5][100];
	int count=0,temp_count = 0,p = 0,ik,k;
	int index1;
	fptr = fopen( "pokemon.txt" , "r");
	while(fscanf(fptr, "%s", temp_str)!=EOF)
		{
			temp_count++;
		}
	fclose(fptr);
	temp_count = temp_count - 2;
	int N = temp_count;
	//printf("N is %d\n",N);
	temp_count = 0;
	setP_N(N);
	/*struct pkmn
	{
		char ID[20];
		char NAME[25],TYPE[150],STRONG_TO[150],WEAK_TO[100];
	}pkmn_array[N];*///********************************************Make this a dynamic value//

//initializing the ids to 0
	for(int i = 0;i<N;i++)
	{
		strcpy(pkmn_array[i].ID,"o");
	}
	fptr = fopen( "pokemon.txt" , "r");
	
	
	if (fptr)
	{
		
		//printf("file opened");
		while (fscanf(fptr, "%s", str)!=EOF)
		{
			count++;
			ik=0;
			if(count>2)
			{
				//printf("\n%s\n\n",str);
				token = strtok(str, "|");
				while( token != NULL )
				{
					if(token != NULL)
					{
						if(ik == 0)
						{
							index1 = hash1(token, N);// call the hash1 function----------------------------
							//printf("%d\n",index1);
						}
						token = token+'\0';
						strcpy(temporary[ik],token);
						token = strtok(NULL, "|");
						ik++;
					}
				}
				if(!strcmp(pkmn_array[index1].ID,"o"))
				{
					strcpy(pkmn_array[index1].ID,temporary[0]);
					//printf("pkmn_array[%d]\tid is :%s",(index1),pkmn_array[index1].ID);
					strcpy(pkmn_array[index1].NAME,temporary[1]);
					//printf("\npkmn_array[%d]\t name is :%s\n",(index1),&pkmn_array[index1].NAME);
					strcpy(pkmn_array[index1].TYPE,temporary[2]);
					//printf("\npkmn_array[%d]\t type is :%s\n",(index1),&pkmn_array[index1].TYPE);
					strcpy(pkmn_array[index1].STRONG_TO,temporary[3]);
					//printf("\npkmn_array[%d]\t strong is :%s\n",(index1),&pkmn_array[index1].STRONG_TO);
					strcpy(pkmn_array[index1].WEAK_TO,temporary[4]);
					//printf("\npkmn_array[%d]\t weak is :%s\n",(index1),&pkmn_array[index1].WEAK_TO);
				}
				else
				{
					do
					{
						index1++;
						if(index1==N)
						{
							index1 = 0;
						}
					}while(strcmp(pkmn_array[index1].ID,"o"));
					strcpy(pkmn_array[index1].ID,temporary[0]);
					//printf("pkmn_array[%d]\tid is :%s",(index1),pkmn_array[index1].ID);
					strcpy(pkmn_array[index1].NAME,temporary[1]);
					//printf("\npkmn_array[%d]\t name is :%s\n",(index1),&pkmn_array[index1].NAME);
					strcpy(pkmn_array[index1].TYPE,temporary[2]);
					//printf("\npkmn_array[%d]\t type is :%s\n",(index1),&pkmn_array[index1].TYPE);
					strcpy(pkmn_array[index1].STRONG_TO,temporary[3]);
					//printf("\npkmn_array[%d]\t strong is :%s\n",(index1),&pkmn_array[index1].STRONG_TO);
					strcpy(pkmn_array[index1].WEAK_TO,temporary[4]);
					//printf("\npkmn_array[%d]\t weak is :%s\n",(index1),&pkmn_array[index1].WEAK_TO);
				}
			}
		}
	}
	fclose(fptr);
	printf("\npokemon table created and populated with data\n");
}
//******************************************Trainer****************************************//

trainers()
{
	//printf("\n\n------------trainers----------------------\n\n");
	FILE *fptr1;
	char str1[999],*token1,tmp1[10],temporary1[5][100],fullname[50][50];
	char *token;
	int count1=0,ij,N1,temp_count1 = 0,iter,index,y=0,as=0,ak;
	fptr1 = fopen( "trainers.txt" , "r");
	
	if(fptr1)
	{
		while(fscanf(fptr1, "%s", str1)!=EOF)
		{
			temp_count1++;
		}		
		N1 = temp_count1 - 2;
		//printf("%d\n",temp_count1);
		//printf("\nnumber of trainers: %d\n",N1);
		temp_count1 = 0;
	}
	fclose(fptr1);
	setT_N(N1);
	/*struct train
	{
		char FIRSTNAME[30],LASTNAME[50],BADGES_HELD[100],POKEMON_OWNED[500];
		char AGE[10];
	}train_array[N1];*///********************************************Make this a dynamic value//
	
	for(int i = 0;i<N1;i++)
	{
		strcpy(train_array[i].FIRSTNAME,"o");
		strcpy(train_array[i].LASTNAME,"o");
	}
	
	
	for(int i = 0;i<50;i++)
	{
		strcpy(fullname[i],"o");
	}
	
	
	
	fptr1 = fopen( "trainers.txt" , "r");
	if(fptr1)
	{
		while(fscanf(fptr1, "%s", str1)!=EOF)
		{
			count1++;
			ij = 0;
			if(count1>2)
			{
				//printf("\n%s\n",str1);
				token1 = strtok(str1, "|");
				iter++;			
				while( token1 != NULL )
				{
					if(token1 != NULL)
					{
						strcpy(temporary1[ij],token1);
						token1 = strtok(NULL, "|");
						ij++;
					}					
				}
				//printf("%s\n---",fullname[0]);
				strcpy(fullname[count1-3],temporary1[0]);
				//printf("%s\n---",fullname[count1-3]);
				strcat(fullname[count1-3],temporary1[1]);
				strcat(fullname[count1-3],"\0");
				ak = 0;
				for(y=0;fullname[count1-3][y]!='\0';y++)
				{
					as = fullname[count1-3][y];
					if(ak == 0)
					{
						index = as;
						ak++;
					}					
					else
					{
						index = hash2(as, index);
					}
					as =0;
				}
				index = index%N1;
				//printf("%d\n",index);
				if(!strcmp(train_array[index].FIRSTNAME,"o")&&!strcmp(train_array[index].LASTNAME,"o"))
				{
					strcpy(train_array[index].FIRSTNAME,temporary1[0]);
					//printf("\n\t\t train_array[%d].FIRSTNAMEis  :%s",index,train_array[index].FIRSTNAME);
					strcpy(train_array[index].LASTNAME,temporary1[1]);
					//printf("\n\t\t train_array[%d].LASTNAMEis :%s\n",index,&train_array[index].LASTNAME);
					strcpy(train_array[index].AGE,temporary1[2]);
					//printf("\n\t\t train_array[%d].AGE is :%s\n",index,&train_array[index].AGE);
					strcpy(train_array[index].BADGES_HELD,temporary1[3]);
					//printf("\n\t\t train_array[%d].BADGES_HELD are :%s\n",index,&train_array[index].BADGES_HELD);
					strcpy(train_array[index].POKEMON_OWNED,temporary1[4]);
					//printf("\n\t\t train_array[%d].POKEMON_OWNED are is :%s\n",index,&train_array[index].POKEMON_OWNED);	
				}			
				else
				{
					do
					{
						index++;
						if(index==N1)
						{
							index = 0;
						}
					}while(strcmp(train_array[index].FIRSTNAME,"o")&&strcmp(train_array[index].LASTNAME,"o"));
					strcpy(train_array[index].FIRSTNAME,temporary1[0]);
					//printf("\n\t\t train_array[%d].FIRSTNAMEis  :%s",index,train_array[index].FIRSTNAME);
					strcpy(train_array[index].LASTNAME,temporary1[1]);
					//printf("\n\t\t train_array[%d].LASTNAMEis :%s\n",index,&train_array[index].LASTNAME);
					strcpy(train_array[index].AGE,temporary1[2]);
					//printf("\n\t\t train_array[%d].AGE is :%s\n",index,&train_array[index].AGE);
					strcpy(train_array[index].BADGES_HELD,temporary1[3]);
					//printf("\n\t\t train_array[%d].BADGES_HELD are :%s\n",index,&train_array[index].BADGES_HELD);
					strcpy(train_array[index].POKEMON_OWNED,temporary1[4]);
					//printf("\n\t\t train_array[%d].POKEMON_OWNED are is :%s\n",index,&train_array[index].POKEMON_OWNED);	
				}

			}
		}
	}
	fclose(fptr1);
	printf("\ntrainers table has been created and populted\n\n");
}


void insert_into(char r,char *ins)
{
	char *tok2,split[100][100];
	int u=0,inserting=0;
	printf("%s\n",ins);
	tok2 = strtok(ins,"|");
	while( tok2 != NULL )
	{
		if(tok2 != NULL)
		{
			strcpy(split[u],tok2);
			u++;
			tok2 = strtok(NULL,"|");
		}					
	}
	if(r == 'p')
	{
		for(int y=0;y<p_N;y++)
		{
			if(strcmp(split[0],pkmn_array[y].ID)==0)
			{
				inserting = 1;
				//printf("cannot inserting the record since there is a record already existing with the id: %s \n",split[0]);
				printf("cannot insert\n");
			}
		}
	
			if(inserting == 0)
			{
				strcpy(pkmn_array[p_N].ID,split[0]);
				//printf("\n\t%s",pkmn_array[p_N+1].ID);
				strcpy(pkmn_array[p_N].NAME,split[1]);
				//printf("\t%s",pkmn_array[p_N+1].NAME);
				strcpy(pkmn_array[p_N].TYPE,split[2]);
				//printf("\t%s",pkmn_array[p_N+1].TYPE);
				strcpy(pkmn_array[p_N].STRONG_TO,split[3]);
				//printf("\t%s",pkmn_array[p_N+1].STRONG_TO);
				strcpy(pkmn_array[p_N].WEAK_TO,split[4]);
				//printf("\t%s",pkmn_array[p_N+1].WEAK_TO);
				p_N = p_N+1;
				printf("inserting into pokemons\n");
			}
	}
	else if(r == 't')
	{
		
		for(int y=0;y<t_N;y++)
		{
			if((strcmp(split[0],train_array[y].FIRSTNAME)==0) && (strcmp(split[1],train_array[y].LASTNAME)==0))
			{
				inserting = 1;
				printf("cannot inserting the record since there is a record already existing with the id: %s|%s \n",split[0],split[1]);
			}
		}
	
			if(inserting == 0)
			{
				strcpy(train_array[t_N].FIRSTNAME,split[0]);
				//printf("\n\t%s",train_array[t_N+1].FIRSTNAME);
				strcpy(train_array[t_N].LASTNAME,split[1]);
				//printf("\t%s",train_array[t_N+1].LASTNAME);
				strcpy(train_array[t_N].AGE,split[2]);
				//printf("\t%s",train_array[t_N+1].AGE);
				strcpy(train_array[t_N].BADGES_HELD,split[3]);
				//printf("\t%s",train_array[t_N+1].BADGES_HELD);
				strcpy(train_array[t_N].POKEMON_OWNED,split[4]);
				//printf("\t%s",train_array[t_N+1].POKEMON_OWNED);
				t_N = t_N+1;
				printf("inserting into trainers\n");
			}
	
	}
}

void update_into(char u, char *upd)
{
	char *tok,updated[100][100];
	int i=0,updating=0,line = 0;
	printf("%s\n",upd);
	tok = strtok(upd,"|");
	while( tok != NULL )
	{
		if(tok != NULL)
		{
			strcpy(updated[i],tok);
			i++;
			tok = strtok(NULL,"|");
		}					
	}
	if(u == 'p')
	{
		for(int y=0;y<p_N;y++)
		{
			if(strcmp(updated[0],pkmn_array[y].ID)==0)
			{
				updating = 1;
				printf("Pokemon record is being updated \n");
				line = y;
			}
		}
	
			if(updating == 1)
			{
				strcpy(pkmn_array[line].ID,updated[0]);
				//printf("\n\t%s",pkmn_array[line].ID);
				strcpy(pkmn_array[line].NAME,updated[1]);
				//printf("\t%s",pkmn_array[line].NAME);
				strcpy(pkmn_array[line].TYPE,updated[2]);
				//printf("\t%s",pkmn_array[line].TYPE);
				strcpy(pkmn_array[line].STRONG_TO,updated[3]);
				//printf("\t%s",pkmn_array[line].STRONG_TO);
				strcpy(pkmn_array[line].WEAK_TO,updated[4]);
				//printf("\t%s",pkmn_array[line].WEAK_TO);
				//p_N = p_N+1;
			}
			else
			{
				printf("\n\n record cannot be updated as the row with id : %d doesn't exit in the pokemon table\n",updated[0]);
			}
	}
	else if(u == 't')
	{
		
		for(int y=0;y<t_N;y++)
		{
			if((strcmp(updated[0],train_array[y].FIRSTNAME)==0) && (strcmp(updated[1],train_array[y].LASTNAME)==0))
			{
				updating = 1;
				printf("Trainers record is updated \n");
				line = y;
			}
		}
	
			if(updating == 1)
			{
				strcpy(train_array[line].FIRSTNAME,updated[0]);
				//printf("\n\t%s",train_array[line].FIRSTNAME);
				strcpy(train_array[line].LASTNAME,updated[1]);
				//printf("\n\t%s",train_array[line].LASTNAME);
				strcpy(train_array[line].AGE,updated[2]);
				//printf("\n\t%s",train_array[line].AGE);
				strcpy(train_array[line].BADGES_HELD,updated[3]);
				//printf("\n\t%s",train_array[line].BADGES_HELD);
				strcpy(train_array[line].POKEMON_OWNED,updated[4]);
				//printf("\n\t%s",train_array[line].POKEMON_OWNED);
				//t_N = t_N+1;
			}
			else
			{
				printf("\n\n record cannot be updated as the row with id : %d doesn't exit in the trainers table\n",updated[0]);
			}
	
	}
}

void delete_into(char u, char *del)
{
	char *tok,deleted[100][100];
	int i=0,deleting=0,line = 0;
	printf("%s\n",del);
	tok = strtok(del,"|");
	while( tok != NULL )
	{
		if(tok != NULL)
		{
			strcpy(deleted[i],tok);
			//printf("---%s",deleted[i]);
			i++;
			tok = strtok(NULL,"|");
		}					
	}
	if(u == 'p')
	{
		for(int y=0;y<p_N;y++)
		{
			if(strcmp(deleted[0],pkmn_array[y].ID)==0)
			{
				deleting = 1;
				//printf("Pokemon record is being updated \n");
				line = y;
			}
		}
	
			if(deleting == 1)
			{
				strcpy(pkmn_array[line].ID,"o");
			}
			else
			{
				printf("record cannot be deleted\n");
			}
	}
	if(u == 't')
	{
		
		for(int y=0;y<t_N;y++)
		{
			if((strcmp(deleted[0],train_array[y].FIRSTNAME)==0) && (strcmp(deleted[1],train_array[y].LASTNAME)==0))
			{
				deleting = 1;
				//printf("Trainers record is deleted \n");
				line = y;
			}
		}
	
			if(deleting == 1)
			{
				strcpy(train_array[line].FIRSTNAME,"o");
				printf("record deleted\n");
			}
			else
			{
				printf("record not found to delete\n");
			}
	
	}	
}

void sel(char u, char *sel)
{
	char *tok,selected[100][100];
	int i=0,selecting=0,line = 0;
	printf("%s\n",sel);
	tok = strtok(sel,"|");
	while( tok != NULL )
	{
		if(tok != NULL)
		{
			strcpy(selected[i],tok);
			//printf("---%s",deleted[i]);
			i++;
			tok = strtok(NULL,"|");
		}					
	}
	if(u == 'p')
	{
		for(int y=0;y<p_N;y++)
		{
			if(strcmp(selected[0],pkmn_array[y].ID)==0)
			{
				printf("\nID : %s\t",pkmn_array[y].ID);
				printf("NAME : %s\t",pkmn_array[y].NAME);
				printf("TYPE : %s\t",pkmn_array[y].TYPE);
				printf("STRONG TO : %s\t",pkmn_array[y].STRONG_TO);
				printf("WEAK TO : %s\t",pkmn_array[y].WEAK_TO);
				selecting = 1;
			}
		}	
			if(selecting == 1)
			{
				printf("\n");
				//strcpy(pkmn_array[line].ID,"o");
			}
			else
			{
				printf("record cannot be displayed\n");
			}
	}
	if(u == 't')
	{
		
		for(int y=0;y<t_N;y++)
		{
			if((strcmp(selected[0],train_array[y].FIRSTNAME)==0) && (strcmp(selected[1],train_array[y].LASTNAME)==0))
			{
				selecting = 1; 
				printf("\nFIRSTNAME :  %s\n",train_array[y].FIRSTNAME);
				printf("LASTNAME :  %s\n",train_array[y].LASTNAME);
				printf("AGE :  %s\n",train_array[y].AGE);
				printf("BADGES_HELD :  %s\n",train_array[y].BADGES_HELD);
				printf("%s",train_array[y].POKEMON_OWNED);
				//FIRSTNAME,LASTNAME,AGE,BADGES_HELD,POKEMON_OWNED
			}
		}
	
			if(selecting == 1)
			{
				printf("\n");
				
			}
			else
			{
				printf("record cannot be displayed\n");
			}
	
	}
}
void w()
{
	FILE *wr,*wr1;
	wr = fopen("pokemon_output.txt","w");
	fputs("ID\n",wr);
	fputs("ID,NAME,TYPE,STRONG_TO,WEAK_TO\n",wr);
	for(int i=0;i<p_N;i++)
	{
		if(strcmp(pkmn_array[i].ID,"o") != 0)
		{
			fputs(pkmn_array[i].ID,wr);
			fputs("|",wr);
			fputs(pkmn_array[i].NAME,wr);
			fputs("|",wr);
			fputs(pkmn_array[i].TYPE,wr);
			fputs("|",wr);
			fputs(pkmn_array[i].STRONG_TO,wr);
			fputs("|",wr);
			fputs(pkmn_array[i].WEAK_TO,wr);
			if(i<p_N-1)
			{
				fputs("\n",wr);
			}
		}
	}
	fclose(wr);
	wr1 = fopen("trainers_output.txt","w");
	fputs("FIRSTNAME,LASTNAME\n",wr);
	fputs("FIRSTNAME,LASTNAME,AGE,BADGES_HELD,POKEMON_OWNED\n",wr);
	for(int i=0;i<t_N;i++)
	{
		if(strcmp(train_array[i].FIRSTNAME,"o") != 0)
		{
			fputs(train_array[i].FIRSTNAME,wr);
			fputs("|",wr);
			fputs(train_array[i].LASTNAME,wr);
			fputs("|",wr);
			fputs(train_array[i].AGE,wr);
			fputs("|",wr);
			fputs(train_array[i].BADGES_HELD,wr);
			fputs("|",wr);
			fputs(train_array[i].POKEMON_OWNED,wr);
			if(i<t_N-1)
			{
				fputs("\n",wr);
			}
		}
	}
	fclose(wr1);
}

void display_pokemon()
{
	//if(strcmp(pkmn_array[6].ID,NULL)==0)
	//{
		//printf("---------\n");
	//}
	for(int r=0;r<p_N;r++)
	{
			
			printf("\n%s",pkmn_array[r].ID);
			
			printf("\n%s",pkmn_array[r].NAME);
			
			printf("\n%s",pkmn_array[r].TYPE);
			
			printf("\n%s",pkmn_array[r].STRONG_TO);
			
			printf("\n%s",pkmn_array[r].WEAK_TO);
		printf("\n------------------\n");
	}
}


void display_trainers()
{
	for(int r=0;r<t_N;r++)
	{
			
			printf("\n%s",train_array[r].FIRSTNAME);
			
			printf("\n%s",train_array[r].LASTNAME);
			
			printf("\n%s",train_array[r].AGE);
			
			printf("\n%s",train_array[r].BADGES_HELD);
			
			printf("\n%s",train_array[r].POKEMON_OWNED);
		printf("\n------------------\n");
	}
}