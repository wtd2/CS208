#include <bits/stdc++.h>

using namespace std;

const int maxn = 5050;

typedef long long ll;

struct node {
    int s, t, v;
}t[maxn];

int id[maxn], ch[maxn];

bool cmp1(node a, node b) {return a.s < b.s;}
bool cmp2(node a, node b) {return a.v > b.v;}

bool check(int num, int pos) {
    if(id[pos] > t[num].t) return 0;
    if(ch[pos] == 0) return ch[pos] = num, 1;
    if(t[ch[pos]].t < t[num].t) return check(num, pos + 1);
    else {
        if(check(ch[pos], pos + 1)) return ch[pos] = num, 1;
        else return 0;
    }
}

int main() {
    int n; scanf("%d", &n); id[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d%d%d", &t[i].s, &t[i].t, &t[i].v);
    }
    sort(t + 1, t + n + 1, cmp1);
    for(int i = 1; i <= n; i++) {
        id[i] = max(id[i - 1] + 1, t[i].s);
    }
    sort(t + 1, t + n + 1, cmp2);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int pos = 1;
        while(pos <= n && id[pos] < t[i].s) pos++;
        if(check(i, pos)) ans += t[i].v;
    }
    printf("%lld\n", ans);
    return 0;
}