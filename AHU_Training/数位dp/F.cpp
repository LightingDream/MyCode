#include <bits/stdc++.h>
using namespace std;
typedef pair<long long, long long> pll;
#define mp make_pair
#define fi first
#define se second
const long long mod = 1e9 + 7;
const int maxn = 25;

int a[maxn];
long long fac[maxn];
inline long long sqr(long long x)
{
    return x * x % mod;
}
struct Node
{
    long long cnt;
    long long sum, sqr;
}dp[maxn][11][11];

Node dfs(int pos, int mod1, int mod2, bool limit)
{
    if(pos == -1)
    {
        if(mod1 && mod2) return Node{1, 0, 0};
        else return Node{0, 0, 0};
    }
    if(!limit && dp[pos][mod1][mod2].cnt != -1) return dp[pos][mod1][mod2];
    int up = limit ? a[pos] : 9;
    Node res;
    res.cnt = 0;
    res.sum = 0;
    res.sqr = 0;
    for(int i = 0; i <= up; ++i)
    {
        if(i == 7) continue;
        Node tmp = dfs(pos - 1, (mod1 + i) % 7, (mod2 * 10 + i) % 7, limit && i == a[pos]);
        res.cnt = (res.cnt + tmp.cnt) % mod;
        res.sum = ((res.sum + tmp.cnt * fac[pos] * i % mod) % mod + tmp.sum) % mod;
        res.sqr = ((res.sqr + tmp.sqr) % mod + tmp.sum * 2 % mod * i % mod * fac[pos] % mod) % mod;
        res.sqr = (res.sqr + tmp.cnt * sqr(fac[pos] * i % mod) % mod) % mod;
    }
    return limit ? res : dp[pos][mod1][mod2] = res;
}

inline long long cal(long long x)
{
    int cnt = 0;
    while(x)
    {
        a[cnt++] = x % 10;
        x /= 10;
    }
    return dfs(cnt - 1, 0, 0, true).sqr;
}

inline long long ask(long long l, long long r)
{
    return (cal(r) - cal(l - 1) + mod) % mod;
}
int main()
{
    memset(dp, -1, sizeof dp);
    fac[0] = 1;
    for(int i = 1; i < maxn; ++i) fac[i] = 10 * fac[i - 1] % mod;
    int T;
    scanf("%d", &T);
    while(T--)
    {
        long long l, r;
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", ask(l, r));
    }
    return 0;
}

