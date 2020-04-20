#include <bits/stdc++.h>

using namespace std;

const int maxn = 62;

typedef long long ll;

ll query(ll x) {
	if(x == 0) return 0;
	ll ans = 0;
	for(int i = 0; i < maxn; i++) if((1ll << i) <= x && x < (1ll << i + 1)) {
		ans = 1ll << i;
		ans += query((1ll << i + 1) - x - 1);
		ans -= (1ll << i + 1) - x - 1;
		return ans;
	}
	return 0;
}

int main() {
	int q; scanf("%d", &q);
	while(q--) {
		ll u, v; scanf("%lld%lld", &u, &v);
		printf("%lld\n", query(v) - query(u - 1));
	}
	return 0;
}