# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2500 + 10, MR = 1000 + 10;

struct Section
{
	int l, r;

	bool operator < (const Section &A) const {
		return r < A.r;
	}
};

int n, m;
Section cow[NR];
int flag[MR];

int getpos(int x)
{
	for (int i = cow[x].l; i <= cow[x].r; i++)
		if (flag[i]) return i;
	return -1;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &cow[i].l, &cow[i].r);
	sort(cow + 1, cow + n + 1);
	for (int i = 1, x, w; i <= m; i++)
		scanf("%d%d", &x, &w), flag[x] += w;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int tmp = getpos(i);
		if (tmp != -1) flag[tmp]--, ans++;
	}
	printf("%d\n", ans);
	return 0;
}