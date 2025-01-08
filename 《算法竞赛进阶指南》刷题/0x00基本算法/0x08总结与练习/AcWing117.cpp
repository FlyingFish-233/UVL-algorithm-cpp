# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <deque>

using namespace std;

int cnt[20];
deque< pair<int, bool> > q[20];

int main()
{
	for (int i = 1; i <= 13; i++)
		for (int j = 1; j <= 4; j++) {
			char c; int x;
			cin >> c;
			switch (c) {
				case '0': x = 10; break;
				case 'J': x = 11; break;
				case 'Q': x = 12; break;
				case 'K': x = 13; break;
				case 'A': x = 1; break;
				default: x = c - '0';
			}
			q[i].push_back(make_pair(x, false));
		}
	for (int i = 1; i <= 4; i++) {
		int x = q[13].front().first;
		bool up = q[13].front().second;
		q[13].pop_front();
		while (x < 13) {
			if (!up) cnt[x]++;
			q[x].push_front(make_pair(x, true));
			int tmp = x;
			x = q[tmp].back().first;
			up = q[tmp].back().second;
			q[tmp].pop_back();
		}
	}
	int ans = 0;
	for (int i = 1; i <= 12; i++)
		if (cnt[i] == 4) ans++;
	printf("%d\n", ans);
	return 0;
}