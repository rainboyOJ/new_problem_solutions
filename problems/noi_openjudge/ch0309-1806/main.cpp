/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;


map<string,string> m;
char t[100];

int main(){
    bool flag = true;
    while(cin.getline(t,100)){
        int len = strlen(t);
        if( len == 0) {
            flag = 0;
            continue;
        }

        if( flag){
            int i;
            for(i=0;i<len;i++){
                if( t[i] == ' ')
                    break;
            }
            string a(t,t+i);
            string b(t+i+1,t+len);
            m[b] = a;
        }
        else {
            string a(t,t+len);
            if( m[a].length() > 0 )
                cout << m[a] << endl;
            else
                cout << "eh" << endl;
        }

    }
    return 0;
}
