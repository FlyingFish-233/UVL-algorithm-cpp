// P3390 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int mod = 1e9 + 7;

int row;

struct Matrix
{
	static const int Max = 110;
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

	void read()
	{
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= row; j++)
				scanf("%d", &num[i][j]);
	}

	void print()
	{
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= row; j++)
				printf("%d ", num[i][j]);
			puts("");
		}
	}

	Matrix operator * (const Matrix &A) const {
		Matrix S;
		for (int k = 1; k <= row; k++)
			for (int i = 1; i <= row; i++)
				for (int j = 1; j <= row; j++)
					(S.num[i][j] += 1ll * num[i][k] * A.num[k][j] % mod) %= mod;
		return S;
	}

	Matrix fastPow(long long x)
	{
		Matrix S(1), base = *this;
		for (long long i = x; i; i >>= 1, base = base * base)
			if (i & 1) S = S * base;
		return S;
	}
};

Matrix A;

int main()
{
	long long k;
	scanf("%d%lld", &row, &k);
	A.read();
	A.fastPow(k).print();
	return 0;
}