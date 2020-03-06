#include <bits/stdc++.h>

using namespace std;

const int maxn = 5000500;

typedef long long ll;

struct node {
	int val, id;
	bool operator< (const node &rhs) const {
		return val < rhs.val;
	}
}a[maxn];

int L[maxn], R[maxn], ans[maxn], num[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i].val); a[i].id = i; num[i] = a[i].val;
	}
	sort(a, a + n);
	L[a[0].id] = -1; R[a[n - 1].id] = -1;
	for(int i = 1; i < n; i++) {
		R[a[i - 1].id] = a[i].id;
		L[a[i].id] = a[i - 1].id;
	}
	for(int i = n - 1; i >= 0; i--) {
		if(L[i] == -1 && R[i] == -1) ans[i] = num[i];
		else if(L[i] == -1) ans[i] = abs(num[i] - num[R[i]]);
		else if(R[i] == -1) ans[i] = abs(num[i] - num[L[i]]);
		else ans[i] = min(abs(num[i] - num[R[i]]), abs(num[i] - num[L[i]]));
		if(R[i] != -1) L[R[i]] = L[i];
		if(L[i] != -1) R[L[i]] = R[i];
	}
	ll sum = 0;
	for(int i = 0; i < n; i++) sum += ans[i];
	printf("%lld\n", sum);
	return 0;
}