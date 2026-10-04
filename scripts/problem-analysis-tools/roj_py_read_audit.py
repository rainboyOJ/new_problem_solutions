#!/usr/bin/env python3
"""审计 roj Python 题解的读入风格，并生成批量整改任务表。

按 `.agents/skills/python-oj-short/SKILL.md` 第一节「读入优先用 next() 顺序消费」判定：

- offset_index: 先 read().split() 再算偏移下标/切片，属于 skill 明列的反例，必须改。
- line_read:    用 input()/readline() 逐行取 token，固定 token 格式应改成 next()，建议改。
- whole_read:   sys.stdin.read() 整篇读取（保留空格换行），属允许的替代，需人工确认理由。
- line_iter:    for line in sys.stdin（按行处理），属允许的替代，需人工确认理由。
- unpack_ok:    先 split 但只整体解包/取首项，多数无需改，抽检确认。
- next_ok:      已用 iter() + next() 顺序消费。
- no_stdin:     不读标准输入。

用法：
  python3 scripts/problem-analysis-tools/roj_py_read_audit.py
  python3 scripts/problem-analysis-tools/roj_py_read_audit.py --json /tmp/roj_read_audit.json --md /tmp/roj_read_audit.md
  python3 scripts/problem-analysis-tools/roj_py_read_audit.py --tier offset_index --ids
  python3 scripts/problem-analysis-tools/roj_py_read_audit.py --check problems/roj/10002
"""

from __future__ import annotations

import argparse
import json
import pathlib
import re
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]

TIER_MUST_FIX = "offset_index"
TIER_SHOULD_FIX = "line_read"
TIER_REVIEW = ("whole_read", "line_iter", "unpack_ok")
TIER_OK = ("next_ok", "no_stdin")

SPLIT_CALL = re.compile(r"sys\.stdin(?:\.buffer)?\.read\(\)\s*\.\s*split\(")
WHOLE_READ = re.compile(r"sys\.stdin\.read\(\)(?!\s*\.)")
LINE_ITER = re.compile(r"for\s+\w+\s+in\s+sys\.stdin\b")
TOKEN_LINE_READ = re.compile(r"(?<!\.)\binput\(\)|sys\.stdin\.readline\(\)|sys\.stdin\.buffer\.readline\(\)")
NEXT_CALL = re.compile(r"\bnext\(")
ITER_CALL = re.compile(r"\biter\(")
ARITH_INDEX = re.compile(r"\b(\w+)\[([^\]\n]*[+\-*/][^\]\n]*)\]")
VAR_SLICE = re.compile(r"\b(\w+)\[([^\]\n]*:[^\]\n]*)\]")


def _strip_comments_and_strings(line: str) -> str:
    """粗略去掉行内注释，避免把注释里的示例当代码。"""
    out = []
    in_str = None
    prev = ""
    for ch in line:
        if in_str:
            out.append(ch)
            if ch == in_str and prev != "\\":
                in_str = None
        else:
            if ch in "\"'":
                in_str = ch
                out.append(ch)
            elif ch == "#":
                break
            else:
                out.append(ch)
        prev = ch if ch != "\\" or prev != "\\" else ""
    text = "".join(out)
    if "#" in text:
        text = text.split("#", 1)[0]
    return text


ASSIGN_NAMES = re.compile(r"^\s*([A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)*)\s*(?::\s*[^=]+?)?\s*=(?!=)")
SPLIT_THEN_INDEX = re.compile(r"split\([^)]*\)\s*\[")


