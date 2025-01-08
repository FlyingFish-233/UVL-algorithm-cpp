// P5788 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 3e6 + 10;

int n;
int a[NR];
int top, s[NR];
int ans[NR];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = n; i >= 1; i--) {
        while (top && a[s[top]] <= a[i]) top--;
        if (top) ans[i] = s[top];
        s[++top] = i;
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}