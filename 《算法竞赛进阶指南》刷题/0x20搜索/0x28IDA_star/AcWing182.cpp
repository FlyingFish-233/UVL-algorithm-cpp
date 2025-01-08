# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 100;

int n, dep, gsz;
vector<int> g[NR];
bool used[NR];

int id(int x, int y, int face)
{
	int save = (x - 1) * (2 * n + 1) + y;
	switch (face) {
		case 0: return save;
		case 1: return save + n;
		case 2: return save + n + 1;
		case 3: return save + (2 * n + 1);
	}
	return -1;
}

bool check(vector<int> &a)
{
	for (int i = 0; i < (int) a.size(); i++)
		if (used[a[i]]) return false;
	return true;
}

int f()
{
	static bool save[NR];
	memcpy(save, used, sizeof(used));
	int cnt = 0;
	for (int i = 1; i <= gsz; i++)
		if (check(g[i])) {
			cnt++;
			for (int j = 0; j < (int) g[i].size(); j++)
				used[g[i][j]] = true;
		}
	memcpy(used, save, sizeof(save));
	return cnt;
}

bool IDA_star(int step)
{
	if (step + f() > dep) return false;
	if (f() == 0) return true;
	for (int i = 1; i <= gsz; i++)
		if (check(g[i])) {
			for (int j = 0; j < (int) g[i].size(); j++) {
				if (used[g[i][j]]) continue;
				used[g[i][j]] = true;
				if (IDA_star(step + 1)) return true;
				used[g[i][j]] = false;
			}
			return false;
		}
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		gsz = 0;
		for (int l = 1; l <= n; l++)
			for (int i = 1; i <= n - l + 1; i++)
				for (int j = 1; j <= n - l + 1; j++) {
					g[++gsz].clear();
					for (int k = 0; k < l; k++) {
						g[gsz].push_back(id(i, j + k, 0));
						g[gsz].push_back(id(i + k, j, 1));
						g[gsz].push_back(id(i + k, j + l - 1, 2));
						g[gsz].push_back(id(i + l - 1, j + k, 3));
					}
				}
		memset(used, false, sizeof(used));
		int k;
		scanf("%d", &k);
		for (int i = 1, x; i <= k; i++)
			scanf("%d", &x), used[x] = true;
		for (dep = 0; !IDA_star(0); dep++);
		printf("%d\n", dep);
	}
	return 0;
}