def scan_read_style(code: str) -> dict:
    """判定读入风格，返回 tier / 证据行号 / 涉及的名字。

    判定规则（严格照 skill 第一节“拿不准时先写 next()”）：
    - offset_index: 把 read().split() 的结果存下来，再用带变量/算术的下标或切片取 token；
      这是 skill 明列的反例，必须改。
    - literal_index: 只用常量下标（data[0]、data[1]）按位置取数据；同样是人肉偏移，
      但改起来很短，归为建议改。
    - line_read: input()/readline() 逐行取 token，建议改。
    - whole_read / line_iter: skill 允许的替代，需在交付里写明理由。
    - unpack_ok: split 结果只做整体解包或直接进表达式，没有下标访问。
    - next_ok: 已用 iter() + next() 顺序消费。
    - no_stdin: 不读标准输入。
    """
    lines = [_strip_comments_and_strings(line) for line in code.splitlines()]
    split_kinds: dict[str, str] = {}   # 名字 -> raw（原始 token 字符串表）/ parsed（已转成数值/容器）
    inline_index_lines: list[int] = []
    has_split = False
    has_whole_read = False
    has_line_iter = False
    token_line_reads: list[int] = []
    for number, line in enumerate(lines, 1):
        if not line.strip():
            continue
        if SPLIT_CALL.search(line):
            has_split = True
            if SPLIT_THEN_INDEX.search(line):
                # 例：n = int(sys.stdin.buffer.read().split()[0])
                inline_index_lines.append(number)
                continue
            match = ASSIGN_NAMES.match(line)
            if match:
                parsed = bool(re.search(r"\b(map|tuple|list|set|int|float|sorted)\s*\(", line)) \
                    or bool(re.search(r"\[.*\bfor\b", line))
                for name in match.group(1).split(","):
                    split_kinds.setdefault(name.strip(), "parsed" if parsed else "raw")
        if WHOLE_READ.search(line):
            has_whole_read = True
        if LINE_ITER.search(line):
            has_line_iter = True
        if TOKEN_LINE_READ.search(line):
            token_line_reads.append(number)

    arithmetic_lines: list[int] = []   # 下标/切片里带变量或算术
    literal_lines: list[int] = []      # 只用常量下标
    parsed_literal_lines: list[int] = []   # 已转数值数组后用常量下标取位置量
    parsed_computed_lines: list[int] = []  # 已转数值数组后用变量下标访问
    for number, line in enumerate(lines, 1):
        if not line.strip():
            continue
        for match in re.finditer(r"\b([A-Za-z_]\w*)\[([^\]\n]*)\]", line):
            name, expr = match.group(1), match.group(2)
            kind = split_kinds.get(name)
            if kind is None:
                continue
            is_slice = ":" in expr
            computed = False
            for part in expr.split(":", 1):
                part = part.strip()
                if not part:
                    continue
                if re.search(r"[A-Za-z_]\w*", part) or re.search(r"[+\-*/%]\s*\d", part):
                    computed = True
            if kind == "parsed" and not is_slice:
                if computed:
                    parsed_computed_lines.append(number)
                else:
                    parsed_literal_lines.append(number)
                continue
            if computed:
                arithmetic_lines.append(number)
            else:
                literal_lines.append(number)

    # 已转数值的数组：既用常量下标取位置量、又用变量下标按位置取数据，是典型的“人肉偏移”
    parsed_mixed = bool(parsed_literal_lines) and bool(parsed_computed_lines)
    if parsed_mixed:
        arithmetic_lines.extend(parsed_computed_lines[:2])

    has_next = bool(NEXT_CALL.search(code)) and bool(ITER_CALL.search(code))
    arithmetic_lines = sorted(set(arithmetic_lines))
    literal_lines = sorted(set(literal_lines))
    parsed_literal_lines = sorted(set(parsed_literal_lines))
    inline_index_lines = sorted(set(inline_index_lines))
    token_lines = sorted(set(token_line_reads))

    if arithmetic_lines or inline_index_lines:
        tier = TIER_MUST_FIX
        reasons = [f"第 {n} 行：用变量/算术下标或切片取 token" for n in arithmetic_lines[:4]]
        reasons += [f"第 {n} 行：split() 后直接取下标" for n in inline_index_lines[:2]]
    elif literal_lines:
        tier = "literal_index"
        reasons = [f"第 {n} 行：用常量下标按位置取数据" for n in literal_lines[:4]]
    elif parsed_literal_lines:
        tier = "parsed_literal"
        reasons = [f"第 {n} 行：转成数值数组后用常量下标取位置量" for n in parsed_literal_lines[:4]]
    elif token_lines and not has_next:
        tier = TIER_SHOULD_FIX
        reasons = [f"第 {n} 行：input()/readline() 逐行取 token" for n in token_lines[:5]]
    elif has_whole_read:
        tier = "whole_read"
        reasons = ["sys.stdin.read() 整篇读取（属允许的替代，需写理由）"]
    elif has_line_iter:
        tier = "line_iter"
        reasons = ["for line in sys.stdin 按行处理（属允许的替代，需写理由）"]
    elif has_next:
        tier = "next_ok"
        reasons = []
    elif has_split:
        tier = "unpack_ok"
        reasons = ["split 结果只做整体解包或直接进表达式，无下标访问"]
    else:
        tier = "no_stdin"
        reasons = []

    return {
        "tier": tier,
        "reasons": reasons,
        "has_arith": bool(arithmetic_lines),
        "offset_lines": arithmetic_lines,
        "literal_lines": literal_lines,
        "parsed_literal_lines": parsed_literal_lines,
        "token_lines": token_lines,
        "has_split": has_split,
        "has_next": has_next,
    }


