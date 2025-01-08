// P3809 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int n, m;
char s[NR];
int sa[NR], rk[NR];
int cnt[NR], id[NR];

void getRank(int w)
{
	static int oldrk[NR];
	memcpy(oldrk, rk, sizeof(rk));
	rk[sa[1]] = m = 1;
	for (int i = 2; i <= n; i++) {
		if (oldrk[sa[i]] != oldrk[sa[i - 1]] || oldrk[sa[i] + w] != oldrk[sa[i - 1] + w]) m++;
		rk[sa[i]] = m;
	}
}

void init()
{
	for (int i = 1; i <= n; i++)
		cnt[rk[i] = s[i]]++, m = max(m, rk[i]);
	for (int i = 1; i <= m; i++)
		cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; i--)
		sa[cnt[rk[i]]--] = i;
	getRank(0);
}

int main()
{
	scanf("%s", s + 1), n = strlen(s + 1);
	init();
	for (int w = 1; w <= n; w <<= 1) {
		int p = 0;
		for (int i = n; i >= n - w + 1; i--)
			id[++p] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > w) id[++p] = sa[i] - w;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++)
			cnt[rk[id[i]]]++;
		for (int i = 1; i <= m; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; i--)
			sa[cnt[rk[id[i]]]--] = id[i];
		getRank(w);
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", sa[i]);
	puts("");
	return 0;
}