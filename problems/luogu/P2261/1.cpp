/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 06月 30日 星期二 16:17:16 CST */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
typedef long long ll;

int n,m;
int k,c;

void init(){
    scanf("%d%d",&n,&k);
    ll ans = 0;
    for(int l=1,r;l<=min(k,n);l = r+1){
        r = k/(k/l);
        r = min(r,n);
        ans += (ll)(k/l)*(l+r)*(r-l+1)/2;
    }
    ans = (ll)n*k - ans;
    printf("%lld\n",ans);
}

int main(){
    init();
    return 0;
}

