import sys
import heapq

def main():
    def get_ints():
        for line in sys.stdin:
            for token in line.split():
                yield int(token)

    tokens = get_ints()
    try:
        n = next(tokens)
        m = next(tokens)
    except StopIteration:
        return

    m += 1

    ans = 0
    sum_val = 0
    cnt = 0
    pq = []

    for i in range(1, n + 1):
        try:
            h = next(tokens)
            v = next(tokens)
        except StopIteration:
            break

        if i > m:
            break

        sum_val += v
        extra = h - 1
        if extra > 0:
            sum_val += extra * v
            cnt += extra
            heapq.heappush(pq, (v, extra))

        budget = m - i
        while pq and cnt - pq[0][1] >= budget:
            top_v, top_extra = heapq.heappop(pq)
            cnt -= top_extra
            sum_val -= top_extra * top_v

        if cnt > budget:
            over = cnt - budget
            ans = max(ans, sum_val - pq[0][0] * over)
        else:
            ans = max(ans, sum_val)

    print(ans)

if __name__ == '__main__':
    main()
