#include <stdio.h>
#include <stdlib.h> //to change color of cmd
#include <time.h> //to add time to each todo
#include <string.h> //for string functions
#include <conio.h> //for getch
#include<windows.h> //for beeping sound

struct ToDo {
	char str[200];
	char time_str[50];
	int count;
} todo[200], priv_todo[200];

void splashScreen();

char compareArray(char arr1[], char arr2[]);

int inPrivate(int p);

int addToDo(int *i);

int deleteToDo(int *i);

int updateToDo(int i);

void viewToDo(int limit);

int beeping();

// GLOBAL VARIABLES
int screen_check = 0;
static int count_main = 0;
static int count_priv = 0;
int p_check = 1;
char passS[6];

int main() {
	int a;
	
	if (screen_check == 0) {
		splashScreen();
		passS[0] = ' ';
	}
	screen_check = 0;
	beeping();
	while(1) {
		system("Color 4E");
		system("cls");
		printf("\tWelcome to the ToDo List Application! ");
		printf("What would you like to do?\n\n");		
		printf("1. Add a ToDo\n2. Delete a ToDo\n3. Update a ToDo \n4. View your ToDo List\n5. Go to InPrivate ToDo Mode\n6. Exit\n   ");
		scanf("%d", &a);
		beeping();
		
		switch(a) {
			case 1:
				addToDo(&count_main);
				break;
			case 2:
				deleteToDo(&count_main);
				break;
			case 3:
				updateToDo(count_main);
				break;
			case 4:
				viewToDo(count_main);
				break;
			case 5:
				inPrivate(count_priv);
				break;
			case 6:
				exit(1);
			default:
				printf("\a Invalid input! Please enter a number from the given choices!\n\n");
				getch();
		}
	}
}

int inPrivate(int p) {
	system("Color 0A");
	int a;
	screen_check = 1; // check to know we're in Private mode
    char passL[6]; // array to store password (S for signup, L for login)
    p_check = 0;
    
    int i = 0, j = 0, num = 0, cap = 0, small = 0; // variables to check username & password
    
    while(1) {
    	if(passS[0] == ' ') {
    		system("cls");
    		printf("First time user - CREATE A PASSWORD\nSIGN UP \n");
    		printf("\nPlease Enter Password:\n");
    		fflush(stdin);
		    char ch;
			int pos=0;
			while(1){
				ch=getch();
				if(ch==13){ //enter value in ascii
					break;
				}
				else if(ch==8){//backspace
					printf("\b \b");
					pos--;
					passS[pos]='\0';	
				}
				else if(ch==32 || ch==9){//space or tab
					continue;
				}
				else{
					if(pos<15){
						passS[pos]=ch;
						pos++;
						printf("*");
					}
					else{
						printf("\nPassword can only contain lesser or equal to 15 characters.");
						break;
					}
				}		
			}
			passS[pos]='\0';
		    
	//	    CHECKING PASSWORD:
		        
		    while (passS[i] != '\0') {
		        if(passS[i] >= 48 && passS[i] <= 57) {
		        	num++;
				}
				if(passS[i] >= 65 && passS[i] <= 90) {
		        	cap++;
				}
				if(passS[i] >= 97 && passS[i] <= 122) {
		        	small++;
				}
		        i++;
		    }
		    if(num >= 1 && cap >= 1 && small >= 1 && i == 6) {
		    	p_check = 1;
		    	printf("\nPassword created successfully! Enter any key to access InPrivate ToDo menu... ");
		    	getch();
			} else {
				printf("\a\nPassword must contain six characters, at least 1 numeric, 1 capital and 1 small letter.\n");
				system("pause");
				num = 0, cap = 0, small = 0, i = 0, passS[0] = ' ';
				continue;
			}
		} else if(p_check == 0) {
			system("cls");
			while(1) {
				printf("Before entering the InPrivate ToDo menu, kindly enter the password you created\nLOGIN\n");
			    printf("\nPlease Enter Password:\n");
			    fflush(stdin);
		    	char ch;
				int pos=0;
				while(1){
					ch=getch();
					if(ch==13){ //enter value in ascii
						break;
					}
					else if(ch==8){//backspace
						printf("\b \b");
						pos--;
						passL[pos]='\0';	
					}
					else if(ch==32 || ch==9){//space or tab
						continue;
					}
					else{
						if(pos<15){
							passL[pos]=ch;
							pos++;
							printf("*");
						}
						else{
							printf("\nPassword can only contain lesser or equal to 15 characters.");
							break;
						}
					}		
				}
				passL[pos]='\0';	
			    
			    int checkpass = 0;
			    checkpass = (compareArray(passS, passL));
			    
			    if(checkpass == 0) {
			    	printf("Password is correct! Press any key to enter InPrivate Menu...");
			    	getch;
			    	break;
				} else {
					printf("\a\nPassword is not correct, try again!\n");
					continue;
				}
			}
		}

    	system("cls");
		printf("\tYOU ARE NOW BROWSING THE PRIVATE TODO LIST MENU - ");
		printf("What would you like to do?\n\n");	
		printf("1. Add a ToDo\n2. Delete a ToDo\n3. Update a ToDo \n4. View your ToDo List\n5. Go to Main Menu\n6. Exit\n   ");
		scanf("%d", &a);
		beeping();
		
		switch(a) {
			case 1:
				addToDo(&count_priv);
				break;
			case 2:
				deleteToDo(&count_priv);
				break;
			case 3:
				updateToDo(count_priv);
				break;
			case 4:
				viewToDo(count_priv);
				break;
			case 5:
				main();
				break;
			case 6:
				exit(1);
				beeping();
			default:
				printf("\aInvalid input! Please enter a number from the given choices!\n\n");
				getch();
		}
	}
}

