// P6623 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

# define ls tree[rt].next[0]
# define rs tree[rt].next[1]

using namespace std;

const int NR = 525010 + 10, MR = 1 << 21;

struct Node
{
    int next[2], val, cnt;
    Node() { next[0] = next[1] = val = cnt = 0; }
};

int pool[MR];
Node tree[MR];

int newNode() { return pool[++pool[0]]; }
void del(int x) { tree[x] = Node(), pool[pool[0]--] = x; }

void pushUp(int rt)
{
    tree[rt].cnt = tree[ls].cnt + tree[rs].cnt;
    tree[rt].val = (tree[ls].val << 1) ^ (tree[rs].val << 1) ^ (tree[rs].cnt & 1);
}

void insert(int &rt, int x, int k)
{
    if (rt == 0) rt = newNode();
    if (k == 21) { tree[rt].cnt++; return;}
    insert(tree[rt].next[x >> k & 1], x, k + 1);
    pushUp(rt);
}

int merge(int x, int y)
{
    if (x == 0 || y == 0) return x + y;
    tree[x].val ^= tree[y].val;
    tree[x].cnt += tree[y].cnt;
    tree[x].next[0] = merge(tree[x].next[0], tree[y].next[0]);
    tree[x].next[1] = merge(tree[x].next[1], tree[y].next[1]);
    del(y);
    return x;
}

void add1(int rt)
{
    swap(ls, rs);
    if (ls) add1(ls);
    pushUp(rt);
}

int n;
int v[NR];
vector<int> g[NR];
int rt[NR];
long long ans;

void dfs(int x)
{
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        dfs(y), rt[x] = merge(rt[x], rt[y]);
    }
    add1(rt[x]), insert(rt[x], v[x], 0);
    ans += tree[rt[x]].val;
}

int main()
{
    for (int i = 1; i < MR; i++)
        pool[i] = i;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    for (int i = 2, x; i <= n; i++)
        scanf("%d", &x), g[x].push_back(i);
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}
