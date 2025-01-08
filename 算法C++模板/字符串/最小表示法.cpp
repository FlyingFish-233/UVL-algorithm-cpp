// P1368 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 6e5 + 10;

int n;
int s[NR];

int getMin()
{
    for (int i = 1; i <= n; i++)
        s[i + n] = s[i];
    int i = 1, j = 2, k;
    while (i <= n && j <= n) {
        for (k = 0; k < n; k++)
            if (s[i + k] != s[j + k]) break;
        if (k == n) break;
        if (s[i + k] > s[j + k]) i = i + k + 1, i += (i == j);
        else j = j + k + 1, j += (i == j);
    }
    return min(i, j);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &s[i]);
    int ans = getMin();
    for (int i = ans; i <= ans + n - 1; i++)
        printf("%d ", s[i]);
    puts("");
    return 0;
}