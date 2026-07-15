import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


data = read_all_ints()
machine_count, job_count = data[0], data[1]
order = [x - 1 for x in data[2:2 + machine_count * job_count]]
pos = 2 + machine_count * job_count
machine_for = []
for _ in range(job_count):
    machine_for.append([x - 1 for x in data[pos:pos + machine_count]])
    pos += machine_count
duration_for = []
for _ in range(job_count):
    duration_for.append(data[pos:pos + machine_count])
    pos += machine_count

machine_busy = [[] for _ in range(machine_count)]
next_operation = [0] * job_count
job_finish = [0] * job_count

for job in order:
    op = next_operation[job]
    machine = machine_for[job][op]
    duration = duration_for[job][op]
    start = job_finish[job]
    while any(not (start + duration <= l or r <= start) for l, r in machine_busy[machine]):
        start += 1
    machine_busy[machine].append((start, start + duration))
    job_finish[job] = start + duration
    next_operation[job] += 1

print(max(job_finish))
