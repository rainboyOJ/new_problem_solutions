worst_day = 0
longest_time = 8

for day in range(1, 8):
    school_time, extra_time = map(int, input().split())
    total_time = school_time + extra_time
    if total_time > longest_time:
        longest_time = total_time
        worst_day = day

print(worst_day)
