# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n;
char s[NR];
int f[NR][NR];
int pre[NR][NR];

void update(int l, int r, int d)
{
    for (int i = l + d; i <= r; i++)
        if (s[i] != s[i - d]) return;
    if (f[l][r] > f[l][l + d - 1] + 3 + ((r - l + 1) / d >= 10))
        f[l][r] = f[l][l + d - 1] + 3 + ((r - l + 1) / d >= 10),  pre[l][r] = -d;
}

void print(int l, int r)
{
    int k = pre[l][r];
    if (l == r) { printf("%c", s[l]); return; }
    if (k > 0) print(l, k), print(k + 1, r);
    else k = -k, printf("%d(", (r - l + 1) / k), print(l, l + k - 1), printf(")");
}

int main()
{
    scanf("%s", s + 1), n = strlen(s + 1);
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++) f[i][i] = 1, pre[i][i] = -1;
    for (int len = 2; len <= n; len++)
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            for (int i = l; i < r; i++)
                if (f[l][r] > f[l][i] + f[i + 1][r])
                    f[l][r] = f[l][i] + f[i + 1][r], pre[l][r] = i;
            for (int i = 1; i * i <= len; i++) if (len % i == 0)
                update(l, r, i), update(l, r, len / i);
        }
    print(1, n);
    puts("");
    return 0;
}