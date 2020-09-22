#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

void afisare_matrice(int n, int m, int** a)
{
	system("cls");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			if (a[i][j] == 0) printf(". ");
			else printf("x ");
		printf("\n");
	}
}
void afisare_fisier(int n, int m, int** a, char* file_out)
{
	FILE* f = fopen(file_out, "w");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			fprintf(f, "%d ", a[i][j]);
		fprintf(f, "\n");
	}
}
int** alocare_matrice(int n, int m)
{
	int** matr = NULL;
	matr = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++)
		matr[i] = (int*)malloc(sizeof(int) * m);
	return matr;
}

int return_m(char* file_in, char* file_out, int mode, int x)
{
	int n, m = 0;
	FILE* f = fopen(file_in, "r");
	if (f != NULL)
	{
		if (mode == 0 || mode == 2)
			fscanf(f, "%d%d", &n, &m);
		else if (mode == 1)
		{
			x--;
			fseek(f, SEEK_SET, SEEK_END);
			m = ((ftell(f) / 2) / x);
		}
	}
	return m;
}

int return_n(char* file_in, char* file_out, int mode)
{
	int n = 0, m = 0;
	FILE* f = fopen(file_in, "r");
	char buffer;
	int nr = 0;
	if (f != NULL)
	{
		if (mode == 0 || mode == 2)
		{
			fscanf(f, "%d%d", &n, &m);
			rewind(f);
		}
		else if (mode == 1)
		{
			while (!feof(f))
			{
				fscanf(f, "%c", &buffer);
				if (buffer == '\n') nr++;
			}
			nr++;
			n = nr;
		}
	}
	else {
		printf("NU");
	}
	return n;
}

int numar_caractere(char* file_in)
{
	FILE* f = fopen(file_in, "r");
	char a;
	int nr = 0;
	if (f != NULL)
	{
		while (!feof(f))
		{
			fscanf(f, "%c", &a);
			if (a == '\n') nr++;
			else if (a == ' ') nr++;
		}
		nr++;
	}
	return nr;
}

int** zero(int** matrice, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matrice[i][j] = 0;
	return matrice;
}

int** citire(char* file_in, char* file_out, int mode)
{
	int** matrice = NULL;
	FILE* f = fopen(file_in, "r");
	FILE* g = fopen(file_out, "w");
	int n = 0, m = 0, i = 0, j = 0, max = 0, nr = 0, spatii = 0, x = 0, y = 0;
	if (f == NULL)
		fprintf(g, "%s", "Fisierul nu exista!");
	else {
		if (mode == 0 || mode == 2) {
			fscanf(f, "%d%d", &n, &m);
		}
		else if (mode == 1) {
			spatii = numar_caractere(file_in);
			max = spatii;
			n = return_n(file_in, file_out, 1);
			m = max / n;
		}
		if (n < 3 || m < 3)
			fprintf(g, "%s", "Configuratie invalida");
		else {
			matrice = alocare_matrice(n, m);
			if (mode == 0 || mode == 1) {
				for (int i = 0; i < n; i++)
					for (int j = 0; j < m; j++)
						fscanf(f, "%d", &matrice[i][j]);
			}
			else if (mode == 2) {
				matrice = zero(matrice, n, m);
				while (!feof(f))
				{
					fscanf(f, "%d%d", &x, &y);
					matrice[x][y] = 1;
				}
			}
		}
	}
	return matrice;
}


int** initializare(int** m1, int** m2, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			m2[i][j] = m1[i][j];
	return m2;
}

