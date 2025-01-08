// AcWing92 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

int n;
vector <int> chosen;

void solve(int x)
{
	if (x > n) {
		for (int i = 0; i < (int) chosen.size(); i++)
			printf("%d ", chosen[i]);
		puts("");
		return;
	}
	solve(x + 1);
	chosen.push_back(x);
	solve(x + 1);
	chosen.pop_back();
}

int main()
{
	scanf("%d", &n);
	solve(1);
	return 0;
}