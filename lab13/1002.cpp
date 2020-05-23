#include <bits/stdc++.h>

#define clr(x) memset(x, 0, sizeof(x))

using namespace std;

const int maxn = 100010, mod = 998244353;

int dp[2][201][2], tot[201][2], x[maxn];

void get_sum(int pos) {
    clr(tot);
    for(int i = 1; i <= 200; i++) 
        for(int j = 0; j < 2; j++)
            tot[i][j] = (tot[i - 1][j] + dp[pos][i][j]) % mod;
}

int main() {
    int n; scanf("%d", &n); clr(dp);
    for(int i = 1; i <= n; i++) scanf("%d", &x[i]);
    if(x[1] == -1) {
        for(int i = 1; i <= 200; i++) dp[1][i][0] = 1;
    } else dp[1][x[1]][0] = 1;
    get_sum(1);
    for(int t = 2; t <= n; t++) {
        int cur = t & 1, lst = cur ^ 1;
        clr(dp[cur]);
        if(x[t] == -1) {
            for(int i = 1; i <= 200; i++) {
                dp[cur][i][0] = (tot[i - 1][0] + tot[i - 1][1]) % mod;
                dp[cur][i][1] = ((dp[lst][i][0] + dp[lst][i][1]) % mod + (tot[200][1] - tot[i][1] + mod) % mod) % mod;
            }
        } else {
            int i = x[t];
            dp[cur][i][0] = (tot[i - 1][0] + tot[i - 1][1]) % mod;
            dp[cur][i][1] = ((dp[lst][i][0] + dp[lst][i][1]) % mod + (tot[200][1] - tot[i][1] + mod) % mod) % mod;
        }
        get_sum(cur);
    }
    int ans = 0;
    for(int i = 1; i <= 200; i++) ans = (ans + dp[n & 1][i][1]) % mod;
    printf("%d\n", ans);
    return 0;
}