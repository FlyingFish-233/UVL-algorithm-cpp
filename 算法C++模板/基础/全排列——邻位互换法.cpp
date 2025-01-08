# include <cstdio>
# include <algorithm>
# include <cstring>
# include <cmath>

using namespace std;

const int NR = 20;

int n;
int a[NR];
int face[NR]; // face[i]表示a[i]的指针 

// 若一个数比它指针所指的数大，则其处于活动状态 
bool canMove(int x)
{
	int y = x + face[x];
	return y >= 1 && y <= n && a[x] > a[y];
}

// 每次找到处于活动状态的最大的数a[pos]
// 交换a[pos]和a[pos+face[pos]]及其指针 
// 将所有大于a[pos]的数的指针取反 
bool permutation()
{
	int a_max = 0, pos = -1;
	for (int i = 1; i <= n; i++) {
		if (!canMove(i) || a_max > a[i]) continue;
		a_max = a[i], pos = i;
	}
	if (pos == -1) return false;
	int pos_to = pos + face[pos];
	swap(a[pos], a[pos_to]);
	swap(face[pos], face[pos_to]);
	for (int i = 1; i <= n; i++)
		if (a[i] > a_max) face[i] = -face[i];
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		a[i] = i;
	memset(face, -1, sizeof(face));
	do {
		for (int i = 1; i <= n; i++)
			printf("%5d", a[i]);
		printf("\n");
	} while (permutation());
	return 0;
}
