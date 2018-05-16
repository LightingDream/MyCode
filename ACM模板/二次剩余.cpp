/**
 *author: adrui
 *HDU 6128
**/
#include <bits/stdc++.h>
using namespace std;
const int N = 100001;
typedef long long ll;
typedef long long ull;


ll a[N];
ll t;

struct Complex
{
    ll a, b;
    Complex(){}
    Complex(ll _a, ll _b):a(_a),b(_b){}
};

ll Mod(ll a, ll p)
{
    return (a % p + p) % p;
}
ll qmul(ll a, ll b, ll p)
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = Mod(res + a, p);
        a = Mod(a + a, p);
        b >>= 1;
    }
    return res;
}
ll qpow(ll a, ll b, ll p)
{
    ll res = 1;
    while(b)
    {
        if(b & 1) res = qmul(res, a, p);
        a = qmul(a, a, p);
        b >>= 1;
    }
    return res;
}
Complex Cmul(Complex x, Complex y, ll p)
{
    return Complex(Mod(qmul(x.a, y.a, p) + qmul(qmul(x.b, y.b, p), t, p), p), Mod(qmul(x.a, y.b, p) + qmul(x.b, y.a, p), p));
}
Complex Cpow(Complex a, ll b, ll p)
{
    Complex res(1, 0);
    while(b)
    {
        if(b & 1) res = Cmul(res, a, p);
        a = Cmul(a, a, p);
        b >>= 1;
    }
    return res;
}

ll ran(ll p)
{
    ll a = rand() << 16 | rand();
    return ((a << 16) | a) % p;
}
ll work(ll n, ll p)
{
    ll a;
    while(1)
    {
        a = ran(p);
        t = Mod(qmul(a, a, p) - n, p);
        if(qpow(t, (p - 1) >> 1, p) == p - 1) break;
    }
    return Cpow(Complex(a, 1), (p + 1) / 2, p).a;
}

int main()
{
   // freopen("ce.in", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--)
    {
        srand(time(0));
        int n;
        ll p;
        scanf("%d%lld", &n, &p);
        for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        if(p == 2 || qpow(p - 3, (p - 1) >> 1, p) == p - 1)
        {
            puts("0");
            continue;
        }
        ll ans = 0;
        map<ll, int> mp;
        if(p == 3)
        {
            for(int i = 1; i <= n; ++i)
                if(a[i]) ans += mp[a[i]], ++mp[a[i]];
            printf("%lld\n", ans);
            continue;
        }
        ll d = work(p - 3, p);
        d = Mod(d, p);
        ll d1 = d & 1 ? (d - 1) / 2 : (d - 1 + p) / 2;
        ll d2 = qpow(d1, p - 2, p);
        for(int i = 1; i <= n; ++i)
            if(a[i])
            {
                ans += mp[qmul(a[i], d1, p)];
                ans += mp[qmul(a[i], d2, p)];
                ++mp[a[i]];
            }
        printf("%lld\n", ans);
    }

    return 0;
}