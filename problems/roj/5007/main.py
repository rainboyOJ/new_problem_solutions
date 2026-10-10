import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    b = int(input_data[1])
    a = [int(x) for x in input_data[2:]]
    
    sum_a = sum(a)
    lo = 0
    hi = (sum_a + b) // n + 1
    
    ans = 0
    while lo <= hi:
        mid = (lo + hi) // 2
        need = 0
        possible = True
        for cards in a:
            if cards < mid:
                need += mid - cards
                if need > mid:
                    possible = False
                    break
        if possible and need <= b:
            ans = mid
            lo = mid + 1
        else:
            hi = mid - 1
            
    print(ans)

if __name__ == '__main__':
    solve()
