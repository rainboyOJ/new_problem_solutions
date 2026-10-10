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
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int l,n,m; if(!(cin>>l>>n>>m)) return 0; vector<int> pos(n+1); for(int i=0;i<n;i++) cin>>pos[i]; pos[n]=l; int lo=1,hi=l; while(lo<hi){int mid=(lo+hi+1)/2; int cnt=0,prev=0; for(int i=0;i<=n;i++){ if(pos[i]-prev<mid) cnt++; else prev=pos[i]; } if(cnt<=m) lo=mid; else hi=mid-1;} cout<<lo<<'\n'; return 0;}
