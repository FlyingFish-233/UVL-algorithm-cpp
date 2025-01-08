# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 4e4 + 10, MR = 1e3 + 10;

int n, m, ans;
int a[NR], cnt[NR];
int len, t[NR];
vector<int> v[NR];

int sz, blk[NR], L[MR], R[MR];
int b[MR][MR], c[MR][MR];

int calc(int l, int r, int x)
{
	return upper_bound(v[x].begin(), v[x].end(), r) - lower_bound(v[x].begin(), v[x].end(), l);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	memcpy(t, a, sizeof(a));
	sort(t + 1, t + n + 1);
	len = unique(t + 1, t + n + 1) - t - 1;
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(t + 1, t + len + 1, a[i]) - t;

	sz = sqrt(n * log(2) / log(n));
	for (int i = 1; i <= n; i++)
		blk[i] = (i - 1) / sz + 1;
	for (int i = 1; i <= blk[n]; i++)
		L[i] = (i - 1) * sz + 1, R[i] = min(n, i * sz);
	for (int i = 1; i <= n; i++)
		v[a[i]].push_back(i);
	for (int i = 1; i <= blk[n]; i++) {
		memset(cnt, 0, sizeof(cnt));
		int kind = 0, cnt_max = 0;
		for (int j = i; j <= blk[n]; j++) {
			for (int k = L[j]; k <= R[j]; k++)
				if (++cnt[a[k]] > cnt_max || (cnt[a[k]] == cnt_max && a[k] < kind))
					cnt_max = cnt[a[k]], kind = a[k];
			b[i][j] = kind, c[i][j] = cnt_max;
		}
	}

	while (m--) {
		int l, r;
		scanf("%d%d", &l, &r);
		l = (l + ans - 1) % n + 1, r = (r + ans - 1) % n + 1;
		if (l > r) swap(l, r);
		int kind = 0, cnt_max = 0, save;
		if (blk[l] == blk[r]) {
			for (int i = l; i <= r; i++) {
				save = calc(l, r, a[i]);
				if (save > cnt_max || (save == cnt_max && a[i] < kind))
					cnt_max = save, kind = a[i];
			}
			printf("%d\n", ans = t[kind]);
			continue;
		}
		for (int i = l; i <= R[blk[l]]; i++) {
			save = calc(l, r, a[i]);
			if (save > cnt_max || (save == cnt_max && a[i] < kind))
				cnt_max = save, kind = a[i];
		}
		for (int i = L[blk[r]]; i <= r; i++) {
			save = calc(l, r, a[i]);
			if (save > cnt_max || (save == cnt_max && a[i] < kind))
				cnt_max = save, kind = a[i];
		}
		save = c[blk[l] + 1][blk[r] - 1];
		if (save > cnt_max || (save == cnt_max && b[blk[l] + 1][blk[r] - 1] < kind))
			cnt_max = save, kind = b[blk[l] + 1][blk[r] - 1];
		printf("%d\n", ans = t[kind]);
	}
	return 0;
}