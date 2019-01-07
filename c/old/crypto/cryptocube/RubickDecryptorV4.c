/*
Ключ стостоит из:
1. '_' - Обозначение движений против часовой стрелки. т.е. Counter*Move name*Move
2. "0..9" - Номер движений, к слову, движения по часовой стрелке - 0..8,  а против - 1..9
3. "1..(size - 1)" - Идет после движний под номерами - _9, _8, 8, _7, 7, 6 - номер линии.
4. "RSym" - Случайный символ - обозначат конец движения.
5. '-' - Обозначение начала шифровки нового куба (СДЛАТЬ НУ И ПОПЫТАТЬСЯ ОБОЙТИСЬ БЕЗ НЕГО)
5. ":length" - колл-во символов, которое следует выводить.

Пример: _6Y_2J_2J3V_4V1N_4H_3A_6H1V_71D5D_2W61F_81D0O_1V1J_3C_2T:10

Собсна алгоритм: одномерный массив для ключа и для текста, хмм... в ключ нужно добавить размер куба... в самое начало.
Так вот, на основе текста и ключа выделяется 3 мерный массив, затем следует алгоритм считывания ключа...
Так же стоит добавить кол-во движений в самое начало ключа...
Затем начинается алгоритм считывания.
И часть для куба передается в доп массив ключа
Затем на его основании производятся движения в обратном порядке
Далее как обычно...
НУЖНО ПОСТАВИТЬ ЧТО-НИБУДЬ МЕЖДУ КУБАМИ В КЛЮЧЕ!!!
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//Версия проги, выведу перед заполенением.
#define VERSION "0.4.3"

//Колл-во сторон, оно всегда одно... Т.е. нет же куба с 7  сторонами? А если есть, то минус парень...
#define SIDESCOUNT 6

//Числовые значения сторон (для повышения читабельности и упрощения индексиции)
#define F 0
#define U 1
#define B 2
#define D 3
#define L 4
#define R 5

//Size - размер грани куба.
unsigned char size = 0;
//***sides - указатель на 3 мерный массив сторон.
char*** sides = NULL;
//*bufer - указатель на буфер введенный с клавиатуры.
char* bufer = NULL;
//Указаель на буфер для 1 куба.
char* SecondBufer = NULL;
//Указатель на буфер для зашифрованного текста.
char* DecryptedBufer = NULL;
//Массив основного ключа
char* MainKey = NULL;

//Ввод текста с клавиатуры и последущее помещение в буфер.
void CmdGetTextnLength (unsigned long int *PLength)
{
	//Переменная для определения размера выделяемой памяти
	unsigned int memory = 1;
	//Переменная получающая ввод с клавиатуры
	char text;

	printf("\n[!]PLEASE ENTER YOUR TEXT\n");
	printf("[!]TYPE *Enter* AT THE END OF THE INPUT\n");

	while ((text = getchar()) != '\n'){
		if (memory <= *PLength)
			memory = memory * 2;
		bufer = (char*)realloc(bufer, memory * sizeof(char));
		bufer[*PLength] = text;
		(*PLength)++;
	}

	bufer = (char*)realloc(bufer, (*PLength) * sizeof(char));
	DecryptedBufer = (char*)calloc(*PLength, sizeof(char));

	return;
}

//Получение текста из текстового документа
void TxtGetTextnLength (unsigned long int *PLength)
{
	printf("\n[!]PLEASE ENTER YOUR TEXT IN THE *ForDecrypt.txt*\n");
	printf("[!]SAVE AND TYPE *ENTER* TO COUNTINE\n");
	getchar();

	FILE *file;
	file = fopen("C:/c/ForDecrypt.txt", "r");

	//Переменная для определения размера выделяемой памяти
	unsigned int memory = 1;
	//Переменная получающая ввод с клавиатуры
	int text;
	while ((text = fgetc(file)) != EOF){
		if (memory <= *PLength)
			memory = memory * 2;
		bufer = (char*)realloc(bufer, memory * sizeof(char));

		bufer[*PLength] = text;
		(*PLength)++;
	}

	bufer = (char*)realloc(bufer, *PLength * sizeof(char));
	DecryptedBufer = (char*)calloc(*PLength, sizeof(char));

	return;
}

void GetKey(unsigned long int *PLenOfText, unsigned int *PLengthOfKey, unsigned int *PNumOfMoves, unsigned int *PMaxCubeLength, unsigned int *PFMKInd, unsigned int *PNumOfCubes)
{
	printf("\n[!]PLEASE ENTER YOUR KEY\n");
	//Переменная для определения размера выделяемой памяти
	unsigned long int ind;
	unsigned int memory;
	memory = 1;
	ind = 0;
	//Переменная получающая ввод с клавиатуры
	char key;

	while ((key = getchar()) != '\n'){
		if (memory <= ind)
			memory = memory * 2;
		MainKey = (char*)realloc(MainKey, memory * sizeof(char));
		MainKey[ind] = key;
		++ind;
	}
	*PLengthOfKey = ind;
	MainKey = (char*)realloc(MainKey, ind * sizeof(char));

	//Обнуляем индекс
	ind = 0;
	while (key != ':'){
		key = MainKey[ind];
		++ind;
		if (key != ':'){
			*PLenOfText = *PLenOfText + (key - 48);
		}
		if (key != ':'){
			*PLenOfText = *PLenOfText * 10;
		}
	}
	*PLenOfText = *PLenOfText / 10;
	//printf("LenOfText: %i\n", LenOfText);

	key = '\0';
	while (key != ':'){
		key = MainKey[ind];
		++ind;
		if (key != ':'){
			*PNumOfMoves = *PNumOfMoves + (key - 48);
		}
		if (key != ':'){
			*PNumOfMoves = *PNumOfMoves * 10;
		}
	}
	*PNumOfMoves = *PNumOfMoves / 10;

	key = '\0';
	while (key != ':'){
		key = MainKey[ind];
		++ind;
		if (key != ':'){
			*PMaxCubeLength = *PMaxCubeLength + (key - 48);
		}
		if (key != ':'){
			*PMaxCubeLength = *PMaxCubeLength * 10;
		}
	}
	*PMaxCubeLength = *PMaxCubeLength / 10;

	key = '\0';
	while (key != ':'){
		key = MainKey[ind];
		++ind;
		if (key != ':'){
			*PNumOfCubes = *PNumOfCubes + (key - 48);
		}
		if (key != ':'){
			*PNumOfCubes = *PNumOfCubes * 10;
		}
	}
	*PNumOfCubes = *PNumOfCubes / 10;

	*PLengthOfKey = *PLengthOfKey - ind;
	for (int i = 0; i < *PLengthOfKey; ++i)
	{
		MainKey[i] = MainKey[i+ind];
	}

	char MBuf;
	int ind1 = *PLengthOfKey - 1;
	int ind2 = 0;
	while (((ind2 - 1) != ind1) && (ind2 != ind1)){
		MBuf = MainKey[ind2];
		MainKey[ind2] = MainKey[ind1];
		MainKey[ind1] = MBuf;
		++ind2;
		--ind1;
	}
	
	key = '\0';
	ind2 = 0;
	while (key != '-'){
		key = MainKey[ind2];
		++ind2;
		(*PFMKInd)++;
	}

	/*for (int i = 0; i < *PLengthOfKey; ++i)
	{
		printf("%c", MainKey[i]);
	}*/
}

