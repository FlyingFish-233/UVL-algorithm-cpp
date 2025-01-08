# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int p[30][2] = {{1, 3}, {1, 5}, {2, 3}, {2, 5},
					  {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7},
					  {4, 3}, {4, 5},
					  {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7},
					  {6, 3}, {6, 5}, {7, 3}, {7, 5}};

const int q[10][2] = {{3, 3}, {3, 4}, {3, 5}, {4, 3}, {4, 5}, {5, 3}, {5, 4}, {5, 5}};

int dep;
int a[10][10], box[10];
char s[100];

int f()
{
	box[1] = box[2] = box[3] = 0;
	for (int i = 0; i < 8; i++)
		box[a[q[i][0]][q[i][1]]]++;
	int ans = max(box[1], max(box[2], box[3]));
	return 8 - ans;
}

char opposite(char c)
{
	switch (c) {
		case 'A': return 'F';
		case 'B': return 'E';
		case 'C': return 'H';
		case 'D': return 'G';
		case 'E': return 'B';
		case 'F': return 'A';
		case 'G': return 'D';
		case 'H': return 'C';
	}
	return '!';
}

void change(char c)
{
	int save;
	switch(c) {
		case 'A':
			save = a[1][3];
			for (int i = 1; i < 7; i++)
				a[i][3] = a[i + 1][3];
			a[7][3] = save;
			break;

		case 'B':
			save = a[1][5];
			for (int i = 1; i < 7; i++)
				a[i][5] = a[i + 1][5];
			a[7][5] = save;
			break;

		case 'C':
			save = a[3][7];
			for (int i = 7; i > 1; i--)
				a[3][i] = a[3][i - 1];
			a[3][1] = save;
			break;

		case 'D':
			save = a[5][7];
			for (int i = 7; i > 1; i--)
				a[5][i] = a[5][i - 1];
			a[5][1] = save;
			break;

		case 'E':
			save = a[7][5];
			for (int i = 7; i > 1; i--)
				a[i][5] = a[i - 1][5];
			a[1][5] = save;
			break;

		case 'F':
			save = a[7][3];
			for (int i = 7; i > 1; i--)
				a[i][3] = a[i - 1][3];
			a[1][3] = save;
			break;

		case 'G':
			save = a[5][1];
			for (int i = 1; i < 7; i++)
				a[5][i] = a[5][i + 1];
			a[5][7] = save;
			break;

		case 'H':
			save = a[3][1];
			for (int i = 1; i < 7; i++)
				a[3][i] = a[3][i + 1];
			a[3][7] = save;
			break;
	}
}

bool IDA_star(int step)
{
	if (step + f() > dep) return false;
	if (f() == 0) {
		s[step] = '\0';
		if (step == 0) printf("No moves needed\n");
		else printf("%s\n", s);
		printf("%d\n", a[3][3]);
		return true;
	}
	for (int i = 0; i < 8; i++) {
		char c = i + 'A';
		if (step && s[step - 1] == opposite(c)) continue;
		change(s[step] = c);
		if (IDA_star(step + 1)) return true;
		change(opposite(c));
	}
	return false;
}

int main()
{
	int x;
	while (scanf("%d", &x) && x) {
		a[p[0][0]][p[0][1]] = x;
		for (int i = 1; i < 24; i++)
			scanf("%d", &x), a[p[i][0]][p[i][1]] = x;
		for (dep = 0; ; dep++)
			if (IDA_star(0)) break;
	}
	return 0;
}