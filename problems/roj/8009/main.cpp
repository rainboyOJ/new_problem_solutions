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
const int ALPHA=18;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); string s1,s2; if(!(cin>>s1>>s2)) return 0; int n; cin>>n; vector<string> qs(n); for(int i=0;i<n;i++) cin>>qs[i]; vector<vector<int> > pos1(ALPHA),pos2(ALPHA); for(int i=0;i<(int)s1.size();i++) pos1[s1[i]-'a'].push_back(i); for(int i=0;i<(int)s2.size();i++) pos2[s2[i]-'a'].push_back(i); int bad_single=0; for(int c=0;c<ALPHA;c++) if(pos1[c].size()!=pos2[c].size()) bad_single|=1<<c; vector<vector<int> > pref1(ALPHA, vector<int>(s1.size()+1)), pref2(ALPHA, vector<int>(s2.size()+1)); for(int y=0;y<ALPHA;y++){for(int i=0;i<(int)s1.size();i++) pref1[y][i+1]=pref1[y][i]+(s1[i]-'a'==y); for(int i=0;i<(int)s2.size();i++) pref2[y][i+1]=pref2[y][i]+(s2[i]-'a'==y);} vector<int> bad_pair(ALPHA); for(int aa=0;aa<ALPHA;aa++) for(int bb=aa+1;bb<ALPHA;bb++){bool ok=pos1[aa].size()==pos2[aa].size() && pos1[bb].size()==pos2[bb].size(); if(ok){for(int i=0;i<(int)pos1[aa].size();i++) if(pref1[bb][pos1[aa][i]]!=pref2[bb][pos2[aa][i]]){ok=false;break;}} if(!ok){bad_pair[aa]|=1<<bb; bad_pair[bb]|=1<<aa;}} for(int qi=0;qi<n;qi++){int mask=0; for(int i=0;i<(int)qs[qi].size();i++) mask|=1<<(qs[qi][i]-'a'); int bad=mask&bad_single; while(mask && !bad){int bit=mask&-mask; mask^=bit; int c=__builtin_ctz(bit); bad=bad_pair[c]&mask;} cout<<(bad?'N':'Y');} cout<<'\n'; return 0;}
