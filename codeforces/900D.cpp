// <reference path="globals/node/index.d.ts" />
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef set<int> VI;
typedef long long ll;
typedef map<int, ll> MILL;
const ll mod = 1e9 + 7;

VI prime;
MILL mp;
map<int, int> vis;
vector<int> test;

ll qpow(ll a, ll b)
{
    ll ret = 1;
    while(b)
    {
        if(b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}
ll cal(int x)
{
	if(x == 1) return 1;
	if(vis[x]) return mp[x];
	ll ret = qpow(2ll, x - 1ll);
	for(auto u : prime)
    {
        if(u > x) break;
		if(x % u == 0) ret = (ret - cal(x / u) + mod) % mod;
    }
    vis[x] = 1;
  // printf("%d %I64d\n", x, ret);
	return mp[x] = ret;
}

int main()
{
	int x, y;
	scanf("%d%d", &x, &y);
	if(y % x) puts("0");
	else
	{
		int n = y / x;
		for(int i = 1; i * i <= n; ++i)
			if(n % i == 0)
			{
				if(i != 1) prime.insert(i);
				prime.insert(n / i);
			}
		printf("%I64d\n", cal(n));
	}

	return 0;
}
