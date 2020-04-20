#include <bits/stdc++.h>

using namespace std;

const int maxn = 500050;

typedef long long ll;

int idx[maxn], idy[maxn], x[maxn], y[maxn], tmp[maxn];

struct node {
	int x, y;
	bool operator< (const node &rhs) const {
		if(x == rhs.x) return y < rhs.y;
		return x < rhs.x;
	}
}e[maxn];

ll cdq(int l, int r) {
	if(l == r) return 0;
	int mid = (l + r) >> 1, cur = 0; ll ret = 0;
	ret += cdq(l, mid) + cdq(mid + 1, r);
	for(int i = l; i <= mid; i++) tmp[cur++] = e[i].y;
	sort(tmp, tmp + cur);
	for(int i = mid + 1; i <= r; i++) ret += upper_bound(tmp, tmp + cur, e[i].y) - tmp;
	return ret;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &e[i].x, &e[i].y);
	}
	sort(e + 1, e + n + 1);
	printf("%lld\n", cdq(1, n));
	return 0;
}