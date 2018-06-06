#include <bits/stdc++.h>
using namespace std;


bool judge(string s){
        int l = 0, r = s.length() - 1;
        while(s[l] == 'A') ++l;
        while(r >= 0 && s[r] == 'A') --r;
        if(r - l < 2) return false;
        r = s.length() - 1 - r;
        if(l == 0 && r) return false;
        if(l && r == 0) return false;
        if(l == 0 && r == 0){
                if(s[0] != 'P' && s[s.length() - 1] != 'T') return false;
                for(int i = 1; i < s.length() - 1; ++i)
                        if(s[i] != 'A') return false;
                return true;
        }
        if(r % l) return false;
        int cnt = r / l;
        r = s.length() - 1 - r;
        if(r - l != cnt + 1) return false;
        if(s[l] != 'P' && s[r] != 'T') return false;
        for(int i = l + 1; i < r; ++i)
                if(s[i] != 'A') return false;
        return true;
}

int main(){
        int n;
        cin >> n;
        while(n--){
                string s;
                cin >> s;
                printf("%s\n", judge(s) ? "YES" : "NO");
        }
        return 0;
}
