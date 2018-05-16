#include <cstdio>
using namespace std;
/**
	get the inv number of a mod p (a, p) = 1 -> (ax % p = 1)
**/

template <class T> void mod(T &x, T p) { x = (x % p + p) % p; }

template <class T>
T extend_gcd(T a, T b, T &x, T &y)/**ax + by = gcd(a, b)*/
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	T d = extend_gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}


template <class T>
T Inv(T a, T p)
{
	T x, y;
	extend_gcd(a, p, x, y);
	mod(x, p);
	return x;
}

template <class T> 
T qpow(T a, T b, T p) 
{ 
	T res = 1 % p; 
	while (b)
	{
		if (b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;/**有时需要qmul**/
	}
	return res;
}
template <class T>
T phi(T x)
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
template <class T> T inv(T a, T p){ return qpow(a, phi(p) - 1, p); }


/**
连续区间:
	inv筛, O(n)预处理一个区间内mod p 的inv
	k * i + r = p (i > r > 0 )
	则 inv(i) = p - k * inv(r)
	inv[i] = (p - p / i) * inv[p % i] % p;
阶乘逆元(组合数):
	预处理n!的逆元反推
	inv[i - 1] = inv[i] * i % p;
**/

int main()
{
	printf("%d\n", Inv(2, 5));
	return 0;
}