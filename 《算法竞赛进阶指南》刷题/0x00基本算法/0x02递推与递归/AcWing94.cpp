# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 10;

int n, q[NR];
bool used[NR];

void solve(int x)
{
	if (x > n) {
		for (int i = 1; i <= n; i++)
			printf("%d ", q[i]);
		puts("");
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (used[i]) continue;
		q[x] = i, used[i] = true;
		solve(x + 1);
		used[i] = false;
	}
}

int main()
{
	scanf("%d", &n);
	solve(1);
	return 0;
}