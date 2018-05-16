#include <bits/stdc++.h>
using namespace std;
const int maxn = 25;

long long dp[maxn][2][1 << 11][11];
int a[maxn];
int one[1 << 11];
int k;
inline int update(int s, int bit)
{
    for(int i = bit; i < 11; ++i)
        if(s & (1 << i))
        {
            s ^= 1 << i;
            break;
        }
    return s | (1 << bit);
}
long long dfs(int pos, int zero, int state, bool limit, int k)
{
    if(pos == -1) return one[state] == k;
    if(one[state] > k) return 0;
    if(!limit && ~dp[pos][zero][state][k]) return dp[pos][zero][state][k];
    int up = limit ? a[pos] : 9;
    long long res = 0;
    for(int i = 0; i <= up; ++i)
    {
        int zero_tmp = zero && i == 0;
        int state_tmp = zero_tmp ? 0 : update(state, i);
        res += dfs(pos - 1, zero_tmp, state_tmp, limit && a[pos] == i, k);
    }
    return limit ? res : dp[pos][zero][state][k] = res;
}

inline long long cal(long long x, int k)
{
    int cnt = 0;
    while(x)
    {
        a[cnt++] = x % 10;
        x /= 10;
    }
    return dfs(cnt - 1, 1, 0, true, k);
}

inline int lowbit(int x)
{
    return x & (-x);
}
int main()
{
    memset(dp, -1, sizeof dp);
    one[0] = 0;
    for(int i = 1; i < 1 << 11; ++i) one[i] = one[i ^ lowbit(i)] + 1;
    int T, cas = 0;
    scanf("%d", &T);
    while(T--)
    {
        long long l, r;
        scanf("%I64d%I64d%d", &l, &r, &k);
        printf("Case #%d: %I64d\n", ++cas, cal(r, k) - cal(l - 1, k));
    }
    return 0;
}

