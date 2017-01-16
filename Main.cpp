#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include "time.h" // needed to use time functions
#include "stdlib.h" // needed to use rand function
#include <string>
#include <Windows.h>

using namespace std;

//const int for array size cant be changed
const int char_array_size = 20;
//array to hold the users name
char playerName[char_array_size];

int playerChoice = 0;

//health variables
int playerHealth = 100;
int enemyHealth = 100;

//attack hitpoint variables
int normalAttackHitpoints_plr = 10;
int normalAttackHitpoints_enmy = 10;
int heavyAttackHitpoints_plr = 20;
int heavyAttackHitpoints_enmy = 20;
int defendHealthPoints = 5;

//variables used to increase or decrease player or enemy chance of hitting
int playerPenalty = 0;
int enemyPenalty = 0;

//variable to store random number thats generated
int randNumber;

bool isCounterAttackPlayed = false;
bool isPlayerAmuletUsed = false;
bool isEnemyAmuletUsed = false;

//Function initialisers
void startGame();

void playerAttack();
void enemyAttack();

void options1();
void options2();

void genRandomNumber();

void playerNormalAttack();
void enemyNormalAttack();

void playerHeavyAttack();
void enemyHeavyAttack();

void playerCounterAttack();
void enemyCounterAttack();

void playerDefend();
void enemyDefend();

void useAmulet();
void playerAmulet();



int main()
{
	srand(time(NULL)); // 'seeds' random number generator with current time

	//call start game function
	startGame();
	printf("*********  FIGHT  *********\n\n\n");

	bool isDone = false;

	//Game loop. ends when isDone == true
	while (isDone == false)
	{
		//call player attack function
		playerAttack();

		
		enemyAttack();
		if (enemyHealth <= 0)
		{
			isDone = true; //ends the game loop
		}
		if (playerHealth <= 0)
		{
			isDone = true; //ends the game loop
		}

		printf("\n\nPress enter to Continue\n");
		
		_getch();   // waits for user input
	}

	system("CLS");

	if (enemyHealth <= 0)
	{
		printf("\n\n%s has defeated the monster", playerName);
	}

	if (playerHealth <= 0)
	{
		printf("\n\nYou have been defeated\n");
	}

	
	printf("\n\nPress Enter to quit");
	//Waits for user to input a character
	_getch();
	//Closes the program
	return 0;
}

void startGame()
{

	printf("Enter Your Name: ");
	//stores users input into array
	fgets(playerName, char_array_size, stdin);

	//prints the player name and health on screen
	printf("%s has %d health\n", playerName, playerHealth);
	printf("Monster has %d health\n\n", enemyHealth);

}


//function to get user input for attack
void playerAttack()
{

	options1();

	scanf_s("%d", &playerChoice);

	//checks users input against each of the cases
	switch (playerChoice)
	{
	case 1:
		printf("\n\n\n\n\n\n%s chose Normal Attack!!\n\n", playerName);
		playerNormalAttack();
		break;
	case 2:
		printf("\n\n\n\n\n\n%s chose Heavy Attack!!\n\n", playerName);
		playerHeavyAttack();
		break;
		case 3:
			if (isCounterAttackPlayed == true)
			{
				printf("Enemy is using counter attack choose another option");
				return playerAttack();
			}
			else
			{
				printf("You chose Counter Attack!!\n\n");
				printf("Enemy chance of hitting reduced by 20% \n\n");
				isCounterAttackPlayed = true;
				enemyPenalty = 20;
			}
		
		break;
	case 4:
		printf("\n\n\n\n\n\n%s chose to defend", playerName);
		playerDefend();
		break;
	case 5:
		if (isPlayerAmuletUsed == true)
		{
			printf("Amulet already used!!\n\n");
		}
		else
		{
			printf("You used your Amulet!");
			playerAmulet();
		}
	//if wrong number typed in invalid input is shown and they choose again
	default:
		printf("Invalid Choice!");
		//restarts the function
		return playerAttack();
		break;


	}

	printf("\nEnemy health is %d\n\n", enemyHealth);
}

void enemyAttack()
{

	//random number can only be between 0 and 4
	int randNum = 4;
	int enemyAttack = (rand() % randNum); // generates random integer between 0 and 4;

	//checks random number against each of the cases
	switch (enemyAttack)
	{
	case 0:
		printf("\n\nEnemy used normal attack\n\n");
		enemyNormalAttack();
		break;
	case 1:
		printf("\n\nEnemy Used Heavy attack!\n\n");
		enemyHeavyAttack();
		break;
	case 2:
		if (isCounterAttackPlayed == true)
		{
			printf("Player is using counter attack choose another option");
			enemyNormalAttack();
		}
		else
		{
			printf("Enemy chose Counter Attack!!\n\n");
			printf("Enemy chance of hitting reduced by 20%\n\n");
			isCounterAttackPlayed = true;
			playerPenalty = 20;
		}
		break;
	case 3:
		printf("Enemy Chose to Defend\n");
		enemyDefend();
	}
	printf("\n\nPlayer health is %d\n\n", playerHealth);



}

