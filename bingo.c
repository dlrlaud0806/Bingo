#include <stdio.h> 

#include <time.h> 

#include <Windows.h> 

void init(int bingo[5][5])
{
	int i,j;
	int sour, dest, sour2, dest2;
	int temp;
	for (i = 0; i < 5; i++)
		for(j=0;j<5;j++)
			bingo[i][j] = i*5 + j + 1;


	for (i = 0; i < 100; i++)
	{
		sour = rand() % 5;
		sour2 = rand() % 5;
		dest = rand() % 5;
		dest2 = rand() % 5;
		temp = bingo[sour][sour2];
		bingo[sour][sour2] = bingo[dest][dest2];
		bingo[dest][dest2] = temp;
	}
}

void printBingoBoard(int bingo[5][5], int bingo2[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++) {
			if (bingo2[i][j] == 1) {
					printf("(%d)\t", bingo[i][j]);
			}
			else {
					printf("%d\t", bingo[i][j]);
			}
		}
		printf("\n");
	}
}

int checkBingo(int bingo[5][5])
{
	int bingoCheck[12] = { 0 };
	int count = 0;
	int i, j;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (bingo[i][j] == 1)
				bingoCheck[i]++;

			if (bingo[j][i] == 1)
				bingoCheck[i + 5]++;
		}

		for (j = i; j <= i; j++)
			if (bingo[i][j] == 1)
				bingoCheck[10]++;
	}

	for (i = 4; i >= 0; i--)
		for (j = 4 - i; j >= 4 - i; j--)
			if (bingo[i][j] == 1)
				bingoCheck[11]++;

	for (i = 0; i < 12; i++)
		if (bingoCheck[i] == 5)
			count++;
	return count;
}




void inputNum(int userBingo_1[5][5], int comBingo_1[5][5], int userBingo_2[5][5], int comBingo_2[5][5])
{
	int num;
	int isCheck;
	while (1)
	{
		isCheck = 0;
		printf("당신의 차례입니다. 몇 번을 열까요? : ");
		scanf_s("%d", &num);
		if (num < 1 || num > 25)
			printf("1 ~ 25 사이의 숫자를 입력해주세요\n");
		else
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (userBingo_1[i][j] == num)
					{
						userBingo_2[i][j] = 1;
						isCheck = 1;
					}
					if (comBingo_1[i][j] == num)
					{
						comBingo_2[i][j] = 1;
					}
				}
			}
			if (isCheck)
				break;
			else
				printf("이미 입력한 숫자입니다.\n");
		}
	}
}


int randNum(int userBingo_1[5][5], int comBingo_1[5][5], int userBingo_2[5][5], int comBingo_2[5][5])
{
	int num = 0;

	Sleep(1000);
	if (comBingo_2[2][2] == 0)
		num = comBingo_1[2][2];
	else {
		for (int i = 0; i < 5; i++) {
			if (comBingo_2[i][i] == 0) {
				num = comBingo_1[i][i];
				break;
			}
			else if (comBingo_2[i][4 - i] == 0) {
				num = comBingo_1[i][4 - i];
				break;
			}
		}
	}
	if(num == 0)
		num = rand() % 25 + 1;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (userBingo_1[i][j] == num)
			{
				userBingo_2[i][j] = 1;
			}
			if (comBingo_1[i][j] == num)
			{
				comBingo_2[i][j] = 1;
			}
		}
	}

	return num;
}


int main()
{
	int userBingo[5][5];
	int userBingo2[5][5] = { 0, };
	int comBingo[5][5];
	int comBingo2[5][5] = { 0, };
	int comBingo3[5][5] = { 0, };
	int userCount;
	int comCount;
	bool isTurn = 0;
	int num = 0;
	srand((unsigned int)time(NULL));

	//섞기
	init(userBingo);
	init(comBingo);

	while (1)
	{
		userCount = checkBingo(userBingo2);
		comCount = checkBingo(comBingo2);
		system("cls");
		printf("============user============\n");
		printBingoBoard(userBingo, userBingo2);
		printf("========computer============\n");
		printBingoBoard(comBingo, comBingo2);

		printf("사용자 : %d줄 빙고\n", userCount);
		printf("컴퓨터 : %d줄 빙고\n", comCount);

		if ( userCount >= 5 && comCount < 5 )
		{
			printf("당신이 이겼습니다.\n");
			break;
		}
		else if (userCount < 5 && comCount >= 5)
		{
			printf("컴퓨터가 이겼습니다.\n");
			break;
		}
		else if (userCount == 5 && comCount == 5)
		{
			printf("비겼습니다.\n");
		}
		

		isTurn = !isTurn;


		if (isTurn && num != 0) {
			printf("컴퓨터의 차례입니다. %d번을 선택했습니다. \n", num);
			inputNum(userBingo, comBingo, userBingo2, comBingo2);
		}
		else if (isTurn && num == 0) {
			inputNum(userBingo, comBingo, userBingo2, comBingo2);
		}
		else
			num = randNum(userBingo, comBingo, userBingo2, comBingo2);
	}
}