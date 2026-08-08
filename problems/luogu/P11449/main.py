import sys

def main():
    LU = []
    for d in range(2, 11):
        L = 4 * 10 * (10**(d-1) - 1) // 9 + 5
        U = 5 * 10**(d-1) - 1
        LU.append((L, U))

    data = sys.stdin.buffer.read().split()
    T = int(data[0])
    out = []
    for i in range(1, T + 1):
        N = int(data[i])
        ans = 0
        for L, U in LU:
            if N >= L:
                ans += min(U, N) - L + 1
            else:
                break
        out.append(str(ans))
    sys.stdout.write('\n'.join(out) + '\n')

main()
