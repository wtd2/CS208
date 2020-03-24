#include <bits/stdc++.h>

#define pii pair<int, int>

const int maxn = 500050;

using namespace std;

pii num[maxn];

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &num[i].second, &num[i].first);
            num[i].second *= -1;
        }
        sort(num + 1, num + n + 1);
        int lst = 0, ans = 0;
        for(int i = 1; i <= n; i++) {
            if(-num[i].second > lst) lst = num[i].first, ans++;
        }
        printf("%d\n", ans);
    }

    return 0;
}