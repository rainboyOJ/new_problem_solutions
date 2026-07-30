/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <iostream>
using namespace std;


void swap(int &x,int &y){
	int t= x;
	x =y;
	y =t;
}

//
bool dfs(int t1,int t2){
	if(t1 < t2) swap(t1,t2);
	if( t1 % t2 == 0 || t1 / t2 >=2) 
		return true;
	return !dfs(t1-t2,t2);
}


int main(){
	int x,y;
	
	while(1){
		cin >> x >> y;
		if( x== 0 && y== 0)
			break;
		if( dfs(x,y))
			cout << "win" << endl;
		else
			cout << "lose" << endl;
	}
	
	return 0;
}
