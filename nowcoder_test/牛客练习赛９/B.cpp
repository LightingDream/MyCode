#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int maxn=1e6+10;

bool valid[maxn];
int ans[500010];

void getprime(int n,int &tot,int ans[])
{
    tot=0;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){
            tot++;
            ans[tot]=i;
        }
        //下面的主角是小于等于i的每个质数
        for(int j=1;(j<=tot) && (i*ans[j]<=n);++j){
            valid[i*ans[j]]=false;
            if(i%ans[j]==0) break;//如果整除就break;
        }
    }
}

ll mod_mul(ll a,ll b,ll c){//a*b %c 乘法改加法 防止超long long
    ll res=0;
    a=a%c;
    while(b)
    {
        if(b&1) res=(res+a)%c;
        b>>=1;
        a=(a+a)%c;
    }
    return res;
}

ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    a=a%c;
    while(b)
    {
        if(b&1) res=mod_mul(res,a,c);
        b>>=1;
        a=mod_mul(a,a,c);
    }
    return res;
}

bool test(ll n,ll a,ll d)
{//d=n-1
    if(!(n&1)) return false;
    while(!(d&1))  d>>=1;//将d分解为奇数
    ll t=fast_exp(a,d,n);
    while(d!=n-1 && t!=1 && t!=n-1){
        t=mod_mul(t,t,n);
        d<<=1;
    }
    return ((t==n-1) || (d&1) ==1 );
}

bool is_prime(ll n){
    if(n<2) return false;
    if(n < 1000010) return valid[n];
    ll a[30];
    srand(time(0));
    for(int i=0;i<5;++i) {//测试5次
        a[i]=rand()%(n-2)+2;//取[2,n-1]随机数
        if(!test(n,a[i],n-1)) return false;//a^n-1 % n =1 fermat
    }
    return true;//如果上面所有测试都是true
}


int main()
{
    ios::sync_with_stdio(false);
    int Count;
    getprime(1000010,Count,ans);
    //cout<<Count<<endl;
    //cout<<ans[1]<<endl;
    int t;
    scanf("%d", &t);
    while(t--)
    {
        ll n;
        scanf("%lld", &n);
        for(int i=1;i<=Count;++i){
            ll tmp=n-(ll)ans[i];
            if(is_prime(tmp)){
                printf("%d %lld\n", ans[i], n - ans[i]);
                break;
            }
        }
    }
    return 0;
}
