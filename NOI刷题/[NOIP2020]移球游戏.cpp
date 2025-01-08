// P7115 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 60, MR = 510;

int n, m;
int top[NR], a[NR][MR];
bool flag[NR];
int tot, ans[1000000][2];

void change(int x, int y)
{
    ans[++tot][0] = x, ans[tot][1] = y;
    a[y][++top[y]] = a[x][top[x]--];
}

bool cmp(bool type, int x, int y)
{
    return (type == 0) ? (x <= y) : (x > y);
}

void modify(int x, int y, int mid, bool type)
{
    int s = 0;
    for (int k = 1; k <= m; k++) s += cmp(type, a[x][k], mid);
    for (int k = 1; k <= s; k++) change(y, n + 1);
    for (int k = m; k >= 1; k--) change(x, cmp(type, a[x][k], mid) ? y : n + 1);
    for (int k = 1; k <= s; k++) change(y, x);
    for (int k = 1; k <= m - s; k++) change(n + 1, x);
    for (int k = 1; k <= m - s; k++) change(y, n + 1);
    for (int k = 1; k <= m - s; k++) change(x, y);
    for (int k = m; k >= 1; k--) change(n + 1, (top[x] < m && cmp(type, a[n + 1][k], mid)) ? x : y);
}

void solve(int l, int r)
{
    if (l == r) return;
    memset(flag, false, sizeof(flag));
    int mid = (l + r) >> 1;
    for (int i = l; i <= mid; i++)
        for (int j = mid + 1; j <= r; j++) if (!flag[i] && !flag[j]) {
            int s = 0;
            for (int k = 1; k <= m; k++) s += (a[i][k] <= mid) + (a[j][k] <= mid);
            if (s >= m) modify(i, j, mid, 0), flag[i] = true;
            else modify(j, i, mid, 1), flag[j] = true;
        }
    solve(l, mid), solve(mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1, x; j <= m; j++)
            scanf("%d", &x), a[i][++top[i]] = x;
    solve(1, n);
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
        printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}