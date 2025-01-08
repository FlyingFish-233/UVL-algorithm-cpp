# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 20;

int n, dep;
vector<int> a(NR);

int f()
{
	int cnt = 0;
	for (int i = 0; i <= n; i++)
		if (a[i + 1] != a[i] + 1) cnt++;
	return ceil(1.0 * cnt / 3);
}

bool IDA_star(int step)
{
	if (step + f() > dep) return false;
	if (f() == 0) return true;
	vector<int> save = a, now;
	for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++) {
			now.assign(save.begin() + l, save.begin() + r + 1);
			a = save;
			a.erase(a.begin() + l, a.begin() + r + 1);
			for (int p = 1; p <= n - (r - l + 1); p++) {
				a.insert(a.begin() + p, now.begin(), now.end());
				if (IDA_star(step + 1)) return true;
				a.erase(a.begin() + p, a.begin() + p + (r - l + 1));
			}
		}
	a = save;
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		a[0] = 0, a[n + 1] = n + 1;
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (dep = 0; dep <= 4; dep++)
			if (IDA_star(0)) { printf("%d\n", dep); break; }
		if (dep == 5) printf("5 or more\n");
	}
	return 0;
}