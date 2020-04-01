#include <bits/stdc++.h>

#define double long double
#define mp make_pair
#define pii pair<double, int>
#define clr(x) memset(x, 0, sizeof(x))
#define reg(i, u, v) for(int i = head[u], v = e[i].to; i; i = e[i].next, v = e[i].to)

using namespace std;

const int maxn = 10010, maxm = 1000010, mod = 19260817;

double dis[maxn]; int head[maxn], conn[maxn], d[maxn], cnt = 1, n, m, S, T; bool vis[maxn];
priority_queue<pii, vector<pii>, greater<pii> > pq;

struct edge {
    int to, next, raw_w;
    double w;
}e[maxm];

void insert(int u, int v, int w) {
    e[++cnt].to = v; e[cnt].next = head[u]; e[cnt].raw_w = w; e[cnt].w = log((double)w); head[u] = cnt;
}

void dijkstra() {
    dis[S] = 0; pq.push(mp(dis[S], S));
    while(!pq.empty()) {
        pii p = pq.top(); pq.pop(); int u = p.second;
        if(vis[u]) continue; vis[u] = 1;
        reg(i, u, v) if(dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                conn[v] = u; d[v] = e[i].raw_w;
                pq.push(mp(dis[v], v));
            }
    }
}

int main() {
    scanf("%d%d", &n, &m); clr(vis); clr(head);
    for(int i = 1; i <= n; i++) dis[i] = 1e9;
    for(int i = 0; i < m; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        insert(u, v, w);
    }
    S = 1; T = n;
    dijkstra();
    int ans = 1, cur = n;
    while(cur != 1) {
        ans = 1ll * ans * d[cur] % mod;
        cur = conn[cur];
    }
    printf("%d\n", ans);
    return 0;
}