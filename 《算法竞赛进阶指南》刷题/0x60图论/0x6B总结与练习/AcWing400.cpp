// P7771 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10, MR = 2e5 + 10;

int n, lim;
vector<int> g[NR];
int len, fte[NR], ans[MR];

void euler(int x)
{
    for (int i = fte[x]; i < (int) g[x].size(); i = fte[x])
        fte[x] = i + 1, euler(g[x][i]);
    ans[++len] = x;
}

int main()
{
    scanf("%d", &n), lim = (1 << (n - 1)) - 1;
    for (int i = 0; i <= lim; i++) {
        g[i].push_back((i << 1) & lim);
        g[i].push_back(((i << 1) & lim) | 1);
    }
    euler(0);
    reverse(ans + 1, ans + len + 1);
    printf("%d ", 1 << n);
    for (int i = 1; i <= len - 1; i++)
        printf("%d", ans[i] >> (n - 2));
    puts("");
    return 0;
}