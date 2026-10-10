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
const int INF = 1000000000;
int n,m,qnum,kcells; vector<int> free_cell; vector<vector<int> > adj; map<ll, vector<int> > memo;
vector<int> blank_dist(int src,int blocked){ vector<int> dist(kcells,INF); if(src<0||src>=kcells) return dist; dist[src]=0; queue<int> q; q.push(src); while(!q.empty()){int u=q.front();q.pop(); for(int i=0;i<(int)adj[u].size();i++){int v=adj[u][i]; if(v!=blocked && dist[v]>dist[u]+1){dist[v]=dist[u]+1; q.push(v);}}} return dist; }
vector<int> near_dist(int p,int a){ ll key=(ll)p*kcells+a; if(memo.count(key)) return memo[key]; vector<int> d=blank_dist(a,p), res; for(int i=0;i<(int)adj[p].size();i++) res.push_back(d[adj[p][i]]); memo[key]=res; return res; }
struct Node{int c,p,a; bool operator<(const Node&o)const{ return c>o.c; }};
int play(int e0,int s,int t){ if(!free_cell[s]||!free_cell[t]||!free_cell[e0]) return -1; if(s==t) return 0; vector<int> first=blank_dist(e0,s); map<pair<int,int>, int> best; priority_queue<Node> pq; for(int i=0;i<(int)adj[s].size();i++){int a=adj[s][i]; if(first[a]<INF){best[{s,a}]=first[a]; pq.push({first[a],s,a});}} while(!pq.empty()){Node cur=pq.top();pq.pop(); pair<int,int> key={cur.p,cur.a}; if(best[key]!=cur.c) continue; if(cur.p==t) return cur.c; pair<int,int> nk={cur.a,cur.p}; if(cur.c+1 < (best.count(nk)?best[nk]:INF)){best[nk]=cur.c+1; pq.push({cur.c+1,cur.a,cur.p});} vector<int> nd=near_dist(cur.p,cur.a); for(int i=0;i<(int)adj[cur.p].size();i++){int b=adj[cur.p][i], step=nd[i]; pair<int,int> nk2={cur.p,b}; int old=best.count(nk2)?best[nk2]:INF; if(step<INF && cur.c+step<old){best[nk2]=cur.c+step; pq.push({cur.c+step,cur.p,b});}} } return -1; }
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); if(!(cin>>n>>m>>qnum)) return 0; kcells=n*m; free_cell.resize(kcells); for(int i=0;i<kcells;i++) cin>>free_cell[i]; adj.assign(kcells, vector<int>()); for(int i=0;i<kcells;i++) if(free_cell[i]){int r=i/m,c=i%m; int js[4]={i-1,i+1,i-m,i+m}; bool ok[4]={c>0,c<m-1,r>0,r<n-1}; for(int z=0;z<4;z++) if(ok[z] && free_cell[js[z]]) adj[i].push_back(js[z]);} for(int qq=0;qq<qnum;qq++){int ex,ey,sx,sy,tx,ty;cin>>ex>>ey>>sx>>sy>>tx>>ty; ex--;ey--;sx--;sy--;tx--;ty--; cout<<play(ex*m+ey,sx*m+sy,tx*m+ty)<<'\n';} return 0;}
