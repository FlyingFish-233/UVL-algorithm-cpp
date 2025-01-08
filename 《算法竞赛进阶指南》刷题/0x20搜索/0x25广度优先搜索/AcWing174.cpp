# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 30;
const int face[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char ch[4][2] = {{'n', 'N'}, {'s', 'S'}, {'w', 'W'}, {'e', 'E'}};

struct Node
{
	int sta, x, y;
	string s;
};

int n, m;
char c[NR][NR];

bool check(int x, int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m && c[x][y] != '#';
}

string modify(int x1, int y1, int x2, int y2)
{
	bool vis[NR][NR];
	memset(vis, false, sizeof(vis));
	vis[x1][y1] = true;

	queue<Node> q;
	q.push((Node) {-1, x1, y1, ""});

	while (!q.empty()) {
		int x = q.front().x, y = q.front().y;
		string s = q.front().s;
		q.pop();
		if (x == x2 && y == y2) return s;
		for (int i = 0; i < 4; i++) {
			int x0 = x + face[i][0], y0 = y + face[i][1];
			if (!check(x0, y0) || vis[x0][y0]) continue;
			vis[x0][y0] = true;
			q.push((Node) {-1, x0, y0, s + ch[i][0]});
		}
	}
	return "!";
}

int value(char x)
{
	for (int i = 0; i < 4; i++)
		if (ch[i][0] == x) return i;
	for (int i = 0; i < 4; i++)
		if (ch[i][1] == x) return i + 4;
	return 8;
}

bool cmp(string s1, string s2)
{
	int len1 = s1.length(), len2 = s2.length();
	string a1 = "", a2 = "";
	for (int i = 1; i < len1; i++)
		if (s1[i] >= 'A' && s1[i] <= 'Z') a1 += s1[i];
	for (int i = 1; i < len2; i++)
		if (s2[i] >= 'A' && s2[i] <= 'Z') a2 += s2[i];
	int num1 = a1.length(), num2 = a2.length();
	if (num1 != num2) return num1 < num2;
	if (len1 != len2) return len1 < len2;
	for (int i = 0; i < len1; i++)
		if (value(s1[i]) != value(s2[i])) return value(s1[i]) < value(s2[i]);
	return false;
}

int main()
{
	int cnt = 0;
	while (scanf("%d%d", &n, &m) && n && m) {
		cnt++;
		for (int i = 1; i <= n; i++)
			scanf("%s", c[i] + 1);
		int Sx, Sy, Tx, Ty, Bx, By;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (c[i][j] == 'B') Bx = i, By = j;
				if (c[i][j] == 'S') Sx = i, Sy = j;
				if (c[i][j] == 'T') Tx = i, Ty = j;
				if (c[i][j] != '#') c[i][j] = '.';
			}

		bool vis[NR][NR][4];
		memset(vis, false, sizeof(vis));
		queue<Node> q;
		c[Bx][By] = '#';
		for (int i = 0; i < 4; i++) {
			int x0 = Bx + face[i][0], y0 = By + face[i][1];
			if (!check(x0, y0)) continue;
			string s = modify(Sx, Sy, x0, y0);
			if (s == "!") continue;
			vis[Bx][By][i] = true;
			q.push((Node) {i, Bx, By, s});
		}
		c[Bx][By] = '.';

		string ans = "!";
		cout << "Maze #" << cnt << endl;
		while (!q.empty()) {
			int sta = q.front().sta, x = q.front().x, y = q.front().y;
			string s = q.front().s;
			q.pop();

			if (x == Tx && y == Ty) {
				if (ans == "!" || cmp(s, ans)) ans = s;
				continue;
			}

			int x0 = x + face[sta ^ 1][0], y0 = y + face[sta ^ 1][1];
			if (check(x0, y0) && !vis[x0][y0][sta]) {
				vis[x0][y0][sta] = true;
				q.push((Node) {sta, x0, y0, s + ch[sta ^ 1][1]});
			}
			c[x][y] = '#';
			for (int i = 0; i < 4; i++) {
				x0 = x + face[i][0], y0 = y + face[i][1];
				if (i == sta || vis[x][y][i] || !check(x0, y0)) continue;
				string s0 = modify(x + face[sta][0], y + face[sta][1], x0, y0);
				if (s0 == "!") continue;
				vis[x][y][i] = true;
				q.push((Node) {i, x, y, s + s0});
			}
			c[x][y] = '.';
		}
		if (ans == "!") cout << "Impossible." << endl << endl;
		else cout << ans << endl << endl;
	}
	return 0;
}