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
const int AND=0, OR=1, NOT=2;
struct Child{int l,r;};
int calc(int op,int l,int r){ if(op==AND) return l&r; if(op==OR) return l|r; return l^1; }
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); vector<string> tokens; string tok; while(cin>>tok) tokens.push_back(tok); if(tokens.empty()) return 0; int pos=0; vector<string> expr; while(pos<(int)tokens.size() && !(tokens[pos][0]>='0'&&tokens[pos][0]<='9')) expr.push_back(tokens[pos++]); int n=atoi(tokens[pos++].c_str()); vector<int> val(n); for(int i=0;i<n;i++) val[i]=atoi(tokens[pos++].c_str()); int q=atoi(tokens[pos++].c_str()); vector<int> op_of, leaf_val, var_leaf(n,-1), stack; vector<Child> child; for(int ti=0;ti<(int)expr.size();ti++){string s=expr[ti]; int v=op_of.size(); if(s=="!"){int c=stack.back(); stack.pop_back(); stack.push_back(v); op_of.push_back(NOT); child.push_back({c,-1}); leaf_val.push_back(-1);} else if(s=="&"||s=="|"){int cr=stack.back(); stack.pop_back(); int cl=stack.back(); stack.pop_back(); stack.push_back(v); op_of.push_back(s=="&"?AND:OR); child.push_back({cl,cr}); leaf_val.push_back(-1);} else {int id=atoi(s.c_str()+1)-1; stack.push_back(v); op_of.push_back(-1); child.push_back({-1,-1}); leaf_val.push_back(val[id]); var_leaf[id]=v;}} int root=stack[0]; vector<int> node_val(op_of.size()); for(int v=0;v<(int)op_of.size();v++){int op=op_of[v]; if(op<0) node_val[v]=leaf_val[v]; else {int cl=child[v].l, cr=child[v].r; node_val[v]=calc(op,node_val[cl],cr>=0?node_val[cr]:0);}} vector<int> sens(op_of.size()); sens[root]=1; for(int v=(int)op_of.size()-1;v>=0;v--){int op=op_of[v]; if(op<0) continue; int cl=child[v].l, cr=child[v].r; if(op==NOT){sens[cl]=sens[v]; continue;} int pass_l=op==AND?node_val[cr]:1-node_val[cr]; int pass_r=op==AND?node_val[cl]:1-node_val[cl]; sens[cl]=sens[v]&pass_l; sens[cr]=sens[v]&pass_r;} for(int i=0;i<q;i++){int id=atoi(tokens[pos++].c_str()); cout<<(node_val[root]^sens[var_leaf[id-1]])<<'\n';} return 0;}
