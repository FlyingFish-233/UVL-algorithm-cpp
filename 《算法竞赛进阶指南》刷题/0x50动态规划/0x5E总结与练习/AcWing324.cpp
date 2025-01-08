# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <map>

using namespace std;

const int NR = 210;

int n, m;
int a[NR];
vector<int> g[NR];

int now;
map<string, int> mp;

bool flag[NR];
int sz[NR], f[NR][NR];

void dfs(int x)
{
    sz[x] = 1;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        dfs(y), sz[x] += sz[y];
    }
    f[x][0] = 0;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        for (int j = sz[x]; j >= 0; j--)
            for (int k = 0; k <= min(j, sz[y]); k++)
                f[x][j] = min(f[x][j], f[x][j - k] + f[y][k]);
    }
    if (x != 0) f[x][sz[x]] = min(f[x][sz[x]], a[x]);
}

int main()
{
    string s;
    while (cin >> s && s != "#") {
        n = atoi(s.c_str()), cin >> m;
        for (int i = 0; i <= n; i++) g[i].clear();
        memset(flag, false, sizeof(flag));
        now = 0, mp.clear();
        for (int i = 1; i <= n; i++) {
            cin >> s;
            if (mp.count(s) == 0) mp[s] = ++now;
            int x = mp[s]; cin >> a[x];
            getline(cin, s);
            if (s.size() == 0) continue;
            s += ' ';
            for (int j = 1, pre = 0; j < (int) s.size(); j++)
                if (s[j] == ' ') {
                    string s2 = string(s, pre + 1, j - pre - 1);
                    if (mp.count(s2) == 0) mp[s2] = ++now;
                    int y = mp[s2];
                    g[x].push_back(y), flag[y] = true;
                    pre = j;
                }
        }
        memset(f, 0x3f, sizeof(f));
        for (int i = 1; i <= n; i++)
            if (!flag[i]) g[0].push_back(i);
        dfs(0);
        int ans = 2e9;
        for (int i = m; i <= n; i++)
            ans = min(ans, f[0][i]);
        printf("%d\n", ans);
    }
    return 0;
}