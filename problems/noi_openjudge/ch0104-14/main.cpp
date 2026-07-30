/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int  main(){
	int w,y;
	scanf("%d",&w);
	scanf("%c",&y);
	scanf("%c",&y);
	int h = 8;
	if( w - 1000 > 0){
		int c = w - 1000;
		h = h + (c / 500) * 4;
		if( c % 500 != 0){
			h = h +4;
		}
	}
	if( y == 'y')
		h = h + 5;
	printf("%d",h);
	return 0;
}
