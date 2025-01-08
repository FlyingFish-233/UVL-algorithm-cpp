// AcWing93 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

int n, m;
vector <int> chosen;

void solve(int x)
{
	if ((int) chosen.size() > m || (int) chosen.size() + (n - x + 1) < m) return;
	if (x > n) {
		for (int i = 0; i < (int) chosen.size(); i++)
			printf("%d ", chosen[i]);
		puts("");
		return;
	}
	chosen.push_back(x);
	solve(x + 1);
	chosen.pop_back();
	solve(x + 1);
}

int main()
{
	scanf("%d%d", &n, &m);
	solve(1);
	return 0;
}