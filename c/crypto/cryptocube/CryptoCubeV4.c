#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//Версия проги, выведу перед заполенением.
#define VERSION "0.4.4"

//Колл-во сторон, оно всегда одно... Тп, нет же куба с 7  сторонами? А если есть, то минус парень...
#define SIDESCOUNT 6
//Нужно вводить значение ТОЛЬКО исходя из size*size*SIDESCOUNT, но вот проблемка... я уже перобовал вводить другие, утечка...
//При 150 ноль ошибок...
//При 216 не правильно шифрует...
#define MAXCUBELENGTH 150

//Числовые значения сторон (для повышения читабельности и упрощения индексиции)
#define F 0
#define U 1
#define B 2
#define D 3
#define L 4
#define R 5

//Size - размер грани куба используется почти везде.
unsigned char size = 0;


//***sides - указатель на 3 мерный массив сторон.
char*** sides = NULL;
//*bufer - указатель на буфер введенный с клавиатуры.
char* bufer = NULL;
//Указаель на буфер для 1 куба.
char* SecondBufer = NULL;
//Указатель на буфер для зашифрованного текста.
char* CryptedBufer = NULL;
//Указатель на ОСНОВНОЙ массив ключа
char* MainKey = NULL;

//Ввод текста с клавиатуры и последущее помещение в буфер.
void CmdGetTextnLength (unsigned long int *Plength, unsigned int *PNumOfCubes, unsigned char *PMovesCount)
{
	//Переменная для определения размера выделяемой памяти
	unsigned int memory = 1;
	//Переменная получающая ввод с клавиатуры
	char text;

	printf("\n[!]PLEASE ENTER YOUR TEXT\n");
	printf("[!]TYPE *Enter + Ctrl + Z* AT THE END OF THE INPUT\n");

	while ((text = getchar()) != EOF){
		if (text == '\n')
			text = '~';
		if (memory <= *Plength)
			memory = memory * 2;
		bufer = (char*)realloc(bufer, memory * sizeof(char));
		bufer[*Plength] = text;
		(*Plength)++;
	}

	bufer = (char*)realloc(bufer, *Plength * sizeof(char));
	
	printf("[!]LENGTH = %i SYMBOLS\n", *Plength);

	//Определение кол-ва кубов
	unsigned int ind = *Plength;
	if (*Plength > MAXCUBELENGTH){
		while (ind > MAXCUBELENGTH){
			ind = ind - MAXCUBELENGTH;
			(*PNumOfCubes)++;
		} 
	}

	MainKey = (char*)calloc((*PMovesCount) * 4 * (*PNumOfCubes), sizeof(char));
	CryptedBufer = (char*)calloc(MAXCUBELENGTH* (*PNumOfCubes), sizeof(char));
	return;
}

//Ввод текста из текстового документа для послед. действий
void TxtGetTextnLength (unsigned long int *Plength, unsigned int *PNumOfCubes, unsigned char *PMovesCount)
{
	FILE *file;

	printf("\n[!]PLEASE ENTER YOUR TEXT IN THE *ForEncrypt.txt*\n");
	printf("[!]SAVE AND TYPE *ENTER* TO COUNTINE\r\n");
	getchar();
	file = fopen("C:/c/ForEncrypt.txt", "r");

	//Переменная для определения размера выделяемой памяти
	unsigned long int memory = 1;
	//Переменная получающая ввод с клавиатуры
	int text;
	while ((text = fgetc(file)) != EOF){
		if (text == '\n')
			text = '~';
		if (memory <= (*Plength))
			memory = memory * 2;
		bufer = (char*)realloc(bufer, memory * sizeof(char));

		bufer[*Plength] = text;
		(*Plength)++;
	}
	fclose(file);
	bufer = (char*)realloc(bufer, (*Plength) * sizeof(char));
	
	printf("[*]LENGTH = %i SYMBOLS\n", *Plength);

	//Определение кол-ва кубов
	unsigned long int ind = *Plength;
	if (*Plength > MAXCUBELENGTH){
		while (ind > MAXCUBELENGTH){
			ind = ind - MAXCUBELENGTH;
			(*PNumOfCubes)++;
		} 
	}

	MainKey = (char*)calloc(*PMovesCount * 4 * (*PNumOfCubes), sizeof(char));
	CryptedBufer = (char*)calloc(MAXCUBELENGTH* (*PNumOfCubes), sizeof(char));
	return;
}

