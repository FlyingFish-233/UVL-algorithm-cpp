# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int mod = 1e4;

int n, row = 2;

struct Matrix
{
	static const int Max = 5;
	int num[Max][Max];

	Matrix()
	{
		memset(num, 0, sizeof(num));
	}

	Matrix(int x)
	{
		memset(num, 0, sizeof(num));
		for (int i = 1; i <= row; i++)
			num[i][i] = x;
	}

	void print()
	{
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= row; j++)
				printf("%d ", num[i][j]);
			puts("");
		}
		puts("=========================\n");
	}

	Matrix operator * (const Matrix &A) const {
		Matrix S;
		for (int k = 1; k <= row; k++)
			for (int i = 1; i <= row; i++)
				for (int j = 1; j <= row; j++)
					(S.num[i][j] += num[i][k] * A.num[k][j]) %= mod;
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

Matrix S, A;

int main()
{
	A.num[1][1] = 1, A.num[1][2] = 1;
	A.num[2][1] = 1, A.num[2][2] = 0;
	while (scanf("%d", &n) && n != -1) {
		if (n == 0) { printf("0\n"); continue; }
		S.num[1][1] = 1, S.num[1][2] = 0;
		S = S * A.fastPow(n - 1);
		printf("%d\n", S.num[1][1]);
	}
	return 0;
}