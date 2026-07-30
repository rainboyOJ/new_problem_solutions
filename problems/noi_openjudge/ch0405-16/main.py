case_number = 1
while True:
    counts = list(map(int, input().split()))
    if not any(counts):
        break
    total = sum((value + 1) * count for value, count in enumerate(counts))
    possible = total % 2 == 0
    if possible:
        target = total // 2
        reachable = 1
        mask = (1 << (target + 1)) - 1
        for value, count in enumerate(counts, start=1):
            batch = 1
            while count:
                take = min(batch, count)
                reachable |= reachable << (value * take)
                reachable &= mask
                count -= take
                batch <<= 1
        possible = (reachable >> target) & 1
    result = "Can be divided." if possible else "Can't be divided."
    print(f"Collection #{case_number}:\n{result}\n")
    case_number += 1
