// P7771 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10, MR = 2e5 + 10;

int n, m;
vector<int> g[NR];
int in[NR], out[NR];
int len, fte[NR], ans[MR];

void euler(int x)
{
    for (int i = fte[x]; i < (int) g[x].size(); i = fte[x])
        fte[x] = i + 1, euler(g[x][i]);
    ans[++len] = x;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        in[y]++, out[x]++;
    }
    int tmp = 0, s = 1;
    for (int i = 1; i <= n; i++)
        if (in[i] != out[i]) {
            tmp++;
            if (in[i] == out[i] - 1) s = i;
        }
    if (tmp != 0 && tmp != 2) return printf("No\n"), 0;
    for (int i = 1; i <= n; i++)
        sort(g[i].begin(), g[i].end());
    euler(s);
    reverse(ans + 1, ans + len + 1);
    for (int i = 1; i <= len; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}