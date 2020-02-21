#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;

unordered_map<string, int> mb, mg;

string bname[maxn], gname[maxn], name;
int brk[maxn][maxn], grk[maxn][maxn], top[maxn];
int bch[maxn], gch[maxn];

int main() {
	ios::sync_with_stdio(0);
	int n; cin >> n;

	cin >> bname[0];
	for(int j = 0; j < n; j++) cin >> gname[j], mg[gname[j]] = j, brk[0][j] = j;
	for(int i = 1; i < n; i++) {
		cin >> bname[i];
		for(int j = 0; j < n; j++) {
			cin >> name; brk[i][j] = mg[name];
		}
	}
	for(int i = 0; i < n; i++) {
		mb[bname[i]] = i; bch[i] = -1; top[i] = 0;
	}

	for(int i = 0; i < n; i++) {
		cin >> name; int id = mg[name];
		for(int j = 0; j < n; j++) {
			cin >> name;
			grk[id][mb[name]] = j;
		}
		gch[i] = -1;
	}

	int tot = 0;
	while(tot < n) {
		for(int i = 0; i < n; i++) if(bch[i] == -1) {
			int love = brk[i][top[i]++];
			if(gch[love] == -1) {
				gch[love] = i;
				bch[i] = love;
				tot++;
			} else if(grk[love][gch[love]] > grk[love][i]) {
				bch[gch[love]] = -1;
				gch[love] = i;
				bch[i] = love;
			}
		}
	}
	for(int i = 0; i < n; i++) {
		cout << bname[i] << " " << gname[bch[i]] << "\n";
	}
	return 0;
}