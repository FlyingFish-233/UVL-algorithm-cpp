# include <cstdio>
# include <algorithm>
# include <cstring>
# include <cmath>

using namespace std;

const int NR = 20;

int n;
int a[NR];
int face[NR]; // face[i]��ʾa[i]��ָ�� 

// ��һ��������ָ����ָ���������䴦�ڻ״̬ 
bool canMove(int x)
{
	int y = x + face[x];
	return y >= 1 && y <= n && a[x] > a[y];
}

// ÿ���ҵ����ڻ״̬��������a[pos]
// ����a[pos]��a[pos+face[pos]]����ָ�� 
// �����д���a[pos]������ָ��ȡ�� 
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
