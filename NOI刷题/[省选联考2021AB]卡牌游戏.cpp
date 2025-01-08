// P7514 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define v first
# define id second

using namespace std;

typedef pair<int, int> PII;

const int NR = 2e6 + 10;

int n, m;
PII a[NR];
int tot, tot2;
bool flag[NR];

void add(int x)
{
    flag[x] = true;
    if (x <= n) {
        if (!flag[x + n]) tot++;
        else tot2--;
    }
    else {
        if (!flag[x - n]) tot++, tot2++;
    }
}

void del(int x)
{
    flag[x] = false;
    if (x <= n) {
        if (!flag[x + n]) tot--;
        else tot2++;
    }
    else {
        if (!flag[x - n]) tot--, tot2--;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 2 * n; i++)
        scanf("%d", &a[i].v), a[i].id = i;
    sort(a + 1, a + 2 * n + 1);
    int ans = 1e9;
    for (int i = 1, j = 1; i <= 2 * n; i++) {
        while (j <= 2 * n && (tot < n || tot2 > m)) add(a[j++].id);
        if (tot == n && tot2 <= m) ans = min(ans, a[j - 1].v - a[i].v);
        del(a[i].id);
    }
    printf("%d\n", ans);
    return 0;
}

