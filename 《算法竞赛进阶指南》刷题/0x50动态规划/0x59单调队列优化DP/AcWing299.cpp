# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

int n;
int a[NR];

long long m;
long long s[NR];

int lg[NR], st[NR][30];

int getmax(int l, int r)
{
    int len = lg[r - l + 1];
    return max(st[l][len], st[r - (1 << len) + 1][len]);
}

int pre[NR];
long long f[NR];

struct Node
{
    int x, y; long long val;
    bool operator < (const Node &cmp) const {
        return val > cmp.val;
    }
};

int q[NR];
bool flag[NR];
priority_queue<Node> h;

int main()
{
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] > m) return printf("-1\n"), 0;
        s[i] = s[i - 1] + a[i];
        st[i][0] = a[i];
    }
    lg[0] = -1;
    for (int i = 1; i <= n; i++)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= lg[n]; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    for (int i = 1, j = 1; i <= n; i++) {
        while (j <= i && s[i] - s[j - 1] > m) j++;
        pre[i] = j;
    }
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = f[pre[i] - 1] + getmax(pre[i], i);
        while (l <= r && s[i] - s[q[l]] > m) flag[q[l++]] = true;
        while (l <= r && a[q[r]] <= a[i]) flag[q[r--]] = true;
        q[++r] = i;
        if (l < r) h.push((Node) {q[r - 1], i, f[q[r - 1]] + a[i]});
        while (!h.empty() && (flag[h.top().x] || flag[h.top().y])) h.pop();
        if (!h.empty()) f[i] = min(f[i], h.top().val);
    }
    printf("%lld\n", f[n]);
    return 0;
}