# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <set>

using namespace std;

const int NR = 2e5 + 10;

int n;
vector<int> g[NR];
int s[NR];

void dfs(int x, int fa)
{
    s[x] = 1;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (y != fa) dfs(y, x), s[x] += s[y];
    }
}

multiset<int> st[2];
bool flag[NR], vis[NR];
int ans = 2e9;

int query(int x, int y, int z)
{
    return max(x, max(y, z)) - min(x, min(y, z));
}

int get_near(int t, int k)
{
    multiset<int>::iterator it = st[t].lower_bound(k);
    multiset<int>::iterator it2 = it; it2--;
    if ((*it) - k <= k - (*it2)) return *it;
    return *it2;
}

void getans(int x, int fa)
{
    if (x != 1) {
        int k = (n + s[x]) / 2;
        if ((n + s[x]) % 2 == 1) k++;
        int save = get_near(0, k);
        ans = min(ans, query(s[x], save - s[x], n - save));

        k = (n - s[x]) / 2;
        if ((n - s[x]) % 2 == 1) k++;
        save = get_near(1, k);
        ans = min(ans, query(s[x], save, n - s[x] - save));

        st[0].insert(s[x]);
    }
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (y != fa) getans(y, x);
    }
    st[0].erase(st[0].lower_bound(s[x])), st[1].insert(s[x]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n - 1; i++)
        scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
    dfs(1, 0);
    st[0].insert(-1e9), st[0].insert(1e9);
    st[1].insert(-1e9), st[1].insert(1e9);
    getans(1, 0);
    printf("%d\n", ans);
    return 0;
}
