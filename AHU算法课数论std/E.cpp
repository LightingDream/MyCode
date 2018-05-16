#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000001;
bool isPrime[maxn];
int prime[maxn / 5];
int cnt;

void Euler_Seive(){
	memset(isPrime, true, sizeof isPrime);
	isPrime[1] = false;
	for(int i = 2; i < maxn; ++i){
		if(isPrime[i]) prime[++cnt] = i;
		for(int j = 1; j <= cnt && i * prime[j] < maxn; ++j){
			isPrime[i * prime[j]] = false;
			if(i % prime[j] == 0) break;
		}
	}

}

long long cal(long long x){
	long long res = 1;
	for(int i = 1; i <= cnt && (long long) prime[i] * prime[i] <= x; ++i){
		if(x % prime[i] == 0){
			int cnt = 0;
			while(x % prime[i] == 0){
				x /= prime[i];
				++cnt;
			}
			res *= 2 * cnt + 1;
		}
	}
	if(x > 1) res *= 3;
	return (res + 1) >> 1;
}

int main(){
	Euler_Seive();
	int T; int cas = 0;
	cin >> T;
	while(T--){
		long long n;
		cin >> n;
		cout << "Case " << ++cas << ": " << cal(n) << endl;
	}
	return 0;
}
