# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, a[NR];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	int pos = n / 2 + 1, sum = 0;
	for (int i = 1; i <= n; i++)
		sum += abs(a[i] - a[pos]);
	printf("%d\n", sum);
	return 0;
}