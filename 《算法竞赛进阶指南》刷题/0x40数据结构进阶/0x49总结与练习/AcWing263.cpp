# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10, MR = 400;

int n, c, m, ans;
int a[NR], cnt[NR];
int sz, blk[NR], L[MR], R[MR];
int s[MR][NR], f[MR][MR];

int main()
{
	scanf("%d%d%d", &n, &c, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sz = sqrt(n);
	for (int i = 1; i <= n; i++)
		blk[i] = (i - 1) / sz + 1;
	for (int i = 1; i <= blk[n]; i++)
		L[i] = (i - 1) * sz + 1, R[i] = min(n, i * sz);

	for (int i = 1; i <= blk[n]; i++) {
		memset(cnt, 0, sizeof(cnt));
		int num = 0;
		for (int j = i; j <= blk[n]; j++) {
			for (int k = L[j]; k <= R[j]; k++)
				if ((++cnt[a[k]]) % 2 == 0) num++;
				else if (cnt[a[k]] != 1) num--;
			f[i][j] = num;
		}
	}
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= blk[n]; i++) {
		for (int j = L[i]; j <= R[i]; j++)
			cnt[a[j]]++;
		memcpy(s[i], cnt, sizeof(cnt));
	}

	memset(cnt, 0, sizeof(cnt));
	while (m--) {
		int l, r;
		scanf("%d%d", &l, &r);
		l = (l + ans) % n + 1, r = (r + ans) % n + 1;
		if (l > r) swap(l, r);

		if (blk[l] == blk[r]) {
			ans = 0;
			for (int i = l; i <= r; i++)
				if ((++cnt[a[i]]) % 2 == 0) ans++;
				else if (cnt[a[i]] != 1) ans--;
			for (int i = l; i <= r; i++)
				cnt[a[i]] = 0;
			printf("%d\n", ans);
			continue;
		}

		ans = f[blk[l] + 1][blk[r] - 1];
		for (int i = l; i <= R[blk[l]]; i++) {
			if (cnt[a[i]] == 0) cnt[a[i]] = s[blk[r] - 1][a[i]] - s[blk[l]][a[i]];
			if ((++cnt[a[i]]) % 2 == 0) ans++;
			else if (cnt[a[i]] != 1) ans--;
		}
		for (int i = L[blk[r]]; i <= r; i++) {
			if (cnt[a[i]] == 0) cnt[a[i]] = s[blk[r] - 1][a[i]] - s[blk[l]][a[i]];
			if ((++cnt[a[i]]) % 2 == 0) ans++;
			else if (cnt[a[i]] != 1) ans--;
		}
		for (int i = l; i <= R[blk[l]]; i++)
			cnt[a[i]] = 0;
		for (int i = L[blk[r]]; i <= r; i++)
			cnt[a[i]] = 0;
		printf("%d\n", ans);
	}
	return 0;
}