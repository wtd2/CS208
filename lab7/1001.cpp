#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxm = 1000010;

struct edge {
    int u, v, w;
    bool operator< (const edge &rhs) const {
        return w < rhs.w;
    }
}e[maxm];

int c[maxm], n, m, fa[maxm];

int id(int x, int y) {
    return (x - 1) * m + y;
}

int find(int x) {
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d", &c[id(i, j)]);
        }
    } int cnt = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fa[id(i, j)] = id(i, j);
            if(i != n) e[++cnt] = (edge){id(i, j), id(i + 1, j), c[id(i, j)] ^ c[id(i + 1, j)]};
            if(j != m) e[++cnt] = (edge){id(i, j), id(i, j + 1), c[id(i, j)] ^ c[id(i, j + 1)]};
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