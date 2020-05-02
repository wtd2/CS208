#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

const int sigma = 3, maxn = 200100;
//const llu inf = 3llu * (1llu << 62);
const double inf = 1e100;

int D = 0;

struct point {
    ll num[sigma];
    ll& operator[] (const int x) {return num[x];}
    bool operator< (const point &a) const {
        return (num[D] == a.num[D] && num[(D + 1) % sigma] == a.num[(D + 1) % sigma] && num[(D + 2) % sigma] < a.num[(D + 2) % sigma])
        || (num[D] == a.num[D] && num[(D + 1) % sigma] < a.num[(D + 1) % sigma])
        || (num[D] < a.num[D]);
    }
}a[maxn];

ll print[2][sigma];

namespace kd {

    double sqr(ll x) {
        return 1.0 * x * x;
    }

    double ans = inf;

    struct node {
        int ch[2];
        ll num[sigma], val[sigma][2];
        int& operator[] (const int x) {return ch[x];}
    }tr[maxn];

    void pushup(int t, int x) {
        for(int i = 0; i < sigma; i++)
            tr[t].val[i][0] = min(tr[t].val[i][0], tr[x].val[i][0]);
        for(int i = 0; i < sigma; i++)
            tr[t].val[i][1] = max(tr[t].val[i][1], tr[x].val[i][1]);
    }

    int build(int l, int r, int dir) {
        int mid = (l + r) >> 1; D = dir; nth_element(a + l, a + mid, a + r + 1);
        for(int i = 0; i < sigma; i++) tr[mid].num[i] = tr[mid].val[i][0] = tr[mid].val[i][1] = a[mid].num[i];
        if(l < mid) tr[mid][0] = build(l, mid - 1, (dir + 1) % sigma), pushup(mid, tr[mid][0]);
        if(mid < r) tr[mid][1] = build(mid + 1, r, (dir + 1) % sigma), pushup(mid, tr[mid][1]);
        return mid;
    }

    double f(int t, ll x, ll y, ll z) {
        double ret = 0;
        ret += sqr(max(tr[t].val[0][0] - x, 0ll)) + sqr(max(x - tr[t].val[0][1], 0ll));
        ret += sqr(max(tr[t].val[1][0] - y, 0ll)) + sqr(max(y - tr[t].val[1][1], 0ll));
        ret += sqr(max(tr[t].val[2][0] - z, 0ll)) + sqr(max(z - tr[t].val[2][1], 0ll));
        return ret;
    }

    double dis(int t, ll x, ll y, ll z) {
        return sqr(tr[t].num[0] - x) + sqr(tr[t].num[1] - y) + sqr(tr[t].num[2] - z);
    }

    void insert(int &x, int y, int dir) {
        if(!x) {x = y; return;}
        pushup(x, y);
        if(tr[y].num[dir] < tr[x].num[dir]) insert(tr[x][0], y, (dir + 1) % sigma);
        else insert(tr[x][1], y, (dir + 1) % sigma);
    }

    void query(int t, ll x, ll y, ll z) {
        double d = dis(t, x, y, z);
        if(ans > d) {
            ans = d;
            print[0][0] = x; print[0][1] = y; print[0][2] = z;
            print[1][0] = tr[t].num[0]; print[1][1] = tr[t].num[1]; print[1][2] = tr[t].num[2];
        }
        double dl = inf, dr = inf;
        if(tr[t][0]) dl = f(tr[t][0], x, y, z);
        if(tr[t][1]) dr = f(tr[t][1], x, y, z);
        if(dl < dr) {
            if(dl < ans) query(tr[t][0], x, y, z);
            if(dr < ans) query(tr[t][1], x, y, z);
        } else {
            if(dr < ans) query(tr[t][1], x, y, z);
            if(dl < ans) query(tr[t][0], x, y, z);
        }
    }

}

int main() {
    int n, k, tot = 1; scanf("%d%d", &n, &k);
    assert(1 <= n && n <= int(1e5));
    assert(1 <= k && k <= 3);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < k; j++) {
            assert(int(-1e9) <= a[i][j] && a[i][j] <= int(1e9));
            scanf("%lld", &a[i][j]);
        }
        for(int j = k; j < sigma; j++) a[i][j] = 0;
    }
    int rt = kd::build(1, 1, 0); kd::ans = inf;
    for(int i = 2; i <= n; i++) {
        ll x = a[i][0], y = a[i][1], z = a[i][2];
        kd::query(rt, x, y, z); ++tot;
        kd::tr[tot].num[0] = kd::tr[tot].val[0][0] = kd::tr[tot].val[0][1] = x;
        kd::tr[tot].num[1] = kd::tr[tot].val[1][0] = kd::tr[tot].val[1][1] = y;
        kd::tr[tot].num[2] = kd::tr[tot].val[2][0] = kd::tr[tot].val[2][1] = z;
        kd::insert(rt, tot, 0);
    }
    bool less = 0;
    for(int i = 0; i < k; i++) {
        if(print[0][i] < print[1][i]) break;
        if(print[0][i] > print[1][i]) {less = 1; break;}
    }
    for(int i = 0; i < k; i++) {
        printf("%lld%c", print[less][i], (i == k - 1) ? '\n' : ' ');
    }
    for(int i = 0; i < k; i++) {
        printf("%lld%c", print[less ^ 1][i], (i == k - 1) ? '\n' : ' ');
    }
    return 0;
}

