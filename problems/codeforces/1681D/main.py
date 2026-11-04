import sys
from collections import defaultdict, deque

## number , step
type Item = tuple[int,int]

def num_len(n):
    return len(str(n))

def num_iter(n):
    while n :
        yield n % 10
        n //= 10



def solve(data):
    n = next(data)
    num = next(data)
    q= deque()
    q.append((num,0))
    vis = defaultdict(bool)
    ans = -1;
    
    while q:
        cur,step = q.popleft()
        # print(cur,step)
        for i in num_iter(cur):
            if i ==0 or i == 1 :
                continue
            nxt = cur * i
            # print(f"nxt({nxt}) = {cur} * {i}")
            if num_len(nxt) > n:
                continue
            if num_len(nxt)  == n:
                ans = step + 1
                print(ans)
                return
            if vis[nxt] == False:
                vis[nxt] = True
                q.append((nxt,step+1))
    print(ans)
    
    


if __name__ == "__main__":
    data = iter(map(int, sys.stdin.buffer.read().split()))
    solve(data)
