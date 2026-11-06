import sys
from collections import defaultdict, deque

## 队列元素：当前整数，已经用掉的步数
type Item = tuple[int,int]


# 返回 n 的十进制位数（不含前导零）
def num_len(n):
    return len(str(n))


# 逐位取出 n 的十进制数位：37 -> 7, 3
def num_iter(n):
    while n :
        yield n % 10
        n //= 10



def solve(data):
    n = next(data)      # 目标位数
    num = next(data)    # 初值 x
    q= deque()          # BFS 队列，按层扩展
    q.append((num,0))   # 初值入队，步数为 0
    vis = defaultdict(bool)  # 访问集合：记录已入队过的整数，防止重复展开
    ans = -1;           # 默认无解，输出 -1

    while q:
        cur,step = q.popleft()   # 队头出队：当前整数与已用步数
        # print(cur,step)
        for i in num_iter(cur):  # 枚举 cur 出现过的每一个数位
            if i ==0 or i == 1 : # 剪枝：乘 0 归零卡死，乘 1 不改变整数
                continue
            nxt = cur * i        # 一步操作：乘上数位 i
            # print(f"nxt({nxt}) = {cur} * {i}")
            if num_len(nxt) > n: # 剪枝：位数已超过 n，之后回不来
                continue
            if num_len(nxt)  == n:   # 首次命中 n 位，BFS 保证步数最少
                ans = step + 1
                print(ans)
                return
            if vis[nxt] == False:    # 去重：只展开第一次到达的状态
                vis[nxt] = True
                q.append((nxt,step+1))
    print(ans)                       # 队列耗尽仍未命中，无解
    
    


if __name__ == "__main__":
    data = iter(map(int, sys.stdin.buffer.read().split()))  # 顺序读入两个整数
    solve(data)
