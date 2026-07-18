machine_count, job_count = map(int, input().split())
order = [x - 1 for x in map(int, input().split())]
machine_for = [list(map(lambda x: int(x) - 1, input().split())) for _ in range(job_count)]
duration_for = [list(map(int, input().split())) for _ in range(job_count)]

max_time = job_count * machine_count * 20 + 1
busy = [[False for _ in range(max_time)] for _ in range(machine_count)]
next_operation = [0 for _ in range(job_count)]
job_finish_time = [0 for _ in range(job_count)]
answer = 0

for job in order:
    operation = next_operation[job]
    machine = machine_for[job][operation]
    duration = duration_for[job][operation]

    start = job_finish_time[job]
    while True:
        can_place = True
        for time in range(start, start + duration):
            if busy[machine][time]:
                start = time + 1
                can_place = False
                break
        if can_place:
            break

    for time in range(start, start + duration):
        busy[machine][time] = True

    finish = start + duration
    job_finish_time[job] = finish
    next_operation[job] += 1
    answer = max(answer, finish)

print(answer)