def first_statement_block(code: str) -> str:
    """去掉 shebang、文件头注释、import，返回剩下的开头，用来判断模块 docstring。"""
    body = re.sub(r"^#![^\n]*\n", "", code)
    body = re.sub(r"^(#[^\n]*\n)+", "", body)
    body = re.sub(r"^(import [^\n]*\n|from [^\n]*\n)+", "", body)
    return body.lstrip()


def signature_types(code: str) -> list[str]:
    """收集函数签名/返回值里出现的复合类型。"""
    found: list[str] = []
    for params, ret in re.findall(r"def \w+\((.*?)\)\s*->\s*([^:\n]+):", code, re.S):
        text = f"{params} {ret}"
        for match in re.finditer(r"\b(?:list|dict|tuple|set)\[[^\[\]]*(?:\[[^\]]*\][^\[\]]*)*\]", text):
            found.append(match.group(0))
        for match in re.finditer(r"\b(?:list|dict|tuple|set)\[[^\[\]]*\|[^\[\]]*\]", text):
            found.append(match.group(0))
    return found


SIMPLE_TYPE = re.compile(r"^(list|dict|set|tuple)\[(int|str|float|bool|bytes)\]$")


def type_alias_candidates(code: str) -> list[str]:
    """按 skill：嵌套容器或含 | 的复合类型在签名里出现 2 次以上才该起 type 别名。"""
    counts: dict[str, int] = {}
    for item in signature_types(code):
        counts[item] = counts.get(item, 0) + 1
    hits = []
    for item, count in counts.items():
        if count < 2 or SIMPLE_TYPE.match(item):
            continue
        if "[" in item[item.index("[") + 1 :] or "|" in item:
            hits.append(item)
    return sorted(set(hits))


