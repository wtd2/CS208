#include <bits/stdc++.h>

using namespace std;

int cnt[26]; char str[100010];

priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        for(int i = 0; i < 26; i++) cnt[i] = 0;
        scanf("%s", str); int len = strlen(str);
        for(int i = 0; i < len; i++) cnt[str[i] - 'a']++;
        for(int i = 0; i < 26; i++) if(cnt[i] != 0) pq.push(cnt[i]);
        int ans = 0;
        while(!pq.empty()) {
            int p = pq.top(); pq.pop();
            if(pq.empty()) {
                if(ans == 0) ans = p;
                break;
            }
            int q = pq.top(); pq.pop();
            ans += p + q;
            pq.push(p + q);
        }
        printf("%d\n", ans);
    }
    return 0;
}