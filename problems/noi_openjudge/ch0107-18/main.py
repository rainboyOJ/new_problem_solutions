first = input().strip()
second = input().strip()

if first in second:
    print(f"{first} is substring of {second}")
elif second in first:
    print(f"{second} is substring of {first}")
else:
    print("No substring")
