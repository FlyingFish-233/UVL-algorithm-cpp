// P1177 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 100010;

int n;
int a[NR];

void quickSort(int l, int r)
{
	if (l >= r) return;
    int t1 = l, t2 = r, key = a[(l + r) >> 1];
    do {
        while (a[t1] < key) t1++;
        while (a[t2] > key) t2--;
        if (t1 <= t2) swap(a[t1++],a[t2--]);
    } while (t1 <= t2);
    quickSort(l, t2), quickSort(t1, r);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	quickSort(1, n);
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
