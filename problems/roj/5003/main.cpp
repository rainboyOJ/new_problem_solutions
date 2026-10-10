/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n; if(!(cin>>n)) return 0; vector<ll>a(n); for(int i=0;i<n;i++) cin>>a[i]; sort(a.begin(),a.end()); ll total=0; int l=0,r=n-1; while(r-l>2){ll aa=a[l],bb=a[l+1],cc=a[r-1],dd=a[r]; if(2*bb<aa+cc){total+=aa+2*bb+dd; r-=2;} else {total+=aa+dd; r--;}} total += (r-l==2 ? a[l]+a[l+1]+a[r] : a[r]); cout<<total<<'\n'; return 0;}
