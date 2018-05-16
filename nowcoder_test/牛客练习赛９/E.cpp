#include <bits/stdc++.h>
using namespace std;
const int up = 1e9;
const int sqr = ceil(sqrt(up));
bool jz[sqr + 10];
int pr[sqr + 10];
intc nt;
void init()
{
    for(int i = 2; i <= sqr; ++i)
    {
        if(jz[i]) pr[++cnt] = i;
        for(int j = 1; j <= cnt && i * pr[j] <= sqr; ++j)
        {
            jz[i * pr[j]] = 1;
            if(i % pr[j] == 0) break;
        }
    }
}

inline int cal(int l, int p)
{
    int res = l;
    for(int i = 1; pr[i] < p; ++i)
        res -= l /
}
int main()
{
    int x, y;
    scanf("%d%d", &x, &y);
    if((long long)x * y > up) return puts("0"), 0;
    if(x == 1) return printf("%d\n", y), 0;
    if(x > 1 && y >= sqr) return puts("0"), 0;
    int l = x, r = up / y;
    if(cal(r, y) < x) return puts("0"), 0;
    while(r - l > 1)
    {
        int mid = (l + r) >> 1;
        if(cal(mid, y) >= x) r = mid;
        else l = mid;
    }
    printf("%d\n", r * y);
    return 0;
}
