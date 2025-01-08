// P3265 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 510;

int n, m;
long double mat[NR][NR];
int c[NR], dim, ans;

void Gause()
{
	for (int i = 1; i <= n; i++) {
		int row = 0;
		for (int j = dim + 1; j <= n; j++)
			if (fabs(mat[j][i]) > 1e-8 && (row == 0 || c[j] < c[row])) row = j;
		if (row == 0) continue;
		dim++, ans += c[row];
		swap(mat[dim], mat[row]), swap(c[dim], c[row]);
		for (int j = 1; j <= n; j++) if (dim != j) {
			long double rate = mat[j][i] / mat[dim][i];
			for (int k = i; k <= m; k++)
				mat[j][k] -= rate * mat[dim][k];
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> mat[i][j];
	for (int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
	Gause();
	printf("%d %d\n", dim, ans);
	return 0;
}