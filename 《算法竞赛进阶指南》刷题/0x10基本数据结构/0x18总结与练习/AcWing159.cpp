# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10, MR = 75 + 10;

int n, m;
char s[NR][MR];
int fail[NR];

bool check(int k, int x, int y)
{
	for (int i = 1; i <= k; i++)
		if (s[x][i] != s[y][i]) return false;
	return true;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	int w = 1;
	for ( ; w <= m; w++) {
		bool flag = true;
		for (int i = 1; i <= n; i++)
			for (int j = w + 1; j <= m; j++)
				if (s[i][j] != s[i][j - w]) { flag = false; break; }
		if (flag) break;
	}
	fail[0] = fail[1] = 0;
	for (int i = 2, j = 0; i <= n; i++) {
		while (j > 0 && !check(w, j + 1, i)) j = fail[j];
		if (check(w, j + 1, i)) j++;
		fail[i] = j;
	}
	printf("%d\n", w * (n - fail[n]));
	return 0;
}