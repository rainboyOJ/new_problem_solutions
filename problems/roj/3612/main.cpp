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
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); int n; if(!(cin>>n)) return 0; vector<ll> h(n); for(int i=0;i<n;i++) cin>>h[i]; int up=1,down=1; for(int i=1;i<n;i++){ if(h[i]>h[i-1]) up=down+1; else if(h[i]<h[i-1]) down=up+1; } cout<<max(up,down)<<'\n'; return 0;}
