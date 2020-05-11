#include <bits/stdc++.h>

#define clr(x) memset(x, 0, sizeof(x))

const int maxn = 262145, mod = 998244353, G = 3;

typedef long long ll;

int a[maxn], pwn[maxn];
int fac[maxn], ans[maxn], cnt = 0;
int f[maxn], g[maxn];

int pow(int a, int n, int mod) {
    int ret = 1;
    for(; n; n >>= 1, a = 1ll * a * a % mod) if(n & 1) ret = 1ll * ret * a % mod;
    return ret;
}

int calc_root(int p) {
    // euler theorem: x^{p-1}=1(mod p), then check p-1 is the least number
    if(p == 2) return 1;
    for(int i = 2; i * i < p; i++) if((p - 1) % i == 0) {
        fac[++cnt] = i;
        if(i * i != (p - 1)) fac[++cnt] = (p - 1) / i;
    }
    for(int x = 2; x < p; x++) {
        bool ok = 1;
        for(int i = 1; i <= cnt; i++) if(pow(x, (p - 1) / fac[i], p) == 1) {ok = 0; break;}
        if(ok) return x;
    }
    return 0;
}

void getwn() {
    for(int i = 1; i < maxn; i <<= 1) pwn[i] = pow(G, (mod - 1) / i, mod);
}

void ntt(int *a, int n, int t) {
    if(n == 1) return;
    int l[n >> 1], r[n >> 1];
    for(int i = 0; i < n; i += 2) {
        l[i >> 1] = a[i];
        r[i >> 1] = a[i + 1];
    }
    ntt(l, n >> 1, t); ntt(r, n >> 1, t);
    int w = 1, wn = pwn[n]; if(t == -1) wn = pow(wn, mod - 2, mod);
    for(int i = 0; i < (n >> 1); i++, w = 1ll * w * wn % mod) {
        a[i] = (l[i] + 1ll * r[i] * w) % mod;
        a[i + (n >> 1)] = (l[i] - 1ll * r[i] * w % mod + mod) % mod;
    }
}

int main() {
    getwn(); clr(a); clr(ans);
    int n, m = 1, p; scanf("%d%d", &n, &p);
    int pe = calc_root(p), cnt = 0;
    f[0] = 1; g[1] = 0;
    for(int i = 1; i < p - 1; i++) {
        f[i] = 1ll * f[i - 1] * pe % p;
        g[f[i]] = i;
    }
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x); x %= p;
        if (x == 0) cnt++; else a[g[x]]++;
    }
    while(m < (p << 1)) m <<= 1;
    ntt(a, m, 1);
    for(int i = 0; i < m; i++) a[i] = 1ll * a[i] * a[i] % mod;
    ntt(a, m, -1);
    int inv = pow(m, mod - 2, mod);
    for(int i = 0; i < m; i++) a[i] = 1ll * a[i] * inv % mod;
    for(int i = 0; i < (p << 1); i++) ans[f[(i % (p - 1))]] += a[i];
    ans[0] = 1ll * n * n - 1ll * (n - cnt) * (n - cnt);
    for(int i = 0; i < p; i++) printf("%d\n", ans[i]);
    return 0;
}
