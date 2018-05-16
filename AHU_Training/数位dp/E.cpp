#include <bits/stdc++.h>
using namespace std;
const int maxn = 15;
int dp[maxn][10100];
int a[maxn];
int Up;
int dfs(int pos, int v, bool limit)
{
    if(pos == -1) return v <= Up;
    if(v > Up) return 0;
    if(!limit && ~dp[pos][Up - v]) return dp[pos][Up - v];
    int up = limit ? a[pos] : 9;
    int res = 0;
    for(int i = 0; i <= up; ++i)
        res += dfs(pos - 1, v + i * (1 << pos), limit ? i == a[pos] : limit);
    return limit ? res : dp[pos][Up - v] = res;
}
inline int cal(int x)
{
    int cnt = 0;
    while(x)
    {
        a[cnt++] = x % 10;
        x /= 10;
    }
    return dfs(cnt - 1, 0, true);
}
inline int Tran(int x)
{
    int res = 0, val = 1;
    while(x)
    {
        res = res + val * (x % 10);
        x /= 10;
        val <<= 1;
    }
    return res;
}
int main()
{
    int T, cas = 0;
    scanf("%d", &T);
    memset(dp, -1, sizeof dp);
    while(T--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        Up = Tran(a);
        printf("Case #%d: %d\n", ++cas, cal(b));
    }
    return 0;
}
