# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

struct Bigint
{
    static const int SIZE = 1010, base = 1e4, width = 4;
    int num[SIZE], len;

    Bigint () {
        memset(num, 0, sizeof(num)), len = 1;
    }

    Bigint (int x) {
        memset(num, 0, sizeof(num)), len = 0;
        while (x) num[++len] = x % base, x /= base;
        if (len == 0) len++;
    }

    void read(){
        char str[SIZE];
        scanf("%s", str);
        int sz = strlen(str);
        len = (sz - 1) / width + 1;
        for (int i = 1; i <= len; i++)
            for (int j = max(0, sz - width * i); j <= sz - width * (i - 1) - 1; j++)
                num[i] = num[i] * 10 + str[j] - '0';
    }

    void print() {
        printf("%d", num[len]);
        for (int i = len - 1; i >= 1; i--)
            printf("%04d", num[i]);
        puts("");
    }

    bool operator < (const Bigint &cmp) const {
        if (len != cmp.len) return len < cmp.len;
        for (int i = len; i >= 1; i--)
            if(num[i] != cmp.num[i]) return num[i] < cmp.num[i];
        return false;
    }

    bool operator > (const Bigint &cmp) const { return cmp < *this; }
    bool operator <= (const Bigint &cmp) const { return !(cmp < *this); }
    bool operator != (const Bigint &cmp) const { return cmp < *this || *this < cmp; }
    bool operator == (const Bigint &cmp) const { return !(cmp < *this || *this < cmp); }

    Bigint operator + (const Bigint &A) const {
        Bigint S;
        S.len = max(len, A.len);
        for (int i = 1; i <= S.len; i++) {
            S.num[i] += num[i] + A.num[i];
            if (S.num[i] >= base) {
                S.num[i] -= base;
                S.num[i + 1]++;
            }
        }
        while (S.num[S.len + 1]) S.len++;
        return S;
    }

    Bigint operator - (const Bigint &A) const {
        Bigint S;
        S.len = max(len, A.len);
        for (int i = 1; i <= S.len; i++) {
            S.num[i] += num[i] - A.num[i];
            if (S.num[i] < 0){
                S.num[i] += base;
                S.num[i + 1]--;
            }
        }
        while (!S.num[S.len] && S.len > 1) S.len--;
        return S;
    }

    Bigint operator * (const int &x) const {
        Bigint S = *this;
        for (int i = 1; i <= S.len; i++)
            S.num[i] *= x;
        for (int i = 1; i <= S.len; i++) {
            S.num[i + 1] += S.num[i] / base;
            S.num[i] %= base;
            while (S.num[S.len + 1]) S.len++;
        }
        return S;
    }

    Bigint operator / (const int &x) const {
        Bigint S = *this;
        int now = 0;
        for (int i = S.len; i >= 1; i--) {
            now = now * base + S.num[i];
            S.num[i] = now / x;
            now %= x;
        }
        while (S.num[S.len] == 0 && S.len > 1) S.len--;
        return S;
    }

    Bigint operator * (const Bigint &A) const {
        Bigint S;
        if ((A.len == 1 && A.num[1] == 0) || (len == 1 && num[1] == 0)) return S;
        S.len = A.len + len - 1;
        for (int i = 1; i <= len; i++)
            for (int j = 1; j <= A.len; j++) {
                S.num[i + j - 1] += num[i] * A.num[j];
                S.num[i + j] += S.num[i + j - 1] / base;
                S.num[i + j - 1] %= base;
            }
        while (S.num[S.len + 1]) S.len++;
        return S;
    }
};

const int NR = 51;

int n = 50;
Bigint C[NR][NR], two[NR * NR];
Bigint f[NR];

int main()
{
    for (int i = 0; i <= n; i++)
        C[i][0] = Bigint(1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    two[0] = Bigint(1);
    for (int i = 1; i <= n * n; i++)
        two[i] = two[i - 1] * 2;
    f[1] = Bigint(1);
    for (int i = 2; i <= n; i++) {
        f[i] = two[i * (i - 1) / 2];
        for (int j = 1; j < i; j++)
            f[i] = f[i] - f[j] * C[i - 1][j - 1] * two[(i - j) * (i - j - 1) / 2];
    }
    while (scanf("%d", &n) && n) f[n].print();
    return 0;
}