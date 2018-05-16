#include <cstdio>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;
const ll p = 1000000001;
const int N = 8001;

template <class T>
T read()
{
	T x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = 10 * x + ch - '0'; ch = getchar(); }
	return x * f;
}

inline ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
inline ll Abs(ll x) { return x >= 0 ? x : -x; }
/**
POJ 1707
author: adrui

暴力:
\sum_{i = 1} ^ n i ^ k =
1 / (k + 1) [(n + 1) ^ (k + 1)
- (n + 1)
- \sum_{i = 2} ^ k
C(k + 1, i) * \sum_{j = 1} ^ n j ^ (k + 1 - i)]
伯努利数自然幂和:
\sum_{i = 1} ^ n i ^ k =
1 / (k + 1) * \sum_{i = 0} ^  k C(k + 1, i) * B[i] * [(n + 1) ^ (k + 1 - i)]
性质:
\sum_{k = 0} ^ n C(n + 1, k) * B[k] = 0 ->
B[n] = -1 / (n + 1) * \sum_{k = 0} ^ {n - 1} * C(n + 1, k) * B[k]
B[0] = 1;

**/

struct Node
{
	ll u, d;
	Node() {}
	Node(ll _u, ll _d) :u(_u), d(_d) {}
	Node operator - (const Node &rhs) const
	{
		ll l = lcm(d, rhs.d);
		return Node(u * l / d - rhs.u * l / rhs.d, l).adjust();
	}
	Node operator + (const Node &rhs) const
	{
		return (*this - rhs * (-1)).adjust();
	}
	Node adjust() const
	{
		ll D = gcd(Abs(u), d);
		return Node(u / D, d / D);
	}
	Node operator * (ll x) const
	{
		return Node(u * x, d).adjust();
	}
	void operator = (const Node &rhs)
	{
		u = rhs.u;
		d = rhs.d;
	}
	void output()
	{
		printf("(%lld, %lld)\n", u, d);
	}
}ans[22];

template <class T = ll>
struct Natural_Power_Sum
{
	static const int N = 22;
	T C[N][N];
	Node B[N];
	Natural_Power_Sum()
	{
		for (int i = 0; i < N; ++i) C[i][0] = C[i][i] = 1;
		for (int i = 2; i < N; ++i)
			for (int j = 1; j < i; ++j)
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		B[0] = Node(1, 1);
		for (int i = 1; i < N - 1; ++i)
		{
			B[i] = Node(0, 1);
			for (int j = 0; j < i; ++j)
				B[i] = B[i] + B[j] * C[i + 1][j];
			B[i].d *= i + 1;
			B[i].u *= -1;
			//	B[i].output();
			B[i] = B[i].adjust();
			//	B[i].output();
			/**B[i]不一定是整数*/
		}
	}

	void solve(int k)
	{
		ll l = 1;
		for (int i = 0; i <= k + 1; ++i)
		{
			ans[i] = Node(C[k + 1][i], 1);
			for (int j = 1; j <= k + 1 - i && j <= k; ++j)
			{
				//  B[j].output();
				//   (B[j] * (C[k + 1][j] * C[k + 1 - j][i])).output();
				ans[i] = ans[i] + (B[j] * (C[k + 1][j] * C[k + 1 - j][i]));
				//  ans[i].output();
			}
			ans[i].d *= k + 1;
			ans[i] = ans[i].adjust();
			//	ans[i].output();
			l = lcm(l, ans[i].d);
		}
		printf("%lld", l);
		for (int i = k + 1; i >= 0; --i)
			printf(" %lld", l / ans[i].d * ans[i].u);
		puts("");
	}
};
Natural_Power_Sum<ll> adrui;
int main()
{
	//freopen("ce.out", "w", stdout);
	//	for(ll k = 1; k <= 20; ++k)
	//adrui.solve(19);
	adrui.solve(read<ll>());
	return 0;
}