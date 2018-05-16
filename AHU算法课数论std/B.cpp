#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    int T;
    int a, b;
    cin >> T;
    while(T--){
        cin >> a >> b;
        int time = a / b, i;
        for(i = 2; gcd(i, time) > 1;++i);
        cout << i * b << endl;
    }
    return 0;
}
