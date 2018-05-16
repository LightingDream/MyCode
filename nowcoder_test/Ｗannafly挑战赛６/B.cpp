#include <bits/stdc++.h>
using namespace std;
#define N 12

double a[N], b[N], c[N];
double p[N];
double ans[N + 1];

int main()
{

    for(int i = 0; i < N; ++i) cin >> a[i];
    for(int i = 0; i < N; ++i) cin >> b[i];
    for(int i = 0; i < N; ++i) cin >> c[i];
    for(int i = 0; i < N; ++i) p[i] = 1 - (1 - a[i]) * (1 - b[i]) * (1 - c[i]);

    for(int i = 0; i < 1 << N; ++i)
    {
        int cnt = 0;
        double t = 1;
        for(int j = 0; j < N; ++j)
            if(i & (1 << j))
            {
                t *= p[j];
                ++cnt;
            }else t *= 1 - p[j];
        ans[cnt] += t;
    }

    for(int i = 0; i <= N; ++i) cout << fixed << setprecision(6) << ans[i] << endl;
    return 0;
}
