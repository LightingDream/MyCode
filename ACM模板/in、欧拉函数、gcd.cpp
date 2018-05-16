#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;

template <class T> T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
template <class T>
T getPhi(T x)
{
	T res = x;
	for (T i = 2; i * i <= x; ++i)
	{
		if (x % i == 0)
		{
			res -= res / i;
			while (x % i == 0) x /= i;
		}
	}
	if (x > 1) res -= res / x;
	return res;
}
template <class T>
T read()
{
	T x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = 10 * x + ch - '0'; ch = getchar(); }
	return x * f;
}



int main()
{
	ll t = read<ll>();
	if (t < 0) printf("%lld\n", t), t = -t;
	printf("%lld %lld\n", getPhi(t), gcd(t, 2ll));
	return 0;
}