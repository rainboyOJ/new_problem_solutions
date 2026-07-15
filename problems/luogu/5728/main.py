n = int(input())
students = []

for _ in range(n):
    chinese, math, english = map(int, input().split())
    total = chinese + math + english
    students.append((chinese, math, english, total))

answer = 0

for i in range(n):
    for j in range(i + 1, n):
        ok = True
        for subject in range(3):
            if abs(students[i][subject] - students[j][subject]) > 5:
                ok = False
                break
        if ok and abs(students[i][3] - students[j][3]) <= 10:
            answer += 1

print(answer)
