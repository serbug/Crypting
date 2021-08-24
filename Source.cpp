/////////////////////////////////
///                           ///
///      AUTHOR:  B. S.       ///
///      TEL: 060685260       ///  
///                           ///
/////////////////////////////////

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h> // Libraria pentru culori text, marime consola, ect.
#include <MMsystem.h> // Libraria pentru redarea fisierelor audio format .wav in preprocesor trebuie sa fie inclus si winmm.lib 
#include <time.h>  // Libraria ce lucreaza cu timpul


using namespace std;

HANDLE f1;  // variabila pentru culoare text
FILE *f;    // variabila pentru fisier
HWND console = GetConsoleWindow(); // marimea consolei
RECT r;   // variabila pentru consola

int i, j, n;
char meniu, o, file[20], file1[20], pass[30];


void criptare();           // functia criptare mesaj
void creare();             // functia creare mesaj pentru criptare
void decriptare();         // functia decriptare mesaj
void menu();               // functia afisare menu principal 
void afisarecript();       // functia afisare mesaj criptat
void afisaredecript();     // functia afisare mesaj decriptat
void gotoxy(int a, int b); // functia de pozitionare 
void player();             // functia pentru redarea audio
void autor();              // eticheta
void date_time();          // functia ora si data calculatorului 
void criptare_fisier();    // functia de cryptare fisier .txt

typedef struct crypt
{
	char fisier[1000], password[30];
}cry;

cry x[10];

void main()
{

	f1 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetWindowRect(console, &r); //stores the console's current dimensions

	autor();

m: system("cls");
	MoveWindow(console, r.left, r.top, 800, 800, TRUE);
	menu();

	meniu = _getch();

	switch (meniu)
	{
	case '1': system("cls");  creare(); criptare();  _getch(); goto m;
	case '2': system("cls");  decriptare(); _getch(); goto m;
	case '3': system("cls");  afisaredecript(); _getch(); goto m;
	case '4': system("cls");  afisarecript(); _getch(); goto m;
	case '5': system("cls");  player(); _getch(); goto m;
	case '6': system("cls");  criptare_fisier(); criptare();  goto m;
	case '7': system("cls");  exit(1);

	default: SetConsoleTextAttribute(f1, 12); cout << "\n\n\n\t\t\t\t Ati tastat un buton necorespunzator !"; _getch(); goto m;
	}

	_getch();
}

void criptare()
{

	n = strlen(x[i].fisier);

	for (j = 0; j < n; j++)
	{
		x[i].fisier[j] += n;
		_strrev(x[i].fisier);
	}
	SetConsoleTextAttribute(f1, 15);
	cout << "\n\n\n -> Dati un nume fisierului (.txt): ";  SetConsoleTextAttribute(f1, 10); cin >> file; _strupr(file);
	f = fopen(file, "w+");

	fwrite(&x[i], sizeof(x[i]), 1, f);

	fclose(f);

	_getch();

}

