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
const ll INF = (ll)1000000000000000000LL;
ll comb_count(int n,int r){ if(r<0||r>n) return 0; if(r>n-r) r=n-r; ll ans=1; for(int i=1;i<=r;i++) ans=ans*(n-r+i)/i; return ans; }
void gen_combos(int n,int take,int start,vector<int>&cur,vector<vector<int> >&all){ if((int)cur.size()==take){all.push_back(cur);return;} for(int i=start;i<n;i++){cur.push_back(i); gen_combos(n,take,i+1,cur,all); cur.pop_back();}}
ll best_score(vector<vector<ll> > &mat,int take,int pick){ int height=mat.size(), width=mat[0].size(); vector<vector<ll> > flat(height, vector<ll>(width*width)); for(int r=0;r<height;r++) for(int i=0;i<width;i++) for(int j=0;j<width;j++) flat[r][i*width+j]=llabs(mat[r][i]-mat[r][j]); vector<vector<int> > all; vector<int> cur; gen_combos(height,take,0,cur,all); ll best=INF; for(int ci=0;ci<(int)all.size();ci++){vector<int> combo=all[ci]; vector<ll> v(width); for(int b=0;b<width;b++) for(int z=0;z+1<(int)combo.size();z++) v[b]+=llabs(mat[combo[z]][b]-mat[combo[z+1]][b]); vector<ll> h(width*width); for(int z=0;z<(int)combo.size();z++) for(int p=0;p<width*width;p++) h[p]+=flat[combo[z]][p]; vector<ll> dp=v; for(int step=1;step<pick;step++){ vector<ll> ndp(width,INF); for(int j=1;j<width;j++){ll mn=INF; int base=j*width; for(int i=0;i<j;i++) mn=min(mn, dp[i]+h[base+i]); ndp[j]=v[j]+mn;} dp=ndp;} for(int i=0;i<width;i++) best=min(best,dp[i]); } return best; }
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); int n,m,r,c; if(!(cin>>n>>m>>r>>c)) return 0; vector<vector<ll> > rows(n, vector<ll>(m)); for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>rows[i][j]; if(comb_count(n,r)<=comb_count(m,c)) cout<<best_score(rows,r,c)<<'\n'; else {vector<vector<ll> > tr(m, vector<ll>(n)); for(int i=0;i<n;i++) for(int j=0;j<m;j++) tr[j][i]=rows[i][j]; cout<<best_score(tr,c,r)<<'\n';} return 0;}