void GetNumOfCubes (unsigned long int Length, unsigned int *PNumOfCubes, unsigned int MaxCubeLength)
{
	unsigned long int LLength = Length;
	//Определение кол-ва кубов
	while (LLength > 0){
		LLength = LLength - MaxCubeLength;
		(*PNumOfCubes)++;
	}

	if ((LLength + MaxCubeLength) < 0){
		(*PNumOfCubes)--;
	}
	
	/*if (*PLength > *PMaxCubeLength){
		*PNumOfCubes = *PLength / *PMaxCubeLength;
	}*/
	return;
}

//Функция разделения текста на части для последующего шифрования.
void MoreBufs (unsigned long int *PCountChar, unsigned long int *PICountChar, unsigned long int *PLength, unsigned int *PLenOfCube, unsigned int *PMaxCubeLength, unsigned int *PNumOfCycles)
{
	unsigned long int SBInd = 0;

	//Размер куба.
	size = 0;

	//Длинна текста заносимого в куб.
	*PLenOfCube = 0;

	unsigned long int ind = *PLength - (*PCountChar);
	if (ind > *PMaxCubeLength){
		*PLenOfCube = *PMaxCubeLength;
		SecondBufer = (char*)calloc(*PMaxCubeLength, sizeof(char));
		for (unsigned long int i = *PICountChar; i < (*PMaxCubeLength + (*PMaxCubeLength * (*PNumOfCycles))) ; ++i){
			SecondBufer[SBInd] = bufer[i];
			++SBInd;
			(*PCountChar)++;
		}
		(*PNumOfCycles)++;
	}
	else{
		*PLenOfCube = 0;
		SecondBufer = (char*)calloc(ind, sizeof(char));
		for (unsigned long int j = *PICountChar; j < *PLength; ++j)
		{
			SecondBufer[SBInd] = bufer[j];
			++SBInd;
			(*PLenOfCube)++;
			(*PCountChar)++;
		}
	}
	*PICountChar = *PCountChar;

	//Определение размера куба.
	while ((size*size*SIDESCOUNT) < *PLenOfCube || size < 3){
		++size;
	}
}

