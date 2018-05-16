#include <bits/stdc++.h>
using namespace std;


int extend_gcd(int a, int b, int &x, int &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	int d = extend_gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int main(){
	int T;
	cin >> T;
	while(T--){
		int n, B;
		cin >> n >> B;
		int x, y;
		int d = extend_gcd(9973, B, x, y);
		y *= n;
		y %= 9973;
		if(y < 0) y += 9973;
		cout << y << endl;
	}
	return 0;
}

