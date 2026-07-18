k=int(input())
day=coin=total=0
while total<k:
    day+=1
    for _ in range(day):
        if total>=k: break
        coin+=day; total+=1
print(coin)