//Заполнение 3 мерного массива значениями из буфера.
void SidesFill (unsigned long int *PLength, unsigned int *PLenOfCube)
{
	unsigned char Oz = SIDESCOUNT;
	unsigned int Ox = size;
	unsigned int Oy = size;
	

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
				if (SBInd <= *PLength){
				sides[z][x][y] = SecondBufer[SBInd];
				++SBInd;
				}
				if (SBInd > *PLenOfCube){
					
					ind = rand()%3;
					switch(ind){
						case 0:
							RandomSym = rand()%(57-48) + 48;
							break;
						case 1:
							RandomSym = rand()%(90-65) + 65;
							break;
						case 2:
							RandomSym = rand()%(122-97) + 97;
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
		}*/
		printf("\n");
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

void DecryptText (unsigned int *PNumOfMoves, unsigned int *PMKInd, unsigned int *PCurrentLoop, unsigned int *PNumOfCubes, unsigned int *PFMKInd)
{
	char key;
	int CurrentMove = 0;
	*PMKInd = *PFMKInd + 1;


	if (*PCurrentLoop == (*PNumOfCubes - 1))
		*PMKInd = 1;
	// printf("\nPMKIND: %i\n", *PMKInd);
	while (CurrentMove < *PNumOfMoves){
		key = MainKey[*PMKInd];
		// printf("\n1KEY = %c\n", key);
		switch(key){
			case'_':
				// printf("\n2KEY = %c\n", key);
				(*PMKInd)++;
				key = MainKey[*PMKInd];
				// printf("\n3KEY = %c\n", key);
				switch(key){
					case'9':
						(*PMKInd)++;
						key = MainKey[*PMKInd];
						key = key - 48;
						EMove(key);
						// printf("\nEMove line:%d\n", key);
						break;
					case'8':
						(*PMKInd)++;
						key = MainKey[*PMKInd];
						key = key - 48;
						SMove(key);
						// printf("\nSMove line:%d\n", key);
						break;
					case'7':
						(*PMKInd)++;
						key = MainKey[*PMKInd];
						key = key - 48;
						MMove(key);
						// printf("\nMMove line:%d\n", key);
						break;
					case'6':
						RMove();
						break;
					case'5':
						LMove();
						break;
					case'4':
						DMove();
						break;
					case'3':
						BMove();
						break;
					case'2':
						UMove();
						break;
					case'1':
						FMove();
						break;
				}
				break;
			case'0':
				CounterFMove();
				break;
			case'1':
				CounterUMove();
				break;
			case'2':
				CounterBMove();
				break;
			case'3':
				CounterDMove();
				break;
			case'4':
				CounterLMove();
				break;
			case'5':
				CounterRMove();
				break;
			case'6':
				(*PMKInd)++;
				key = MainKey[*PMKInd];
				key = key - 48;
				CounterMMove(key);
				// printf("\nCounterMMove line:%d\n", key);
				break;
			case'7':
				(*PMKInd)++;
				key = MainKey[*PMKInd];
				key = key - 48;
				CounterSMove(key);
				// printf("\nCounterSMove line:%d\n", key);
				break;
			case'8':
				(*PMKInd)++;
				key = MainKey[*PMKInd];
				key = key - 48;
				CounterEMove(key);
				// printf("\nCounterEMove line:%d\n", key);
				break;
			default:
				--CurrentMove;
				break;
		}
		++CurrentMove;
		(*PMKInd)++;
	}
}

void GetDecryptedText (unsigned long int *PCBInd)
{
	for (int z = 0; z < SIDESCOUNT; ++z)
	{
		for (int x = 0; x < size; ++x)
		{
			for (int y = 0; y < size; ++y)
			{
				DecryptedBufer[*PCBInd] = sides[z][x][y];
				(*PCBInd)++;
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

void CmdDecryptedText (unsigned long int *PLenOfText)
{
	printf("\r\n[!]DECRYPTED TEXT:\r\n");
	for (int i = 0; i < *PLenOfText; ++i)
	{
		if (DecryptedBufer[i] == '~')
			DecryptedBufer[i] = '\n';
		printf("%c", DecryptedBufer[i]);
	}
	free(DecryptedBufer);
	free(MainKey);
}

void TxtDecryptedText (unsigned long int *PLenOfText)
{
	FILE *file;
	file = fopen("C:/c/Decrypted.txt", "w");

	for (unsigned long int i = 0; i < *PLenOfText; ++i)
	{
		if (DecryptedBufer[i] == '~')
			DecryptedBufer[i] = '\n';
		fprintf(file, "%c", DecryptedBufer[i]);
	}
	free(DecryptedBufer);
	free(MainKey);
	printf("\n[+]DECRYPTION WAS FINISHED DECRYPTED TEXT SAVED IN *Decrypted.txt*\n");
}

//Ну, тип сердце моей проги... Точка входа.
int main (void)
{	

	//Эти две переменные позволяют сохранять значение последнего введенного символа.
	unsigned long int CountChar = 0; 
	unsigned long int ICountChar = 0;

	//length - длинна введенной строки.
	unsigned long int length = 0;

	//Длинна текста.
	unsigned long int LenOfText = 0;

	//Length of cube - длинна строки в 1 кубе.
	unsigned int LengthOfCube = 0;

	//Индекс буфера массив 
	unsigned long int CBInd = 0;

	//Длинна 
	unsigned int LengthOfKey = 0;
	unsigned int NumOfMoves = 0;
	unsigned int MaxCubeLength = 0;

	//Кол-во кубов - ОБЯЗАТЕЛЬНАЯ
	unsigned int NumOfCubes = 0;

	//Переменная отвечающая за идекс в функции MoreBufs
	unsigned int NumOfCycles = 0;

	//1 т.к. 1 всегда идет буква.
	unsigned int MKInd = 1;
	unsigned int FMKInd = 0;
	//Данный цикл
	unsigned int CurrentLoop = 0;
	//Переменные времени
	unsigned int time1 = 0;
	unsigned int time2 = 0;
	unsigned int time3 = 0;
	unsigned int time4 = 0;

	time1 = clock();
	printf("\nCryptoCube V%s\n", VERSION);

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
			CmdGetTextnLength(&length);
			break;
		case '2':
			TChoseInd = 2;
			TxtGetTextnLength(&length);
			break;
		default:
			break;
		}
	}

	GetKey(&LenOfText, &LengthOfKey, &NumOfMoves, &MaxCubeLength, &FMKInd, &NumOfCubes);
	// printf("\nLength: %i ;MaxCubeLength : %i\n", length, MaxCubeLength);
	// printf("\n%d\n", NumOfCubes);
	time2 = clock();
	for (CurrentLoop = 0; CurrentLoop < NumOfCubes; ++CurrentLoop)
	{
		//Заполнение доп. буфера
		MoreBufs(&CountChar, &ICountChar, &length, &LengthOfCube, &MaxCubeLength, &NumOfCycles);
		//Заполнение 3 мерного массива.
		SidesFill(&length, &LengthOfCube);
		// printf("\nFILL SIDES\n");
		// SidesVisual();
		//Функции выполнения сдвига в случайном порядке и получения ключа.
		DecryptText(&NumOfMoves, &MKInd, &CurrentLoop, &NumOfCubes, &FMKInd);
		// printf("\nCHANGED SIDES\n");
		// SidesVisual();
		//Получение частей зашифрованного текста.
		GetDecryptedText(&CBInd);
		//Освобождение трех мерного массива.
		FreeSides();
		// printf("CLOOP: %i\n", CurrentLoop);
	}
	time3 = clock();
	switch(TChoseInd){
		case 1:
			CmdDecryptedText(&LenOfText);
			break;
		case 2:
			TxtDecryptedText(&LenOfText);
			break;
	}
	time4 = clock();
	printf("\n[*]TYPE ENTER TO CLOSE PROGRAMM\n");
	printf("[+]TIME:\nThe whole time: %i\nprogramm time: %i\nJust moves: %i\n", time4, (time4 - time1), (time3 - time2));
	getchar();
	return EXIT_SUCCESS;
}
//Ну крч... я понял как избавиться от части глобальных переменных, а может и от всех 
//нужно просто сохранить её адрес, передать его в функцию и менять значения по адресу.
//Почему - то онн берет не то движение...
//Крч, проблема в том, что программа берет 1 лишний куб... Нужно сделать перерассчет в функции GetNumOfCubes();
