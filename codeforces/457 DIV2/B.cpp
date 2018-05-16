#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;
int cnt;
int prime[maxn];
bool isPrime[maxn];
void Euler_Seive()
{
    memset(isPrime, true, sizeof isPrime);
    isPrime[1] = 0;
    for(int i = 2; i < maxn; ++i)
    {
        if(isPrime[i]) prime[++cnt] = i;
        for(int j = 1; j <= cnt && i * prime[j] < maxn; ++j)
        {
            isPrime[i * prime[j]] = 0;
            if(i % prime[j] == 0) break;
        }
    }
}
int main()
{
    Euler_Seive();
    int n, m;
    int ans;
    cin >> n >> m;
    for(int i = 1; i <= cnt; ++i)
        if(prime[i] >= n - 1)
    {
        ans = prime[i];
        break;
    }
    cout << ans << ' ' << ans << endl;
    for(int i = 1; i < n -1; ++i) cout << i << " " << i + 1 << " " << 1 << endl;
    cout << n - 1 << ' ' << n << ' ' <<ans - n + 2 << endl;
    m -= n - 1;

    for(int i = 1; m && i < n - 1; ++i)
        for(int j = i + 2; m && j <= n; ++j)
    {
        cout << i << ' ' << j << ' ' << 100000000 << endl;
        --m;
    }
    return 0;
}
