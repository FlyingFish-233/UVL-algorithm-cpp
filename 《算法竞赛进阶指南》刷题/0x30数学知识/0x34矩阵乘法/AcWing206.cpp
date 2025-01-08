# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 100;

int row;

struct Matrix
{
	long long num[NR][NR];

	Matrix()
	{
		memset(num, 0, sizeof(num));
	}

	Matrix(int x)
	{
		memset(num, 0, sizeof(num));
		for (int i = 0; i <= row; i++)
			num[i][i] = x;
	}

	void print()
	{
		for (int i = 0; i <= row; i++) {
			for (int j = 0; j <= row; j++)
				printf("%lld ", num[i][j]);
			puts("");
		}
		puts("=========================\n");
	}

	Matrix operator * (const Matrix &A) const {
		Matrix S;
		for (int k = 0; k <= row; k++)
			for (int i = 0; i <= row; i++)
				for (int j = 0; j <= row; j++)
					S.num[i][j] += num[i][k] * A.num[k][j];
		return S;
	}

	Matrix fastPow(int x)
	{
		Matrix S(1), base = *this;
		for (int i = x; i; i >>= 1, base = base * base)
			if (i & 1) S = S * base;
		return S;
	}
};

int n, m, tim, act;
char c[20][20], s[20][20];
Matrix A[NR], T, S;

int main()
{
	scanf("%d%d%d%d", &n, &m, &tim, &act);
	row = n * m;
	for (int i = 0; i < n; i++)
		scanf("%s", c[i]);
	for (int i = 0; i < act; i++)
		scanf("%s", s[i]);
	for (int i = 0; i < 60; i++)
		A[i].num[row][row] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			int x = i * m + j, tmp = c[i][j] - '0', len = strlen(s[tmp]);
			for (int k = 0; k < 60; k++) {
				if (s[tmp][k % len] >= '0' && s[tmp][k % len] <= '9')
					A[k].num[x][x] = 1, A[k].num[row][x] = s[tmp][k % len] - '0';
				if (s[tmp][k % len] == 'N' && i - 1 >= 0)
					A[k].num[x][(i - 1) * m + j] = 1;
				if (s[tmp][k % len] == 'W' && j - 1 >= 0)
					A[k].num[x][i * m + j - 1] = 1;
				if (s[tmp][k % len] == 'S' && i + 1 < n)
					A[k].num[x][(i + 1) * m + j] = 1;
				if (s[tmp][k % len] == 'E' && j + 1 < m)
					A[k].num[x][i * m + j + 1] = 1;
			}
		}
	T = Matrix(1);
	for (int i = 0; i < 60; i++)
		T = T * A[i];
	S.num[0][row] = 1;
	S = S * T.fastPow(tim / 60);
	for (int i = 0; i < tim % 60; i++)
		S = S * A[i];
	long long ans = 0;
	for (int i = 0; i < row; i++)
		ans = max(ans, S.num[0][i]);
	printf("%lld\n", ans);
	return 0;
}