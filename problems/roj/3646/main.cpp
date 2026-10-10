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
struct State{int d,x,y,magic,c; bool operator<(const State&o)const{return d>o.d;}};
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int m,n; if(!(cin>>m>>n)) return 0; vector<vector<int> > color(m+1, vector<int>(m+1,-1)); for(int i=0;i<n;i++){int x,y,c;cin>>x>>y>>c; color[x][y]=c;} map<array<int,4>, int> dist; priority_queue<State> pq; int sc=color[1][1]; array<int,4> st={1,1,0,sc}; dist[st]=0; pq.push({0,1,1,0,sc}); int dx[4]={-1,1,0,0}, dy[4]={0,0,-1,1}; int ans=-1; while(!pq.empty()){State cur=pq.top();pq.pop(); array<int,4> key={cur.x,cur.y,cur.magic,cur.c}; if(dist[key]!=cur.d) continue; if(cur.x==m && cur.y==m){ans=cur.d; break;} for(int z=0;z<4;z++){int nx=cur.x+dx[z], ny=cur.y+dy[z]; if(nx<1||nx>m||ny<1||ny>m) continue; int nd,nmagic,nc; if(color[nx][ny]!=-1){nc=color[nx][ny]; nd=cur.d+(nc!=cur.c); nmagic=0;} else if(cur.magic) continue; else {nc=cur.c; nd=cur.d+2; nmagic=1;} array<int,4> nk={nx,ny,nmagic,nc}; if(!dist.count(nk)||nd<dist[nk]){dist[nk]=nd; pq.push({nd,nx,ny,nmagic,nc});}}} cout<<ans<<'\n'; return 0;}
