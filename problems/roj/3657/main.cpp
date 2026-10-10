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
vector<int> VAL,Lc,Rc; map<pair<int,int>, bool> MEMO;
bool mirror_tree(int a,int b){ if(a<0||b<0) return a<0&&b<0; vector<array<int,3> > st; st.push_back({a,b,0}); while(!st.empty()){array<int,3> cur=st.back(); st.pop_back(); int x=cur[0],y=cur[1],stage=cur[2]; if(x<0||y<0) continue; pair<int,int> key={x,y}; if(stage){int lx=Lc[x], ry=Rc[y], rx=Rc[x], ly=Lc[y]; bool aok=MEMO.count({lx,ry})?MEMO[{lx,ry}]:(lx<0&&ry<0); bool bok=MEMO.count({rx,ly})?MEMO[{rx,ly}]:(rx<0&&ly<0); MEMO[key]=aok&&bok;} else if(MEMO.count(key)) continue; else if(VAL[x]!=VAL[y]) MEMO[key]=false; else {st.push_back({x,y,1}); st.push_back({Lc[x],Rc[y],0}); st.push_back({Rc[x],Lc[y],0});}} return MEMO[{a,b}];}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n; if(!(cin>>n)) return 0; VAL.assign(n+1,0); for(int i=1;i<=n;i++) cin>>VAL[i]; Lc.assign(n+1,0); Rc.assign(n+1,0); for(int i=1;i<=n;i++) cin>>Lc[i]>>Rc[i]; vector<int> order, st; st.push_back(1); while(!st.empty()){int x=st.back();st.pop_back(); order.push_back(x); if(Lc[x]>0) st.push_back(Lc[x]); if(Rc[x]>0) st.push_back(Rc[x]);} vector<int> sz(n+1); int best=0; for(int i=(int)order.size()-1;i>=0;i--){int x=order[i]; int sub=1+(Lc[x]>0?sz[Lc[x]]:0)+(Rc[x]>0?sz[Rc[x]]:0); sz[x]=sub; if(sub>best && mirror_tree(Lc[x],Rc[x])) best=sub;} cout<<best<<'\n'; return 0;}
