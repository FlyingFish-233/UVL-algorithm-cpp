# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e5 + 10;

int n, m;
long long lim;
int a[NR], b[NR], save[NR];

bool check(int l, int mid, int r)
{
	for (int i = mid + 1; i <= r; i++)
		b[i] = a[i];
	sort(b + mid + 1, b + r + 1);
	int t1 = l, t2 = mid + 1, len = r - l + 1;
	for (int i = 1; i <= len; i++)
		if (t2 > r || (t1 <= mid && b[t1] < b[t2])) save[i] = b[t1++];
		else save[i] = b[t2++];
	long long sum = 0;
	for (int i = 1; i <= m && i < len - i + 1; i++)
		sum += 1ll * (save[len - i + 1] - save[i]) * (save[len - i + 1] - save[i]);
	return sum <= lim;
}

int solve(int x)
{
	int delta = 1, now = x;
	b[x] = a[x];
	while (delta) {
		if (now + delta <= n && check(x, now, now + delta)) {
			now += delta, delta <<= 1;
			for (int i = x; i <= now; i++)
				b[i] = save[i - x + 1];
		}
		else delta >>= 1;
	}
	return now;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%lld", &n, &m, &lim);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		int ans = 0;
		for (int i = 1; i <= n; i = solve(i) + 1)
			ans++;
		printf("%d\n", ans);
	}
	return 0;
}