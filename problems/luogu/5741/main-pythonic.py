def total(student):
    return student[1] + student[2] + student[3]

def is_close(left, right):
    for subject in range(1, 4):
        if abs(left[subject] - right[subject]) > 5:
            return False
    return abs(total(left) - total(right)) <= 10

n = int(input())
students = []

for _ in range(n):
    name, chinese, math, english = input().split()
    students.append((name, int(chinese), int(math), int(english)))

for i in range(n):
    for j in range(i + 1, n):
        if is_close(students[i], students[j]):
            print(students[i][0], students[j][0])
