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
const int INF=1000000000;
void rise(vector<int>&nt, vector<int>&nc, vector<int>&tap, vector<int>&cnt, int dx, int m){ for(int h=1;h<=m;h++){int t=h+dx; if(t>m) t=m; int v=tap[h]+1; if(v<nt[t]) nt[t]=v; if(cnt[h]>nc[t]) nc[t]=cnt[h]; int w=nt[h]+1; if(w<nt[t]) nt[t]=w; if(nc[h]>nc[t]) nc[t]=nc[h];}}
void fall(vector<int>&nt, vector<int>&nc, vector<int>&tap, vector<int>&cnt, int dy, int m){ for(int to=1;to<=m-dy;to++){int from=to+dy; if(tap[from]<nt[to]) nt[to]=tap[from]; if(cnt[from]>nc[to]) nc[to]=cnt[from];}}
void pass_pipe(vector<int>&nt, vector<int>&nc, pair<int,int> gap, int m){int low=gap.first, high=gap.second; for(int h=1;h<=low;h++){nt[h]=INF; nc[h]=-1;} for(int h=high;h<=m;h++){nt[h]=INF; nc[h]=-1;} for(int h=low+1;h<high;h++) if(nc[h]>=0) nc[h]++;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n,m,k; if(!(cin>>n>>m>>k)) return 0; vector<pair<int,int> > steps(n); for(int i=0;i<n;i++) cin>>steps[i].first>>steps[i].second; vector<pair<int,int> > pipe(n, {-1,-1}); for(int i=0;i<k;i++){int p,l,h;cin>>p>>l>>h; pipe[p]={l,h};} vector<int> tap(m+1), cnt(m+1); int best=0; for(int x=0;x<n;x++){vector<int> nt(m+1,INF), nc(m+1,-1); rise(nt,nc,tap,cnt,steps[x].first,m); fall(nt,nc,tap,cnt,steps[x].second,m); if(x+1<n && pipe[x+1].first!=-1) pass_pipe(nt,nc,pipe[x+1],m); for(int h=1;h<=m;h++) best=max(best,nc[h]); tap=nt; cnt=nc;} int few=INF; for(int h=1;h<=m;h++) few=min(few,tap[h]); bool won=few<INF; cout<<(won?1:0)<<'\n'<<(won?few:best)<<'\n'; return 0;}