char compareArray(char arr1[], char arr2[]) {
	int s = 0;
	while (arr1[s] != '\0') {
        if(arr1[s] != arr2[s]) {
        	return 1;
        	break;
		}
		s++;
	}
}

int addToDo (int *i) {
	char input[200];
	system("cls");
	if (screen_check == 1) {
		system("Color 0A");
		p_check = 1;
		printf("Enter the ToDo you want to add: \n   ");
		fflush(stdin);
		gets(input);
		beeping();
		
		//ADDING TODO TO ARRAY
		strcpy(priv_todo[*i].str, input);
		
		time_t t;
	    time(&t);
	    
	    //ADDING TIME TO ARRAY
	    strcpy(priv_todo[*i].time_str, ctime(&t));
	    
	    //ADDING COUNT 
	    priv_todo[*i].count = (*i)+1;
		(*i)++;
		
	} else {
		system("Color 3F");
		printf("Enter the ToDo you want to add: \n   ");
		fflush(stdin);
		gets(input);
		beeping();
		
		//ADDING TODO TO ARRAY
		strcpy(todo[*i].str, input);
		
		time_t t;
	    time(&t);
	    
	    //ADDING TIME TO ARRAY
	    strcpy(todo[*i].time_str, ctime(&t));
	    
	    //ADDING COUNT 
	    todo[*i].count = (*i)+1;
		(*i)++;
	}
	
	
    
    printf("\n\nTodo Added! Enter any key to go back...\n");  
   	getch();
}

int deleteToDo(int *i) {
	if (screen_check == 1) {
		system("Color 0A");
		p_check = 1;
	} else {
		system("Color 2F");
	}
	system("cls");
	int n, j;
	if(*i) {
		printf("Your ToDo list: \n");
		for(j = 0; j < *i; j++) {
			if (screen_check == 1) {
				printf("%d.)  ", priv_todo[j].count);
				printf("%s\n", priv_todo[j].str);
			} else {
				printf("%d.)  ", todo[j].count);
				printf("%s\n", todo[j].str);
			}
		}
		printf("\nEnter the ToDo number you want to delete: ");
		scanf("%d", &n);

		for(j = 0; j < *i; j++) {
			if (screen_check == 1) {
				if(n == priv_todo[j].count) {
					beeping();
					if(n == priv_todo[(*i-1)].count) {
						(*i)--;
						j--;
						printf("\n\nToDo deleted! ");
						break;
					}
					for(int c = n-1; c < (*i)-1; c++) {
						strcpy(priv_todo[c].str, priv_todo[c+1].str);
						strcpy(priv_todo[c].time_str, priv_todo[c+1].time_str);
						priv_todo[c].count = priv_todo[c+1].count;
						(*i)--;
					}
					for(int c = 0; c < *i; c++) {
						priv_todo[c].count = (c+1);
					}
					printf("\n\nToDo deleted! ");
					break;
				}
			} else {
				if(n == todo[j].count) {
					beeping();
					if(n == todo[(*i-1)].count) {
						(*i)--;
						j--;
						printf("\n\nToDo deleted! ");
						break;
					}
					for(int c = n-1; c < (*i)-1; c++) {
						strcpy(todo[c].str, todo[c+1].str);
						strcpy(todo[c].time_str, todo[c+1].time_str);
						todo[c].count = todo[c+1].count;
						(*i)--;
					}
					for(int c = 0; c < *i; c++) {
						todo[c].count = (c+1);
					}
					printf("\n\nToDo deleted! ");
					break;
				}
			}
		}
		if(j == *i) {
			printf("\aThe ToDo number you entered does not exist!\n\n");
		}
	} else {
		printf("\n\nToDo list is empty, add ToDos first then you can delete them!\n\n");
	}
	printf("Enter any key to go back...\n");
   	getch();
}

