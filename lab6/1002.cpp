#include <bits/stdc++.h>

#define mp make_pair
#define pii pair<ll, int>
#define clr(x) memset(x, 0, sizeof(x))
#define reg(i, u, v) for(int i = head[u], v = e[i].to; i; i = e[i].next, v = e[i].to)

using namespace std;

typedef long long ll;

const int maxn = 50010, maxm = 500010;

ll dis[maxn], a[maxn], b[maxn]; int head[maxn], cnt = 1, n, m, S, T; bool vis[maxn];
priority_queue<pii, vector<pii>, greater<pii> > pq;

struct edge {
    int to, next; ll w;
}e[maxm];

void insert(int u, int v, int w) {
    e[++cnt].to = v; e[cnt].next = head[u]; e[cnt].w = 1ll * w; head[u] = cnt;
}

ll calc(ll x, int u) {
    if(x % (a[u] + b[u]) < a[u]) return (x / (a[u] + b[u])) * (a[u] + b[u]) + a[u];
    else return x;
}

void dijkstra() {
    dis[S] = 0; pq.push(mp(dis[S], S));
    while(!pq.empty()) {
        pii p = pq.top(); pq.pop(); int u = p.second;
        if(vis[u]) continue; vis[u] = 1;
        reg(i, u, v) if(dis[v] > calc(dis[u] + e[i].w, v)) {
            dis[v] = calc(dis[u] + e[i].w, v);
            pq.push(mp(dis[v], v));
        }
    }
}

int main() {
    scanf("%d%d", &n, &m); clr(vis); clr(head);
    memset(dis, 0x3f, sizeof(dis));
    for(int i = 0; i < m; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        insert(u, v, w);
    }
    for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &b[i]);
    S = 1; T = n;
    dijkstra();
    printf("%lld\n", dis[T]);
    return 0;
}