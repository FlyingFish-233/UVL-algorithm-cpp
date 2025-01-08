// P1177 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>
# include <vector>

using namespace std;

const int NR = 1e5 + 10, MR = 1e6 + 10;
const int sz = 1e3;

int n;
int a[NR];
vector<int> bucket[MR];

void insertionSort(vector<int> &v)
{
	for (int i = 0; i < (int) v.size(); i++)
		for (int j = i - 1; j >= 0 && v[j] > v[j + 1]; j--)
			swap(v[j], v[j + 1]);
}

void bucketSort()
{
	int a_max = -2e9, a_min = 2e9;
	for (int i = 1; i <= n; i++)
		a_max = max(a_max, a[i]), a_min = min(a_min, a[i]);
	int tot = (a_max - a_min) / sz;
	for (int i = 0; i <= tot; i++)
		bucket[i].clear();
	for (int i = 1; i <= n; i++)
		bucket[(a[i] - a_min) / sz].push_back(a[i]);
	int tmp = 0;
	for (int i = 0; i <= tot; i++) {
		insertionSort(bucket[i]);
		for (int j = 0; j < (int) bucket[i].size(); j++)
			a[++tmp] = bucket[i][j];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	bucketSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
