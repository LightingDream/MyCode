#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
const int max_m = 1 << 15;
const int max_n = 100001;
const ll mod = 1e9 + 7;

int n, m;
char s[20];
ll p[max_n];
int cnt[max_m];
ll v[max_m];
int bitcnt[max_m];
bool vis[max_m];
vi vec[max_m];

template <typename T>
T read()
{
    T x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = 10 * x + ch - '0'; ch = getchar();}
    return x * f;
}
inline ll Mod(ll x){return (x % mod + mod) % mod;}
inline int lowbit(int x){return x & (-x);}
void init()
{
    bitcnt[0] = 0; p[0] = 1;
    for(int i = 1; i < max_n; ++i) p[i] = p[i - 1] * 2 % mod;
    for(int i = 1; i < max_m; ++i) bitcnt[i] = bitcnt[i ^ lowbit(i)] + 1;
    for(int i = 1; i < max_m; ++i)
    {
        vi bit_pos;
        for(int j = 0; j < 15; ++j) if(i & (1 << j)) bit_pos.push_back(j);
        for(int j = 0; j < 1 << bitcnt[i]; ++j)
        {
            int x = 0;
            for(int k = 0; k < bitcnt[i]; ++k)
                if(j & (1 << k)) x |= 1 << bit_pos[k];
            vec[i].push_back(x);
        }
    }
}
void dfs(int x, int m)
{
    vis[x] = 1;
    for(int k = 0; k < vec[x].size(); ++k)
    {
        int u = vec[x][k];                       //非空子集
        v[x] = Mod(v[x] + p[cnt[u]] - 1);            //2 ^ cnt - 1
    }
    v[x] = Mod(v[x] + 1);                       //空集
                                                //更新cnt
    for(int i = 0; i < m; ++i)
        if(x & (1 << i) && !vis[x ^ (1 << i)])
        {
            for(int k = 0; k < vec[x].size(); ++k)
            {
                int u = vec[x][k];
                if(u & (1 << i)) cnt[u ^ (1 << i)] += cnt[u];//x子集中有bit i就更新
            }
            dfs(x ^ (1 << i), m);
            for(int k = 0; k < vec[x].size(); ++k)
            {
                int u = vec[x][k];             //恢复
                if(u & (1 << i)) cnt[u ^ (1 << i)] -= cnt[u];
            }
        }
}
void in()
{
    memset(cnt, 0, sizeof cnt);
    memset(vis, 0, sizeof vis);
    memset(v, 0, sizeof v);
    n = read<int>(), m = read<int>();
    for(int i = 0; i < n; ++i)
    {
        scanf("%s", s);
        int x = 0;
        for(int j = 0; j < m; ++j)
            if(s[j] == 'Y') x |= 1 << j;
        ++cnt[x];
    }
   // v[0] = 1;
    vis[0] = 1;
    dfs((1 << m) - 1, m);
}

ll solve()
{
    in();
    ll res = 0;                 // res
    for(int i = 1; i < 1 << m; ++i)
    {
        ll ans = 0;             //the ans for bit i
                         //for i : v1 && v2 && ... vn = 2^n - (!v1 || !v2 || .. !vn) // = 2^n - (bitcnt[j] & 1 ? v[j] : -v[j]) for j bit of i(j是i的非空子集)容//斥
        for(int k = 0; k < vec[i].size(); ++k)
        {
            int j = vec[i][k];
            if(j == 0) continue;
            ans += bitcnt[j] & 1 ? v[j] : -v[j];//v[j]是bit j的贡献(j bit位//各子集数量分别贡献)
            ans = Mod(ans);
        }
        ans = Mod(p[n] - ans);
        res ^= ans;
    }
    return res;
}
int main()
{
    init();
    int T = read<int>();
    for(int kas = 1; kas <= T; ++kas) printf("Case #%d: %lld\n", kas,solve());
    return 0;
}