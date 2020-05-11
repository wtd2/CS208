#include <bits/stdc++.h>

#define clr(x) memset(x, 0, sizeof(x))

const int maxn = 10000100;

typedef long long ll;

struct node {
    ll num[3], flg;
    node() {flg = 0; memset(num, 0, sizeof(num));}
    ll& operator[] (const int x) {return num[x];}
};

node ans[maxn], quick[101];

node get_ans(ll n) {
    int dep = 0;
    if(n < maxn && ans[n].flg == 1) return ans[n];
    for(int i = 0; i < 60; i++) if((1ll << i) < n && n <= (1ll << (i + 1))) {dep = i; break;}
    if(quick[dep].flg == 0) {
        quick[dep] = get_ans(1ll << dep);
    }
    node ret = quick[dep], tmp = get_ans(n - (1ll << dep));
    for(int i = 0; i < 3; i++) ret[(i + 1) % 3] += tmp[i];
    if(n < maxn) {ans[n] = ret; ans[n].flg = 1;}
    return ret;
}

int main() {
    ans[0][0] = ans[0][1] = ans[0][2] = 0; ans[0].flg = 1;
    ans[1][0] = 1; ans[1][1] = ans[1][2] = 0; ans[1].flg = 1;
    int T; scanf("%d", &T);
    while(T--) {
        ll x; scanf("%lld", &x); node ret = get_ans(x);
        printf("%lld %lld %lld\n", ret[0], ret[1], ret[2]);
    }
    return 0;
}
