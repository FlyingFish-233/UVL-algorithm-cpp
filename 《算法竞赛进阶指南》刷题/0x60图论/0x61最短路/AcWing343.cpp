# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 30, MR = 1e3 + 10;

int n, m;
int u[MR], v[MR];
bool vis[NR], g[NR][NR];


void floyd()
{
	for (int k = 1; k <= 26; k++)
		for (int i = 1; i <= 26; i++)
			for (int j = 1; j <= 26; j++)
				g[i][j] |= g[i][k] & g[k][j];
}

bool wrong()
{
	for (int i = 1; i <= 26; i++)
		for (int j = i + 1; j <= 26; j++)
			if (g[i][j] && g[j][i]) return true;
	return false;
}

bool right()
{
	int cnt = 0;
	for (int i = 1; i <= 26; i++)
		for (int j = i + 1; j <= 26; j++)
			if (g[i][j] ^ g[j][i]) cnt++;
	return cnt == (n - 1) * n / 2;
}

int in[NR];
queue<int> q;

string topSort()
{
	memset(in, 0, sizeof(in));
	for (int i = 1; i <= 26; i++)
		for (int j = 1; j <= 26; j++)
			if (g[i][j]) in[j]++;
	for (int i = 1; i <= 26; i++)
		if (in[i] == 0 && vis[i]) q.push(i);
	string ans = "";
	while (!q.empty()) {
		int x = q.front(); q.pop();
		ans += x + 'A' - 1;
		for (int i = 1; i <= 26; i++)
			if (g[x][i] && --in[i] == 0) q.push(i);
	}
	return ans;
}

int main()
{
	while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0)) {
		memset(g, false, sizeof(g));
		memset(vis, false, sizeof(vis));
		for (int i = 1; i <= m; i++) {
			string s;
			cin >> s;
			vis[u[i] = s[0] - 'A' + 1] = true;
			vis[v[i] = s[2] - 'A' + 1] = true;
		}
		bool flag = false;
		for (int i = 1; i <= m; i++) {
			g[u[i]][v[i]] = true;
			floyd();
			if (wrong()) {
				flag = true;
				printf("Inconsistency found after %d relations.\n", i);
				break;
			}
			if (right()) {
				flag = true;
				printf("Sorted sequence determined after %d relations: ", i);
				cout << topSort() << "." << endl;
				break;
			}
		}
		if (!flag) printf("Sorted sequence cannot be determined.\n");
	}
	return 0;
}