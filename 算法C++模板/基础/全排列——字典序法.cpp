// P1088 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 10010;

int n, m;
int a[NR];

bool cmp(int x, int y)
{
	return x > y;
}

// 找最长单调递减后缀[pos+1,n], a[pos+1 ~ k] > a[pos]
// 交换a[pos]和a[k], 再将[pos+1,n]转置
bool permutation()
{
	int pos = n - 1;
	while (pos > 0 && a[pos] > a[pos + 1]) pos--;
	if (pos == 0) return false;
	int k = upper_bound(a + pos + 1, a + n + 1, a[pos], cmp) - a - 1;
	swap(a[pos], a[k]);
	for (int i = pos + 1; i <= (n + pos) / 2; i++)
		swap(a[i], a[n + pos + 1 - i]);
	return true;
}

int main()
{
	scanf("%d", &n);
	scanf("%d", &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++)
		permutation();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}