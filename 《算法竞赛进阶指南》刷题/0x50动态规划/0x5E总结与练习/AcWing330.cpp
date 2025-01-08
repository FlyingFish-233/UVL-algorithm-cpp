# pragma GCC optimize(2)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 2e3 + 10;

int n, k;
int a[NR], s[NR];
priority_queue<int, vector<int>, less<int> > q1;
priority_queue<int, vector<int>, greater<int> > q2;
int cost[NR][NR], f[NR][30];

int main()
{
    while (scanf("%d%d", &n, &k) && !(n == 0 && k == 0)) {
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
        for (int i = 1; i <= n; i++) {
            int s1 = 0, s2 = 0;
            while (!q1.empty()) q1.pop();
            while (!q2.empty()) q2.pop();
            for (int j = i; j >= 1; j--) {
                if (!q1.empty() && a[j] <= q1.top()) q1.push(a[j]), s1 += a[j];
                else q2.push(a[j]), s2 += a[j];
                while ((int) q1.size() > (i - j + 1) / 2) {
                    int x = q1.top();
                    q2.push(x), q1.pop();
                    s2 += x, s1 -= x;
                }
                while ((int) q1.size() < (i - j + 1) / 2) {
                    int x = q2.top();
                    q1.push(x), q2.pop();
                    s1 += x, s2 -= x;
                }
                cost[j][i] = (q1.size() * q2.top() - s1) + (s2 - q2.size() * q2.top());
            }
        }
        memset(f, 0x3f, sizeof(f)), f[0][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= k; j++)
                for (int p = 0; p < i; p++)
                    f[i][j] = min(f[i][j], f[p][j - 1] + cost[p + 1][i]);
        printf("%d\n", f[n][k]);
    }
    return 0;
}