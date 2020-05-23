#include <bits/stdc++.h>

using namespace std;

int c[101][101], v[101][101], dp[2][1001];

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= k; j++) {
			int x, y; scanf("%d%d%d", &c[i][j], &x, &y);
			v[i][j] = x + y;
		}
	}
	for(int pos = 1; pos <= n; pos++) {
		int cur = pos & 1, lst = cur ^ 1;
		for(int i = 0; i <= m; i++) dp[cur][i] = dp[lst][i];
		for(int i = 0; i <= m; i++) {
			for(int j = 1; j <= k; j++) if(i + c[pos][j] <= m) {
				dp[cur][i + c[pos][j]] = max(dp[cur][i + c[pos][j]], dp[lst][i] + v[pos][j]);
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= m; i++) ans = max(ans, dp[n & 1][i]);
	printf("%d\n", ans);
	return 0;
}