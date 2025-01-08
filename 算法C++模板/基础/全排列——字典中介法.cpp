# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 10010;

int n, m;
int a[NR];
int mid[NR]; // mid[i]表示排列中第i位后面比a[i]小的数的个数
bool flag[NR]; // flag[i]表示新排列中数字i是否被使用 

bool permutation()
{
	for (int i = 1; i <= n - 1; i++)
		for (int j = i + 1; j <= n; j++)
			mid[i] += (a[i] > a[j]);
	mid[n - 1] += m;
	for (int i = n - 1; i > 0 && mid[i] >= n - i + 1; i--) {
		mid[i - 1] += mid[i] / (n - i + 1); // 第i位的进位制为n-i+1
		mid[i] %= n - i + 1;
	}
	if (mid[0] > 0) return false;
	for (int i = 1; i <= n; i++) {
		int pos = 1;
		for (int j = 0; pos <= n; pos++) {
			j += !flag[pos];
			if (j > mid[i]) break;
		}
		flag[pos] = true;
		a[i] = pos;
	}
	return true;
}

int main()
{
	scanf("%d", &n);
	scanf("%d", &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	permutation();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
