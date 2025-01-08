// P4198 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e5 + 10;

int n;
int h[NR];
int tree[NR << 2], cnt[NR << 2];
// 若结点i表示区间[l,r],则tree[i]表示[l,r]中最大数的下标
// cnt[i]表示[mid+1,r]内的前缀严格最大值的个数(不考虑mid+1前的数的影响)

void build(int rt, int l, int r)
{
	tree[rt] = l, cnt[rt] = 1;
	if (l == r) return;
	build(ls, l, mid);
	build(rs, mid + 1, r);
}

bool cmp(int x, int y)
{
	if (y == 0) return h[x] > 0;
	return 1ll * h[x] * y > 1ll * h[y] * x;
}

// 统计[l,r]中大于x的前缀严格最大值个数
int calc(int rt, int l, int r, int x)
{
	if (l == r) return cmp(l, x);
	if (cmp(tree[ls], x)) return calc(ls, l, mid, x) + cnt[rt];
	return calc(rs, mid + 1, r, x);
}

void modify(int rt, int l, int r, int x)
{
	if (l == r) return;
	if (x <= mid) modify(ls, l, mid, x);
	else modify(rs, mid + 1, r, x);
	tree[rt] = cmp(tree[ls], tree[rs]) ? tree[ls] : tree[rs];
	cnt[rt] = calc(rs, mid + 1, r, tree[ls]);
}

int main()
{
	int T;
	scanf("%d%d", &n, &T);
	build(1, 1, n);
	while (T--) {
		int x, y;
		scanf("%d%d", &x, &y);
		h[x] = y, modify(1, 1, n, x);
		printf("%d\n", calc(1, 1, n, 0));
	}
	return 0;
}