//user options
void options1()
{
	printf("\n\nChoose Your Attack\n");
	printf("1. Normal Attack deals 10 damage\n");
	printf("2. Heavy Attack deals 20 damage\n");
	printf("3. Counter Attack deals 6 damage and reduces enemy attack chance by 20%\n");
	printf("4. Defend increases health by 5\n");
	printf("5. Use amulet: increase damage by 1.5 times ONE TIME USE\n\n");
}

//user options for when amulet is used
void options2()
{
	printf("\n\nChoose Your Attack\n");
	printf("1. Normal Attack deals 10 damage\n");
	printf("2. Heavy Attack deals 20 damage\n");
	printf("3. Counter Attack deals 6 damage and reduces enemy attack chance by 20%\n");
	printf("4. Defend increases health by 5\n");
	printf("5. USED!!! ------ Use amulet: increase damage by 1.5 times\n");
}

//generates random number between 1 and 100 
//used for percentage hit chance
void genRandomNumber()
{
	int max = 100;
	randNumber = (rand() % max) + 1;
}

//players normal attack 80% chance of hitting
void playerNormalAttack()
{
	genRandomNumber();
	//attack will hit if random number is higher than 20
	if (randNumber >= 20 + playerPenalty)
	{
		enemyHealth -= normalAttackHitpoints_plr;
	}
	else if (randNumber < 20 + playerPenalty)
	{
		printf("Attack missed!!\n\n");
		if (isCounterAttackPlayed == true)
		{
			enemyCounterAttack();
		}
		isCounterAttackPlayed = false;
	}
	playerPenalty = 0;
	normalAttackHitpoints_plr = 10;

}

//enemy normal attack 80% chance of hitting
void enemyNormalAttack()
{
	genRandomNumber();
	if (randNumber >= 20 + enemyPenalty)
	{
		playerHealth -= normalAttackHitpoints_enmy;
	}
	else if (randNumber < 20 + enemyPenalty)
	{
		printf("\nEnemy Attack missed!!\n");
		if (isCounterAttackPlayed == true)
		{
			playerCounterAttack();
		}
		isCounterAttackPlayed = false;
	}
	enemyPenalty = 0;
	normalAttackHitpoints_enmy = 10;
}

//player heavy attack 50% chance of hitting
void playerHeavyAttack()
{
	genRandomNumber();
	int heavyAttackHitpoints = 20;
	if (randNumber >= 50 + playerPenalty)
	{
		enemyHealth -= heavyAttackHitpoints_plr;
	}
	else if (randNumber < 50 + playerPenalty)
	{
		printf("Attack missed!!\n");
		if (isCounterAttackPlayed == true)
		{
			enemyCounterAttack();
		}
		isCounterAttackPlayed = false;
	}
	playerPenalty = 0;
	heavyAttackHitpoints_plr = 20;

}

void enemyHeavyAttack()
{
	genRandomNumber();
	if (randNumber >= 50 + enemyPenalty)
	{
		playerHealth -= heavyAttackHitpoints_enmy;
	}
	else if (randNumber < 50 + enemyPenalty)
	{
		printf("Enemy Attack missed!!\n");
		if (isCounterAttackPlayed == true)
		{
			playerCounterAttack();
		}
		isCounterAttackPlayed = false;
	}
	enemyPenalty = 0;
	heavyAttackHitpoints_enmy = 20;
}

void playerCounterAttack()
{
	int counterAttackHitpoints = 6;
	enemyHealth -= counterAttackHitpoints;
	printf("Player Counters and deals 6 damage\n\n");
	printf("enemy health is now %d", enemyHealth);
	isCounterAttackPlayed = false;
}

void enemyCounterAttack()
{
	int counterAttackHitpoints = 6;
	playerHealth -= counterAttackHitpoints;
	printf("Enemy Counters and deals 6 damage\n\n");
	printf("Player health is now %d", playerHealth);
	isCounterAttackPlayed = false;
}

void playerDefend()
{
	enemyPenalty = 30;
	if (playerHealth <= 95)
	{
		printf("\n\nEnemy attack chance reduced by 30%\n\n");
		playerHealth += defendHealthPoints;
	}
	else
	{
		printf("Health cannot go above 100 choose another option!");
		return playerAttack();
	}
}

void enemyDefend()
{
	playerPenalty = 30;
	if (enemyHealth <= 95)
	{
		printf("\n\nPlayer attack chance reduced by 30%\n\n");
		enemyHealth += defendHealthPoints;
	}
	else
	{
		printf("Health cannot go above 100 choose another option!\n\n");
		return enemyAttack();
	}
}

void playerAmulet()
{
	normalAttackHitpoints_plr * 1.5;
	heavyAttackHitpoints_plr * 1.5;
}

void enemyAmulet()
{
	normalAttackHitpoints_enmy * 1.5;
	heavyAttackHitpoints_enmy * 1.5;
}
