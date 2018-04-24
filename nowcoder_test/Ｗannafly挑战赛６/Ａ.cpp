#include <bits/stdc++.h>
using namespace std;


int main()
{
    int	T;
    scanf("%d", &T);

    while(T--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", (int)sqrt(r + 0.01) - (l ? (int)sqrt(l - 1 + 0.01) : -1));
    }

    return 0;
}
