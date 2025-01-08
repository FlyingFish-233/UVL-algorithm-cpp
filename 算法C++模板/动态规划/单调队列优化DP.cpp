// AcWing298 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e4 + 10, MR = 110;

struct Array
{
    int l, p, s;
    bool operator < (const Array &cmp) const {
        return s < cmp.s;
    }
};

int n, m;
Array a[MR];
deque< pair<int, int> > q;
int f[MR][NR];

// f[i][j] = max(f[i-1][k] + a[i].p*(j-k)) 其中j-a[i].l <= k <= a[i].s-1, j >= a[i].s
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &a[i].l, &a[i].p, &a[i].s);
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++) {
        while (!q.empty()) q.pop_front();
        for (int j = max(0, a[i].s - a[i].l); j <= a[i].s - 1; j++) {
            while (!q.empty() && q.front().second <= f[i - 1][j] - a[i].p * j) q.pop_front();
            q.push_front({j, f[i - 1][j] - a[i].p * j});
        }
        for (int j = 1; j <= n; j++) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (j < a[i].s) continue;
            while (!q.empty() && q.back().first < j - a[i].l) q.pop_back();
            if (!q.empty()) f[i][j] = max(f[i][j], a[i].p * j + q.back().second);
        }
    }
    printf("%d\n", f[m][n]);
    return 0;
}