//Выбор кол-ва сдвигов
void GetNumOfMoves (unsigned char *PMovesCount)
{
	printf("\n[!]SELECT COMPLEXITY OF ENCRYPTION\n");
	printf("1: Easy\n2: Medium\n3: Hard\n");

	char select;
	while (*PMovesCount == 0){
		select = getchar();
		getchar();
		switch (select){
		case '1':
			*PMovesCount = 10;
			break;
		case '2':
			*PMovesCount = 25;
			break;
		case '3':
			*PMovesCount = 50;
			break;
		default:
			break;
		}
	}
}

//выбор языка текста дозаполнения
void GetRandomize (unsigned char *PSrandSym)
{
	printf ("\n[!]SELECT LANGUAGE OF YOUR TEXT:\n");
	printf("1: English\n2: Russian\n3: Numbers\n4:All symbols\n");

	char select;
	while (*PSrandSym == 0){
		select = getchar();
		getchar();
		switch (select){
		case '1':
			*PSrandSym = 1;
			break;
		case '2':
			*PSrandSym = 2;
			break;
		case '3':
			*PSrandSym = 3;
			break;
		case '4':
			*PSrandSym = 4;
			break;
		default:
			break;
		}
	}
}


//Функция разделения текста на части для последующего шифрования.
void MoreBufs (unsigned long int *PCountChar,unsigned long int *PICountChar,unsigned long int *Plength, int *PLengthOfCube, unsigned int *PNumOfCycles)
{
	int SBInd = 0;

	//Размер куба.
	size = 0;

	//Длинна текста заносимого в куб.
	*PLengthOfCube = 0;

	unsigned long int ind = *Plength - (*PCountChar);
	if (ind > MAXCUBELENGTH){
		*PLengthOfCube = MAXCUBELENGTH;
		SecondBufer = (char*)calloc(MAXCUBELENGTH, sizeof(char));
		for (unsigned long int i = *PICountChar; i < (MAXCUBELENGTH + (MAXCUBELENGTH * (*PNumOfCycles))) ; ++i){
			SecondBufer[SBInd] = bufer[i];
			++SBInd;
			(*PCountChar)++;
		}
		(*PNumOfCycles)++;
	}
	else{
		*PLengthOfCube = 0;
		SecondBufer = (char*)calloc(ind, sizeof(char));
		for (unsigned long int j = *PICountChar; j < *Plength; ++j)
		{
			SecondBufer[SBInd] = bufer[j];
			++SBInd;
			(*PLengthOfCube)++;
			(*PCountChar)++;
		}
	}
	*PICountChar = *PCountChar;

	//Определение размера куба.
	while ((size*size*SIDESCOUNT) < *PLengthOfCube || size < 3){
		++size;
	}
}