int updateToDo(int i) {
	if (screen_check == 1) {
		system("Color 0A");
		p_check = 1;
	} else {
		system("Color 7C");
	}
	system("cls");
	int n, j;
	char input[200];
	if(i) {
		printf("Your ToDo list: \n");
		for(j = 0; j < i; j++) {
			if (screen_check == 1) {
				printf("%d.)  ", priv_todo[j].count);
				printf("%s\n", priv_todo[j].str);
			} else {
				printf("%d.)  ", todo[j].count);
				printf("%s\n", todo[j].str);
			}
		}
		printf("\nEnter the ToDo number you want to update: ");
		scanf("%d", &n);
		for(j = 0; j < i; j++) {
			if (screen_check == 1) {
				if(n == priv_todo[j].count) {
					printf("Enter the ToDo you want to add: \n   ");
					fflush(stdin);
					gets(input);
					beeping();
					strcpy(priv_todo[j].str, input);
					
					time_t t;
	    			time(&t);
				    strcpy(priv_todo[j].time_str, ctime(&t));
					break;
				}
			} else {
				if(n == todo[j].count) {
					printf("Enter the ToDo you want to add: \n   ");
					fflush(stdin);
					gets(input);
					beeping();
					strcpy(todo[j].str, input);
					
					time_t t;
	    			time(&t);
				    strcpy(todo[j].time_str, ctime(&t));
					break;
				}
			}
		}
		if(j == i) {
			printf("\aThe ToDo number you entered does not exist!");
		}
	} else {
		printf("ToDo list is empty, add ToDos first then you can update them!");
	}
	
	printf("\n\nEnter any key to go back...\n");  
   	getch();
}

void viewToDo(int limit) {
	if (screen_check == 1) {
		system("Color 0A");
		p_check = 1;
	} else {
		system("Color 5F");
	}
	system("cls");
	if(limit) {
		printf("Your ToDo list: \n");
		for(int j = 0; j < limit; j++) {
			if (screen_check == 1) {
				printf("%d.)  ", priv_todo[j].count);
				printf("%s\t\t", priv_todo[j].str);
				printf("%s\n", priv_todo[j].time_str);
			} else {
				printf("%d.)  ", todo[j].count);
				printf("%s\t\t", todo[j].str);
				printf("%s\n", todo[j].time_str);
			}
		}
	} else {
		printf("ToDo list is empty! Enter ToDos to first then view them!");
	}
	
	printf("\n\nEnter any key to go back...\n");  
   	getch();
}

void splashScreen() {
	system("Color 2F");
	printf("\n");
	printf("\t\f   *********   *********        *********      *********\n");
	printf("\t|        *      *       *        *        *     *       *\n");
	printf("\t|        *      *  ***  *   ***  *   ***   *    *  ***  *\n");
	printf("\t|        *      *  ***  *   ***  *   ***    *   *  ***  *\n");
	printf("\t|        *      *       *        *         *    *       *\n");
	printf("\t|        *      *********        **********     *********");
	printf("\n\t__________________________________________________________\n");
	printf("\t                                                             *         *    ********  *********** |\n");
	printf("\t     ^      ^                                                *         *    *              *      |\n");
	printf("\t     0      0                                                *         *    *              *      |\n");
	printf("\t         7             A Project By                          *         *    ********       *      |\n");
	printf("\t      (____)                ~Team SHUT~                      *         *           *       *      |\n");
	printf("\t                                                             *         *           *       *      |\n");
	printf("\t                                                             *******   *    ********       *      \f\n");
	printf("\n\t                                                         __________________________________________");
	printf("\n\n\n\n\t\t\t");  
   	system("pause");
}
int beeping(){
	Beep(555,300);
}
