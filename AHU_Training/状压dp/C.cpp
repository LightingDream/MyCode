#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1 << 10;
int one[maxn];
int cnt;
int state[62];
int rstate[110];

inline int lowbit(int x)
{
    return x & (-x);
}
void init()
{
    one[0] = 0;
    for(int i = 0; i < maxn; ++i)
    {
        if(i) one[i] = one[i ^ lowbit(i)] + 1;
        if((i & (i >> 1)) || (i & (i >> 2))) continue;
        else  state[cnt++] = i;
    }
}


int dp[110][62][62];
char str[15];

int main()
{
    init();
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
    {
        rstate[i] = 0;
        scanf("%s", str);
        for(int j = 0; j < m; ++j)
            if(str[j] == 'P') rstate[i] += 1 << j;
    }
    memset(dp, -1, sizeof dp);
    for(int i = 0; i < cnt; ++i)
    {
        if((~rstate[1]) & state[i]) continue;
        else dp[1][i][0] = one[state[i]];
    }
    for(int i = 2; i <= n; ++i)
    {
        for(int j = 0; j < cnt; ++j)
        {
            if((~rstate[i]) & state[j]) continue;
            for(int k = 0; k < cnt; ++k)
            {
                if(state[j] & state[k]) continue;
                if((~rstate[i - 1]) & state[k]) continue;
                for(int t = 0; t < cnt; ++t)
                {
                    if(state[j] & state[t]) continue;
                    if(dp[i - 1][k][t] == -1) continue;
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][t] + one[state[j]]);
                   //printf("ce : %d %d %d %d\n", i, state[j], state[k], dp[i][j][k]);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < cnt; ++i)
        for(int j = 0; j < cnt; ++j)
            ans = max(ans, dp[n][i][j]);
    printf("%d\n", ans);
	return 0;
}
