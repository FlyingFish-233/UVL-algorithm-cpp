// P7915 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int n;
int a[NR];
char s[NR];
bool flag[NR];

bool dfs(int x, int l, int r, int l0, int r0)
{
    if (x == n / 2) return true;
    if (l0 > l && a[l] == a[l0]) s[x] = 'L', s[n - x - 1] = 'L', flag[l] = flag[l0] = true;
    else if (r0 <= r && r0 > l && a[l] == a[r0]) s[x] = 'L', s[n - x - 1] = 'R', flag[l] = flag[r0] = true;
    else if (l0 >= l && l0 < r && a[r] == a[l0]) s[x] = 'R', s[n - x - 1] = 'L', flag[r] = flag[l0] = true;
    else if (r0 < r && a[r] == a[r0]) s[x] = 'R', s[n - x - 1] = 'R', flag[r] = flag[r0] = true;
    else return false;
    while (flag[l] && l <= l0) l++;
    while (flag[r] && r >= r0) r--;
    while (flag[l0] && l <= l0) l0--;
    while (flag[r0] && r >= r0) r0++;
    return dfs(x + 1, l, r, l0, r0);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n), n <<= 1;
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        int t1, t2;
        for (int i = 1; i <= n; i++) {
            if (i != 1 && a[i] == a[1]) t1 = i;
            if (i != n && a[i] == a[n]) t2 = i;
        }
        s[n] = '\0';
        for (int i = 1; i <= n; i++) flag[i] = false;
        if (dfs(0, 1, n, t1, t1)) { printf("%s\n", s); continue; }
        for (int i = 1; i <= n; i++) flag[i] = false;
        if (dfs(0, 1, n, t2, t2)) { printf("%s\n", s); continue; }
        printf("-1\n");
    }
    return 0;
}

