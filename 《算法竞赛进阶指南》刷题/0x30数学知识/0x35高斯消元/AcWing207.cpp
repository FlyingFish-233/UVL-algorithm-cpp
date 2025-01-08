# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 20;

int n;
double a[NR][NR];
double mat[NR][NR], ans[NR];

bool Gause()
{
	for (int i = 1; i <= n; i++) {
		int row = i;
		for (int j = i + 1; j <= n; j++)
			if (fabs(mat[j][i]) > fabs(mat[row][i])) row = j;
		if (fabs(mat[row][i]) < 1e-8) return false;
		swap(mat[row], mat[i]);
		for (int j = 1; j <= n; j++) if (i != j) {
			double rate = mat[j][i] / mat[i][i];
			for (int k = i; k <= n + 1; k++)
				mat[j][k] -= mat[i][k] * rate;
		}
	}
	for (int i = 1; i <= n; i++)
		ans[i] = mat[i][n + 1] / mat[i][i];
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lf", &a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			mat[i][j] = 2 * (a[i + 1][j] - a[i][j]);
			mat[i][n + 1] += a[i + 1][j] * a[i + 1][j] - a[i][j] * a[i][j];
		}
	Gause();
	for (int i = 1; i <= n; i++)
		printf("%.3f ", ans[i]);
	return 0;
}