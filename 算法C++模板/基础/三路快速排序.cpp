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
    int i = l, t1 = l, t2 = r, key = a[(l + r) >> 1];
    while (i <= t2) {
    	if (a[i] < key) swap(a[i++], a[t1++]);
    	else if (a[i] > key) swap(a[i], a[t2--]);
    	else i++;
    }
    quickSort(l, t1 - 1), quickSort(t2 + 1, r);
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
