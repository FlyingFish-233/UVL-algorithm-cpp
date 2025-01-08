// AcWing137 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10, PR = 99991;

int n, a[NR][6];
vector<int> h[NR];

bool check(int x, int y)
{
	for (int d = 0; d <= 5; d++) {
		bool flag = true;
		for (int i = 0; i <= 5; i++)
			if (a[x][i] != a[y][(i + d) % 6]) { flag = false; break; }
		if (flag) return true;
		flag = true;
		for (int i = 0; i <= 5; i++)
			if (a[x][5 - i] != a[y][(i + d) % 6]) { flag = false; break; }
		if (flag) return true;
	}
	return false;
}

bool insert(int x)
{
	int sum = 0, mul = 1;
	for (int i = 0; i <= 5; i++) {
		sum = (sum + a[x][i]) % PR;
		mul = 1ll * mul * a[x][i] % PR;
	}
	int val = (sum + mul) % PR;
	for (int i = 0; i < (int) h[val].size(); i++)
		if (check(x, h[val][i])) return true;
	h[val].push_back(x);
	return false;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= 5; j++)
			scanf("%d", &a[i][j]);
		if (insert(i)) {
			printf("Twin snowflakes found.\n");
			return 0;
		}
	}
	printf("No two snowflakes are alike.\n");
	return 0;
}