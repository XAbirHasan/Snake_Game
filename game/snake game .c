#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

// all methods here.
void movement();
void Eat_and_dead();
void key_input();
void Draw_board();
int high_score(int read);
void update_difficulty();
void welcome_show();
void instructions();
void thank_show();
void game();

// global variable.

int head_dx, head_dy;

int fruit_dx, fruit_dy;

int i, j, k, l;

int score;
int h_score;
int gameOver;

int board_width = 30, board_hight = 20;

// for body parts.
int tail_dx[500], tail_dy[500];
int number_of_tail;
int tail_1_dx, tail_1_dy, next_tail_dx, next_tail_dy;

// movement
int left, right, up, down;
int key_move;

char key;
char move;

int offset;

void movement()
{
	tail_1_dx = tail_dx[0];
	tail_1_dy = tail_dy[0];

	tail_dx[0] = head_dx;
	tail_dy[0] = head_dy;

	for (i = 1; i < number_of_tail; i++)
	{
		next_tail_dx = tail_dx[i];
		next_tail_dy = tail_dy[i];

		tail_dx[i] = tail_1_dx;
		tail_dy[i] = tail_1_dy;

		tail_1_dx = next_tail_dx;
		tail_1_dy = next_tail_dy;

	}
	/**
	The ascii values of the:

        Up key - 72

        Down key - 80

        Left key - 75

        Right key - 77
    */
    if (move == 'w' || move == 'W' || move == 72)
    {
        up = 1;        // up
        down = 0;
        left = 0;
        right = 0;
    }
    if (move == 's' || move == 'S' || move == 80)
    {
        up = 0;
        down = 1;        //down
        left = 0;
        right = 0;
    }
    if (move == 'a' || move == 'A' || move == 75)
    {
        up = 0;
        down = 0;
        left = 1;       //left
        right = 0;
    }
    if (move == 'd' || move == 'D' || move == 77)
    {
        up = 0;
        down = 0;
        left = 0;
        right = 1;       //right;
    }

    // MOVEMENT
    if (up == 1)
    {
        head_dy--;         // up
    }
    if (down == 1)
    {
        head_dy++;         //down
    }
    if (left == 1)
    {
        head_dx--;       //left
    }
    if (right == 1)
    {
        head_dx++;       //right;
    }


	if (head_dx >= board_width)
	{
		head_dx = 0;
	}
	else if (head_dx < 0)
	{
		head_dx = board_width - 1;
	}
	if (head_dy >= board_hight)
	{
		head_dy = 0;
	}
	else if (head_dy < 0)
	{
		head_dy = board_hight - 1;
	}

}

void Eat_and_dead()
{
    for (l = 0; l < number_of_tail; l++)
    {
        if (head_dx == tail_dx[l] && head_dy == tail_dy[l])
        {
            gameOver = 1;
        }
    }
    if (head_dx == fruit_dx && head_dy == fruit_dy)
    {
        score += 10;
        fruit_dx = rand() % board_width;
        fruit_dy = rand() % board_hight;
        number_of_tail++;
    }

}


void key_input()
{
	if (_kbhit())
	{
		key = _getch();
		/**
		if(key == 0 || key == 224)
        {
            key = _getch();
        }
        */
		move = key;


		if(move == 'p' || move == 'P')
        {
            score += 10; // to update score cheat.
        }
        if(move == 'x' || move == 'X')
        {
            gameOver = 1; // to exit the game .
        }

	}
}


void Draw_board()
{
	system("cls");
	printf("\t\t\t\t");

	for (i = 0; i < board_width + 2; i++)
	{
		printf("-");
	}
	printf("\n");
	for (i = 0; i < board_hight; i++)
	{
		for (j = 0; j < board_width; j++)
		{
			if (j == 0)
			{
				printf("\t\t\t\t|");
			}

			if (i == head_dy && j == head_dx)
			{
				printf("O");
			}
			else if (i == fruit_dy && j == fruit_dx)
			{
				printf("$");
			}

			else
			{
				int  tailshow = 0;
				for (k = 0; k < number_of_tail; k++)
				{
					if (tail_dx[k] == j && tail_dy[k] == i)
					{
						printf("o");
						tailshow = 1;
					}
				}
				if (tailshow == 0)
					printf(" ");
			}

			if (j == board_width - 1)
			{
				printf("|");
			}

		}
		printf("\n");
	}
	printf("\t\t\t\t");
	for (i = 0; i < board_width + 2; i++)
	{
		printf("-");
	}

	printf("\n\n\t\t\t\tScore = %d\n", score);
	//printf("\ngameOver= %d",gameOver);
}

int high_score(int read)
{
    FILE *fptr;
    char file_path [100] = "HighScore.txt";
    if(read == 1)
    {
        fptr = fopen(file_path, "r");

        if(fptr == NULL)
        {
            printf("Error!");
            fclose(fptr);

            // create new file if not exits.
            int init_h_score = 0;
            fptr = fopen(file_path, "a+");
            fprintf(fptr, "%d", init_h_score);
        }
        fscanf(fptr, "%d", &h_score);
        fclose(fptr);

        return 0;
    }

    if(h_score < score)
    {
        fptr = fopen(file_path, "w");
        fprintf(fptr, "%d", score);
        fclose(fptr);
        return 1;
    }

}

