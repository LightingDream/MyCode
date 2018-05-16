#include <bits/stdc++.h>
using namespace std;

int cal(int x){
	int res = 1;
	for(int i = 2; i * i <= x; ++i){
		if(x % i == 0){
			int cnt = 0;
			while(x % i == 0){
				x /= i;
				++cnt;
			}
			res *= cnt + 1;
		}
	}
	if(x > 1) res *= 2;
	return res;
}

int main(){
	int n;
	while(cin >> n, n) cout << (n == 1 ? 0 : cal(n) - 2) << endl;
	return 0;
}


