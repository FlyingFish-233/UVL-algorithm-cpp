// AcWing179 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 5e5 + 10;
const int nxt[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char c[4] = {'u', 'd', 'l', 'r'};

string S, T = "123456780";

int f(string s)
{
	int now = 0;
	for (int i = 0; i < 9; i++) {
		int pos = T.find(s[i]);
		now += abs(i / 3 - pos / 3) + abs(i % 3 - pos % 3);
	}
	return now;
}

struct Node
{
	string s;
	int d;

	bool operator < (const Node &cmp) const {
		return d + f(s) > cmp.d + f(cmp.s);
	}
};

priority_queue<Node> q;
int dis[NR];
bool vis[NR];

int pre[NR], face[NR];

int factory[10];

int Cantor(string s)
{
	int now = 0;
	for (int i = 0; i < 9; i++)
		for (int j = i + 1; j < 9; j++)
			if (s[i] > s[j]) now += factory[9 - i - 1];
	return now;
}

bool check()
{
	int cnt = 0;
	for (int i = 0; i < 9; i++) if (S[i] != '0')
		for (int j = i + 1; j < 9; j++)
			if (S[j] != '0' && S[i] > S[j]) cnt++;
	return cnt & 1;
}

void print(int now)
{
	if (now == Cantor(S)) return;
	print(pre[now]);
	putchar(c[face[now]]);
}

int main()
{
	for (int i = 0; i < 9; i++) {
		char c;
		cin >> c;
		if (c == 'x') S += '0';
		else S += c;
	}
	if (check()) {
		printf("unsolvable\n");
		return 0;
	}
	factory[0] = 1;
	for (int i = 1; i < 9; i++)
		factory[i] = factory[i - 1] * i;
	memset(dis, 0x3f, sizeof(dis));
	q.push((Node) {S, dis[Cantor(S)] = 0});
	while (!q.empty()) {
		string s = q.top().s;
		q.pop();
		if (s == T) break;
		int pos = s.find('0'), x = pos / 3, y = pos % 3;
		int save = Cantor(s);
		if (vis[save]) continue;
		vis[save] = true;
		for (int i = 0; i < 4; i++) {
			int x0 = x + nxt[i][0], y0 = y + nxt[i][1];
			if (x0 < 0 || y0 < 0 || x0 > 2 || y0 > 2) continue;
			string s0 = s;
			swap(s0[x * 3 + y], s0[x0 * 3 + y0]);
			int save0 = Cantor(s0);
			if (vis[save0] || dis[save0] <= dis[save] + 1) continue;
			pre[save0] = save, face[save0] = i;
			q.push((Node) {s0, dis[save0] = dis[save] + 1});
		}
	}
	print(Cantor(T));
	return 0;
}