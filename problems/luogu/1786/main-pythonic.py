role_rank = {
    "BangZhu": 0,
    "FuBangZhu": 1,
    "HuFa": 2,
    "ZhangLao": 3,
    "TangZhu": 4,
    "JingYing": 5,
    "BangZhong": 6,
}

new_roles = (
    ["HuFa"] * 2
    + ["ZhangLao"] * 4
    + ["TangZhu"] * 7
    + ["JingYing"] * 25
)

n = int(input())
members = []

for index in range(n):
    name, role, contribution, level = input().split()
    members.append({
        "name": name,
        "role": role,
        "contribution": int(contribution),
        "level": int(level),
        "index": index,
    })

adjustable = [
    member for member in members
    if member["role"] != "BangZhu" and member["role"] != "FuBangZhu"
]
adjustable.sort(key=lambda member: (-member["contribution"], member["index"]))

for rank, member in enumerate(adjustable):
    if rank < len(new_roles):
        member["role"] = new_roles[rank]
    else:
        member["role"] = "BangZhong"

members.sort(key=lambda member: (
    role_rank[member["role"]],
    -member["level"],
    member["index"],
))

for member in members:
    print(member["name"], member["role"], member["level"])
