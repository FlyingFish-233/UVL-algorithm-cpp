// P1031 (100 pts) 
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n; 
int a[NR];

int main()
{
	scanf("%d", &n);
	int x = 0;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), x += a[i];
	x /= n;
	int ans = 0;
	for (int i = 1; i <= n - 1; i++)
		if (a[i] != x) {
			a[i + 1] -= x - a[i];
			a[i] = x; // a[i] += x - a[i] 
			ans++;
		}
	printf("%d", ans);
	return 0;
}
