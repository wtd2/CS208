#include <bits/stdc++.h>

#define clr(x) memset(x, -1, sizeof(x))

using namespace std;

int dp[2][31][301], c[91], v[91];

int main() {
	int M; scanf("%d", &M);
	for(int i = 1; i <= 90; i++) {
		int x, y; scanf("%d%d%d", &c[i], &x, &y);
		v[i] = x + y;
	}
	clr(dp); dp[0][0][0] = 0; 
	for(int i = 1; i <= 90; i++) {
		int cur = i & 1, pre = cur ^ 1;
		clr(dp[cur]);
		for(int j = 0; j <= min(i, 30); j++) 
			for(int k = 0; k <= M; k++) if(dp[pre][j][k] != -1) {
				dp[cur][j][k] = max(dp[cur][j][k], dp[pre][j][k]);
				if(j + 1 <= 30 && k + c[i] <= M) 
					dp[cur][j + 1][k + c[i]] = max(dp[cur][j + 1][k + c[i]], dp[pre][j][k] + v[i]);
		}
	}
	int ans = 0;
	for(int k = 0; k <= M; k++) ans = max(ans, dp[0][30][k]);
	printf("%d\n", ans);
	return 0;
}