#include <bits/stdc++.h>
using namespace std;

int a[100010];
int cnt[1000010];
int main()
{

	int n;
	scanf("%d", &n);
	a[0] = 0;
	for(int i = 1; i <= n; ++i)
    {
        scanf("%d" , &a[i]);
        a[i] += a[i - 1];
        ++cnt[a[i]];
    }
	long long ans = 0;

		for(int i = 1; i <= n; ++i)
		{
            for(int k = 0; a[i - 1] + k * k <= a[n]; ++k)
            {
                ans += cnt[a[i - 1] + k * k];
            }
            --cnt[a[i]];
		}

	printf("%lld\n", ans);
	return 0;
}
