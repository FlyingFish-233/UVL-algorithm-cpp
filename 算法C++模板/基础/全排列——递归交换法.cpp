// P1706 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 20;

int n;
int a[NR];

void permutation(int x)
{
	if (x == n) {
		for (int i = 1; i <= n; i++)
			printf("%5d", a[i]);
		printf("\n");
		return;
	}
	for (int i = x; i <= n; i++) {
		sort(a + x, a + n + 1);
		swap(a[x], a[i]);
		permutation(x + 1);
		swap(a[x], a[i]);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		a[i] = i;
	permutation(1);
	return 0;
}
