#include <bits/stdc++.h>
using namespace std;
char s[30];
int t;
inline int cal(char x)
{
    return x - '0';
}
int get(char a[])
{
    return (10 * cal(a[0]) + cal(a[1])) * 3600 + (10 * cal(a[3]) + cal(a[4])) * 60 + (10 * cal(a[6]) + cal(a[7]));
}
int main()
{
    scanf("%s", s);
    scanf("%s", s);
    scanf("%d", &t);
    int ans = t / 86400;
    t %= 86400;
    int second = get(s);
    printf("%d\n", ans + (t + second >= 86400));
    return 0;
}
