import sys
import heapq

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    
    tasks = []
    idx = 1
    for _ in range(n):
        t = int(input_data[idx])
        w = int(input_data[idx+1])
        tasks.append((t, w))
        idx += 2
        
    tasks.sort(key=lambda x: (x[0], -x[1]))
    
    pq = []
    
    for t, w in tasks:
        if len(pq) < t:
            heapq.heappush(pq, w)
        elif pq and pq[0] < w:
            heapq.heappop(pq)
            heapq.heappush(pq, w)
            
    print(sum(pq))

if __name__ == '__main__':
    solve()
