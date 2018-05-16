#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000001;
bool isPrime[maxn];
int prime[maxn / 5];
int mo[maxn];
int cnt;

void Euler_Seive(){
	memset(isPrime, true, sizeof isPrime);
	isPrime[1] = false;
	mo[1] = 1;
	for(int i = 2; i < maxn; ++i){
		if(isPrime[i]) {
			prime[++cnt] = i;
			mo[i] = -1;
		}
		for(int j = 1; j <= cnt && i * prime[j] < maxn; ++j){
			isPrime[i * prime[j]] = false;
			if(i % prime[j] == 0){
				mo[i * prime[j]] = 0;
				break;
			}
			mo[i * prime[j]] = -mo[i];
		}
	}
}

int cal(int x){
	int res = 0;
	for(int i = 1; (long long)i * i <= x; ++i)
		res += mo[i] * x / (i * i);
	return res;
}

int search(int x){
	int l = 0, r = 2000000000;
	while(r - l > 1){
		int mid = ((long long)l + r) >> 1;
		if(cal(mid) >= x) r = mid;
		else l = mid;
	}
	return r;
}

int main(){
	Euler_Seive();
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		cout << search(n) << endl;
	}
	return 0;
}
