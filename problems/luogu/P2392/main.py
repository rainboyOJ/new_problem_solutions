def subject_time(times):
    total = sum(times)
    reachable = {0}

    for time in times:
        reachable |= {current + time for current in reachable}

    best = total
    for left in reachable:
        best = min(best, max(left, total - left))
    return best


sizes = list(map(int, input().split()))
answer = 0

for size in sizes:
    times = list(map(int, input().split()))
    answer += subject_time(times[:size])

print(answer)
