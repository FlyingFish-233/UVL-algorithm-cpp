# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int row, mod = 1e7 + 7;

struct Matrix
{
    static const int Max = 13;
    int num[Max][Max];

    Matrix () {
        memset(num, 0, sizeof(num));
    }

    Matrix (int k) {
        memset(num, 0, sizeof(num));
        for (int i = 1; i <= row; i++)
            num[i][i] = k;
    }

    void clear() {
        memset(num, 0, sizeof(num));
    }

    Matrix operator + (const Matrix &A) const {
        Matrix S;
        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= row; j++)
                S.num[i][j] = (num[i][j] + A.num[i][j]) % mod;
        return S;
    }

    Matrix operator * (const Matrix &A) const {
        Matrix S;
        for (int k = 1; k <= row; k++)
            for (int i = 1; i <= row; i++)
                for (int j = 1; j <= row; j++)
                    (S.num[i][j] += 1ll * num[i][k] * A.num[k][j] % mod) %= mod;
        return S;
    }

    Matrix fastPow(int k)
    {
        Matrix S(1), base = *this;
        for (int i = k; i; i >>= 1, base = base * base)
            if (i & 1) S = S * base;
        return S;
    }
};

int n, m;
Matrix S, A;

int main()
{
    while (scanf("%d%d", &n, &m) != EOF) {
        S.clear(), A.clear(), row = n + 2;
        for (int i = 1, x; i <= n; i++)
            scanf("%d", &x), S.num[1][i] = x % mod;
        S.num[1][n + 1] = 233, S.num[1][n + 2] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                A.num[i][j] = 1;
        for (int i = 1; i <= n; i++)
            A.num[n + 1][i] = 1;
        A.num[n + 1][n + 1] = 10, A.num[n + 2][n + 1] = 3, A.num[n + 2][n + 2] = 1;
        S = S * A.fastPow(m);
        printf("%d\n", S.num[1][n]);
    }
    return 0;
}