# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <set>
# include <map>
# include <queue>

using namespace std;

const int NR = 2e4 + 10;

int gcd(int x, int y);
bool solve(int step, int x, int y);
bool dfs(int step, int x, int y);

int target, dep;

int gcd(int x, int y)
{
	if (y == 0) return x;
	return gcd(y, x % y);
}

bool solve(int step, int x, int y)
{
	if (x == 0 || target % gcd(x, y)) return false;
	if (x > y) swap(x, y);
	return dfs(step + 1, x, y);
}

bool dfs(int step, int x, int y)
{
	if (step == dep) return x == target || y == target;
	if (y << (dep - step) < target) return false;
	int t[4] = {x + x, x + y, y + y, y - x};
	for (int i = 0; i < 4; i++) {
		if (solve(step, x, t[i])) return true;
		if (solve(step, y, t[i])) return true;
	}
	return false;
}

int main()
{
	scanf("%d", &target);
	for (dep = 0; !dfs(0, 0, 1); dep++);
	printf("%d\n", dep);
	return 0;
}