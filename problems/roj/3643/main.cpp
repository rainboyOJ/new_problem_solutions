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
const double EPS=1e-6; const int INF=1<<30;
struct Point{double x,y;};
int line_of(vector<Point>&pts,int i,int j){ if(i==j) return 1<<i; double x1=pts[i].x,y1=pts[i].y,x2=pts[j].x,y2=pts[j].y; if(fabs(x1-x2)<EPS) return 1<<i; double a=(y1/x1-y2/x2)/(x1-x2); if(a>=-EPS) return 1<<i; double b=y1/x1-a*x1; int mask=0; for(int k=0;k<(int)pts.size();k++) if(fabs(a*pts[k].x*pts[k].x+b*pts[k].x-pts[k].y)<EPS) mask|=1<<k; return mask; }
int solve_level(vector<Point>&pts){int n=pts.size(), full=(1<<n)-1; vector<vector<int> > line(n, vector<int>(n)); for(int i=0;i<n;i++) for(int j=0;j<n;j++) line[i][j]=line_of(pts,i,j); vector<int> dp(1<<n,INF); dp[0]=0; for(int mask=0;mask<(1<<n);mask++){int rest=full^mask; if(dp[mask]==INF||rest==0) continue; int low=0; while(((rest>>low)&1)==0) low++; int nxt=dp[mask]+1; for(int j=0;j<n;j++){int nm=mask|line[low][j]; if(nxt<dp[nm]) dp[nm]=nxt;}} return dp[full];}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int T; if(!(cin>>T)) return 0; while(T--){int n; string m; cin>>n>>m; vector<Point> pts(n); for(int i=0;i<n;i++) cin>>pts[i].x>>pts[i].y; cout<<solve_level(pts)<<'\n';} return 0;}
