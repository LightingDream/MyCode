#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef double ld;
typedef vector<int> VI;
typedef VI::iterator VIT;
typedef map<int, int> MII;
typedef map<int, ll> MILL;

const int MAX_N = 1000010;

namespace Number_Theory
{
	const int N = 100010;
	int phi[N];
	int pr[N / 5];
	int cnt;
	bool jz[N];
	void init()
	{
		memset(jz, true, sizeof jz);
		jz[1] = 0;
		for(int i = 2; i < N; ++i)
		{
			if(jz[i])
			{
				pr[++cnt] = i;
				phi[i] = i - 1;
			}
			for(int j = 1; j <= cnt && i * pr[j] < N; ++j)
			{
				jz[i * pr[j]] = 0;
				if(i % pr[j] == 0)
				{
					phi[i * pr[j]] = phi[i] * pr[j];
					break;
				}
				phi[i * pr[j]] = phi[i] * (pr[j] - 1);
			}

		}
	}
}
int main()
{
	/**printf("%d\n", test(0));**/
	int a;
	scanf("%d", &a);
	printf("%d\n", a);
	return 0;
}
