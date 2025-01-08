// P1706 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 20;

int n;
int a[NR];
bool flag[NR];

void permutation(int x)
{
	if (x > n) {
		for (int i = 1; i <= n; i++)
			printf("%5d", a[i]);
		printf("\n");
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (flag[i]) continue;
		a[x] = i;
		flag[i] = true;
		permutation(x + 1);
		flag[i] = false;
	}
}

int main()
{
	scanf("%d", &n);
	permutation(1);
	return 0;
}
