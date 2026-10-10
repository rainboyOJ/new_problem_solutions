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
const ll NEG=-(ll)1000000000000000000LL;
vector<ll> advance_col(vector<ll>&dp, vector<ll>&pre){int n=dp.size(); vector<ll> lo(n),hi(n),res(n); ll best=NEG; for(int r=0;r<n;r++){best=max(best,dp[r]-pre[r]); lo[r]=best;} best=NEG; for(int r=n-1;r>=0;r--){best=max(best,dp[r]+pre[r+1]); hi[r]=best;} for(int c=0;c<n;c++) res[c]=max(pre[c+1]+lo[c], hi[c]-pre[c]); return res;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; vector<vector<ll> > pre(m, vector<ll>(n+1)); for(int i=0;i<n;i++) for(int j=0;j<m;j++){ll v;cin>>v; pre[j][i+1]=pre[j][i]+v;} vector<ll> dp(n); for(int i=0;i<n;i++) dp[i]=pre[0][i+1]; for(int j=1;j<m;j++) dp=advance_col(dp,pre[j]); cout<<dp[n-1]<<'\n'; return 0;}
