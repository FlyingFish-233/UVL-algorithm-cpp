// P3810 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

struct Node
{
	int x, y, z, cnt, id;

	bool operator < (const Node &cmp) const {
		if (x != cmp.x) return x < cmp.x;
		if (y != cmp.y) return y < cmp.y;
		return z < cmp.z;
	}

	bool operator == (const Node &cmp) const {
		return x == cmp.x && y == cmp.y && z == cmp.z;
	}
};

int n, m, k;
Node a[NR], b[NR];
int ans[NR], box[NR];

int s[NR];

int lowbit(int x)
{
	return x & (-x);
}

void modify(int x, int delta)
{
	for (int i = x; i <= k; i += lowbit(i))
		s[i] += delta;
}

int getsum(int x)
{
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		sum += s[i];
	return sum;
}

void dfs(int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1;
	dfs(l, mid), dfs(mid + 1, r);

	int t1 = l, t2 = mid + 1;
	for (int i = l; i <= r; i++)
		if (t2 > r || (t1 <= mid && a[t1].y <= a[t2].y)) modify(a[t1].z, a[t1].cnt), b[i] = a[t1++];
		else ans[a[t2].id] += getsum(a[t2].z), b[i] = a[t2++];
	for (int i = l; i <= mid; i++) modify(a[i].z, -a[i].cnt);
	for (int i = l; i <= r; i++) a[i] = b[i];
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z), a[i].id = i, a[i].cnt = 1;
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		if (a[i] == a[i - 1]) b[m].cnt++, ans[b[m].id]++;
		else b[++m] = a[i];
	}
	memcpy(a, b, sizeof(b));
	dfs(1, m);
	for (int i = 1; i <= m; i++)
		box[ans[a[i].id]] += a[i].cnt;
	for (int i = 0; i < n; i++)
		printf("%d\n", box[i]);
	return 0;
}