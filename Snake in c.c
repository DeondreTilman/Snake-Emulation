/************************************************************************************
SNAKE recreation                                                                    *
Written by deondre tilman
inpiration taken from Sanzal on youtube                                             *
************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////LIBRAIRIES////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////CONSTANTS//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define N 20
#define M 40
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////VARIABLES//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//loop variables
int i,j;
//areay for the game play area
int Field[N][M];
//used to define the position "cordinates" of the snake
int x, y;
//a place holder used to initalize the snake
int Gy;
//head of snake
int head;
//tail of snake
int tail;
//used for the game loop
int game;
//used for the frogs in the game
int frogs;
//variables for the position of frog
int a, b;
//variable used to store the keyboard button that was pressed 
int key;
//variable used for continuous movement and we want the snake to move right in the begining so its value will be 'd'
int dir;
//keep track of score
int score;
//keep track of high score in the leaderboard
int highScore1, highScore2, highScore3;
//Declare files pointers to get the high score, and leaderboard names from their respective files
FILE *s, *n;
//track if highScore was changed
bool changed = FALSE;
//control difficulty(speed of game)
int difficulty=0, remain;
//declare a string for the users names for the leaderboard
char name[3], name2[3], name3[3];
//keep track of if the highscore color change screen has already been ran
int ran;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////SNAKEINITIALIZATION FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//snake position at the begining of the game
void snakeInitialization(){
	//opens the highscore.txt file in read mode and prints the highscore then closes the file
	s = fopen("highscore.txt", "r");
	fscanf(s, "%d", &highScore1);
	fclose(s);
	
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////GAMEOVER FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ends the game
void gameOver(){
	remain = difficulty;
	difficulty = 10;
	//creates a beep when the player loses and changes the color
	printf("\a");
	system("COLOR 0F");
	system("Cls");
	//a variable for the upprcase loop
	int ii = 0;
	
//////////////preREADING NAMES//////////////////
	n = fopen("Leaderboard.txt", "r");
	fscanf(n, "%s\n%s\n%s", &name, &name2, &name3);
	fclose(n);
 ////////////preREADING SCORES/////////////////
 	s = fopen("highscore.txt", "r");
	fscanf(s, "%d\n%d\n%d", &highScore1, &highScore2, &highScore3);
	fclose(s);

	//checks if the score is greater than the high score and if so replaces the score with  the new score
	if((score > highScore1) || (changed == TRUE)){
		int hs = 0;
		while(hs<14){
		printf("New High Score %d!!!!!\n\n", score);
		system("COLOR 09");
		system("COLOR 0A");
		system("COLOR 0D");
  		system("Cls");
  		usleep(5000);
		hs++;
		}
		system("COLOR 0F");
		//creates and/or opens a file named highscore in write mode and stores the value of the score in that file. then closes
		s = fopen("highscore.txt", "w");
		fprintf(s, "%d\n%d\n%d", score, highScore2, highScore3);
		fclose(s);
		printf("Enter your three initials\n");
		scanf("%s", name);
		for (ii = 0; ii <= 4; ii++) {                                              //loop to turn lowercase into uppercase due to the differnce in lowercase to uppercase being 32
      		if(name[ii] >= 97 && name[ii] <= 122) {
         		name[ii] = name[ii] -32;
      		}
   		}
		n = fopen("Leaderboard.txt", "w");
		fprintf(n, "%s\n%s\n%s", name, name2, name3);
		fclose(n);
	}
	//same thing for the second high score
	else if (score > highScore2){
		s = fopen("highscore.txt", "w");
			fprintf(s, "%d\n%d\n%d", highScore1, score, highScore3);
			fclose(s);
		printf("You beat the second highest score");
		sleep(1);
		system("Cls");
		printf("Enter your three initials\n");
		scanf("%s", name2);
		for (ii = 0; ii <= 4; ii++) {
      		if(name2[ii] >= 97 && name2[ii] <= 122) {
         		name2[ii] = name2[ii] -32;
      		}
   		}
		n = fopen("Leaderboard.txt", "w");
		fprintf(n, "%s\n%s\n%s", name, name2, name3);
		fclose(n);
	}
	//same thing for the third high score
	else if (score > highScore3){
		s = fopen("highscore.txt", "w");
		fprintf(s, "%d\n%d\n%d", highScore1, highScore2, score);
		fclose(s);
		printf("You beat the third highhest score");
		sleep(1);
		system("Cls");
		printf("Enter your three initials\n");
		scanf("%s", name3);
		for (ii = 0; ii <= 4; ii++) {
      		if(name3[ii] >= 97 && name3[ii] <= 122) {
         		name3[ii] = name3[ii] - 32;
      		}
   		}
		n = fopen("Leaderboard.txt", "w");
		fprintf(n, "%s\n%s\n%s", name, name2, name3);
		fclose(n);
	}
	
//////////////READING NAMES//////////////////
//place the names into their variables
	n = fopen("Leaderboard.txt", "r");
	fscanf(n, "%s\n%s\n%s", &name, &name2, &name3);
	fclose(n);
 ////////////READING SCORES/////////////////
 //place the scores into their respective variables
 	s = fopen("highscore.txt", "r");
	fscanf(s, "%d\n%d\n%d", &highScore1, &highScore2, &highScore3);
	fclose(s);
	
//print game over, highscore and current score
	system("Cls");
	printf("\n\n         GAME OVER");
	printf("             Score: %d\n\n", score);
	printf("\t\t   LEADERBOARD\n\t\t   1.%s: %d\n\t\t   2.%s: %d\n\t\t   3.%s: %d", name, highScore1, name2, highScore2, name3, highScore3);
	game = 1;
	sleep(5);
	system("Cls");
	//give the user the option to quit or restart
	while (1){
		system("pause");
	system("Cls");
	printf("press 1 to play again or press 2 to quit then press Enter\n");
	int option;
	scanf("%d", &option);
	if (option == 1){
		system("Cls");
		game = 0;
		difficulty = remain;
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////PRINT FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function will be used to display the game
void print(){
	//creates the top border of game area
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
	
	//prints the current score and the high score
	printf("current score: %d\thighScore: %d", score, highScore1);
	
	//if the current score is greater than the high score play a color change screen and change the high score to the current score
	if (score > highScore1){
	highScore1=score;
	printf("       NEW HIGH SCORE");
	int now = 0;
	if (ran == 0){
		while(now<=3){
			system("COLOR 24");
			system("COLOR 96");
			system("COLOR 57");
			system("COLOR 0F");
			system("COLOR 32");
			++now;
			ran = 1;
		}
	}
	changed = TRUE;//if this is changed the the new high score screen will still show
}

printf("\n");
//creates the left and right borders of game area
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
//creates the bottom border of game area
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RESETSCREENPOSITON FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	//set the cursor(of the active screen buffer(hOut)) to the top left corner of the screen(x=0, y=0 as specified above)
	SetConsoleCursorPosition(hOut, Position);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RANDOMFROG FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////CONTINOUS FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//returns the asciii value of the button pressed on the keyboard but does not print the key 
int getch_noblock(){
	//if a key is hit
	if(_kbhit())
	//return the key that was pressed
		return _getch();	
	else
		return -1;	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////MOVEMENT FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//moves the snake 
void movement(){
	//calls the getch_noblock function to obtain the key pressed 
	key = getch_noblock();
	//changes the casing to lower case
	key = tolower(key);
	
	//the first half of this if statement ensures that a valid key was pressed
	//the second half is used to prevent the user from moving the snake back into its self
	//ascii values - d = 100, a = 97, w = 119, s = 115
	//the difference between d and a is 3 so the program won't allow that movement,
	// the the difference between w and d is 19 so the program will allow that change in direction
	if (((key == 'd' || key == 'a')|| (key == 'w' || key == 's')) && (abs(dir-key)>5))
		dir=key;
	//moves the snake head right if the d key is presses
	if (dir == 'd'){
		y++;
		//if the snake is not at an empty space and the snake is not at a frog then the snake must be on itself and the game is over
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
			//plays a sound whent he frog is eaten
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
		//if the snake reaches the left border it will return on the right border
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
		//if the nake head is at the frog increase the score and delete the frog, and increase the length of the tail
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
	//if p is pressed the game is paused
	while (key == 'p'){
		system("Cls");
		//displays the paused screen and promps the user for input on wheather or not they want to quit or continue
		printf("\t\t\t\t\tPAUSED\t\t\n Press Q to quit then press enter or press any button and press enter to continue playing\n");
		scanf("%c", &key);
  		key = tolower(key);
		if (key == 'q'){
			system("Cls");
			printf("\t\tsorry to see you go");
			sleep(1);
			gameOver();
		}
		else{
 	 	system("Cls");
 	 	key = 'd';
 	    }
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////TAILREMOTE FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tailRemote(){
	//this will simultaneously increase the value of the tail whic is the last character of the snake and then set that place value to zero as the snake moves
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if (Field[i][j] == tail)
				Field[i][j] = 0;

		}
	}
	tail++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////HIDECURSOR FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////GAMEPLAY FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gamePlay(){
//this funtion is the game loop that calls all the funtions
	snakeInitialization();
	while(game == 0){
		//24 is the color code for green and red
		system("COLOR 24");
		print();
		resetScreenPosition();
		randomFrog();
		movement();
		tailRemote();
		hideCursor();
		//the sleep controls the speed at which the loop will run and the speed depends on the chosen difficulty
		usleep(difficulty);
	 }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////MENUE FUCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int menue(ready){
int i = 1;
//prints the snake start up screen
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
    //prompts the user to play
    printf("press E to play ore Q to exit then press Enter\n");
	char choice;
	scanf("%c", &choice);
  	choice = tolower(choice);
  	//if the uses presses e to enter then they will be asked for what difficulty they would like to play in
    if (choice == 101){
    	system("Cls");
    	int choice2;
		printf("Select difficulty Then press Enter\n1:Hard\n2:Normal\n3:Easy\n");
		scanf("%d", &choice2);
		if (choice2 == 1){
			difficulty = 10;
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////MAIN FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main() {
	system("COLOR B0");
	//creates a cordinate variable and initializes the x and y positions. this will control how much scrool room there is
	COORD coord;
    coord.X = 300;
    coord.Y = 120;
//this creates a rectangle variable and the cordinats of the positions are initalized
    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = 21;
    Rect.Right = 110;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Gets a Handle on the active console
    SetConsoleScreenBufferSize(Handle, coord);           // Sets the console(buffer) size to the COORD cordinates
    SetConsoleWindowInfo(Handle, TRUE, &Rect);          //set window size to the size of the rect
	
	
int play = 0;
play = menue(play);
if (play == 1){
	system("Cls");
	//prints the rules of the game and the controls then does the ready set go screen and then calls the game loop
	printf("CONTROLS:\nW: Up\nS: Down\nA: Left\nD: Right\nP: Pause\nQ: Quit\n\n\n");
	printf("RULES:\n1.)Catch the frogs %c to increase your score\n\n2.)DONT run into yourself", 15);
	sleep(7);
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

