#include <bits/stdc++.h>
using namespace std;

int a[100010];
int main()
{
    int n;
    scanf("%d", &n);
    int mn = 1e9 + 1;
    int last = -1e5;
    int ans = 2e5 + 1;
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        mn = min(mn, a[i]);
    }
    for(int i = 1; i <= n; ++i)
        if(mn == a[i])
        {
            ans = min(ans, i - last);
            last = i;
        }
    printf("%d\n", ans);
    return 0;
}