void update_difficulty()
{
    if(score < 100)
    {
        offset = 200;
    }
    else if(score < 200)
    {
        offset = 175;
    }
    else if(score < 300)
    {
        offset = 150;
    }
    else if(score < 400)
    {
        offset = 125;
    }
    else if(score < 500)
    {
        offset = 100;
    }
    else if(score < 600)
    {
        offset = 75;
    }
    else if(score < 700)
    {
        offset = 50;
    }
    else if(score < 800)
    {
        offset = 25;
    }
    else if(score < 900)
    {
        offset = 15;
    }
    else
    {
        offset = 0;
    }
}

void welcome_show()
{
    char welcome[100] = "........Welcome to my snake game........";
    char loading[100] = "........LOADING........";

    int it1, it2, it3;
    for(it3 = 0; it3< 2; it3++)
    {
        printf("\n\n\n\n\n\t\t\t");
        for(it1 = 0; loading[it1] != '\0'; it1++)
        {
            printf("%c",loading[it1]);
            for(it2 = 0; it2< 70000000; it2++){}
        }
        system("cls");
    }

    printf("\n\n\n\n\n\t\t\t");
    for(it1 = 0; welcome[it1] != '\0'; it1++)
    {
        printf("%c",welcome[it1]);
        for(it2 = 0; it2< 50000000; it2++){}
    }

    printf("\n\n\t\t\t\t press any key to play\n\n\n\t\t\t\t   ");
    _getch();
}

void instructions()
{
    char ins[100] = "Instruction Menu :";

    int it1, it2;
    printf("\n\n\t");
    for(it1 = 0; ins[it1] != '\0'; it1++)
    {
        printf("%c",ins[it1]);
        for(it2 = 0; it2< 50000000; it2++){}
    }

    printf("\n\n\t\tw key for move UP");
    printf("\n\t\ts key for move down");
    printf("\n\t\ta key for move LEFT");
    printf("\n\t\td key for move RIGHT");

    printf("\n\n\t\tYou can use ARROW keys for movement");

    printf("\n\n\n\tpress any key for go back\n\t");
    _getch();
}

void thank_show()
{
    char thanks[100] = "..............Thank you..............";

    int it1, it2;
    printf("\n\n\n\t\t");
    for(it1 = 0; thanks[it1] != '\0'; it1++)
    {
        printf("%c",thanks[it1]);
        for(it2 = 0; it2< 50000000; it2++){}
    }
    printf("\n\n\t\t     ....press any key to exit....\n\n\n\t\t\t\t   ");
    printf("\n\n\t\t\t....@(Md. Abir Hasan)....\n\n\n\t\t\t\t   ");
}

void game()
{
    welcome_show();
    while (gameOver != 1)
    {
        Eat_and_dead();

        if (gameOver !=1) // if not dead.
        {
            Draw_board();
            movement();
            key_input();
            update_difficulty();

            int c, d;

            // for make movement control with time.
            for ( c = 1 ; c <= 100*offset ; c++ )
            {
                for ( d = 1 ; d <= 10000 ; d++ ){}
            }
        }
    }

    if(gameOver=1)
    {
        system("cls");
        int best = high_score(0);
        int it1, it2;
        if(best == 1) // check for high score or not
        {
            char good[100] = "....*Congrats High Score*....";
            printf("\n\n\t\t     ");
            for(it1 = 0; good[it1] != '\0'; it1++)
            {
                printf("%c",good[it1]);
                for(it2 = 0; it2< 50000000; it2++){}
            }
        }
        char show_score[50] = "Your score is : ";
        printf("\n\n\t\t\t  ");
        for(it1 = 0; show_score[it1] != '\0'; it1++)
        {
            printf("%c",show_score[it1]);
            for(it2 = 0; it2< 50000000; it2++){}
        }

        printf("%d\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t ",score);

        char thanks[50] = "........Thank you for playing........";
        for(it1 = 0; thanks[it1] != '\0'; it1++)
        {
            printf("%c",thanks[it1]);
            for(it2 = 0; it2< 50000000; it2++){}
        }
        printf("\n\n\t\t     ....press any key to exit....\n\n\n\t\t\t\t   ");
        printf("\n\t\t\t....@(Md. Abir Hasan)....\n\n\n\t\t\t\t   ");
    }
}

void main()
{
    // to set object at random position.
	srand(time(NULL));
	head_dx = rand() % board_width;
	head_dy = rand() % board_hight;

	fruit_dx = rand() % board_width;
	fruit_dy = rand() % board_hight;

	high_score(1); // read high_score

	left =  right =  up =  down = 0; // initial values

	int option;

	main_menu:
    system("cls");

	printf("\n\n Chose your option:\n\t1. press for Play the Game\n\t2. for instruction\n\t3. for Exit\n\t");
	scanf("%d",&option);
	system("cls");

	if(option == 1)
    {
        game();
    }

    else if(option == 2)
    {
        instructions();
        goto main_menu;
    }

    else if(option == 3)
    {
        thank_show();
    }
    else
    {
        goto main_menu;
    }

    _getch();
}
