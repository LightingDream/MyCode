#include <bits/stdc++.h>
using namespace std;

long long cal(long long x)
{
    long long res = 0;
    for(long long i = 2; i * i * i <= x; ++i)
        res += x / (i * i * i);
    return res;
}
int main()
{
    long long n;
    while(~scanf("%lld", &n))
    {
        long long l = 7, r = 8 * 1e16;
        while(r - l > 1)
        {
        //  printf("%lld %lld\n", l, r);
            long long m = (l + r) >> 1;
            if(cal(m) >= n) r = m;
            else l = m;
        }
        printf("%lld\n", cal(r) == n ? r : -1);
    }
    return 0;
}
