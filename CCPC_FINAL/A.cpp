#include <bits/stdc++.h>
using namespace std;
typedef vector< pair<int, int> > PII;
#define mp make_pair
#define fi first
#define se second
#define pb push_back
bool vis[85][85];

int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

int main()
{
    freopen("out.txt", "w", stdout);
    PII last;
    last.pb(mp(40, 40));
    int ans = 1;
    vis[40][40] = 1;
    for(int i = 1; i <= 20; ++i)
    {
        PII now;
        for(auto u : last)
        {
            int x = u.fi, y = u.se;
            for(int j = 0; j < 8; ++j)
            {
                int fx = x + dx[j], fy = y + dy[j];
                if(!vis[fx][fy])
                {
                    ++ans;
                    vis[fx][fy] = 1;
                    now.pb(mp(fx, fy));
                }
            }
        }
        last = now;
          printf("%d\n", ans);
    }
	return 0;
}
