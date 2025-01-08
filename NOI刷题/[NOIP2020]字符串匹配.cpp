// P7114 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = (1 << 20) + 10;

int n;
char s[NR];
int fail[NR];

void getFail()
{
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[j + 1] != s[i]) j = fail[j];
        if (s[j + 1] == s[i]) j++;
        fail[i] = j;
    }
}

int cnt[30], F1[NR], F2[NR];

void getF()
{
    memset(cnt, 0, sizeof(cnt)), F1[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (++cnt[s[i] - 'a' + 1] & 1) F1[i] = F1[i - 1] + 1;
        else F1[i] = F1[i - 1] - 1;
    }
    memset(cnt, 0, sizeof(cnt)), F2[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        if (++cnt[s[i] - 'a' + 1] & 1) F2[i] = F2[i + 1] + 1;
        else F2[i] = F2[i + 1] - 1;
    }
}

int tmp[30];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        getFail(), getF();
        memset(tmp, 0, sizeof(tmp));
        long long ans = 0;
        for (int i = 1; i < n; i++) {
            if (i >= 2) {
                ans += tmp[F2[i + 1]];
                for (int j = 2*i; j < n; j += i)
                    if (fail[j] && j % (j - fail[j]) == 0 && i % (j - fail[j]) == 0) ans += tmp[F2[j + 1]];
            }
            for (int j = F1[i]; j <= 26; j++) tmp[j]++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}