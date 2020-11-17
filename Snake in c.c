#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define N 20
#define M 40
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//loop variables
int i,j;
//areay for the game area
int Field[N][M];
//used to define the position of the snake
int x, y;
//will be discused soon****
int Gy;
//head of snake
int head;
//tail of snake
int tail;

int game;

int frogs;
//variables for the position of frog
int a, b;
//variable used to store the keyboard button that was pressed 
int key;
//variable used for continuous movement and we want the snake to move right in the begining so its value will be d
int dir;
//keep track of score
int score;
//keep track of high score
int highScore;
//open a file to get the high score
FILE *f;
//track if highScore was changed
bool changed = FALSE;
//control difficulty
int difficulty=0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//snake position at the begining of the game
void snakeInitialization(){
	//opens the highscore.txt file in read mode and prints the highscore then closes the file
	f = fopen("highscore.txt", "r");
	fscanf(f, "%d", &highScore);
	fclose(f);
	
	//sets the entire game area to 0(every position in the array is set to 0) at the start of the game
	for (i=0;i<N;i++){
		for(j=0;j<M;j++){
			Field[i][j]=0;	
		}
	}
	x = N/2;
	y = M/2;
	head = 5;
	tail = 1;
	Gy=y;
	game=0;
	frogs=0;
	dir='d';
	score=0;
//assigns  the values 1,2,3,4, and 5 to the array positions (10,16), (10,17), (10,18), (10,19), and (10,20) respectivley. this will be used to print the body of the snake at the start of the game
	for (i=0;i<head;i++){
		Gy++;
		Field[x][Gy-head] = i+1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ends the game
void gameOver(){
	//creates a beep when the player loses
	printf("\a");
	//clears the screen
	system("Cls");
	//checks if the score is greater than the high score and if so replaces the score with  the new score
	if((score > highScore) || (changed == TRUE)){
	printf("New Highscore %d!!!!!\n\n", score);
	sleep(1);
	system("Cls");
	sleep(1);
	printf("New Highscore %d!!!!!\n\n", score);
	sleep(1);
	system("Cls");
	sleep(1);
	printf("New Highscore %d!!!!!\n\n", score);
	sleep(1);
	system("Cls");
	sleep(1);
	printf("New Highscore %d!!!!!\n\n", score);
	sleep(1);
	system("Cls");
	sleep(1);
	printf("New Highscore %d!!!!!\n\n", score);
	sleep(1);
	//creates and opens a new file named highscore in write mode and stores the value of the score in that file if the score is greater than the high score then closes the file
	f = fopen("highscore.txt", "w");
	fprintf(f, "%d", score);
	fclose(f);
	sleep(2);
}
//print game over, highscore and current score
	system("Cls");
	printf("\n\n         GAME OVER");
	printf("             Score: %d\n\n", score);
	game = 1;
	sleep(3);
	system("Cls");
	
	//if the user presses enter(ascii 13)
	while (1){
		system("pause");
	system("Cls");
	printf("press 1 to play again or press 2 to quit\n");
	int option;
	scanf("%d", &option);
	if (option == 1){
		system("Cls");
		game = 0;
		gamePlay();
		break;
	}
	else if (option == 2){
		exit(0);
		break;
		}
	}
	system("Cls");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function will be used to display the game
void print(){
	//top border of game area
	for(i = 0; i <= M+1; i++){
		if(i == 0){
			printf("%c", 201);	
		}
		else if(i == M+1){
			printf("%c", 187);			
		}
		else{
			printf("%C", 205);
		}
	}
	
	
	printf("current score: %d\thighScore: %d", score, highScore);
	
	
	if (score > highScore){
	highScore=score;
	printf("     NEW HIGH SCORE");
	changed = TRUE;
}

printf("\n");
//left and right borders of game area	
	for (i = 0; i < N; i++){
		printf("%c", 186);
		for (j = 0;j < M;j++){
			if (Field[i][j]==0)printf(" ");
			//line 65 creates the snake body 
			if(Field[i][j]>0 && Field[i][j] != head)printf("%c", 176);
			//line 67 creates the snake head
			if(Field[i][j] == head)printf("%c", 178);
			//line 82 finds the position in the game area with a value of -1 and places a frog there
			if (Field[i][j] == -1) printf("%c", 15);
			if (j==M-1)	printf("%c\n", 186);
	}
}
//bottom border of game area	
	for(i = 0; i <= M+1; i++){
		if(i == 0){
			printf("%c", 200);	
		}
		else if(i == M+1){
			printf("%c", 188);			
		}
		else{
			printf("%C", 205);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//reset the console so the top left of the screen to keep the game area stablized
void resetScreenPosition(){
	//create handle to acces the console
	HANDLE hOut;
	//creat a cordinate variable
	COORD Position;
	//set the handle to the current active screen buffer(the console)
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//assign values to the x and y cordinates for the position variable
	Position.X = 0;
	Position.Y = 0;
	//set the cursor(of the active screen buffer(hOut) to the top left corner of the screen(x=0, y=0 as specified above)
	SetConsoleCursorPosition(hOut, Position);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//generate random position for the frog
randomFrog(){
	//use srand to seed the rand function and use the time funtion to add more randomness
	srand(time(0));
	//set a and b to random numbers to represent the frogs x and y postions
	a = 1 + rand() % 18;
	b = 1 + rand() % 28;
	//if there are no frogs in the game area and the postion in question is empty, set that position value to negative one and add 1 to frogs
	//this is to prevent multiple frogs appearing on screen and to ensure that a frog will not appaer on top of the snake
	if (frogs == 0 && Field[a][b] == 0){
		Field[a][b] = -1;
		frogs = 1;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//returns the asciii value of the button pressed on the keyboard but does not print the key 
int getch_noblock(){
	//if a key is hit
	if(_kbhit())
	//return the key that was pressed
		return _getch();	
	else
		return -1;	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//moves the snake 
void movement(){
	//calls the getch_noblock function to obtain the key pressed 
	key = getch_noblock();
	//changes the casing to lower case
	key = tolower(key);
	
	//the first half of this loop ensures that a valid key was pressed
	//the second half is used to prevent the user from moving the snake back into its self
	//ascii values - d = 100, a = 97, w = 119, s = 115
	//the difference between d and a is 3 so the program won't allow that movement,
	//while the the difference between w and d is 19 so the program will allow that change in direction
	if (((key == 'd' || key == 'a')|| (key == 'w' || key == 's')) && (abs(dir-key)>5))
		dir=key;
	//moves the snake head right id the d key is presses
	if (dir == 'd'){
		y++;
		if(Field[x][y] != 0 && Field[x][y] != -1 ){
			gameOver();
		}
		//if the snake reaches the right border it will return on the left border
		if (y==M-1)y=0;
		//checks if there is a frog in the position and sets frogs to 0 to cause the randomfrog function to create a new frog, increase the snake tail, and increase the score by 5
		if (Field[x][y] == -1){
			frogs = 0;
			score += 5;
			tail-= 2;
			MessageBeep(MB_ICONWARNING);
		}
		head++;
		Field[x][y] = head;
	}	
	//moves the snake head left if a is pressed
	if (dir == 'a'){
		y--;
		if(Field[x][y] != 0 && Field[x][y] != -1 ){
			gameOver();
		}
		//if the snake reaches the left border it will return on the left border
		if (y==0)y=M-1;
		if (Field[x][y] == -1){
			frogs = 0;
			score += 5;
			tail-= 2;
			MessageBeep(MB_ICONWARNING);
		}
		head++;
		Field[x][y] = head;
	}	
	//moves the snake head up if w is pressed 
	if (dir == 'w'){
		x--;
		if(Field[x][y] != 0 && Field[x][y] != -1 ){
			gameOver();
		}
		//if the snake reaches the top border it will return from the bottom
		if (x==-1) x=N-1;
		if (Field[x][y] == -1){
			frogs = 0;
			score += 5;
			tail-= 2;
			MessageBeep(MB_ICONWARNING);
		}
		head++;
		Field[x][y] = head;
	}	
	//moves the snake head down if s is pressed
	if (dir == 's'){
		x++;
 		if(Field[x][y] != 0 && Field[x][y] != -1 ){
			gameOver();
		}
		//if the snake reaches the bottom border it will return from the top
		if (x==N-1)x= 0;
		if (Field[x][y] == -1){
			frogs = 0;
			score += 5;
			tail-= 2;
			MessageBeep(MB_ICONWARNING);
		}
		head++;
		Field[x][y] = head;
	}	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tailRemote(){
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if (Field[i][j] == tail)
				Field[i][j] = 0;

		}
	}
	tail++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//used to hide the cursor
void hideCursor()
{
	//creates a handle to control the active screen buffer
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   //create a variable to hold cursor information
   CONSOLE_CURSOR_INFO info;
   //set cursor size to 100(values typically allowed are 1-100)
   info.dwSize = 100;
   //set the cursor to be invisible
   info.bVisible = FALSE;
   //send the information to the active screen buffer
   SetConsoleCursorInfo(consoleHandle, &info);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gamePlay(){

	snakeInitialization();
	while(game == 0){
		print();
		resetScreenPosition();
		randomFrog();
		movement();
		tailRemote();
		hideCursor();
		usleep(difficulty);
	 }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int menue(ready){
int i = 1;
	while(i == 1){
      printf("S");
      sleep(1);
      printf("N");
      sleep(1);
	  printf("A");
	  sleep(1);
	  printf("K");
	  sleep(1);
	  printf("E");
	  i++;
    }
    sleep(1);
    system("Cls");
    usleep(500);
    
    printf("press E to play ore Q to exit\n");
	char choice;
	scanf("%c", &choice);
  	choice = tolower(choice);
  	
    if (choice == 101){
    	system("Cls");
    	int choice2;
		printf("Select difficulty\n1:Hard\n2:Normal\n3:Easy\n");
		scanf("%d", &choice2);
		if (choice2 == 1){
			difficulty = 1000;
			ready = 1;
		}
		else if (choice2 == 2){
			difficulty = 10000;
			ready = 1;
		}
		else if (choice2 == 3){
			difficulty = 100000;
			ready = 1;
		}
	}
	else
	ready = 0;
	
	return ready;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main() {
	system("COLOR B0");
	COORD coord;
    coord.X = 20;
    coord.Y = 40;

    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = 21;
    Rect.Right = 110;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            //set window size
	
	
int play = 0;
play = menue(play);
if (play == 1){
	printf("CONTROLS:\tW:Up\tS:Down\tA:Left\tD:Right\n");
	printf("RULES:          1.)Catch the frogs %c to increase your score\n\t\t2.)DONT run into yourself", 15);
	sleep(5);
	system("Cls");
	printf("ready ");
	sleep(1);
	printf("set ");
	sleep(1);
	printf("go");
	system("Cls");
	gamePlay();
}
else
	exit(0);
}