//Заполнение 3 мерного массива значениями из буфера.
void SidesFill (unsigned long int *Plength, unsigned int *PLengthOfCube, unsigned char *PSrandSym)
{
	unsigned char Oz = SIDESCOUNT;
	unsigned int Ox = size;
	unsigned int Oy = size;
	
	unsigned char min1, max1, min2, max2;
	switch (*PSrandSym){
		case 1:
			min1 = 97;
			max1 = 122;
			min2 = 65;
			max2 = 90;
			break;
		case 2:
			min1 = 128;
			max1 = 175;
			min2 = 224;
			max2 = 239;
			break;
		case 3:
			min1 = 48;
			max1 = 57;
			min2 = 48;
			max2 = 57;
			break;
		case 4:
			min1 = 33;
			max1 = 47;
			min2 = 91;
			max2 = 96;
			break;
	}

	sides = (char ***)calloc(Oz, sizeof(char **));
	for (int z = 0; z < Oz; ++z)
	{
		sides[z] = (char**)calloc(Ox, sizeof(char*));
		for (int x = 0; x < Ox; x++)
		{
			sides[z][x] = (char *)calloc(Oy, sizeof(char));
		}
	}

	srand(time(NULL));
	char ind;
	char RandomSym;
	unsigned long int SBInd = 0;
	for (unsigned int z = 0; z < Oz; ++z){
		for (unsigned int x = 0; x < Ox; ++x){
			for (unsigned int y = 0; y < Oy; ++y){
				if (SBInd <= *Plength){
				sides[z][x][y] = SecondBufer[SBInd];
				++SBInd;
				}
				if (SBInd > *PLengthOfCube){
					
					ind = rand()%2;
					switch(ind){
						case 0:
							RandomSym = rand()%(max1-min1) + min1;
							break;
						case 1:
							RandomSym = rand()%(max2-min2) + min2;
							break;
					}

					sides[z][x][y] = RandomSym;
				}
			}
		}
	}
	free(SecondBufer);
	return;
}

//Инверсия задней грани куба - для функций поворота грани и MMove... см. развертку куба.
void BSideInv (void)
{
	char bufr;
	unsigned int ind = size - 1;
	unsigned int ind2 = 0;
	while (((ind2 - 1) != ind) && (ind2 != ind)){
		for (unsigned int i = 0; i < size; ++i){
			bufr = sides[B][i][ind2];
			sides[B][i][ind2] = sides[B][i][ind];
			sides[B][i][ind] = bufr;
			
		}
		++ind2;
		--ind;
	}
}

//Визуализация 3 мерного массива.
void SidesVisual (void)
{
	char name;
	for (unsigned int z = 0; z < SIDESCOUNT; ++z){
		switch(z){
			case 0:
			name = 'F';
			break;
			case 1:
			name = 'U';
			break;
			case 2:
			name = 'B';
			break;
			case 3:
			name = 'D';
			break;
			case 4:
			name = 'L';
			break;
			case 5:
			name = 'R';
			break;
		}
		printf("\n(*)%c SIDE\n", name);
		for (unsigned int x = 0; x < size; ++x){
			for (unsigned int y = 0; y < size; ++y){
				printf ("[%c] ", sides[z][x][y]);
			}
			printf("\n");
		}
		/*for (unsigned int x = 0; x < size; ++x){
			for (unsigned int y = 0; y < size; ++y){
				printf ("%c", sides[z][x][y]);
			}
		}
		printf("\n");*/
	}
}

//Поворот грани - часть сложного движения. Т.е. задействован только 1 массив.
void ClockWiseSide (const int MSide)
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < (size / 2); ++i){
		count = count + ((size - 1) - (2 * i));
	}
	char* buf;
	buf = (char*)malloc(count * sizeof(char));

	unsigned int ind = 0;
	for (unsigned int i = 0; i < (size / 2); ++i){
		for (unsigned int j = 0; j < ((size - 1) - i); ++j){
			buf[ind] = sides[MSide][i][((size - 1) - i) - j];
			++ind;
		}
	}

	unsigned int BInd = 0;
	for (unsigned int i = 0; i < (size / 2); ++i){
		for (unsigned int ind = 0; ind < ((size - 1) - (2 * i)); ++ind){
			sides[MSide][i][(size - 1) - ind - i] = sides[MSide][ind + i][i];
			sides[MSide][ind + i][i] = sides[MSide][(size - 1) - i][ind + i];
			sides[MSide][(size - 1) - i][ind + i] = sides[MSide][((size - 1) - i) - ind][(size - 1) - i];
			sides[MSide][((size - 1) - i) - ind][(size - 1) - i] = buf[BInd];
			++BInd;
		}
	}
	free(buf);
	return;
}
void CounterClockWiseSide (const int MSide)
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < (size / 2); ++i){
		count = count + ((size - 1) - (2 * i));
	}
	char* buf;
	buf = (char*)malloc(count * sizeof(char));

	unsigned int ind = 0;
	for (unsigned int i = 0; i < (size / 2); ++i){
		for (unsigned int j = 0; j < ((size - 1) - i); ++j){
			buf[ind] = sides[MSide][i][j + i];
			++ind;
		}
	}

	unsigned int BInd = 0;
	for (unsigned int i = 0; i < (size / 2); ++i){
		for (unsigned int ind = 0; ind < ((size - 1) - (2 * i)); ++ind){
			sides[MSide][i][ind + i] = sides[MSide][ind + i][(size - 1) - i];
			sides[MSide][ind + i][(size - 1) - i] = sides[MSide][(size - 1) - i][((size - 1) - i) - ind];
			sides[MSide][(size - 1) - i][((size - 1) - i) - ind] = sides[MSide][((size - 1) - i) - ind][i];
			sides[MSide][((size - 1) - i) - ind][i] = buf[BInd];
			++BInd;
		}
	}

	free(buf);
	return;
}

