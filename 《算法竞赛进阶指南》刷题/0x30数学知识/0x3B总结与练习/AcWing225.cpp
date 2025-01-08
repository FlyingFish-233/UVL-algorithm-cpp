# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int row, key, mod;

struct Matrix
{
    static const int Max = 31;
    int num[Max][Max];

    Matrix () {
        memset(num, 0, sizeof(num));
    }

    Matrix (int k) {
        memset(num, 0, sizeof(num));
        for (int i = 1; i <= row; i++)
            num[i][i] = k;
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

    Matrix sumPow(int k)
    {
        if (k == 1) return *this;
        Matrix S = sumPow(k / 2);
        S = S + fastPow(k / 2) * S;
        if (k % 2 == 1) S = S + fastPow(k);
        return S;
    }
};

Matrix A, S;

int main()
{
    scanf("%d%d%d", &row, &key, &mod);
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= row; j++)
            scanf("%d", &A.num[i][j]);
    S = A.sumPow(key);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= row; j++)
            printf("%d ", S.num[i][j]);
        puts("");
    }
    return 0;
}