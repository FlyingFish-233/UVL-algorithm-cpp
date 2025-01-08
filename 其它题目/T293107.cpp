# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <map>

using namespace std;

const int NR = 1e5 + 10;

typedef unsigned long long LL;

int n;
char s[NR], ans[NR];
int top, st[NR];
LL f[NR], v[NR];

int tot;
map<LL, int> h;
vector<int> g[NR];

void getans(int l, int r)
{
    if (l > r) return;
    int k = h[v[l]], pos = g[k][g[k].size() - 1];
    ans[l] = '(', ans[pos] = ')';
    while (g[k].size() > 0 && ans[g[k][g[k].size() - 1]]) g[k].pop_back();
    getans(pos + 1, r), getans(l + 1, pos - 1);
}

int main()
{
    scanf("%s", s + 1), n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        if (top > 0 && s[i] - 'a' == st[top]) v[i] = f[top--];
        else st[++top] = s[i] - 'a', v[i] = f[top] = f[top - 1] * 1331 + st[top];
    }
    if (top) return printf("-1\n"), 0;
    for (int i = 1; i <= n; i++) {
        if (h.count(v[i]) == 0) h[v[i]] = ++tot;
        g[h[v[i]]].push_back(i);
    }
    getans(1, n);
    printf("%s\n", ans + 1);
    return 0;
}