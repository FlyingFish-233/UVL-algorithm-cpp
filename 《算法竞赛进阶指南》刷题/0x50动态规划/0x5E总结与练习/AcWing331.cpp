# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n;
int s[NR];
int q[NR], len[NR], f[NR];

int main()
{
    scanf("%d", &n);
    for (int i = n; i >= 1; i--)
        scanf("%d", &s[i]);
    for (int i = 1; i <= n; i++)
        s[i] += s[i - 1];
    int l = 1, r = 0;
    q[++r] = 0;
    for (int i = 1, j = 0; i <= n; i++) {
        while (l <= r && s[q[l]] + len[q[l]] <= s[i]) j = max(j, q[l]), l++;
        f[i] = f[j] + 1, len[i] = s[i] - s[j];
        while (l <= r && s[q[r]] + len[q[r]] >= s[i] + len[i]) r--;
        q[++r] = i;
    }
    printf("%d\n", f[n]);
    return 0;
}