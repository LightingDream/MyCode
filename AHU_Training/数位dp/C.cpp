#include <bits/stdc++.h>
using namespace std;
const int maxn = 15;
int dp[maxn][2][maxn];
int a[maxn];

int dfs(int pos, int pre, int state, int mod, bool limit)
{
    if(pos == -1) return mod == 0;
    if(!limit && ~dp[pos][state][mod]) return dp[pos][state][mod];
    int up = limit ? a[pos] : 9;
    int res = 0;
    for(int i = 0; i <= up; ++i)
    {
        if(pre == 1 && i == 3) continue;
        res += dfs(pos - 1, i, i == 1, (mod * 10 + i) % 13, limit ? i == a[pos] : limit);
    }
    return limit ? res : dp[pos][state][mod] = res;
}
inline int cal(int x)
{
    int cnt = 0;
    while(x)
    {
        a[cnt++] = x % 10;
        x /= 10;
    }
    return dfs(cnt - 1, -1, 0, 0, true);
}
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        memset(dp, -1, sizeof dp);
        printf("%d\n", n / 13 + 1 - cal(n));
    }
    return 0;
}
