#include <bits/stdc++.h>

#define clr(x) memset(x, 0, sizeof(x))

using namespace std;

const int maxn = 1000100, inf = 1e9;

int cnt[maxn], dp[2][5][5];

int main() {
	clr(cnt);
	int n, m; scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		cnt[x]++;
	}
	if(m == 1) return printf("%d\n", cnt[1] / 3), 0;
	for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++) dp[0][i][j] = -inf;
	for(int i = 0; i < 5; i++) if(cnt[1] >= i) {
		for(int j = 0; j < 5; j++) if(cnt[2] >= j) {
			dp[0][i][j] = (cnt[1] - i) / 3 + (cnt[2] - j) / 3;
		}
	}
	// for(int i = 1; i <= m; i++) printf("%d ", cnt[i]); puts("");
	for(int pos = 3; pos <= m; pos++) {
		int cur = pos & 1, pre = cur ^ 1;
		for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++) dp[cur][i][j] = -inf;
		for(int i = 0; i < 3; i++) for(int j = 0; j < 5; j++) {
			for(int k = 0; k < 3; k++) if(k <= min(i, j) && k <= cnt[pos]) {
				for(int l = 0; l < 5; l++) if(k <= cnt[pos] - l){
					dp[cur][j - k][l] = max(dp[cur][j - k][l], dp[pre][i][j] + (cnt[pos] - k - l) / 3 + k);
				}
			}
		}
		for(int i = 3; i >= 0; i--) for(int j = 0; j < 5; j++) dp[cur][i][j] = max(dp[cur][i][j], dp[cur][i + 1][j]);
	}
	int cur = m & 1, ans = 0;
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) ans = max(ans, dp[cur][i][j]);
	printf("%d\n", ans);
	return 0;
}