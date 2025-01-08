// P5202 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 3e5 + 10;

int n, k;
char c[NR];
int f[NR], s[NR];

int q[NR];

bool cmp(int x, int y)
{
    if (f[x] == f[y]) return s[x] < s[y];
    return f[x] < f[y];
}

int main()
{
    scanf("%d%d", &n, &k);
    scanf("%s", c + 1);
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + (c[i] == 'H' ? 1 : -1);
    int l = 1, r = 0; q[++r] = 0;
    for (int i = 1; i <= n; i++) {
        while (l <= r && q[l] < i - k) l++;
        f[i] = f[q[l]] + (s[i] <= s[q[l]]);
        while (l <= r && cmp(i, q[r])) r--;
        q[++r] = i;
    }
    printf("%d\n", f[n]);
    return 0;
}