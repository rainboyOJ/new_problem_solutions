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
const ll NEG = -(1LL<<60);
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); int n,m,q,u,v,t; if(!(cin>>n>>m>>q>>u>>v>>t)) return 0; vector<ll> big(n); for(int i=0;i<n;i++) cin>>big[i]; sort(big.begin(),big.end(),greater<ll>()); vector<ll> leftv,rightv,cut; int ia=0,ib=0,ic=0,nb=0; ll off=0; ll ha=n?big[0]:NEG,hb=NEG,hc=NEG; for(int sec=1;sec<=m;sec++){ll x; if(ha>=hb && ha>=hc){x=ha+off; ia++; ha=ia<n?big[ia]:NEG;} else if(hb>=hc){x=hb+off; ib++; hb=ib<nb?leftv[ib]:NEG;} else {x=hc+off; ic++; hc=ic<nb?rightv[ic]:NEG;} if(sec%t==0) cut.push_back(x); off+=q; ll head=(ll)u*x/v; leftv.push_back(head-off); rightv.push_back(x-head-off); nb++; if(hb==NEG) hb=ib<nb?leftv[ib]:NEG; if(hc==NEG) hc=ic<nb?rightv[ic]:NEG;} vector<ll> rest; for(int i=ia;i<n;i++) rest.push_back(big[i]+off); for(int i=ib;i<nb;i++) rest.push_back(leftv[i]+off); for(int i=ic;i<nb;i++) rest.push_back(rightv[i]+off); sort(rest.begin(),rest.end(),greater<ll>()); for(int i=0;i<(int)cut.size();i++){if(i) cout<<' '; cout<<cut[i];} cout<<'\n'; bool first=true; for(int i=t-1;i<(int)rest.size();i+=t){if(!first) cout<<' '; first=false; cout<<rest[i];} cout<<'\n'; return 0;}
