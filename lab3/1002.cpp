#include <bits/stdc++.h>

using namespace std;

const int maxn = 400040, mod = 998244353;
typedef long long ll;

int digit[maxn][11], cnt[maxn], fac[21], sum[11], tot[11];
ll ans = 0;

int main() {
	int n; scanf("%d", &n);
	fac[0] = 1;
	for(int i = 1; i < 20; i++) fac[i] = 10ll * fac[i - 1] % mod;
	for(int i = 0; i < n; i++) {
		int num; scanf("%d", &num); cnt[i] = 0;
		while(num) {
			digit[i][cnt[i]++] = num % 10;
			num /= 10;
		}
		tot[cnt[i] - 1]++;
	}
	for(int i = 9; i >= 0; i--) {
		sum[i] = sum[i + 1] + tot[i];
	}
	for(int i = 0; i < n; i++) {
		// As p
		for(int d = 0; d < cnt[i]; d++) {
			for(int t = 0; t < d; t++) ans = (ans + (1ll * digit[i][d] * fac[d + t + 1] % mod * tot[t] % mod));
			ans = (ans + (1ll * digit[i][d] * fac[(d << 1) + 1] % mod * sum[d] % mod)) % mod;
		}
		// As q
		ans = (ans + 1ll * digit[i][0] * sum[0] % mod) % mod;
		for(int d = 1; d < cnt[i]; d++) {
			for(int t = 0; t < d - 1; t++) ans = (ans + (1ll * digit[i][d] * fac[d + t + 1] % mod * tot[t] % mod));
			ans = (ans + (1ll * digit[i][d] * fac[d << 1] % mod * sum[d - 1] % mod)) % mod;
		}
	}
	printf("%lld\n", ans);
	return 0;
}