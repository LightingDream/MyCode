#include <bits/stdc++.h>
using namespace std;

long long cal(int x){
	long long res = 1;
	for(int i = 2; i * i <= x; ++i){
		if(x % i == 0){
			int cnt = 0;
			while(x % i == 0){
				x /= i;
				++cnt;
			}
			res *= 6 * cnt;
		}
	}
	if(x > 1) res *= 6;
	return res;
}

int main(){
	int T;
	cin >> T;
	while(T--){
		int G, L;
		cin >> G >> L;
		cout << (L % G == 0 ? cal(L / G) : 0) << endl;
	}
	return 0;
}
