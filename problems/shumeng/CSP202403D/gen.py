#!/usr/bin/env python3
import random
import bisect
import heapq


def main():
    random.seed()
    while True:
        c = random.randint(1, 30)
        m = random.randint(1, min(c, 12))
        n = random.randint(1, 4 * m)
        positions = sorted(random.sample(range(1, c + 1), m))
        water = {x: random.randint(1, 4) for x in positions}
        original = [(x, water[x]) for x in positions]
        operations = []
        for _ in range(n):
            if not positions:
                break
            position = random.choice(positions)
            operations.append(position)
            water[position] += 1
            pending = []
            if water[position] >= 5:
                heapq.heappush(pending, position)
            while pending:
                current = heapq.heappop(pending)
                if current not in water or water[current] < 5:
                    continue
                index = bisect.bisect_left(positions, current)
                positions.pop(index)
                del water[current]
                neighbors = []
                if index > 0: neighbors.append(positions[index - 1])
                if index < len(positions): neighbors.append(positions[index])
                for neighbor in neighbors:
                    water[neighbor] += 1
                    if water[neighbor] == 5:
                        heapq.heappush(pending, neighbor)
        if len(operations) == n:
            print(c, m, n)
            for position, count in original:
                print(position, count)
            for position in operations:
                print(position)
            return


if __name__ == "__main__":
    main()