void decriptare()
{
	clock_t start = clock(), diff; // start timer, diff este o variabila 

	SetConsoleTextAttribute(f1, 15);
	cout << " \n\n\n -> Introduceti denumirea fisierului criptat (.txt): "; SetConsoleTextAttribute(f1, 10); cin >> file; _strupr(file);
	f = fopen(file, "r+");
	if (f == NULL)
	{
		printf("\n\n Ati introdus un nume gresit fisierului sau fisierul cu acest nume -> %s <- nu exista !", file);
		return;
	}

	while (fread(&x[i], sizeof(x[i]), 1, f) == 1)

		fclose(f);
m:
	system("cls");
	SetConsoleTextAttribute(f1, 10);
	gotoxy(65,1); date_time();
	SetConsoleTextAttribute(f1, 14);
	cout << "\n\n\t --> Aveti la dispozitie 30 secunde pentru a introduce password corect !";
	SetConsoleTextAttribute(f1, 15);
	cout << "\n\n\n * Introduceti passwordul fisierului: ";
	SetConsoleTextAttribute(f1, 10);
	cin >> pass;

	_strupr(pass);

	if (strcmp(x[i].password, pass) == 0)
	{
		n = strlen(x[i].fisier);

		for (j = 0; j < n; j++)
		{
			x[i].fisier[j] -= n;
			_strrev(x[i].fisier);
		}
		SetConsoleTextAttribute(f1, 15);
		cout << " \n\n\n -> Dati un nume fisierului decriptat: "; SetConsoleTextAttribute(f1, 10); cin >> file1; _strupr(file1);
		f = fopen(file1, "w+");

		fwrite(&x[i], sizeof(x[i]), 1, f);

		fclose(f);
	}
	else
	{
		system("cls");
		printf("\n\n\t\t\t\t * Password incorect !");

		diff = clock() - start; 

		SetConsoleTextAttribute(f1, 15);
		int msec = diff * 1000 / CLOCKS_PER_SEC;
		printf("\n\n\t\t\t\t 00 m : %d s : %d ms", msec / 1000, msec % 1000); //timer

		if (msec / 1000 >= 30)
		{
			remove(file);
			SetConsoleTextAttribute(f1, 10);
			printf("\n\n\t\t Fisierul Criptat a fost sters din motive de securitate ! ");
		}
		else
		{
			SetConsoleTextAttribute(f1, 14);
			cout << "\n\n\n\t\t\t - > Doriti sa reincercati? Y/N \n\n"; o = _getch();

			if (o == 'y' || o == 'Y')
			{
				goto m;
			}
		}
	}


}
void creare()
{
	SetConsoleTextAttribute(f1, 14);
	cout << "\n * Introduceti mesajul pentru criptare: ";
	SetConsoleTextAttribute(f1, 10);
	
	cin.get(); // tampon de intrare 
	
	gets_s(x[i].fisier); 

    //cin.clear(); cin.ignore(); 
	
	SetConsoleTextAttribute(f1, 15);
	cout << "\n\n * Introduceti un password fisierului: ";
	SetConsoleTextAttribute(f1, 10); cin >> x[i].password;

	_strupr(x[i].password);


}
void menu()
{
	puts("\n\n\n");
	SetConsoleTextAttribute(f1, 10);
	printf(R"EOF(
                              ___  ____  __  ____  ____  __  __ _   ___ 
                             / __)(  _ \(  )(  _ \(_  _)(  )(  ( \ / __)
                            ( (__  )   / )(  ) __/  )(   )( /    /( (_ \
                             \___)(__\_)(__)(__)   (__) (__)\_)__) \___/
         )EOF");

	SetConsoleTextAttribute(f1, 14);
	cout << "\n\n\n\n\n\t\t|#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#|";
	cout << "\n\t\t|#|---------------------------------------------------------------|#|";
	cout << "\n\t\t|#|                                                               |#|";
	cout << "\n\t\t|#|                  ---> CRIPTAREA DATELOR <---                  |#|";
	cout << "\n\t\t|#|                                                               |#|";
	cout << "\n\t\t|#|---------------------------------------------------------------|#|";
	SetConsoleTextAttribute(f1, 15); cout << "\n\t\t|#|                               |                               |#|";
	cout << "\n\t\t|#|  1 -> CREARE MESAJ CRIPTAT    |    2 -> DECRIPTARE MESAJ      |#|";
	cout << "\n\t\t|#|                               |                               |#|";
	cout << "\n\t\t|#|---------------------------------------------------------------|#|";
	cout << "\n\t\t|#|                               |                               |#|";
	cout << "\n\t\t|#|  3 -> AFISARE MESAJ DECRIPTAT |    4 -> AFISARE MESAJ CRIPTAT |#|";
	cout << "\n\t\t|#|                               |                               |#|";
	cout << "\n\t\t|#|---------------------------------------------------------------|#|";
	cout << "\n\t\t|#|                               |                               |#|";
	cout << "\n\t\t|#|  5 -> MUSIC PLAYER            |    6 -> CRIPTARE FISIER .TXT  |#|";
	cout << "\n\t\t|#|                               |                               |#|";
	cout << "\n\t\t|#|---------------------------------------------------------------|#|";
	cout << "\n\t\t|#|                                                               |#|";
	cout << "\n\t\t|#|                         7 -> Iesire                           |#|";
	cout << "\n\t\t|#|                                                               |#|";
	cout << "\n\t\t|#|---------------------------------------------------------------|#|";
	cout << "\n\t\t|#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#||#|\n\n";
}
void afisarecript()
{
	SetConsoleTextAttribute(f1, 15);
	cout << " \n\n\n -> Introduceti denumirea fisierului criptat (.txt): "; SetConsoleTextAttribute(f1, 10); cin >> file; _strupr(file);

	f = fopen(file, "r+");
	if (f == NULL)
	{
		printf("\n\n Ati introdus un nume gresit fisierului sau fisierul cu acest nume -> %s <- nu exista !", file);
		return;
	}
	while (fread(&x[i], sizeof(x[i]), 1, f) == 1)

		fclose(f);
	system("cls");
	SetConsoleTextAttribute(f1, 15);
	cout << "\n\n * Mesajul criptat:"; SetConsoleTextAttribute(f1, 10); cout << "\n\n\n " << x[i].fisier;


	_getch();

}
void afisaredecript()
{
	SetConsoleTextAttribute(f1, 15);
	cout << " \n\n\n -> Introduceti denumirea fisierului decriptat (.txt): "; SetConsoleTextAttribute(f1, 10); cin >> file1; _strupr(file1);

	f = fopen(file1, "r+");
	if (f == NULL)
	{
		printf("\n\n Ati introdus un nume gresit fisierului sau fisierul cu acest nume -> %s <- nu exista !", file1);
		return;
	}
	while (fread(&x[i], sizeof(x[i]), 1, f) == 1)

		fclose(f);
	system("cls");
	SetConsoleTextAttribute(f1, 15);
	cout << "\n\n * Mesajul decriptat:"; SetConsoleTextAttribute(f1, 10); cout << "\n\n\n " << x[i].fisier;

	_getch();
}

void player()
{
m:
	system("cls");
	MoveWindow(console, r.left, r.top, 650, 650, TRUE);

	SetConsoleTextAttribute(f1, 10);
	printf(R"EOF(
       __        ____     _____   _____                  __      
      _\ \ _    /\  _`\  /\  __`\/\  __`\  /'\_/`\      _\ \ _   
     /\_` ' \   \ \ \L\ \\ \ \/\ \ \ \/\ \/\      \    /\_` ' \  
     \/_>   <_   \ \  _ <'\ \ \ \ \ \ \ \ \ \ \__\ \   \/_>   <_ 
       /\_, ,_\   \ \ \L\ \\ \ \_\ \ \ \_\ \ \ \_/\ \    /\_, ,_\
       \/_/\_\/    \ \____/ \ \_____\ \_____\ \_\\ \_\   \/_/\_\/
          \/_/      \/___/   \/_____/\/_____/\/_/ \/_/      \/_/ 
                                                                 
     )EOF");

	SetConsoleTextAttribute(f1, 12);
	gotoxy(13, 15); cout << "|*||*||*||*||*||*||*||*||*||*||*||*||*||*||*||*|";
	gotoxy(13, 16); cout << "|*|                     |                    |*|";
	gotoxy(13, 17); cout << "|*| "; SetConsoleTextAttribute(f1, 15); gotoxy(19, 17); cout << "  1 -> PLAYER   "; SetConsoleTextAttribute(f1, 12); gotoxy(36, 17); cout << " | "; SetConsoleTextAttribute(f1, 15); gotoxy(41, 17); cout << "  2 -> STOP "; gotoxy(57, 17); SetConsoleTextAttribute(f1, 12); cout << " |*| ";
	gotoxy(13, 18); cout << "|*|                     |                    |*|";
	gotoxy(13, 19); cout << "|*||*||*||*||*||*||*||*||*||*||*||*||*||*||*||*|";
	SetConsoleTextAttribute(f1, 14);
	gotoxy(12, 22); cout << "Press < ENTER > to return MENU CRIPTAREA DATELOR !";
	printf("\n\n"); o = _getch();

	if (o == '1')
	{
	m1: system("cls");
		MoveWindow(console, r.left, r.top, 650, 650, TRUE);
		SetConsoleTextAttribute(f1, 10);
		printf(R"EOF(
                  :::::::::  :::            :::   :::   ::: 
                  :+:    :+: :+:          :+: :+: :+:   :+: 
                  +:+    +:+ +:+         +:+   +:+ +:+ +:+  
                  +#++:++#+  +#+        +#++:++#++: +#++:   
                  +#+        +#+        +#+     +#+  +#+    
                  #+#        #+#        #+#     #+#  #+#    
                  ###        ########## ###     ###  ###    
			)EOF");
		SetConsoleTextAttribute(f1, 15);
		gotoxy(13, 10); cout << "|*||*||*||*||*||*||*||*||*||*||*||*||*||*||*||*|";
		gotoxy(13, 11); cout << "|*|                     |                    |*|";
		gotoxy(13, 12); cout << "|*| "; SetConsoleTextAttribute(f1, 12); gotoxy(19, 12); cout << "  1 -> SONG A   "; SetConsoleTextAttribute(f1, 15); gotoxy(36, 12); cout << " | "; SetConsoleTextAttribute(f1, 12); gotoxy(41, 12); cout << "  2 -> SONG B "; gotoxy(57, 12); SetConsoleTextAttribute(f1, 15); cout << " |*| ";
		gotoxy(13, 13); cout << "|*|                     |                    |*|";
		gotoxy(13, 14); cout << "|*||*||*||*||*||*||*||*||*||*||*||*||*||*||*||*|";
		gotoxy(13, 15); cout << "|*|                     |                    |*|";
		gotoxy(13, 16); cout << "|*| "; SetConsoleTextAttribute(f1, 12); gotoxy(19, 16); cout << "  3 -> SONG C   "; SetConsoleTextAttribute(f1, 15); gotoxy(36, 16); cout << " | "; SetConsoleTextAttribute(f1, 12); gotoxy(41, 16); cout << "  4 -> SONG D "; gotoxy(57, 16); SetConsoleTextAttribute(f1, 15); cout << " |*| ";
		gotoxy(13, 17); cout << "|*|                     |                    |*|";
		gotoxy(13, 18); cout << "|*||*||*||*||*||*||*||*||*||*||*||*||*||*||*||*|";
		gotoxy(13, 19); cout << "|*|                     |                    |*|";
		gotoxy(13, 20); cout << "|*| "; SetConsoleTextAttribute(f1, 12); gotoxy(19, 20); cout << "  5 -> SONG E   "; SetConsoleTextAttribute(f1, 15); gotoxy(36, 20); cout << " | "; SetConsoleTextAttribute(f1, 12); gotoxy(41, 20); cout << "  6 -> SONG F "; gotoxy(57, 20); SetConsoleTextAttribute(f1, 15); cout << " |*| ";
		gotoxy(13, 21); cout << "|*|                     |                    |*|";
		gotoxy(13, 22); cout << "|*||*||*||*||*||*||*||*||*||*||*||*||*||*||*||*|";
		gotoxy(13, 23); cout << "|*|                     |                    |*|";
		gotoxy(13, 24); cout << "|*| "; SetConsoleTextAttribute(f1, 12); gotoxy(19, 24); cout << "  7 -> SONG G   "; SetConsoleTextAttribute(f1, 15); gotoxy(36, 24); cout << " | "; SetConsoleTextAttribute(f1, 12); gotoxy(41, 24); cout << "  8 -> SONG H "; gotoxy(57, 24); SetConsoleTextAttribute(f1, 15); cout << " |*| ";
		gotoxy(13, 25); cout << "|*|                     |                    |*|";
		gotoxy(13, 26); cout << "|*||*||*||*||*||*||*||*||*||*||*||*||*||*||*||*|";
		gotoxy(13, 27); cout << "|*|                     |                    |*|";
		gotoxy(13, 28); cout << "|*| "; SetConsoleTextAttribute(f1, 12); gotoxy(19, 28); cout << "  9 -> SONG I   "; SetConsoleTextAttribute(f1, 15); gotoxy(36, 28); cout << " | "; SetConsoleTextAttribute(f1, 12); gotoxy(41, 28); cout << "  0 -> IESIRE "; gotoxy(57, 28); SetConsoleTextAttribute(f1, 15); cout << " |*| ";
		gotoxy(13, 29); cout << "|*|                     |                    |*|";
		gotoxy(13, 30); cout << "|*||*||*||*||*||*||*||*||*||*||*||*||*||*||*||*|\n\n";

		meniu = _getch();

		switch (meniu)
		{
		case '1': { PlaySound(TEXT("music/muz1.wav"), NULL, SND_LOOP | SND_ASYNC);  goto m1; }

		case '2': {PlaySound(TEXT("music/muz2.wav"), NULL, SND_LOOP | SND_ASYNC); goto m1; }

		case '3': { PlaySound(TEXT("music/muz3.wav"), NULL, SND_LOOP | SND_ASYNC); goto m1; }

		case '4': {PlaySound(TEXT("music/muz4.wav"), NULL, SND_LOOP | SND_ASYNC); goto m1; }

		case '5': {PlaySound(TEXT("music/muz5.wav"), NULL, SND_LOOP | SND_ASYNC); goto m1; }

		case '6': {PlaySound(TEXT("music/muz6.wav"), NULL, SND_LOOP | SND_ASYNC); goto m1; }

		case '7': {PlaySound(TEXT("music/muz7.wav"), NULL, SND_LOOP | SND_ASYNC); goto m1; }

		case '8': { PlaySound(TEXT("music/muz8.wav"), NULL, SND_LOOP | SND_ASYNC); goto m1; }

		case '9': {PlaySound(TEXT("music/muz9.wav"), NULL, SND_LOOP | SND_ASYNC); goto m1; }

		case '0': { goto m; }

		default: cout << "\n\n\n\t\t * Ati tastat un buton necorespunzator !"; _getch(); goto m1;
		}

	}
	else if (o == '2')
	{
		MoveWindow(console, r.left, r.top, 500, 500, TRUE);
		system("cls");

		PlaySound(NULL, 0, 0);
	}

}
void gotoxy(int a, int b)
{
	HANDLE hConsoleOutput;
	COORD ord;
	cout.flush();
	ord.X = a;
	ord.Y = b;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, ord);
}
void autor()
{
	MoveWindow(console, r.left, r.top, 800, 800, TRUE);
	system("Color 0C");

	SetConsoleTextAttribute(f1, 9); cout << "\n\n\t\t\t ############"; SetConsoleTextAttribute(f1, 14); cout << "############"; SetConsoleTextAttribute(f1, 12); cout << "############";
	SetConsoleTextAttribute(f1, 9); cout << "\n\t\t\t ############"; SetConsoleTextAttribute(f1, 14); cout << "############"; SetConsoleTextAttribute(f1, 12); cout << "############";
	SetConsoleTextAttribute(f1, 9); cout << "\n\t\t\t ############"; SetConsoleTextAttribute(f1, 14); cout << "############"; SetConsoleTextAttribute(f1, 12); cout << "############";
	SetConsoleTextAttribute(f1, 9); cout << "\n\t\t\t ############"; SetConsoleTextAttribute(f1, 14); cout << "############"; SetConsoleTextAttribute(f1, 12); cout << "############";
	SetConsoleTextAttribute(f1, 9); cout << "\n\t\t\t ############"; SetConsoleTextAttribute(f1, 14); cout << "############"; SetConsoleTextAttribute(f1, 12); cout << "############";
	SetConsoleTextAttribute(f1, 9); cout << "\n\t\t\t ############"; SetConsoleTextAttribute(f1, 14); cout << "############"; SetConsoleTextAttribute(f1, 12); cout << "############";
	printf("\n\n\n\n"); printf(R"EOF(
              ______  __    __ ________ __    __  ______  _______  
             /      \/  |  /  /        /  |  /  |/      \/       \ 
            /$$$$$$  $$ |  $$ $$$$$$$$/$$ |  $$ /$$$$$$  $$$$$$$  |
            $$ |__$$ $$ |  $$ |  $$ |  $$ |__$$ $$ |  $$ $$ |__$$ |
            $$    $$ $$ |  $$ |  $$ |  $$    $$ $$ |  $$ $$    $$< 
            $$$$$$$$ $$ |  $$ |  $$ |  $$$$$$$$ $$ |  $$ $$$$$$$  |
            $$ |  $$ $$ \__$$ |  $$ |  $$ |  $$ $$ \__$$ $$ |  $$ |
            $$ |  $$ $$    $$/   $$ |  $$ |  $$ $$    $$/$$ |  $$ |
            $$/   $$/ $$$$$$/    $$/   $$/   $$/ $$$$$$/ $$/   $$/ 
		)EOF");
	printf("\n\n"); printf(R"EOF(
                        $$$$$$$\            $$$$$$\                 
                        $$  __$$\          $$  __$$\                
                        $$ |  $$ |         $$ /  \__|               
                        $$$$$$$\ |         \$$$$$$\                 
                        $$  __$$\           \____$$\                
                        $$ |  $$ |         $$\   $$ |               
                        $$$$$$$  $$\       \$$$$$$  $$\             
                        \_______/\__|       \______/\__|            

						)EOF");
	SetConsoleTextAttribute(f1, 10);
	printf("\n\n\t\t\t Press < ENTER > to continue...!");
	_getch();
	system("cls");
	MoveWindow(console, r.left, r.top, 800, 400, TRUE);
	SetConsoleTextAttribute(f1, 12);
	gotoxy(38, 3); printf("### RECOMANDARI ###");
	SetConsoleTextAttribute(f1, 15);
	printf("\n\n\n * Fisierele Criptate trebuie sa fie denumite ( ex: Crypting.txt ) ! \n\n\n * Fisierele decryptate la fel trebuie sa fie denumite ( ex: Decrypting.txt ) ! \n\n\n * Fisierul criptat trebuie sa contina password ! \n\n\n * Daca gasiti ceva erori anuntati-ma !");
	SetConsoleTextAttribute(f1, 10);
	cout << "\n\n\n\t\t Press < ENTER > to continue...!";
	_getch();
}
void date_time()
{
	time_t current_time;
	char* c_time_string;

	/* Obtain current time. */
	current_time = time(NULL);

	if (current_time == ((time_t)-1))
	{
		(void)fprintf(stderr, "Failure to obtain the current time.\n");
		exit(EXIT_FAILURE);
	}

	/* Convert to local time format. */
	c_time_string = ctime(&current_time);

	if (c_time_string == NULL)
	{
		(void)fprintf(stderr, "Failure to convert the current time.\n");
		exit(EXIT_FAILURE);
	}

	/* Print to stdout. ctime() has already added a terminating newline character. */
	(void)printf("%s", c_time_string);
	//exit(EXIT_SUCCESS);
}
void criptare_fisier()
{
	SetConsoleTextAttribute(f1, 15);
	cout << " \n\n\n -> Introduceti denumirea fisierului pentru criptare (.txt): "; SetConsoleTextAttribute(f1, 10); cin >> file; _strupr(file);

	SetConsoleTextAttribute(f1, 15);
	cout << "\n\n * Introduceti un password fisierului: ";
	SetConsoleTextAttribute(f1, 10); cin >> x[i].password;

	_strupr(x[i].password);

	f = fopen(file, "r+");
	if (f == NULL)
	{
		printf("\n\n Ati introdus un nume gresit fisierului sau fisierul cu acest nume -> %s <- nu exista !", file);
		return;
	}

	while (fread(&x[i], sizeof(x[i]), 1, f) == 1)

		fclose(f);

	_getch();
	SetConsoleTextAttribute(f1, 14);
	printf(" \n\n\t\t Fisierului criptat trebuie sai dati un alt nume diferit de cel original !");
}