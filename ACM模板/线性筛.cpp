#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1000001;

template <class T = int>
struct Number_Theory
{ 
	T phi[N], mo[N], pr[N / 5], min_divisor[N];
	bool jz[N];
	int cnt;
	void Euler_sieve()
	{
		memset(jz, true, sizeof jz);
		jz[1] = false;
		phi[1] = mo[1] = 1;
		min_divisor[1] = 1;
		for (int i = 2; i < N; ++i)
		{
			if (jz[i])
			{
				pr[++cnt] = i;
				phi[i] = i - 1;
				mo[i] = -1;
				min_divisor[i] = i;
			}
			for (int j = 1; j <= cnt; ++j)
			{
				if (i * pr[j] >= N) break;
				T tmp = i * pr[j];
				min_divisor[tmp] = pr[j];
				jz[tmp] = false;
				if (i % pr[j] == 0)
				{
					phi[tmp] = phi[i] * pr[j];
					mo[tmp] = 0;
					break;
				}
				phi[tmp] = phi[i] * (pr[j] - 1);
				mo[tmp] = -mo[i];
			}
		}
	}
};