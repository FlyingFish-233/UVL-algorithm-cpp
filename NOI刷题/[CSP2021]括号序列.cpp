// P7914 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 510;
const int mod = 1e9 + 7;

int n, k;
char s[NR];
int f[NR][NR];
int sl[NR][NR], sr[NR][NR];

int main()
{
    scanf("%d%d%s", &n, &k, s + 1);
    for (int i = 0; i <= n; i++)
        f[i + 1][i] = sl[i + 1][i] = sr[i + 1][i] = 1;
    for (int len = 1; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if (s[l] == '(' || s[l] == '?') {
                int j1 = l, j2 = l + 1, j3 = l + 1;
                for (int i = l + 1; i <= r; i++) {
                    if (j1 + 1 <= min(i - 1, l + k) && (s[j1 + 1] == '*' || s[j1 + 1] == '?')) j1++;
                    if (i == l + 2) j2 = i;
                    if (i >= l + 3) {
                        if (s[i - 1] == '(' || s[i - 1] == ')') j2 = i;
                        if (j2 < i - k) j2++;
                    }
                    if (i > j3) j3 = i;
                    while (j3 + 1 <= min(i + k, r - 1) && (s[j3 + 1] == '*' || s[j3 + 1] == '?')) j3++;

                    if (s[i] == ')' || s[i] == '?') {
                        int cnt1 = sl[l + 1][i - 1] - sl[j1 + 2][i - 1] + sr[l + 1][i - 2] - sr[l + 1][j2 - 2];
                        int cnt2 = sl[i + 1][r] - sl[j3 + 2][r];
                        cnt1 = (cnt1 % mod + mod) % mod, cnt2 = (cnt2 % mod + mod) % mod;
                        (f[l][r] += 1ll * cnt1 * cnt2 % mod) %= mod;
                    }
                }
            }
            sl[l][r] = (sl[l + 1][r] + f[l][r]) % mod;
            sr[l][r] = (sr[l][r - 1] + f[l][r]) % mod;
        }
    printf("%d\n", f[1][n]);
    return 0;
}

