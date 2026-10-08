import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    
    cnt = [0] * (max(n, 3000000) + 5)
    mxR = 0
    for i in range(1, n + 1):
        r = int(input_data[i])
        cnt[r] += 1
        if r > mxR:
            mxR = r
            
    lim = max(n, mxR)
    mx = 0
    for r in range(1, lim + 1):
        if cnt[r] > mx:
            mx = cnt[r]
            
    bucket = [0] * (mx + 5)
    for r in range(1, lim + 1):
        if cnt[r] > 0:
            bucket[cnt[r]] += 1
            
    ans = 0
    x, y, z = mx, mx, mx
    
    while True:
        while x > 0 and bucket[x] == 0:
            x -= 1
        if x == 0:
            break
        bucket[x] -= 1
        
        while y > 0 and bucket[y] == 0:
            y -= 1
        if y == 0:
            break
        bucket[y] -= 1
        
        while z > 0 and bucket[z] == 0:
            z -= 1
        if z == 0:
            break
        bucket[z] -= 1
        
        if x > 1:
            bucket[x - 1] += 1
        if y > 1:
            bucket[y - 1] += 1
        if z > 1:
            bucket[z - 1] += 1
            
        ans += 1
        
    print(ans)

if __name__ == '__main__':
    solve()