//Функции стандартных односложных движений.
//Line не может равняться 0 и (size - 1)

void MMove (unsigned int line)
{
	char* buf;
	buf = (char*)calloc(size, sizeof(char));

	for (unsigned int i = 0; i < size; ++i){
		buf[i] = sides[F][i][line];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[F][i][line] = sides[U][i][line];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[U][i][line] = sides[B][(size - 1 - i)][(size - 1) - line];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[B][(size - 1 - i)][(size - 1) - line] = sides[D][i][line];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[D][i][line] = buf[i];
	}
	free(buf);
	return;
}
void CounterMMove (int line)
{
	char* buf;
	buf = (char*)malloc(size * sizeof(char));

	for (unsigned int i = 0; i < size; ++i){
		buf[i] = sides[F][i][line];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[F][i][line] = sides[D][i][line];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[D][i][line] = sides[B][(size - 1) - i][(size - 1) - line];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[B][(size - 1) - i][(size - 1) - line] = sides[U][i][line];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[U][i][line] = buf[i];
	}
	free(buf);
	return;
}

void EMove (unsigned int line)
{
	char* buf;
	buf = (char*)malloc(size * sizeof(char));

	for (unsigned int i = 0; i < size; ++i){
		buf[i] = sides[F][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[F][line][i] = sides[R][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[R][line][i] = sides[B][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[B][line][i] = sides[L][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[L][line][i] = buf[i];
	}

	free(buf);
	return;
}
void CounterEMove (unsigned int line)
{
	char* buf;
	buf = (char*)malloc(size * sizeof(char));

	for (unsigned int i = 0; i < size; ++i){
		buf[i] = sides[F][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[F][line][i] = sides[L][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[L][line][i] = sides[B][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[B][line][i] = sides[R][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[R][line][i] = buf[i];
	}

	free(buf);
	return;
}

void SMove (unsigned int line)
{
	char* buf;
	buf = (char*)malloc(size * sizeof(char));

	for (unsigned int i = 0; i < size; ++i){
		buf[i] = sides[L][(size - 1) - i][(size - 1) - line];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[L][(size - 1) - i][(size - 1) - line] = sides[D][line][(size - 1) - i];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[D][line][(size - 1) - i] = sides[R][i][line];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[R][i][line] = sides[U][(size - 1) - line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[U][(size - 1) - line][i] = buf[i];
	}

	free(buf);

	return;
}
void CounterSMove (unsigned int line)
{
	char* buf;
	buf = (char*)malloc(size * sizeof(char));

	for (unsigned int i = 0; i < size; ++i){
		buf[i] = sides[L][i][(size - 1) - line];
	}

	for (unsigned int i = 0; i < size; ++i){
		sides[L][i][(size - 1) - line] = sides[U][(size - 1) - line][(size - 1) - i];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[U][(size - 1) - line][(size - 1) - i] = sides[R][(size - 1) - i][line];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[R][(size - 1) - i][line] = sides[D][line][i];
	}

	for (unsigned int i = 0; i < size; ++i){
			sides[D][line][i] = buf[i];
	}

	free(buf);

	return;
}

//Функции стандартных сложных движений.
//К слову, можно обьеденить функции по и против часовой стрелки и добавить rand, но тогда я не смогу вызывать их по отдельности.
void FMove (void)
{
	ClockWiseSide(F);
	SMove(0);
	// printf("\nFMOVE\n");
	return;
}
void CounterFMove (void)
{
	CounterClockWiseSide(F);
	CounterSMove(0);
	// printf("\nCounterFMove\n");

	return;
}
void UMove (void)
{
	ClockWiseSide(U);
	EMove(0);
	// printf("\nUMOVE\n");
	return;
}
void CounterUMove (void)
{
	CounterClockWiseSide(U);
	CounterEMove(0);
	// printf("\nCounterUMove\n");

	return;
}
void BMove (void)
{
	int l = 0;
	l = size - 1;
	ClockWiseSide(B);
	CounterSMove(l);
	// printf("\nBMOVE\n");
	return;
}
void CounterBMove (void)
{
	int l = 0;
	l = size - 1;
	CounterClockWiseSide(B);
	SMove(l);
	// printf("\nCounterBMove\n");

	return;
}
void DMove (void)
{
	int l = 0;
	l = size - 1;
	ClockWiseSide(D);
	CounterEMove(l);
	// printf("\nDMOVE\n");
	return;
}
void CounterDMove (void)
{
	int l = 0;
	l = size - 1;
	CounterClockWiseSide(D);
	EMove(l);
	// printf("\nCounterDMove\n");

	return;
}
void LMove (void)
{
	ClockWiseSide(L);
	MMove(0);
	// printf("\nLMOVE\n");
	return;
}
void CounterLMove (void)
{	
	CounterClockWiseSide(L);
	CounterMMove(0);
	// printf("\nCounterLMove\n");

	return;
}
void RMove (void)
{
	int l = 0;
	l = size - 1;
	ClockWiseSide(R);
	CounterMMove(l);
	// printf("\nRMOVE\n");
	return;
}
void CounterRMove (void)
{
	int l = 0;
	l = size - 1;
	CounterClockWiseSide(R);
	MMove(l);
	// printf("\nCounterRMove\n");
	return;
}

//Основная функция программы, выполняет случайные движения и заносит их код в буфер для ключа.
void RandMoves (unsigned int *PMKind, unsigned int *PCurrentLoop, unsigned int *PNumOfCubes, unsigned char *PMovesCount, unsigned char *Rand)
{
	//Указатель на массив ключа
	char* key = NULL;
	//Опредление выделяемой под ключ памяти.
	int KeyMemory = *PMovesCount * 4;
	key = (char*)calloc(KeyMemory, sizeof(char));

	srand(*Rand);
	//Декларация переменной для усложнения.
	char RandKey;
	//Декларация переменных для выполнения случайных действий.
	int RandMove, RandLine, i;
	i = 0;
	for (int ind = 0; ind < *PMovesCount; ++ind){

		RandMove = rand()%(8+9)-9;
		RandLine = rand()%((size - 1) - 1) + 1;

		//Условия для выполнения функций сдвига
		switch(RandMove){
			case -9:
				CounterEMove(RandLine);
				// printf("\nCounterEMove line:%d\n", RandLine);
				key[i] = RandLine + 48;
				++i;
				key[i] = '9';
				++i;
				key[i] = '_';
				break;
			case -8:
				CounterSMove(RandLine);
				// printf("\nCounterSMove line:%d\n", RandLine);
				key[i] = RandLine + 48;
				++i;
				key[i] = '8';
				++i;
				key[i] = '_';
				break;
			case -7:
				CounterMMove(RandLine);
				// printf("\nCounterMMove line:%d\n", RandLine);
				key[i] = RandLine + 48;
				++i;
				key[i] = '7';
				++i;
				key[i] = '_';
				break;
			case -6:
				CounterRMove();
				key[i]='6';
				++i;
				key[i] = '_';
				break;
			case -5:
				CounterLMove();
				key[i]='5';
				++i;
				key[i] = '_';
				break;
			case -4:
				CounterDMove();
				key[i]='4';
				++i;
				key[i] = '_';
				break;
			case -3:
				CounterBMove();
				key[i]='3';
				++i;
				key[i] = '_';
				break;
			case -2:
				CounterUMove();
				key[i]='2';
				++i;
				key[i] = '_';
				break;
			case -1:
				CounterFMove();
				key[i]='1';
				++i;
				key[i] = '_';
				break;
			case 0:
				FMove();
				key[i] = '0';
				break;
			case 1:
				UMove();
				key[i] = '1';
				break;
			case 2:
				BMove();
				key[i] = '2';
				break;
			case 3:
				DMove();
				key[i] = '3';
				break;
			case 4:
				LMove();
				key[i] = '4';
				break;
			case 5:
				RMove();
				key[i] = '5';
				break;
			case 6:
				MMove(RandLine);
				// printf("\nMMove line:%d\n", RandLine);
				key[i] = RandLine + 48;
				++i;
				key[i] = '6';
				break;
			case 7:
				SMove(RandLine);
				// printf("\nSMove line:%d\n", RandLine);
				key[i] = RandLine + 48;
				++i;
				key[i] = '7';
				break;
			case 8:
				EMove(RandLine);
				// printf("\nEMove line:%d\n", RandLine);
				key[i] = RandLine + 48;
				++i;
				key[i] = '8';
				break;
		}
		++i;
		RandKey = rand()%(90-65) + 65;
		key[i] = RandKey;
		++i;
	}
	if (*PCurrentLoop == (*PNumOfCubes - 1)){
			MainKey[*PMKind] = '-';
			(*PMKind)++;
	}

	if (*PCurrentLoop == 0 || *PCurrentLoop == (*PNumOfCubes - 1)){
		for (int KInd = 0; KInd < i; ++KInd){
			MainKey[*PMKind] = key[KInd];
			(*PMKind)++;
		}
	}
	free(key);

	/*KeySize = i;
	key = (char*)realloc(key, KeySize * sizeof(char));*/
	//Передача значений массива временного ключа в массив основного ключа.
	}

void GetKey (unsigned long int *Plength, unsigned int *PMKind, unsigned char *PMovesCount, unsigned int *PNumOfCubes)
{
	printf("\n[!]YOU KEY IS:\n");
	printf("%i:", *Plength);
	printf("%i:", *PMovesCount);
	printf("%i:", MAXCUBELENGTH);
	printf("%i:", *PNumOfCubes);
	for (int i = 0; i < *PMKind; ++i)
	{
		printf("%c", MainKey[i]);
	}
	printf("\n[!]SAVE IT TO DECRYPT YOUR TEXT\n");
}

void GetEncryptedText (unsigned long int *PCBInd)
{
	for (int z = 0; z < SIDESCOUNT; ++z)
	{
		for (int x = 0; x < size; ++x)
		{
			for (int y = 0; y < size; ++y)
			{
				CryptedBufer[*PCBInd] = sides[z][x][y];
				(*PCBInd)++;
			}
		}
	}
	return;
}

void Test(void)
{
	printf("\n[!]ENCYPTED TEXT:\n");
	for (int z = 0; z < SIDESCOUNT; ++z)
	{
		for (int x = 0; x < size; ++x)
		{
			for (int y = 0; y < size; ++y)
			{
				printf("%c", sides[z][x][y]);
			}
		}
	}
	return;
}

void FreeSides (void)
{
	for (int y = 0; y < size; ++y){
		for(int x = 0; x < size; ++x){
			free(sides[y][x]);
		}
	}
	for (int i = 0; i < SIDESCOUNT; ++i)
	{
		free(sides[i]);
	}
	free(sides);
}

void CmdEncryptedText (unsigned long int *PCBInd)
{
	printf("\r\n[!]ENCYPTED TEXT:\r\n");
	for (int i = 0; i < *PCBInd; ++i)
	{
		printf("%c", CryptedBufer[i]);
	}
	free(CryptedBufer);
}

void TxtEncryptedText (unsigned long int *PCBInd)
{
	FILE *file;

	file = fopen("C:/c/Encrypted.txt", "w");
	for (unsigned long int i = 0; i < *PCBInd; ++i)
	{
		fprintf(file, "%c", CryptedBufer[i]);
	}
	fclose(file);
	printf("\n[+]ENCRYPTION WAS FINISHED ENCRYPTED TEXT SAVED IN *Encrypted.txt*\n");
}

//Ну, тип сердце моей проги... Точка входа.
int main (void)
{	

	unsigned char SrandSym = 0;

	//Колл-во сдвигов
	unsigned char MovesCount = 0;
	//Эти две переменные позволяют сохранять значение последнего введенного символа.
	unsigned long int CountChar = 0; 
	unsigned long int ICountChar = 0;
	//length - длинна введенной строки.
	unsigned long int length = 0;
	//Length of cube - длинна строки в 1 кубе.
	int LengthOfCube = 0;
	//Индекс буфера массив 
	unsigned long int CBInd = 0;
	//Кол-во кубов - ОБЯЗАТЕЛЬНАЯ
	unsigned int NumOfCubes = 1;
	//Переменная отвечающая за идекс в функции MoreBufs
	unsigned int NumOfCycles = 0;
	//Индекс массива основного ключа
	unsigned int MKInd = 0;
	//Данный цикл
	unsigned int CurrentLoop = 0;

	//Переменные времени
	unsigned int time1 = 0;
	unsigned int time2 = 0;
	unsigned int time3 = 0;
	unsigned int time4 = 0;

	srand(time(NULL));
	unsigned char Rand = rand()%255;
	time1 = clock();

	printf("\nCryptoCube V%s\n", VERSION);

	GetNumOfMoves(&MovesCount);
	GetRandomize(&SrandSym);

	printf("\n[!]PLEASE CHOSE TYPE OF INPUT\n");
	printf("1:by keyboard (max length = 4096 symbols)\n2:by txt\n");
	unsigned char TChoseInd = 0;
	char TChose;
	while (TChoseInd == 0){
		TChose = getchar();
		getchar();
		switch (TChose){
		case '1':
			TChoseInd = 1;
			CmdGetTextnLength(&length, &NumOfCubes, &MovesCount);
			break;
		case '2':
			TChoseInd = 2;
			TxtGetTextnLength(&length, &NumOfCubes, &MovesCount);
			break;
		default:
			break;
		}
	}

	time2 = clock();
	for (int CurrentLoop = 0; CurrentLoop < NumOfCubes; ++CurrentLoop)
	{
		//Заполнение доп. буфера
		MoreBufs(&CountChar, &ICountChar, &length, &LengthOfCube, &NumOfCycles);
		//Заполнение 3 мерного массива.
		SidesFill(&length, &LengthOfCube, &SrandSym);
		// printf("\nFILL SIDES\n");
		// SidesVisual();
		//Функции выполнения сдвига в случайном порядке и получения ключа.
		RandMoves(&MKInd, &CurrentLoop, &NumOfCubes, &MovesCount, &Rand);
		// printf("\nCHANGED SIDES\n");
		// SidesVisual();
		//Получение частей зашифрованного текста.
		GetEncryptedText(&CBInd);
		//Освобождение трех мерного массива.
		FreeSides();
	}
	time3 = clock();
	switch(TChoseInd){
		case 1:
			CmdEncryptedText(&CBInd);
			break;
		case 2:
			TxtEncryptedText(&CBInd);
			break;
	}
	
	GetKey(&length, &MKInd, &MovesCount, &NumOfCubes);
	time4 = clock();
	printf("[*]TYPE ENTER TO CLOSE PROGRAM");
	printf("[+]TIME:\nThe whole time: %i\nprogramm time: %i\nJust moves: %i\n", time4, (time4 - time1), (time3 - time2));
	getchar();
	return EXIT_SUCCESS;
	//SidesVisual(); Функция визуализирующая 3 мерный массив... ТОЛЬКО для проверки движений на валидность.
	//Еще можно сделать так, чтобы каждфй куб дозаполнялся случайными символами (попробую)
	//Сделать подлючение файлов (попробую)
	//После написать архиватор. 000000000 = 90
	// ПРОВЕРИТЬ НА ОШИБКИ(выполнить в срочном порядке), ИСПРАВИТЬ ОШИБКИ В ПРЕД ВЕРСИИ (не стоит), ДОВЕСТИ ЭТУ ДО УМА...
	// Где - то все еще блуждает ошибка, т.к. 216 не шифрует...
}
/*
ДЕЛО НЕ В ДЕКРИПТОРЕ, А В ЕНКРИПТОРЕ! УЖЕ НЕЕТ
ГДЕ-ТО ОШИБКА... УЖЕ НЕТ
Я НАШЕЛ ОШИБКУ, ИСПРАВИЛ ЕЁ, НО ЕСТЬ ЕЩЕ 1 В ДЕКРИПТОРЕ... ТАМ КРЧ КОГДА БЕРЕШЬ 1501 СИМВОЛ, ОН СТРАННО ШИФРУЕТ ПОСЛЕДНИЙ КУБ ГОТОВО
ВАЖНО! ЧЕРТ, ПОЯВЛЯЕТСЯ КАКОЙ_ТО УЖАСНЫЙ ЕНТЕР, КОТОРЫЙ ЛОМАЕТ ВСЮ ДЕШИФРОВКУ! ИСПРАВИЛ
Можно помечать enter символом и при разшифровке ставить там '/n' ГОТОВО
ЛИБО СДЕЛАТЬ НОРМАЛЬНЫЙ РАНДОМ, ЛИБО ИЗМЕНИТЬ КЛЮЧ. (ЛУЧШЕ ИЗМЕНИТЬ КЛЮЧ) ГОТОВО
CДЕЛАТЬ ВЫБОР "сложности шифрования" (10 движений - просто, 30 - средне, 50 - сложно) ГОТОВО
Написать подключение рандомных символов (хз, это будет сложно) ГОТОВО
*/




/*
Ввод

2x2
FFFFUUUUBBBBDDDDLLLLRRRR
123412341234123412341234
1234567890QWERTYUIOPASDF

3x3
FFFFFFFFFUUUUUUUUUBBBBBBBBBDDDDDDDDDLLLLLLLLLRRRRRRRRR
123456789123456789123456789123456789123456789123456789
1234567890QWERTYUIOPASDFGHJKLZXCVBNM123456789123456789

4x4
FFFFFFFFFFFFFFFFUUUUUUUUUUUUUUUUBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDLLLLLLLLLLLLLLLLRRRRRRRRRRRRRRRR
1234567890QWERTY1234567890QWERTY1234567890QWERTY1234567890QWERTY1234567890QWERTY1234567890QWERTY

5x5
FFFFFFFFFFFFFFFFFFFFFFFFFUUUUUUUUUUUUUUUUUUUUUUUUUBBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDDLLLLLLLLLLLLLLLLLLLLLLLLLRRRRRRRRRRRRRRRRRRRRRRRRR
1234567890QWERTYUIOPASDFG1234567890QWERTYUIOPASDFG1234567890QWERTYUIOPASDFG1234567890QWERTYUIOPASDFG1234567890QWERTYUIOPASDFG1234567890QWERTYUIOPASDFG
*/
