import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    if len(input_data) < 6:
        return

    n = int(input_data[0])
    m = int(input_data[1])
    q = int(input_data[2])
    u = int(input_data[3])
    v = int(input_data[4])
    t = int(input_data[5])

    q0_arr = []
    for i in range(n):
        q0_arr.append(int(input_data[6 + i]))
    q0_arr.sort(reverse=True)

    head0 = 0
    tail0 = n

    from collections import deque
    q1 = deque()
    q2 = deque()

    offset = 0
    out1 = []

    for i in range(1, m + 1):
        max_val = -3000000000
        which = -1

        if head0 < tail0 and q0_arr[head0] > max_val:
            max_val = q0_arr[head0]
            which = 0
        if q1 and q1[0] > max_val:
            max_val = q1[0]
            which = 1
        if q2 and q2[0] > max_val:
            max_val = q2[0]
            which = 2

        if which == 0:
            head0 += 1
        elif which == 1:
            q1.popleft()
        elif which == 2:
            q2.popleft()

        L = max_val + offset

        if i % t == 0:
            out1.append(str(L))

        L1 = L * u // v
        L2 = L - L1

        q1.append(L1 - offset - q)
        q2.append(L2 - offset - q)

        offset += q

    if out1:
        sys.stdout.write(" ".join(out1) + "\n")
    else:
        sys.stdout.write("\n")

    out2 = []
    count = 0

    while head0 < tail0 or q1 or q2:
        max_val = -3000000000
        which = -1

        if head0 < tail0 and q0_arr[head0] > max_val:
            max_val = q0_arr[head0]
            which = 0
        if q1 and q1[0] > max_val:
            max_val = q1[0]
            which = 1
        if q2 and q2[0] > max_val:
            max_val = q2[0]
            which = 2

        if which == 0:
            head0 += 1
        elif which == 1:
            q1.popleft()
        elif which == 2:
            q2.popleft()

        count += 1
        if count % t == 0:
            out2.append(str(max_val + offset))

    if out2:
        sys.stdout.write(" ".join(out2) + "\n")
    else:
        sys.stdout.write("\n")


if __name__ == '__main__':
    solve()