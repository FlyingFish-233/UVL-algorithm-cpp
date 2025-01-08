# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 6e5 + 10;

int n, m;
int a[NR], b[NR], c[NR];
int len, t[NR];
int box[NR];

void discrete()
{
	sort(t + 1, t + len + 1);
	len = unique(t + 1, t + len + 1) - t - 1;
}

int query(int x)
{
	return lower_bound(t + 1, t + len + 1, x) - t;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), t[++len] = a[i];
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]), t[++len] = b[i];
	for (int i = 1; i <= m; i++)
		scanf("%d", &c[i]), t[++len] = c[i];
	discrete();
	for (int i = 1; i <= n; i++)
		box[query(a[i])]++;
	int ans0 = 0, ans1 = 0, ans2 = 0;
	for (int i = 1; i <= m; i++) {
		int x = box[query(b[i])], y = box[query(c[i])];
		if (x > ans1 || (x == ans1 && y > ans2))
			ans0 = i, ans1 = x, ans2 = y;
	}
	printf("%d\n", ans0);
	return 0;
}