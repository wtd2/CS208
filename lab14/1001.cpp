#include <bits/stdc++.h>

namespace dinic {

    #define clr(x) memset(x, 0, sizeof(x))

    using namespace std;

    const int maxn = 100010, maxm = 200020;

    struct edge {int to, next, w;} e[maxm];

    int q[maxn], dis[maxn], head[maxn], cur[maxn], cnt = 1, S, T;

    void init() {
        clr(head); clr(cur); cnt = 1;
    }

    void insert(int u, int v, int w) {
        e[++cnt].to = v; e[cnt].next = head[u]; e[cnt].w = w; head[u] = cnt;
        e[++cnt].to = u; e[cnt].next = head[v]; e[cnt].w = 0; head[v] = cnt;
    }

    bool bfs() {
        clr(dis); dis[S] = 1;
        int h = 0, t = 0; q[t++] = S;
        while(h < t) {
            int u = q[h++];
            for(int i = head[u]; i; i = e[i].next) if(!dis[e[i].to] && e[i].w > 0)
                dis[e[i].to] = dis[u] + 1, q[t++] = e[i].to;
        }
        return (dis[T] > 0);
    }

    int dfs(int u, int res) {
        if(u == T || res == 0) return res;
        int ret = 0;
        for(int i = cur[u]; i; i = e[i].next) if(dis[e[i].to] == dis[u] + 1 && e[i].w > 0) {
            int v = e[i].to, flow = dfs(v, min(res - ret, e[i].w));
            e[i].w -= flow; e[i ^ 1].w += flow; ret += flow;
            if(e[i].w > 0) cur[u] = i;
            if(ret == res) break;
        }
        if(ret == 0) dis[u] = 0;
        return ret;
    }

    int dinic() {
        int ret = 0;
        while(bfs()) {
            for(int i = S; i <= T; i++) cur[i] = head[i];
            ret += dfs(S, 1 << 30);
        }
        return ret;
    }

}

using dinic::S;
using dinic::T;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    S = 0; T = n + 1;
    for(int i = 1; i <= n; i++) {
        int st; scanf("%d", &st);
        if(st) dinic::insert(S, i, 1);
        else dinic::insert(i, T, 1);
    }
    for(int i = 1; i <= m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        dinic::insert(u, v, 1);
        dinic::insert(v, u, 1);
    }
    printf("%d\n", dinic::dinic());
    return 0;
}