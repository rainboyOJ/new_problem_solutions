n = int(input())
students = []
for sid in range(1, n + 1):
    c, m, e = map(int, input().split())
    students.append((- (c + m + e), -c, sid, c + m + e))
for _, _, sid, total in sorted(students)[:5]:
    print(sid, total)
