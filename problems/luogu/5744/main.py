def train(student):
    name, age, score = student
    new_age = age + 1
    new_score = min(600, int(score * 1.2))
    return name, new_age, new_score


n = int(input())

for _ in range(n):
    name, age, score = input().split()
    trained = train((name, int(age), int(score)))
    print(trained[0], trained[1], trained[2])
