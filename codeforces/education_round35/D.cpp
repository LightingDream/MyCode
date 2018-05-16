#include <bits/stdc++.h>
using namespace std;
int a[1510];


int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int ans = 0;
    for(int i = 1; i < n; ++i)
        for(int j = i + 1; j <= n; ++j)
            if(a[i] > a[j]) ans ^= 1;
    int q;
    scanf("%d", &q);
    while(q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        r -= l - 1;
        int num = r * (r - 1) / 2;
        ans ^= num % 2;
        printf("%s\n", ans & 1 ? "odd" : "even");
    }
    return 0;
}
