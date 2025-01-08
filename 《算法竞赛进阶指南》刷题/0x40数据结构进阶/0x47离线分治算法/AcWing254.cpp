# pragma GCC optimize(3)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10, L = 1e6 + 1;

struct Array
{
	int id, x, y;
};

int n, m, q;
Array a[NR], b[NR], save[NR];
int s[NR], ans[NR];

inline int lowbit(int x)
{
	return x & (-x);
}

inline void clear(int x)
{
	for (register int i = x; i <= L; i += lowbit(i))
		s[i] = 0;
}

inline void modify(int x, int delta)
{
	for (register int i = x; i <= L; i += lowbit(i))
		s[i] = max(s[i], delta);
}

inline int getmax(int x)
{
	int s_max = 0;
	for (register int i = x; i > 0; i -= lowbit(i))
		s_max = max(s_max, s[i]);
	if (s_max == 0) return -0x3f3f3f3f;
	return s_max;
}

inline void cdq(int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1, t1 = l, t2 = mid + 1;
	cdq(l, mid), cdq(mid + 1, r);
	for (register int i = l; i <= r; i++)
		if (t2 > r || (t1 <= mid && a[t1].x <= a[t2].x)) {
			if (a[t1].id == 0) modify(a[t1].y, a[t1].x + a[t1].y);
			save[i] = a[t1++];
		}
		else {
			if (a[t2].id != 0) ans[a[t2].id] = min(ans[a[t2].id], a[t2].x + a[t2].y - getmax(a[t2].y));
			save[i] = a[t2++];
		}
	for (register int i = l; i <= mid; i++)
		if (a[i].id == 0) clear(a[i].y);
	for (register int i = l; i <= r; i++)
		a[i] = save[i];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (register int i = 1, x, y; i <= n; i++)
		scanf("%d%d", &x, &y), a[i] = (Array) {0, ++x, ++y};
	for (register int i = n + 1, opt, x, y; i <= n + m; i++)
		scanf("%d%d%d", &opt, &x, &y), a[i] = (Array) {((opt == 1) ? 0 : ++q), ++x, ++y};
	memset(ans, 0x3f, sizeof(ans));
	memcpy(b, a, sizeof(a)), cdq(1, n + m);
	for (register int i = 1; i <= 3; i++) {
		for (register int j = 1; j <= n + m; j++) {
			int t1 = b[j].x, t2 = b[j].y;
			b[j].x = t2, b[j].y = L - t1 + 1;
		}
		memcpy(a, b, sizeof(b)), cdq(1, n + m);
	}
	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
	return 0;
}