# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <map>
# include <queue>

using namespace std;

int cnt;
string S, T;
string a[2][20];

map<string, int> dis[2];
queue< pair<string, int> > q[2];

int bfs(int t, int lim)
{
	while (!q[t].empty() && q[t].front().second < lim) {
		string s = q[t].front().first;
		int d = q[t].front().second;
		q[t].pop();
		for (int i = 0; i < cnt; i++)
			for (int pos = s.find(a[t][i], 0); pos != -1; pos = s.find(a[t][i], pos + 1)) {
				string s0 = s;
				s0.erase(pos, a[t][i].size());
				s0.insert(pos, a[!t][i]);
				if (dis[t].count(s0) > 0) continue;
				q[t].push(make_pair(s0, dis[t][s0] = d + 1));
				if (dis[!t].count(s0) > 0) return dis[t][s0] + dis[!t][s0];
			}
	}
	return -1;
}

int main()
{
	cin >> S >> T;
	if (S == T) {
		printf("0\n");
		return 0;
	}
	while (cin >> a[0][cnt] >> a[1][cnt]) cnt++;
	q[0].push(make_pair(S, dis[0][S] = 0));
	q[1].push(make_pair(T, dis[1][T] = 0));
	for (int i = 1; i <= 5; i++)
		for (int t = 0; t <= 1; t++) {
			int save = bfs(t, i);
			if (save != -1) {
				printf("%d\n", save);
				return 0;
			}
		}
	printf("NO ANSWER!\n");
	return 0;
}