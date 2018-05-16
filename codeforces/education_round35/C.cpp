#include <bits/stdc++.h>
using namespace std;

bool judge(int x, int y, int z)
{
    if(x == 1) return true;
    if(x > 3) return false;
    if(x == 2 && y == 2) return true;
    if(x == 2 && y == 4 && z == 4) return true;
    if(x == 3 && y == 3 && z == 3) return true;
    return false;
}

void Swap(int &a, int &b)
{
    int tmp = b;
    b = a;
    a = tmp;
}

int main()
{
    int k1, k2, k3;
    scanf("%d%d%d", &k1, &k2, &k3);
    if(k1 > k2) Swap(k1, k2);
    if(k2 > k3) Swap(k2, k3);
    if(k1 > k2) Swap(k1, k2);
    printf("%s\n", judge(k1, k2, k3) ? "YES" : "NO");
    return 0;
}
