# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e7 + 1000;

bool flag[NR];
int nxt[NR];

int check(int x)
{
    while (x) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

int main()
{
    for (int i = 1, save = 0; i <= 1e7 + 100; i++) {
        if (check(i) && !flag[i]) {
            for (int j = 1; i * j <= 1e7 + 100; j++)
                flag[i * j] = true;
        }
        if (i % 7 != 0 && !flag[i])
            nxt[save] = i, save = i;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        int x;
        scanf("%d", &x);
        if (x % 7 == 0 || flag[x]) printf("-1\n");
        else printf("%d\n", nxt[x]);
    }
    return 0;
}