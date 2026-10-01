import sys
from math import sqrt

def main() -> None:
    data = sys.stdin.read().split()
    it = iter(data)
    n, d = int(next(it)), int(next(it))
    segs = []
    for _ in range(n):
        x, y = int(next(it)), int(next(it))
        if y > d:                       # 纵坐标超过 d，任何雷达都够不着
            print(-1)
            return
        t = sqrt(d * d - y * y)         # 半径 d 的圆与 x 轴交点的半宽
        segs.append((x - t, x + t))     # 小岛可被覆盖 ⟺ 雷达位置落在此区间内
    segs.sort(key=lambda s: s[1])       # 按右端点排序后做区间选点贪心
    ans, pos = 0, float("-inf")         # pos 为上一个已放雷达的位置
    for l, r in segs:
        if l > pos:                     # 当前区间与已有雷达不相交，必须新放一个
            ans += 1
            pos = r                     # 贪心放在右端点，能覆盖后续最多的区间
    print(ans)

main()
