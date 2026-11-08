# 0005 Codeforces 题目的 difficulty 改用官方 rating 数字

## 状态

已采纳（2026-11-06）

## 背景

`problems/**/index.md` 的 `difficulty` 原本是全库统一的 8 档洛谷中文档位（入门 / 普及- / 普及 / 普及+/提高- / 提高 / 提高+/省选- / 省选/NOI- / NOI/NOI+/CTS），唯一来源是 `lib/difficulty.json`。

但 Codeforces 的官方难度本身就是精确数字 rating（800 / 1200 / 1700 / 2400 / 3500…），套洛谷 8 档会把信息严重压平。存量 22 道 CF 题迁移时的对照就暴露了这一点：

| 题号 | 旧洛谷档位 | 官方 rating |
| --- | --- | --- |
| `19D` | 提高+/省选- | **2800** |
| `1120D` | 提高+/省选- | **2500** |
| `1681D` | 普及+/提高- | **1700** |
| `2183A` | 普及- | **800** |

同一档「提高+/省选-」既可能是 2000 也可能是 2800，跨 OJ 混排和 CF 内部排序都失真。`problem-sets/*.md` 生成器其实早已在用官方 `problemset.problems` 显示 rating，数据本来就在。

## 决策

**`difficulty` 采用双标准，按 OJ 分工：**

- `oj: codeforces` → 写官方 rating 数字，YAML 里写成**带引号字符串**（`difficulty: "1500"`）。
  裸数字会被 `gray-matter` 的 js-yaml 解析成 number，破坏「difficulty 是字符串」的既有约定（`tests/fastify-app.test.js` 有断言）。
- 其它 OJ → 保持原来的中文档位枚举，不动。

### 值域

`difficulty` 合法值 = 8 档中文枚举 ∪ 任意正整数（字符串）。所以 CF 题允许 `数字 / 中文档 / 未知` 三者并存：拿不到官方 rating 时（未 rated 的场、Gym、刚出的题）保留旧值，不丢已有信息。

### 跨 OJ 排序

`lib/difficulty.json` 每个中文档位新增 `rating` 字段，作为该档位的**代表 rating**：

| 档位 | 代表 rating |
| --- | --- |
| 入门 | 800 |
| 普及- | 1000 |
| 普及 | 1200 |
| 普及+/提高- | 1500 |
| 提高 | 1800 |
| 提高+/省选- | 2000 |
| 省选/NOI- | 2400 |
| NOI/NOI+/CTS | 2800 |

`sortProblemsForApi`、首页排序、`relation_batch` 的难度序都改成按数值比较：数字直接用，中文档查表换算，未知排最后（`difficultyRating()` / `difficulty_tier()`）。

**这张表是主观约定**，两套难度体系本来不等价；它的作用只是给混排提供一致的比较基准，不代表「洛谷提高 ≡ CF 1800」。

### 徽章上色

任意数字按「最接近代表值」归到 8 档之一，再用该档 slug 上色（`difficultySlug()`）：900→入门、1700→提高、2300→省选/NOI-、3200→NOI。徽章文本直接显示数字本身，不另加 rating 标签。上色与排序共用同一套 8 档，避免「排序位置」和「颜色」互相矛盾。

## 后果

- `fetchers/codeforces.py` 抓题后自动调官方 `problemset.problems` 反查 rating 写入 `difficulty`，建题即带，不再依赖人工估档。
- `label_difficulty.py`（LLM 按 8 档打分）跳过 CF 题与已是纯数字的题，避免用估算覆盖官方真值。
- `check_problem.py` 值域放宽为「中文枚举 或 正整数」；`0`、前导零、旧错档名（如 `提高+`）仍告警。
- 一次性迁移脚本 `scripts/migrate-codeforces-difficulty-to-rating.py`：有 rating 写数字、无 rating 保留旧值，默认 dry-run 打印新旧对照表。
- 顺手修掉一个既有 bug：`relation_batch/tag-config.json` 的 `difficulty_order` 末尾写的是「未知」而 `lib/difficulty.json` 是 `NOI/NOI+/CTS`，导致 `pre_batch.py` 一启动就 `SystemExit`；它的 selftest fixture 也还停留在旧档名，之前根本没跑到检查逻辑。
