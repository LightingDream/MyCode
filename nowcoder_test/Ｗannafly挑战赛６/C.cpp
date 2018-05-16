#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll qpow(ll a, ll b, ll c)
{
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % c;
        a = a * a % c;
        b >>= 1;
    }
    return res;
}

int main()
{
    ll n;
    scanf("%lld", &n);
    if(n < 2) printf("0\n");
    else
    {
            if(n == 2) printf("1\n");
            else
            {
                ll ans = n % mod * ((n - 1) % mod) % mod;
                ans = ans * qpow(2, n - 3, mod) % mod;
                printf("%lld\n", ans);
            }
    }
    return 0;
}
