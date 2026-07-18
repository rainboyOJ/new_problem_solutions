from collections import defaultdict
import heapq
import sys

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    abilities = data[1:1 + n]
    abilities.sort()

    chains = defaultdict(list)
    answer = n

    for x in abilities:
        if chains[x - 1]:
            length = heapq.heappop(chains[x - 1]) + 1
        else:
            length = 1
        heapq.heappush(chains[x], length)

    for heap in chains.values():
        for length in heap:
            if length < answer:
                answer = length

    print(answer)

if __name__ == "__main__":
    main()
