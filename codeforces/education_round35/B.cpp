#include <bits/stdc++.h>
using namespace std;


int main()
{

    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    int ans = 0;
    for(int i = n - b; i <= a; ++i)
        ans = max(ans, min(i == 0 ? 0 : a / i , i == n ? 0 : b / (n - i)));
    printf("%d\n", ans);
    return 0;
}
