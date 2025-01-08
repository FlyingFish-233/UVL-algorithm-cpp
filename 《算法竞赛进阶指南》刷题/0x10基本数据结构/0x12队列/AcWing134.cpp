# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

struct Array
{
	int id, x;

	bool operator < (const Array &cmp) {
		return x < cmp.x;
	}
};

int n;
Array a[NR];

int m, l[NR], r[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i].x), a[i].id = i;
	sort(a + 1, a + n + 1);
	a[0].x = -2e9;
	for (int i = 1; i <= n; i++)
		if (a[i].x != a[i - 1].x) m++, l[m] = a[i].id, r[m] = a[i].id;
		else l[m] = min(l[m], a[i].id), r[m] = max(r[m], a[i].id);
	bool up = false;
	int ans = 1, pre = 2e9;
	for (int i = 1; i <= m; i++) {
		if (up && l[i] < pre) up = false, ans++;
		else if (!up && r[i] > pre) up = true;
		pre = (up) ? r[i] : l[i];
	}
	printf("%d\n", ans);
	return 0;
}