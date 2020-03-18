#include <bits/stdc++.h>

using namespace std;

char str[10];
int st[10][10], deg[10][10], q[101], n, ans = 0, cnt = 0;

inline int idx(int id) {return (id / n) + 1;}
inline int idy(int id) {return (id % n) + 1;}
inline int id(int x, int y) {return (x - 1) * n + (y - 1);}

void dfs(int x, int y, int tot) {
    if (x == n && y == 1) {
        if (tot == cnt) ans++;
        return;
    }
    int h = 0, t = 0, ok = 1;
    q[t++] = id(n, 1);
    st[n][1] = 2;
    while (h < t) {
        int u = idx(q[h]), v = idy(q[h++]);
        if (u != 1 && st[u - 1][v] == 0) {
            st[u - 1][v] = 2;
            q[t++] = id(u - 1, v);
        }
        if (u != n && st[u + 1][v] == 0) {
            st[u + 1][v] = 2;
            q[t++] = id(u + 1, v);
        }
        if (v != 1 && st[u][v - 1] == 0) {
            st[u][v - 1] = 2;
            q[t++] = id(u, v - 1);
        }
        if (v != n && st[u][v + 1] == 0) {
            st[u][v + 1] = 2;
            q[t++] = id(u, v + 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (st[i][j] == 2) st[i][j] = 0;
            else if (st[i][j] == 0) ok = 0;
        }
    }
    if (!ok) return;

    int dx = -1, dy = -1;
    if (x != 1 && st[x - 1][y] == 0) {
        deg[x - 1][y]--;
        if (deg[x - 1][y] == 1) dx = -1, dy = 0;
    }
    if (x != n && st[x + 1][y] == 0) {
        deg[x + 1][y]--;
        if (deg[x + 1][y] == 1) dx = 1, dy = 0;
    }
    if (y != 1 && st[x][y - 1] == 0) {
        deg[x][y - 1]--;
        if (deg[x][y - 1] == 1) dx = 0, dy = -1;
    }
    if (y != n && st[x][y + 1] == 0) {
        deg[x][y + 1]--;
        if (deg[x][y + 1] == 1) dx = 0, dy = 1;
    }

    if (!(dx == -1 && dy == -1)) {
        st[x + dx][y + dy] = 1;
        dfs(x + dx, y + dy, tot + 1);
        st[x + dx][y + dy] = 0;
    } else {
        if (x != 1 && st[x - 1][y] == 0) {
            st[x - 1][y] = 1;
            dfs(x - 1, y, tot + 1);
            st[x - 1][y] = 0;
        }
        if (x != n && st[x + 1][y] == 0) {
            st[x + 1][y] = 1;
            dfs(x + 1, y, tot + 1);
            st[x + 1][y] = 0;
        }
        if (y != 1 && st[x][y - 1] == 0) {
            st[x][y - 1] = 1;
            dfs(x, y - 1, tot + 1);
            st[x][y - 1] = 0;
        }
        if (y != n && st[x][y + 1] == 0) {
            st[x][y + 1] = 1;
            dfs(x, y + 1, tot + 1);
            st[x][y + 1] = 0;
        }
    }

    if (x != 1 && st[x - 1][y] == 0) {
        deg[x - 1][y]++;
    }
    if (x != n && st[x + 1][y] == 0) {
        deg[x + 1][y]++;
    }
    if (y != 1 && st[x][y - 1] == 0) {
        deg[x][y - 1]++;
    }
    if (y != n && st[x][y + 1] == 0) {
        deg[x][y + 1]++;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%s", str + 1);
        for(int j = 1; j <= n; j++) {
            st[i][j] = (str[j] == '.') ? 0 : 1;
            cnt += st[i][j] ^ 1;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            deg[i][j] = 0;
            if(i != 1) deg[i][j] += (st[i - 1][j] == 0);
            if(i != n) deg[i][j] += (st[i + 1][j] == 0);
            if(j != 1) deg[i][j] += (st[i][j - 1] == 0);
            if(j != n) deg[i][j] += (st[i][j + 1] == 0);
        }
    }
    if(st[1][1] == 1 || st[n][1] == 1) return puts("0"), 0;
    st[1][1] = 1; deg[n][1]++;
    dfs(1, 1, 1);
    printf("%d\n", ans);
    return 0;
}