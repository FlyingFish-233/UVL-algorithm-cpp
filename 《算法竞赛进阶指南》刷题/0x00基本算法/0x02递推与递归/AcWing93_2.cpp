# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

int n, m;
vector <int> chosen;
int top, address, stack[100010];

void call(int x, int ret_addr)
{
	int old_top = top;
	stack[++top] = x;
	stack[++top] = ret_addr;
	stack[++top] = old_top;
	address = 0;
}

int ret()
{
	int ret_addr = stack[top - 1];
	top = stack[top];
	return ret_addr;
}

int main()
{
	scanf("%d%d", &n, &m);
	call(1, 0);
	while (top) {
		int x = stack[top - 2];
		switch (address) {
			case 0 :
				if ((int) chosen.size() > m || (int) chosen.size() + n - x + 1 < m) {
					address = ret();
					continue;
				}
				if (x > n) {
					for (int i = 0; i < (int) chosen.size(); i++)
						printf("%d ", chosen[i]);
					puts("");
					address = ret();
					continue;
				}
				chosen.push_back(x);
				call(x + 1, 1);
				continue;

			case 1 :
				chosen.pop_back();
				call(x + 1, 2);
				continue;

			case 2 :
				address = ret();
		}
	}
	return 0;
}