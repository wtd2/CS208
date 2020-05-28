#include <bits/stdc++.h>

#define clr(x) memset(x, -1, sizeof(x))

using namespace std;

int dp[2][101][10100], a[101], b[101], id[101];

int main() {
    int n, sum = 0; clr(dp);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        sum += a[i]; id[i] = b[i]; b[i] = 100 - b[i];
    }
    sort(id + 1, id + n + 1, greater<int>());
    int cnt = 0, tot = 0;
    while(tot < sum) {
        tot += id[++cnt];
    } int m = 100 * cnt - sum;
    clr(dp); dp[0][0][0] = 0;
    for(int pos = 1; pos <= n; pos++) {
        int cur = pos & 1, lst = cur ^ 1; clr(dp[cur]);
        for(int i = 0; i < max(pos, cnt); i++) {
            for(int j = 0; j <= m; j++) {
                dp[cur][i][j] = max(dp[cur][i][j], dp[lst][i][j]);
                if(dp[lst][i][j] != -1 && j + b[pos] <= m)
                    dp[cur][i + 1][j + b[pos]] = max(dp[cur][i + 1][j + b[pos]], dp[lst][i][j] + a[pos]);
            }
        }
    }
    int ans = 0;
    for(int j = 0; j <= m; j++) {
        ans = max(ans, dp[n & 1][cnt][j]);
    }
    printf("%d\n", sum - ans);
    return 0;
}