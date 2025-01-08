// AcWing290 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;

int n, m, x, y;
double f[NR][NR];
double mat[NR][NR], ans[NR];

void Gause()
{
	for (int i = 1; i <= m - 1; i++) {
		double rate = mat[i + 1][i] / mat[i][i];
		mat[i + 1][i] = 0;
		mat[i + 1][i + 1] -= rate * mat[i][i + 1];
		mat[i + 1][m + 1] -= rate * mat[i][m + 1];
	}
	for (int i = m; i >= 2; i--) {
		double rate = mat[i - 1][i] / mat[i][i];
		mat[i - 1][i] = 0;
		mat[i - 1][m + 1] -= mat[i][m + 1] * rate;
	}
	for (int i = 1; i <= m; i++)
		ans[i] = mat[i][m + 1] / mat[i][i];
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &x, &y);
	if (m == 1) {
		for (int i = n - 1; i >= x; i--)
			f[i][1] = f[i + 1][1] + 2;
		printf("%.4f\n", f[x][y]);
		return 0;
	}
	for (int i = n - 1; i >= x; i--) {
		mat[1][1] = 2. / 3, mat[1][2] = -1. / 3, mat[1][m + 1] = f[i + 1][1] / 3 + 1;
		mat[m][m] = 2. / 3, mat[m][m - 1] = -1. / 3, mat[m][m + 1] = f[i + 1][m] / 3 + 1;
		for (int j = 2; j <= m - 1; j++)
			mat[j][j] = 3. / 4, mat[j][j - 1] = mat[j][j + 1] = -1. / 4, mat[j][m + 1] = f[i + 1][j] / 4 + 1;
		Gause();
		memcpy(f[i], ans, sizeof(ans));
	}
	printf("%.4f\n", f[x][y]);
	return 0;
}