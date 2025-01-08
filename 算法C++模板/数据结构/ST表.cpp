// P3865 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
int a[NR], lg2[NR], st[NR][30];

void init()
{
    for (int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int query(int l, int r)
{
    int k = lg2[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    init();
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }
    return 0;
}