def inline_code_copies_main(index_text: str, main_code: str) -> bool:
    """index.md 里是否有代码块基本复刻了 main.py。"""
    main_lines = {line.strip() for line in main_code.splitlines() if len(line.strip()) > 12}
    if len(main_lines) < 3:
        return False
    for block in re.findall(r"```python\n(.*?)\n```", index_text, re.S):
        block_lines = {line.strip() for line in block.splitlines() if len(line.strip()) > 12}
        if len(block_lines & main_lines) >= max(3, len(block_lines) // 2):
            return True
    return False


def display_path(path: pathlib.Path) -> str:
    """仓库内用相对路径，仓库外（如临时目录、测试夹具）用绝对路径。"""
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def audit_problem(problem_dir: pathlib.Path) -> dict | None:
    main = problem_dir / "main.py"
    if not main.exists():
        return None
    code = main.read_text(encoding="utf-8")
    record = scan_read_style(code)
    record["problem"] = f"{problem_dir.parent.name}/{problem_dir.name}"
    record["path"] = display_path(main)
    record["lines"] = len(code.splitlines())

    issues = []
    head = code[:900]
    if "create_at" not in head or "update_at" not in head:
        issues.append("missing_header")
    if first_statement_block(code).startswith(('"""', "'''")):
        issues.append("module_docstring")
    if not re.search(r"def \w+\([^)]*\)\s*->", code):
        issues.append("missing_annotation")
    alias = type_alias_candidates(code)
    if alias:
        issues.append("type_alias:" + ",".join(alias[:3]))

    index = problem_dir / "index.md"
    if index.exists() and inline_code_copies_main(index.read_text(encoding="utf-8"), code):
        issues.append("index_inline_copy")

    record["issues"] = issues
    return record


def collect(problems_root: pathlib.Path) -> list[dict]:
    records = []
    for problem_dir in sorted(problems_root.iterdir()):
        if not problem_dir.is_dir():
            continue
        record = audit_problem(problem_dir)
        if record:
            records.append(record)
    return records


def summarize(records: list[dict]) -> dict:
    tiers: dict[str, int] = {}
    for record in records:
        tiers[record["tier"]] = tiers.get(record["tier"], 0) + 1
    issues: dict[str, int] = {}
    for record in records:
        for issue in record["issues"]:
            key = issue.split(":")[0]
            issues[key] = issues.get(key, 0) + 1
    return {"total": len(records), "tiers": tiers, "issues": issues}


def format_report(records: list[dict], summary: dict) -> str:
    lines = ["# roj Python 读入风格审计", ""]
    lines.append(f"- 题目数（有 main.py）：{summary['total']}")
    lines.append("")
    lines.append("## 读入分级")
    lines.append("")
    lines.append("| tier | 数量 | 说明 |")
    lines.append("| --- | --- | --- |")
    notes = {
        "offset_index": "必须改：split 后用变量/算术下标或切片取 token",
        "literal_index": "建议改：用常量下标按位置取数据",
        "parsed_literal": "轻量改：转成数值数组后用常量下标取位置量",
        "line_read": "建议改：input()/readline() 逐行取 token",
        "whole_read": "允许的替代：整篇 read()，需确认理由",
        "line_iter": "允许的替代：for line in sys.stdin",
        "unpack_ok": "多数无需改：整体解包/直接进表达式",
        "next_ok": "已符合：iter() + next()",
        "no_stdin": "不读标准输入",
    }
    for tier, count in sorted(summary["tiers"].items(), key=lambda item: -item[1]):
        lines.append(f"| `{tier}` | {count} | {notes.get(tier, '')} |")
    lines.append("")
    lines.append("## 附带问题")
    lines.append("")
    for key, count in sorted(summary["issues"].items(), key=lambda item: -item[1]):
        lines.append(f"- {key}: {count}")
    lines.append("")
    for tier in (TIER_MUST_FIX, "literal_index", "parsed_literal", TIER_SHOULD_FIX, "whole_read", "line_iter"):
        subset = [r for r in records if r["tier"] == tier]
        if not subset:
            continue
        lines.append(f"## {tier}（{len(subset)}）")
        lines.append("")
        for record in subset:
            lines.append(f"- `{record['problem']}` {record['lines']} 行：{'；'.join(record['reasons'][:2]) or '-'}")
        lines.append("")
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description="审计 roj Python 题解读入风格")
    parser.add_argument("--problems", default="problems/roj", help="题目根目录")
    parser.add_argument("--json", dest="json_path", help="写出完整 JSON 记录")
    parser.add_argument("--md", dest="md_path", help="写出 Markdown 报告")
    parser.add_argument("--tier", action="append", help="只输出该 tier 的题号（可重复）")
    parser.add_argument("--ids", action="store_true", help="与 --tier 一起用，只打印题号")
    parser.add_argument("--check", help="只检查一个题目目录")
    args = parser.parse_args()

    if args.check:
        directory = pathlib.Path(args.check)
        if not directory.is_absolute():
            directory = REPO_ROOT / directory
        record = audit_problem(directory)
        if not record:
            print(f"没有 main.py：{directory}", file=sys.stderr)
            return 1
        print(json.dumps(record, ensure_ascii=False, indent=2))
        return 0

    root = pathlib.Path(args.problems)
    if not root.is_absolute():
        root = REPO_ROOT / root
    records = collect(root)
    summary = summarize(records)

    if args.tier:
        selected = [r for r in records if r["tier"] in args.tier]
        if args.ids:
            print("\n".join(r["problem"] for r in selected))
        else:
            print(json.dumps(selected, ensure_ascii=False, indent=2))
        return 0

    print(f"题目数 {summary['total']}")
    for tier, count in sorted(summary["tiers"].items(), key=lambda item: -item[1]):
        print(f"  {count:5d}  {tier}")
    print("附带问题：")
    for key, count in sorted(summary["issues"].items(), key=lambda item: -item[1]):
        print(f"  {count:5d}  {key}")

    if args.json_path:
        pathlib.Path(args.json_path).write_text(
            json.dumps({"summary": summary, "records": records}, ensure_ascii=False, indent=2) + "\n",
            encoding="utf-8",
        )
        print(f"写出 {args.json_path}")
    if args.md_path:
        pathlib.Path(args.md_path).write_text(format_report(records, summary) + "\n", encoding="utf-8")
        print(f"写出 {args.md_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
