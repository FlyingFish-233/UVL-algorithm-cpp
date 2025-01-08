# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <ctime>

using namespace std;

const int n = 16, m = 30;
const int nxt[9][2] = {{0,0},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
// const int nxt[9][2] = {{0,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0}};

int a[n + 10][m + 10];

void build()
{
    memset(a, 0, sizeof(a));
    int t = 0;
    while (t < 99) {
        int x = rand() % n + 1, y = rand() % m + 1;
        if (a[x][y] == 0) a[x][y] = -1, t++;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) if (a[i][j] == 0)
            for (int k = 1; k <= 8; k++)
                a[i][j] += (a[i+nxt[k][0]][j+nxt[k][1]] == -1);
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         if (a[i][j] != -1) putchar(' ');
    //         printf("%d ", a[i][j]);
    //     }
    //     puts("");
    // }
}

bool f[n + 10][m + 10];

bool find1() // no rule
{
    memset(f, false, sizeof(f));
    int x, y;
    while (true) {
        x = rand() % n + 1, y = rand() % m + 1;
        if (f[x][y]) continue;
        f[x][y] = true;
        if (a[x][y] == -1) return false;
        if (a[x][y] == 0) return true;
    }
    return false;
}

int calc(int x, int y)
{
    int ans = 0;
    for (int k = 1; k <= 8; k++)
        ans += f[x+nxt[k][0]][y+nxt[k][1]];
    return ans;
}

int l, r, q[100][2];

bool find2() //mathematical rule
{
    memset(f, false, sizeof(f));
    int x, y, k, x0, y0;
    while (true) {
        x = rand() % n + 1, y = rand() % m + 1;
        if (f[x][y]) continue;
        f[x][y] = true;
        // printf("%d %d\n", x, y);
        if (a[x][y] == -1) return false;
        if (a[x][y] == 0) return true;
        if (x == 1 || x == n || y == 1 || y == m || a[x][y] > 1) continue;
        l = 1, r = 0;
        q[++r][0] = x, q[r][1] = y;
        while (l <= r) {
            int t = l;
            for (int i = l + 1; i <= r; i++)
                if (calc(q[t][0], q[t][1]) > calc(q[i][0], q[i][1])) t = i;
            swap(q[t][0], q[l][0]), swap(q[t][1], q[l][1]);
            x = q[l][0], y = q[l][1], k = rand() % 8 + 1;
            if (calc(x, y) >= 2) l++; // if we meet 1, then open 3 cells around it
            while (f[x+nxt[k][0]][y+nxt[k][1]]) k = k % 8 + 1;
            x0 = x+nxt[k][0], y0 = y+nxt[k][1];
            f[x0][y0] = true;
            // printf("%d %d\n", x0, y0);
            if (a[x0][y0] == -1) return false;
            if (a[x0][y0] == 0) return true;
            if (x0 == 1 || x0 == n || y0 == 1 || y0 == m || a[x0][y0] > 1) continue;
            q[++r][0] = x0, q[r][1] = y0;
        }
    }
    return false;
}

bool find3() // diagonal rule
{
    memset(f, false, sizeof(f));
    int x, y, k, x0, y0;
    while (true) {
        x = rand() % n + 1, y = rand() % m + 1;
        if (f[x][y]) continue;
        f[x][y] = true;
        // printf("%d %d\n", x, y);
        if (a[x][y] == -1) return false;
        if (a[x][y] == 0) return true;
        while (true) {
            for (k = 2; k <= 8; k += 2) {
                x0 = x+nxt[k][0], y0 = y+nxt[k][1];
                if (x == 1 || x == n || y == 1 || y == m || a[x][y] > 1) x0 += nxt[k][0], y0 += nxt[k][1];
                if (x0 >= 1 && x0 <= n && y0 >= 1 && y0 <= m && !f[x0][y0]) break; 
            }
            if (k > 8) break;
            f[x0][y0] = true;
            // printf("%d %d\n", x0, y0);
            if (a[x0][y0] == -1) return false;
            if (a[x0][y0] == 0) return true;
            x = x0, y = y0;
        }
    }
    return false;
}

int main()
{
    srand(time(NULL));
    int T, ans = 0;
    scanf("%d", &T);
    while (T--)
        build(), ans += find3();
    printf("%d\n", ans);
    return 0;
}