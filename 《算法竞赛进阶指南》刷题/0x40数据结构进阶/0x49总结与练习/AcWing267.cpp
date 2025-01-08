# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e6 + 10;

struct Array
{
	int id, x, y, val;
};

int w, n, m;
Array a[NR], save[NR];
int s[NR], ans[NR];

int lowbit(int x)
{
	return x & (-x);
}

void clear(int x)
{
	for (int i = x; i <= w; i += lowbit(i))
		s[i] = 0;
}

void modify(int x, int delta)
{
	for (int i = x; i <= w; i += lowbit(i))
		s[i] += delta;
}

int getsum(int x)
{
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		sum += s[i];
	return sum;
}

void cdq(int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1, t1 = l, t2 = mid + 1;
	cdq(l, mid), cdq(mid + 1, r);
	for (int i = l; i <= r; i++)
		if (t2 > r || (t1 <= mid && a[t1].x <= a[t2].x)) {
			if (a[t1].id == 0) modify(a[t1].y, a[t1].val);
			save[i] = a[t1++];
		}
		else {
			if (a[t2].id > 0) ans[a[t2].id] += getsum(a[t2].y);
			if (a[t2].id < 0) ans[-a[t2].id] -= getsum(a[t2].y);
			save[i] = a[t2++];
		}
	for (int i = l; i <= mid; i++)
		if (a[i].id == 0) clear(a[i].y);
	for (int i = l; i <= r; i++)
		a[i] = save[i];
}

int main()
{
	scanf("%*d%d", &w);
	for (int op; scanf("%d", &op) && op != 3; ) {
		if (op == 1) {
			int x, y, val;
			scanf("%d%d%d", &x, &y, &val);
			a[++n] = (Array) {0, x, y, val};
		}
		if (op == 2) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			a[++n] = (Array) {++m, x2, y2, 0};
			a[++n] = (Array) {m, x1 - 1, y1 - 1, 0};
			a[++n] = (Array) {-m, x1 - 1, y2, 0};
			a[++n] = (Array) {-m, x2, y1 - 1, 0};
		}
	}
	cdq(1, n);
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}