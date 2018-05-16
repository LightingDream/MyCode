#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 9;
#define clr(s) memset(s, 0, sizeof s)
int a[210];
long long dp[210][2][2010];
char *BCD[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000",
              "1001"};
struct AC_Auto{
    const static int N = 2010;
    int ch[N][2], f[N], last[N], q[N];
    int sz;
    void init(){
        clr(ch);
        clr(f);
        clr(q);
        clr(last);
        sz = 1;
    }
    void insert(char s[]){
        int len = strlen(s);
        int u = 0;
        for(int i = 0; i < len; ++i){
            int c = s[i] - '0';
            if(!ch[u][c]) ch[u][c] = sz++;
            u = ch[u][c];
        }
        last[u] = 1;
    }
    void getFail(){
        q[0] = 0;
        int now = 0, top = 1;
        while(now < top){
            int t = q[now++];
            for(int i = 0; i < 2; ++i){
                if(ch[t][i]){
                    int p = ch[t][i], u = f[t];
                    while(!ch[u][i] && u) u = f[u];
                    f[p] = t == 0 ? 0 : ch[u][i];
                    last[p] |= last[f[p]];
                    q[top++] = p;
                }
                else ch[t][i] = ch[f[t]][i];
            }
        }
    }
    int query(int u, char s[])
    {
        int len = strlen(s);
        for(int i = 0; i < len; ++i)
        {
            u = ch[u][s[i] - '0'];
            if(last[u]) return -1;
        }
        return u;
    }
}ac;

long long dfs(int pos, bool zero, int u, bool limit)
{
    if(pos == -1) return 1;
    if(!limit && ~dp[pos][zero][u]) return dp[pos][zero][u];
    int up = limit ? a[pos] : 9;
    long long res = 0;
    for(int i = 0; i <= up; ++i)
    {
        int now_u = u;
        if(zero == 0 || i) now_u = ac.query(u, BCD[i]);
        if(~now_u) res = (res + dfs(pos - 1, zero && i == 0, now_u, limit && i == up)) % mod;
    }
    return limit ? res : dp[pos][zero][u] = res;
}
inline long long cal(char x[])
{
    int len = strlen(x);
    for(int i = 0; i < len; ++i) a[i] = x[len - 1 - i] - '0';
    return dfs(len - 1, 1, 0, true);
}

inline long long ask(char A[], char B[])
{
    return (cal(B) - cal(A) + mod) % mod;
}

int main()
{

    int T;
    scanf("%d", &T);

    int n;
    char s[25], A[210], B[210];

    while(T--)
    {
        memset(dp, -1, sizeof dp);
        ac.init();
        scanf("%d", &n);
        while(n--)
        {
            scanf("%s", s);
            ac.insert(s);
        }
        ac.getFail();
        scanf("%s%s", A, B);
        int len = strlen(A);
        int p = len - 1;
        A[len - 1] -= 1;
        while(A[p] < '0')
        {
            A[p] += 10;
            --A[p - 1];
            --p;
        }
        printf("%lld\n", ask(A, B));
    }

    return 0;
}

