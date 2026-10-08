
---

## T4. `pcs2_queue.py claim <pid>` **不接受 pid** —— 按 `--count` 批量抓

**现象**（2026-10-08）：父会话想把在飞的 4 道标为 claimed：

```bash
for p in 5020 5021 5022 5023; do
  python3 .../pcs2_queue.py claim $p --queue .tmp/roj283-queue.jsonl --worker batch6
done
```

结果**标了 40 道**（`D:9 C1:24 C2:5 A:2`），而不是 4 道。

**根因**：`cmd_claim` 的实现是

```python
picked = pool[: args.count]      # ← pool 由 cohort/status 筛选得到，与位置参数无关
```

`claim` 的**位置参数 `pid` 被忽略**，真正起作用的是 `--count`（默认 10）。
我循环调 4 次 ⇒ 每次抓 10 道 ⇒ **4 × 10 = 40**。

**修复方式**：直接用脚本改 JSONL（精确、可逆），不要用 `claim` 做单题标记：

```python
KEEP = {'5020','5021','5022','5023'}
for r in rows:
    if r['pid'] in KEEP: r['status']='claimed'; r['worker']='batch6'
    elif r['status']=='claimed': r['status']='pending'; r['worker']=None
```

**教训（可推广）**：**循环调用一个工具之前，先确认它的参数语义**。
「参数名像 pid」不等于「支持指定 pid」。
本次能无损还原，是因为 `claimed` 之前的旧状态恰好都是 `pending` ——
如果我把 `done` 的题目也误改了，就没有旧状态可还原了。

**附带**：`pcs2_queue.py` 的默认队列是 `.tmp/pcs2-queue.jsonl`，
而 `accept.py` 用的是 `.tmp/roj283-queue.jsonl` —— **必须显式传 `--queue`**，
否则 `stats` 会报 `total: 0`（看不见任何待办）。