void iteratie(int** matrice1, int** matrice2, int n, int m)
{
	int vecini = 0;
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if ((i != 0) && (j != 0) && (i != n - 1) && (j != m - 1))
				vecini = matrice2[i][j + 1] + matrice2[i][j - 1] + matrice2[i + 1][j] + matrice2[i - 1][j] + matrice2[i + 1][j + 1] + matrice2[i + 1][j - 1] + matrice2[i - 1][j + 1] + matrice2[i - 1][j - 1];
			else if (i == 0 && j == 0)
				vecini = matrice2[i][j + 1] + matrice2[i + 1][j] + matrice2[i + 1][j + 1] + matrice2[i][m - 1] + matrice2[i + 1][m - 1] + matrice2[n - 1][j] + matrice2[n - 1][j + 1] + matrice2[n - 1][m - 1];
			else if (i == 0 && j == m - 1)
				vecini = matrice2[i][0] + matrice2[i][j - 1] + matrice2[i + 1][j] + matrice2[n - 1][j] + matrice2[i + 1][0] + matrice2[i + 1][j - 1] + matrice2[n - 1][0] + matrice2[n - 1][j - 1];
			else if (i == n - 1 && j == 0)
				vecini = matrice2[i][j + 1] + matrice2[i][m - 1] + matrice2[0][j] + matrice2[i - 1][j] + matrice2[0][j + 1] + matrice2[0][m - 1] + matrice2[i - 1][j + 1] + matrice2[i - 1][m - 1];
			else if (i == n - 1 && j == m - 1)
				vecini = matrice2[i][0] + matrice2[i][j - 1] + matrice2[0][j] + matrice2[i - 1][j] + matrice2[0][0] + matrice2[0][j - 1] + matrice2[i - 1][0] + matrice2[i - 1][j - 1];
			else if (i == 0)
				vecini = matrice2[i][j + 1] + matrice2[i][j - 1] + matrice2[i + 1][j] + matrice2[n - 1][j] + matrice2[i + 1][j + 1] + matrice2[i + 1][j - 1] + matrice2[n - 1][j + 1] + matrice2[n - 1][j - 1];
			else if (j == 0)
				vecini = matrice2[i][j + 1] + matrice2[i][m - 1] + matrice2[i + 1][j] + matrice2[i - 1][j] + matrice2[i + 1][j + 1] + matrice2[i + 1][m - 1] + matrice2[i - 1][j + 1] + matrice2[i - 1][m - 1];
			else if (i == n - 1)
				vecini = matrice2[i][j + 1] + matrice2[i][j - 1] + matrice2[0][j] + matrice2[i - 1][j] + matrice2[0][j + 1] + matrice2[0][j - 1] + matrice2[i - 1][j + 1] + matrice2[i - 1][j - 1];
			else if (j == m - 1)
				vecini = matrice2[i][0] + matrice2[i][j - 1] + matrice2[i - 1][j] + matrice2[i + 1][j] + matrice2[i + 1][0] + matrice2[i + 1][j - 1] + matrice2[i - 1][0] + matrice2[i - 1][j - 1];
			if (matrice1[i][j] == 1)
				if (vecini == 0 || vecini == 1 || vecini >= 4) matrice1[i][j] = 0;
			if (matrice1[i][j] == 0)
				if (vecini == 3) matrice1[i][j] = 1;
			vecini = 0;
		}
	}
	matrice2 = initializare(matrice1, matrice2, n, m);
	afisare_matrice(n, m, matrice1);
}


int main(int argc, char* argv[])
{
	char* file_in = NULL;
	char* file_out = NULL;
	int steps = 0;
	int** matrice = NULL;
	int** matrice2 = NULL;
	int mode = 0;
	int n = 0, m = 0;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-in") == 0) file_in = _strdup(argv[i + 1]);
		else if (strcmp(argv[i], "-out") == 0) file_out = _strdup(argv[i + 1]);
		else if (strcmp(argv[i], "-steps") == 0) steps = atoi(argv[i + 1]);
		else if (strcmp(argv[i], "-super_dinamic") == 0) mode = 1;
		else if (strcmp(argv[i], "-comprimat") == 0) mode = 2;
	}
	matrice = citire(file_in, file_out, mode);
	matrice2 = citire(file_in, file_out, mode);
	n = return_n(file_in, file_out, mode);
	m = return_m(file_in, file_out, mode, n);
	m -= 1;
	if (n > 3 && m > 3)
	{
		for (int i = 0; i < steps; i++)
		{
			iteratie(matrice, matrice2, n, m);
		}
	}
	afisare_fisier(n, m, matrice, file_out);
}