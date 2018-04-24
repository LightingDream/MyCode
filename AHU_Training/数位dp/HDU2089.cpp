#include <bits/stdc++.h>
using namespace std;
const int maxn = 10;
int dp[maxn][2];
int a[maxn];

inline int dfs(int pos, int pre, int state, bool limit)
{
    if(pos == -1) return 1;
    if(!limit && ~dp[pos][state]) return dp[pos][state];
    int up = limit ? a[pos] : 9;
    int res = 0;
    for(int i = 0; i <= up; ++i)
    {
        if(pre == 6 && i == 2) continue;
        if(i == 4) continue;
        res += dfs(pos - 1, i, i == 6, limit ? i == a[pos] : limit);
    }
    return limit ? res : dp[pos][state] = res;
}
inline int cal(int x)
{
    int cnt = 0;
    while(x)
    {
        a[cnt++] = x % 10;
        x /= 10;
    }
    return dfs(cnt - 1, -1, 0, true);
}

int main()
{
    int l, r;
    while(~scanf("%d%d", &l, &r), l + r)
    {
        memset(dp, -1, sizeof dp);
        printf("%d\n", cal(r) - cal(l - 1));
    }
    return 0;
}
