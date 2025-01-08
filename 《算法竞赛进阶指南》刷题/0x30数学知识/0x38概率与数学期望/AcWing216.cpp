# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n;
int a[NR], b[NR];
double ans[3];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int k = 30; k >= 0; k--) {
        long long num_xor = 0, num_and = 0, num_or = 0;
        for (int i = 1; i <= n; i++) {
            b[i] = a[i] >> k & 1;
            if (b[i] == 1) num_xor++, num_and++, num_or++;
        }
        int last[2] = {0, 0};
        for (int i = 1; i <= n; i++) {
            if (b[i] == 1) num_and += 2 * (i - last[0] - 1), num_or += 2 * (i - 1);
            else num_or += 2 * last[1];
            last[b[i]] = i;
        }
        int c1 = 0, c2 = 0;
        for (int i = 1; i <= n; i++) {
            if (b[i] == 1) num_xor += 2 * c1;
            else num_xor += 2 * c2;
            c1++;
            if (b[i] == 1) swap(c1, c2);
        }
        ans[0] += 1.0 * (1 << k) * num_xor / n / n;
        ans[1] += 1.0 * (1 << k) * num_and / n / n;
        ans[2] += 1.0 * (1 << k) * num_or / n / n;
    }
    printf("%.3f %.3f %.3f\n", ans[0], ans[1], ans[2]);
    return 0;
}