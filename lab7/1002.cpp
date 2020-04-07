#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxm = 4000040;

struct edge {
    int u, v, w;
    bool operator< (const edge &rhs) const {
        return w < rhs.w;
    }
}e[maxm];

int n, m, fa[maxm];

int find(int x) {
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}

int main() {
    scanf("%d", &n); int cnt = 0;
    for(int i = 1; i <= n + 1; i++) fa[i] = i;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n - i + 1; j++) {
            int x; scanf("%d", &x);
            e[++cnt] = (edge){i, i + j, x};
        }
    }
    sort(e + 1, e + cnt + 1);
    ll ans = 0;
    for(int i = 1; i <= cnt; i++) {
        int fx = find(e[i].u), fy = find(e[i].v);
        if(fx != fy) {
            ans += 1ll * e[i].w; fa[fx] = fy;
        }
    }
    printf("%lld\n", ans);
    return 0;
}