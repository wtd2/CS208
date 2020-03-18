#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;
typedef long long ll;

int num[11], st[11], n, sum = 0, u, v;
unordered_map<ll, ll> dp[11];

ll dfs(int cur, int versus) {
    if(cur == versus) {
        if(cur == n) {
            if(num[n] == 0) return 1;
            else return 0;
        }
        if(num[cur] != 0) return 0; ll state = 0;
        for(int i = cur + 1; i <= n; i++) st[i] = num[i];
        sort(st + cur + 1, st + n + 1);
        for(int i = cur + 1; i <= n; i++) {
            state = 28ll * state + st[i];
        }
        if(dp[cur].count(state) != 0) return dp[cur][state];
        else return dp[cur][state] = dfs(cur + 1, n);
    }
    ll ans = 0;
    if((versus - cur) <= u && (versus - cur) * 3 < num[cur]) return 0;
    if((versus - cur) > u && (u * 3 + (versus - cur - u)) < num[cur]) return 0;
    if(u > 0) {
        // 0:3
        if(num[versus] >= 3) {
            num[versus] -= 3; u--;
            ans += dfs(cur, versus - 1);
            num[versus] += 3; u++;
        }
        // 1:2
        if(num[versus] >= 2 && num[cur] >= 1) {
            num[cur] -= 1; num[versus] -= 2; u--;
            ans += dfs(cur, versus - 1);
            num[cur] += 1; num[versus] += 2; u++;
        }
    }
    if(v > 0) {
        // 1:1
        if(num[versus] >= 1 && num[cur] >= 1) {
            num[cur] -= 1; num[versus] -= 1; v--;
            ans += dfs(cur, versus - 1);
            num[cur] += 1; num[versus] += 1; v++;
        }
    }
    if(u > 0) {
        // 2:1
        if(num[versus] >= 1 && num[cur] >= 2) {
            num[cur] -= 2; num[versus] -= 1; u--;
            ans += dfs(cur, versus - 1);
            num[cur] += 2; num[versus] += 1; u++;
        }
        // 3:0
        if(num[cur] >= 3) {
            num[cur] -= 3; u--;
            ans += dfs(cur, versus - 1);
            num[cur] += 3; u++;
        }
    }
    return ans % mod;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &num[i]), sum += num[i];
    int tot = n * (n - 1) / 2;
    u = sum - 2 * tot; v = tot - u;
    if(u < 0 || v < 0) return puts("0"), 0;
    sort(num + 1, num + n + 1);
    printf("%lld\n", dfs(1, n));
    return 0;
}