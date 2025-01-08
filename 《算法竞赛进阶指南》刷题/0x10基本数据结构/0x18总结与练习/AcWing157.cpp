# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

int now = 0;
string str;

string doit()
{
	vector<string> v;
	while (str[++now] == '0') v.push_back(doit());
	sort(v.begin(), v.end());
	string ans = "";
	for (int i = 0; i < (int) v.size(); i++)
		ans += v[i];
	return "0" + ans + "1";
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		cin >> str;
		str = "0" + str + "1";
		now = 0;
		string x = doit();

		cin >> str;
		str = "0" + str + "1";
		now = 0;
		string y = doit();

		if (x == y) puts("same");
		else puts("different");
	}
	return 0;
}