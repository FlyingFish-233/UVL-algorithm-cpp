# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 6e5 + 10, L = 23;

struct Node
{
	int next[2], cnt;
};

int n, m;
int tot, root[NR];
Node tree[NR << 5];

int insert(int oldrt, int x, int k)
{
	int rt = ++tot, t = (x >> k) & 1;
	tree[rt] = tree[oldrt];
	if (k >= 0) tree[rt].next[t] = insert(tree[rt].next[t], x, k - 1);
	tree[rt].cnt++;
	return rt;
}

int query(int rt1, int rt2, int x, int k)
{
	if (k < 0) return 0;
	int t = (x >> k) & 1;
	if (tree[tree[rt2].next[!t]].cnt > tree[tree[rt1].next[!t]].cnt)
		return (1 << k) | query(tree[rt1].next[!t], tree[rt2].next[!t], x, k - 1);
	return query(tree[rt1].next[t], tree[rt2].next[t], x, k - 1);
}

int main()
{
	scanf("%d%d", &n, &m);
	int sum = 0, len = n;
	root[0] = insert(0, 0, L);
	for (int i = 1, x; i <= n; i++)
		scanf("%d", &x), root[i] = insert(root[i - 1], sum ^= x, L);
	while (m--) {
		char op[2]; int l, r, x;
		scanf("%s", op);
		if (op[0] == 'A') {
			scanf("%d", &x);
			root[len + 1] = insert(root[len], sum ^= x, L);
			len++;
		}
		if (op[0] == 'Q') {
			scanf("%d%d%d", &l, &r, &x);
			if (l == 1) printf("%d\n", query(0, root[r - 1], sum ^ x, L));
			else printf("%d\n", query(root[l - 2], root[r - 1], sum ^ x, L));
		}
	}
	return 0;
}