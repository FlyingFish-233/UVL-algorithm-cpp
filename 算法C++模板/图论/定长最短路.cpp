// P2886 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int row;

struct Matrix
{
	int num[210][210];

	Matrix()
	{
		memset(num, 0x3f, sizeof(num));
	}

	Matrix operator * (const Matrix &A) const {
		Matrix S;
		for (int k = 1; k <= row; k++)
			for (int i = 1; i <= row; i++)
				for (int j = 1; j <= row; j++)
					S.num[i][j] = min(S.num[i][j], num[i][k] + A.num[k][j]);
		return S;
	}

	Matrix fastPow(int k)
	{
		Matrix S = *this, base = *this;
		for (int i = k - 1; i; i >>= 1, base = base * base)
			if (i & 1) S = S * base;
		return S;
	}
};

int n, m, s, e;
int p[1010];
Matrix A;

int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &e);
	for (int i = 1; i <= m; i++) {
		int w, x, y;
		scanf("%d%d%d", &w, &x, &y);
		if (p[x] == 0) p[x] = ++row;
		if (p[y] == 0) p[y] = ++row;
        A.num[p[x]][p[y]] = A.num[p[y]][p[x]] = w;
	}
	printf("%d\n", A.fastPow(n).num[p[s]][p[e]]);
	return 0;
}