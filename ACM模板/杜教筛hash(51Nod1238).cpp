#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const ll inv = (mod + 1) / 2;
const ll inv2 = inv * (mod + 1) / 3 % mod;
const int mo = 2333333;
const int N = 1000001;

template <class T>
struct Number_Theory
{
	T phi[N], mo[N], pr[N / 5], min_divisor[N], sum[N];
	bool jz[N];
	int cnt;

	void Euler_sieve()
	{
		memset(jz, true, sizeof jz);
		jz[1] = false;
		phi[1] = mo[1] = 1;
		min_divisor[1] = 1;
		for (int i = 2; i < N; ++i)
		{
			if (jz[i])
			{
				pr[++cnt] = i;
				phi[i] = i - 1;
				mo[i] = -1;
				min_divisor[i] = i;
			}
			for (int j = 1; j <= cnt; ++j)
			{
				if (i * pr[j] >= N) break;
				T tmp = i * pr[j];
				min_divisor[tmp] = pr[j];
				jz[tmp] = false;
				if (i % pr[j] == 0)
				{
					phi[tmp] = phi[i] * pr[j];
					mo[tmp] = 0;
					break;
				}
				phi[tmp] = phi[i] * (pr[j] - 1);
				mo[tmp] = -mo[i];
			}
		}
		sum[0] = 0;
		for (T i = 1; i < N; ++i)
			sum[i] = ((sum[i - 1] + i * i * phi[i]) % mod + mod) % mod;
	}
};
Number_Theory <ll>adrui;


ll Sum(ll x)
{
	return x % mod * ((x * 2 + 1) % mod) % mod * ((x + 1) % mod) % mod * inv2 % mod;
}
ll getSum(ll R, ll L)
{
	return ((Sum(R) - Sum(L)) % mod + mod) % mod;
}
ll n;

template <class T>
struct Hash
{
	T u[mo], v[mo];
	int Last[mo], Next[mo];
	int l;
	void add(T y, T z)
	{
		int k = y % mo;
		++l;
		u[l] = y;
		v[l] = z;
		Next[l] = Last[k];
		Last[k] = l;
	}
	T find(T x)
	{
		int k = x % mo;
		for (int i = Last[k]; i; i = Next[i])
			if (u[i] == x) return v[i];
		return -1;
	}
};
Hash<ll> ha;

ll cal(ll x)
{
	if (x < N) return adrui.sum[x];
	ll t = ha.find(x);
	if (~t) return t;
	ll res = x % mod * ((x + 1) % mod) % mod * inv % mod;
	res = res * res % mod;
	ll r;
	for (ll i = 2; i <= x; i = r + 1)
	{
		ll tmp = x / i;
		r = x / tmp;
		ll mul = getSum(r, i - 1);
		ll ans = cal(tmp) * mul % mod;
		res = ((res - ans) % mod + mod) % mod;
	}
	ha.add(x, res);
	return res;
}


ll Calc(ll x)
{
	ll res = 0;
	ll r;
	for (ll i = 1; i <= x; i = r + 1)
	{
		ll tmp = x / i;
		r = x / tmp;
		ll mul = ((r - i + 1) % mod) % mod * ((r + i) % mod) % mod * inv % mod;
		res = (res + mul * cal(tmp) % mod) % mod;
	}
	r = 0;
	return ((res - r) % mod + mod) % mod;
}
int main()
{
	//freopen("C://Users//�ܱ���//Desktop//ce.out", "w", stdout);
	adrui.Euler_sieve();
	cin >> n;
	cout << Calc(n) << endl;

	return 0;
}
