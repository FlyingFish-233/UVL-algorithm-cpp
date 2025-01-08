// P1177 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 100010;

int n;
int a[NR];

void shellSort()
{
	for (int gap = n / 2; gap >= 1; gap /= 2)
		for (int i = gap + 1; i <= n; i++)
			for (int j = i - gap; j >= 1 && a[j] > a[j + gap]; j -= gap)
				swap(a[j], a[j + gap]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	shellSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
