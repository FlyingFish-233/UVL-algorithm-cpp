# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e4 + 10;

struct Bus
{
	int x, d, num;

	bool operator < (const Bus &cmp) const {
		return num > cmp.num;
	}
};

int n, dep;
int cnt[NR];

int m;
Bus b[NR];

int count()
{
	int ans = 0;
	for (int i = 0; i < 60; i++)
		ans += cnt[i];
	return ans;
}

bool check(Bus now)
{
	for (int i = now.x; i < 60; i += now.d)
		if (cnt[i] == 0) return false;
	return true;
}

void modify(Bus now, int delta)
{
	for (int i = now.x; i < 60; i += now.d)
		cnt[i] += delta;
}

bool dfs(int step, int stt)
{
	int save = count();
	if (step > dep) {
		if (save == 0) return true;
		return false;
	}
	if ((dep - step + 1) * b[stt].num < save) return false;
	for (int i = stt; i <= m; i++) {
		if (!check(b[i])) continue;
		modify(b[i], -1);
		if (dfs(step + 1, i)) return true;
		modify(b[i], 1);
	}
	return false;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++)
		scanf("%d", &x), cnt[x]++;
	for (int x = 0; x < 30; x++)
		for (int d = x + 1; x + d < 60; d++)
			b[++m] = (Bus) {x, d, (59 - x) / d + 1};
	sort(b + 1, b + m + 1);
	for (dep = 1; !dfs(1, 1); dep++);
	printf("%d\n", dep);
	return 0;
}