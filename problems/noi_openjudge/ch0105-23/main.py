stock = int(input())
patient_count = int(input())
requests = map(int, input().split())
rejected = 0

for request in requests:
    if request > stock:
        rejected += 1
    else:
        stock -= request

print(rejected)
