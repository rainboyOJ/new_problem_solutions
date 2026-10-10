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
const int MOD=1000000007;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n,m,k; if(!(cin>>n>>m>>k)) return 0; string A,B; cin>>A>>B; vector<vector<int> > cols(256); for(int i=0;i<m;i++) cols[(unsigned char)B[i]].push_back(i+1); vector<vector<int> > f(m+1, vector<int>(k)), gprev(m+1, vector<int>(k)); for(int idx=0;idx<n;idx++){unsigned char ch=A[idx]; vector<vector<int> > gcur(m+1, vector<int>(k)); vector<int> &vc=cols[ch]; for(int id=(int)vc.size()-1; id>=0; id--){int col=vc[id]; for(int t=0;t<k;t++){ll y = (t==0 ? (col==1?1:0) : f[col-1][t-1]); ll v = gprev[col-1][t] + y; if(v>=MOD) v-=MOD; int joined=v; ll nf=f[col][t]+joined; if(nf>=MOD) nf-=MOD; f[col][t]=nf; gcur[col][t]=joined;}} gprev.swap(gcur);} cout<<f[m][k-1]<<'\n'; return 0;}
