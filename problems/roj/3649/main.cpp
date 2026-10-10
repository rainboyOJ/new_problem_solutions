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
const int N_SCALE=1000000;
int bound_val(const string &s){return s=="n"?N_SCALE:atoi(s.c_str());}
string run_program(int lines,string claim, vector<string>&tok, int &pos){ set<string> alive; vector<pair<pair<int,string>, bool> > st; int depth=0,best=0; bool parent_dead=false, err=false; for(int line=0;line<lines;line++){string op=tok[pos++]; if(op=="F"){string var=tok[pos++],x=tok[pos++],y=tok[pos++]; if(err) continue; if(alive.count(var)){err=true; continue;} st.push_back({{depth,var},parent_dead}); bool dead=parent_dead || bound_val(x)>bound_val(y); if(!dead && x!="n" && y=="n"){depth++; best=max(best,depth);} parent_dead=dead; alive.insert(var);} else if(!err){ if(st.empty()){err=true; continue;} depth=st.back().first.first; string var=st.back().first.second; parent_dead=st.back().second; st.pop_back(); alive.erase(var);} } if(err||!st.empty()) return "ERR"; int expected=0; if(claim!="O(1)") expected=atoi(claim.substr(4, claim.size()-5).c_str()); return best==expected?"Yes":"No";}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); vector<string> tok; string s; while(cin>>s) tok.push_back(s); if(tok.empty()) return 0; int pos=0,T=atoi(tok[pos++].c_str()); for(int i=0;i<T;i++){int l=atoi(tok[pos++].c_str()); string claim=tok[pos++]; cout<<run_program(l,claim,tok,pos)<<'\n';} return 0;}
