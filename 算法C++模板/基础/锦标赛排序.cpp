// P1177 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const int INF = 1e9;

int n;
int a[NR];
int b[NR], tree[NR << 1]; // tree[x]表示x子树中最小的叶子节点对应到a数组中的下标

int winner(int x, int y)
{
    return (a[tree[x]] <= a[tree[y]]) ? tree[x] : tree[y];
}

// 构造一棵2n-1的完全二叉树, 其中n~(2n-1)为叶子节点, 对应a[1]~a[n]
void build()
{
    for (int i = 1; i <= n; i++)
        tree[n + i - 1] = i;
    for (int i = 2 * n - 1; i > 1; i -= 2)
        tree[i >> 1] = winner(i - 1, i);
}

void modify()
{
    a[tree[1]] = INF;
    for (int i = n + tree[1] - 1; i > 1; i >>= 1)
        tree[i >> 1] = winner(i, i ^ 1);
}

void tournamentSort()
{
    build();
    for (int i = 1; i <= n; i++)
        b[i] = a[tree[1]], modify();
    memcpy(a, b, sizeof(b));
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    tournamentSort();
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}