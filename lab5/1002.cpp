#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

const int maxn = 5050;

pii num[maxn]; int tot[maxn];
int n, S, T;

struct cmp {
    bool operator()(int i, int j) {
        return num[i].second > num[j].second;
    }
};
priority_queue<int, vector<int>, cmp> pq;

bool check(int mid) {
    int cur = 1;
    while(!pq.empty()) pq.pop();
    for(int i = 1; i <= n; i++) tot[i] = 0;
    for(int t = S; t <= T; t++) {
        while(cur <= n && t == num[cur].first) {
            pq.push(cur++);
        }
        if(!pq.empty()) {
            int pos = pq.top();
            if(t > num[pos].second) return 0;
            tot[pos]++;
            if(tot[pos] == mid) pq.pop();
        }
    }
    if(!pq.empty()) return 0;
    return 1;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d%d", &num[i].first, &num[i].second);
    sort(num + 1, num + n + 1);
    S = num[1].first; T = num[1].second;
    for(int i = 2; i <= n; i++) T = max(T, num[i].second);
    int l = 0, r = (T - S + 1) / n, ans = 0;
    while(l < r) {
        int mid = r - (r - l >> 1);
        if(check(mid)) l = mid, ans = mid;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
