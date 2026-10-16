import sys

type Graph = list[list[int]]

def solve(data):
    n = next(data)
    G = [ [next(data) for _ in [0] * n] for i in range(n) ]
    for middle in range(n):
        for i in range(n):
            if G[i][middle] == 0 : 
                continue
            for j in range(n):
                G[i][j] |= (G[i][middle] & G[middle][j])
    return G
        
    
    
if __name__ == "__main__":
    data = iter(map(int, sys.stdin.buffer.read().split()))
    g = solve(data)
    print('\n'.join(' '.join(map(str, row)) for row in g))
