// P7913 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

# define PR pair<int, int>

using namespace std;

const int NR = 1e5 + 10;

int n;

struct Array
{
    int m;
    PR a[NR];
    int m0, t[NR << 1];
    int tot, pos[NR], cnt[NR];

    priority_queue<int> q1;
    priority_queue<PR> q2;

    void init()
    {
        sort(a + 1, a + m + 1);
        for (int i = 1; i <= m; i++)
            t[++m0] = a[i].first, t[++m0] = a[i].second;
        sort(t + 1, t + m0 + 1);
        for (int i = 1; i <= m; i++) {
            int l = lower_bound(t + 1, t + m0 + 1, a[i].first) - t;
            int r = lower_bound(t + 1, t + m0 + 1, a[i].second) - t;
            while (!q2.empty() && -q2.top().first < l)
                q1.push(-q2.top().second), q2.pop();
            if (q1.empty()) q1.push(-(++tot));
            pos[i] = -q1.top(), cnt[pos[i]]++, q1.pop();
            q2.push(make_pair(-r, pos[i]));
        }
        for (int i = 1; i <= n; i++)
            cnt[i] += cnt[i - 1];
    }
};

Array A, B;

int main()
{
    scanf("%d%d%d", &n, &A.m, &B.m);
    for (int i = 1; i <= A.m; i++)
        scanf("%d%d", &A.a[i].first, &A.a[i].second);
    for (int i = 1; i <= B.m; i++)
        scanf("%d%d", &B.a[i].first, &B.a[i].second);
    A.init(), B.init();
    int ans = 0;
    for (int i = 0; i <= n; i++)
        ans = max(ans, A.cnt[i] + B.cnt[n - i]);
    printf("%d\n", ans);
    return 0;
}

