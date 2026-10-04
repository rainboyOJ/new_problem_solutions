#!/usr/bin/env python3
"""roj Python 题解的样例抽取与回归验证工具。

用途（配合 roj_py_read_audit.py 的批量整改）：

- 从 `problem.md`（必要时 `index.md`）抽取题目的输入/输出样例；题面格式不统一，
  工具同时支持围栏块、缩进块和裸文本段落，以及 `【输入样例】`、`【样例 1 输入】`、
  `【输入样例#1】`、`## 样例 1 输入`、`### 【样例】`（单段内成对出现）等写法。
- 校准：用基线 commit 里的原版 `main.py` 跑样例，把「原版就能复现期望输出」的题
  标记为可信，后续只有可信样例才能作为整改后的判定依据。
- 回归：跑基线版与工作区当前版，要求两者输出逐字节一致（保持一致），
  可信样例还要求等于期望输出（保证正确）。

用法：
  # 1) 基线校准（写 .tmp/roj_py_sample_calibration.json）
  python3 scripts/problem-analysis-tools/roj_py_sample_regress.py --calibrate --jobs 8

  # 2) 单题回归（基线 vs 工作区）
  python3 scripts/problem-analysis-tools/roj_py_sample_regress.py --problem roj/10002

  # 3) 全部改动过的题回归（有 DIFF 时退出码 1）
  python3 scripts/problem-analysis-tools/roj_py_sample_regress.py --all-changed
"""

from __future__ import annotations

import argparse
import concurrent.futures
import json
import pathlib
import re
import subprocess
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
DEFAULT_CALIBRATION = REPO_ROOT / ".tmp" / "roj_py_sample_calibration.json"

FENCE = re.compile(r"```[a-zA-Z0-9]*\n(.*?)\n```", re.DOTALL)
DECOR = str.maketrans({"#": " ", "*": " ", "【": " ", "】": " ", "`": " ", "：": " ", ":": " "})
IN_WORDS = re.compile(r"(输入样例|样例\s*\d*\s*输入|sample\s*input|^input)", re.I)
OUT_WORDS = re.compile(r"(输出样例|样例\s*\d*\s*输出|sample\s*output|^output)", re.I)
NO_SAMPLE = re.compile(r"见(下发|附件)|不提供|无样例|见文件|\(无\)|（无）")
STOP_HEADING = re.compile(r"^(数据范围|提示|说明|样例说明|题目背景|输入格式|输出格式|注意)")


def clean_line(line: str) -> str:
    return line.translate(DECOR).strip()


def marker_kind(text: str) -> str | None:
    if "样例" not in text and not re.search(r"sample", text, re.I):
        return None
    # “输入输出样例”“输入/输出样例#3”是段落标题，不是某一边的样例正文
    if re.search(r"输入\s*/?\s*输出\s*样例", text) or re.search(r"样例\s*输入\s*/?\s*输出", text):
        return "both"
    has_in = bool(IN_WORDS.search(text))
    has_out = bool(OUT_WORDS.search(text))
    if has_in and has_out:
        return "both"
    if has_in:
        return "in"
    if has_out:
        return "out"
    return "plain"


def payload_after(lines: list[str], start: int) -> tuple[str, int]:
    """取标记行之后的样例正文：围栏块 > 缩进块 > 第一段非空文本。"""
    rest = lines[start:]
    joined = "\n".join(rest)
    match = FENCE.search(joined)
    if match:
        return match.group(1).rstrip("\n"), start + joined[: match.start()].count("\n") + 1

    body: list[str] = []
    for index, line in enumerate(rest):
        stripped = line.strip()
        if stripped.startswith("```"):
            break
        if stripped and set(stripped) <= {"-", "=", "—"}:
            continue                      # markdown 分隔线 / setext 下划线
        cleaned = clean_line(line)
        if not cleaned and not body:
            continue
        if not cleaned and body:
            break
        if STOP_HEADING.match(cleaned) or "样例" in cleaned or "数据范围" in cleaned:
            break
        if cleaned in ("题面", "题目描述", "输入格式", "输出格式"):
            break
        body.append(line[4:] if line.startswith("    ") else line)
    text = "\n".join(body).strip("\n")
    return text, start + len(body) + 1


def extract_samples(path: pathlib.Path) -> list[tuple[str, str]]:
    """返回 [(输入, 期望输出)]；抽不到就返回空列表。"""
    if not path.exists():
        return []
    lines = path.read_text(encoding="utf-8").splitlines()
    ins: list[str] = []
    outs: list[str] = []
    pending_plain: list[str] = []

    for index, line in enumerate(lines):
        cleaned = clean_line(line)
        if not cleaned:
            continue
        kind = marker_kind(cleaned)
        if kind is None:
            continue
        body, _ = payload_after(lines, index + 1)
        if not body.strip():
            continue
        if kind == "in":
            ins.append(body)
        elif kind == "out":
            outs.append(body)
        elif kind == "plain":
            pending_plain.append(body)
        else:
            continue  # 【输入/输出样例#3】这类由文件提供的样例跳过

    if pending_plain and not ins and not outs:
        for order, body in enumerate(pending_plain):
            (ins if order % 2 == 0 else outs).append(body)

    pairs = list(zip(ins, outs))
    return [
        (unescape_markdown(i), unescape_markdown(o))
        for i, o in pairs
        if i.strip() and o.strip() and not NO_SAMPLE.search(o)
    ]


MD_ESCAPE = re.compile(r"\\([\\`*_{}\[\]()#+\-.!<>|~])")
HTML_ENTITIES = {"&lt;": "<", "&gt;": ">", "&amp;": "&", "&quot;": '"', "&#39;": "'", "&nbsp;": " "}


def unescape_markdown(text: str) -> str:
    """样例块里常见 markdown 转义（\\*、\\-、&lt;），不还原会直接污染程序输入。"""
    text = MD_ESCAPE.sub(r"\1", text)
    for entity, char in HTML_ENTITIES.items():
        text = text.replace(entity, char)
    return text


def normalize_output(text: str) -> str:
    lines = [line.rstrip() for line in text.replace("\r\n", "\n").splitlines()]
    while lines and lines[-1] == "":
        lines.pop()
    return "\n".join(lines)


def run_code(source: str, stdin_text: str, timeout: float) -> tuple[str, str]:
    result = subprocess.run(
        [sys.executable, "-c", source],
        input=stdin_text,
        capture_output=True,
        text=True,
        timeout=timeout,
    )
    return result.stdout, result.stderr


def problem_path(problem: str) -> pathlib.Path:
    oj, pid = problem.split("/", 1)
    return REPO_ROOT / "problems" / oj / pid


def base_source(problem: str, base: str) -> str:
    relative = problem_path(problem).relative_to(REPO_ROOT) / "main.py"
    result = subprocess.run(
        ["git", "show", f"{base}:{relative}"],
        cwd=REPO_ROOT,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        raise FileNotFoundError(f"{base}:{relative} 不存在")
    return result.stdout


def samples_for_problem(problem: str) -> tuple[list[tuple[str, str]], str]:
    directory = problem_path(problem)
    for name in ("problem.md", "index.md"):
        pairs = extract_samples(directory / name)
        if pairs:
            return pairs, name
    return [], ""


def judge(pairs: list[tuple[str, str]], source: str, timeout: float) -> tuple[str, str]:
    """跑 source，返回 (状态, 说明)。状态：PASS / SAMPLE_MISMATCH / RUNTIME_ERROR。"""
    for index, (stdin_text, expected) in enumerate(pairs, 1):
        try:
            stdout, stderr = run_code(source, stdin_text, timeout)
        except subprocess.TimeoutExpired:
            return "RUNTIME_ERROR", f"样例 {index} 超时（>{timeout}s）"
        except Exception as error:  # noqa: BLE001
            return "RUNTIME_ERROR", f"样例 {index} 运行异常：{type(error).__name__}"
        if normalize_output(stdout) != normalize_output(expected):
            return (
                "SAMPLE_MISMATCH",
                f"样例 {index} 期望 {normalize_output(expected)[:40]!r} 实际 {normalize_output(stdout)[:40]!r}",
            )
    return "PASS", f"{len(pairs)} 组样例通过"


def calibrate_problem(problem: str, base: str, timeout: float) -> dict:
    pairs, source_file = samples_for_problem(problem)
    record = {"problem": problem, "samples": len(pairs), "sample_file": source_file}
    if not pairs:
        record.update(status="NO_SAMPLE", detail="题面里抽不到可配对的样例")
        return record
    try:
        source = base_source(problem, base)
    except FileNotFoundError as error:
        record.update(status="NO_BASE_FILE", detail=str(error))
        return record
    status, detail = judge(pairs, source, timeout)
    record.update(status=status, detail=detail)
    return record


def find_problems(all_problems: bool = False) -> list[str]:
    problems = []
    for path in sorted((REPO_ROOT / "problems").glob("*/*/main.py")):
        if all_problems or path.parent.parent.name == "roj":
            problems.append(f"{path.parent.parent.name}/{path.parent.name}")
    return problems


def changed_problems(base: str) -> list[str]:
    result = subprocess.run(
        ["git", "diff", "--name-only", base, "--", "problems"],
        cwd=REPO_ROOT,
        capture_output=True,
        text=True,
        check=True,
    )
    problems = set()
    for line in result.stdout.splitlines():
        parts = line.split("/")
        if len(parts) >= 4 and parts[0] == "problems":
            problems.add(f"{parts[1]}/{parts[2]}")
    return sorted(problems)


def load_calibration(path: pathlib.Path) -> dict:
    if not path.exists():
        return {}
    data = json.loads(path.read_text(encoding="utf-8"))
    return {record["problem"]: record for record in data.get("records", data)}


def main() -> int:
    parser = argparse.ArgumentParser(description="roj Python 题解样例抽取与回归验证")
    parser.add_argument("--base", default="HEAD", help="基线 commit（默认 HEAD）")
    parser.add_argument("--problem", action="append", help="只处理这些题（roj/10002）")
    parser.add_argument("--all-changed", action="store_true", help="处理相对基线改动过的题")
    parser.add_argument("--calibrate", action="store_true", help="用基线版跑样例做校准")
    parser.add_argument("--all-problems", action="store_true", help="校准所有 oj（默认只 roj）")
    parser.add_argument("--jobs", type=int, default=8, help="并发进程数")
    parser.add_argument("--timeout", type=float, default=8.0, help="单个样例运行超时（秒）")
    parser.add_argument("--calibration-file", default=str(DEFAULT_CALIBRATION))
    parser.add_argument("--json", dest="json_path", help="写出本次结果 JSON")
    parser.add_argument("--quiet", action="store_true", help="只打印汇总")
    args = parser.parse_args()

    calibration_path = pathlib.Path(args.calibration_file)

    if args.calibrate:
        problems = args.problem or find_problems(args.all_problems)
        calibration_path.parent.mkdir(parents=True, exist_ok=True)
        records: list[dict] = []
        with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
            futures = {pool.submit(calibrate_problem, p, args.base, args.timeout): p for p in problems}
            for count, future in enumerate(concurrent.futures.as_completed(futures), 1):
                records.append(future.result())
                if count % 50 == 0:
                    print(f"  校准进度 {count}/{len(problems)}", file=sys.stderr)
        records.sort(key=lambda item: item["problem"])
        calibration_path.write_text(
            json.dumps({"base": args.base, "records": records}, ensure_ascii=False, indent=2) + "\n",
            encoding="utf-8",
        )
        summary: dict[str, int] = {}
        for record in records:
            summary[record["status"]] = summary.get(record["status"], 0) + 1
        print(f"校准完成：{len(records)} 题 -> {calibration_path}")
        for status, count in sorted(summary.items(), key=lambda item: -item[1]):
            print(f"  {count:5d}  {status}")
        return 0

    if args.problem:
        problems = args.problem
    elif args.all_changed:
        problems = changed_problems(args.base)
    else:
        parser.error("需要 --problem、--all-changed 或 --calibrate")

    calibration = load_calibration(calibration_path)
    if not calibration:
        print(f"提示：还没有校准文件 {calibration_path}，将只做基线一致性比较。", file=sys.stderr)

    results = []
    failed = 0
    for problem in problems:
        pairs, sample_file = samples_for_problem(problem)
        record = {"problem": problem, "samples": len(pairs), "sample_file": sample_file}
        trusted = calibration.get(problem, {}).get("status") == "PASS"
        record["samples_trusted"] = trusted
        if not pairs:
            record.update(status="NO_SAMPLE", detail="题面里抽不到可配对的样例")
            results.append(record)
            if not args.quiet:
                print(f"{problem}\tNO_SAMPLE\t无可用样例")
            continue
        try:
            original = base_source(problem, args.base)
        except FileNotFoundError:
            record.update(status="NO_BASE_FILE", detail="基线里没有 main.py")
            results.append(record)
            print(f"{problem}\tNO_BASE_FILE")
            continue
        current = (problem_path(problem) / "main.py").read_text(encoding="utf-8")

        status = "PASS"
        detail = ""
        for index, (stdin_text, expected) in enumerate(pairs, 1):
            try:
                base_out, _ = run_code(original, stdin_text, args.timeout)
                new_out, _ = run_code(current, stdin_text, args.timeout)
            except subprocess.TimeoutExpired:
                status, detail = "RUNTIME_ERROR", f"样例 {index} 超时"
                break
            if normalize_output(base_out) != normalize_output(new_out):
                status = "DIFF"
                detail = (
                    f"样例 {index} 基线 {normalize_output(base_out)[:40]!r} "
                    f"工作区 {normalize_output(new_out)[:40]!r}"
                )
                break
            if trusted and normalize_output(expected) != normalize_output(new_out):
                status = "WRONG"
                detail = (
                    f"样例 {index} 期望 {normalize_output(expected)[:40]!r} "
                    f"实际 {normalize_output(new_out)[:40]!r}"
                )
                break
        if status == "PASS":
            detail = f"{len(pairs)} 组样例与基线一致" + ("，且等于期望输出" if trusted else "（样例未校准，只比一致性）")
        record.update(status=status, detail=detail)
        results.append(record)
        if status != "PASS":
            failed += 1
        if not args.quiet:
            print(f"{problem}\t{status}\t{detail}")

    print(f"\n汇总：{len(results)} 题，失败 {failed} 题")
    if args.json_path:
        pathlib.Path(args.json_path).write_text(
            json.dumps({"base": args.base, "results": results}, ensure_ascii=False, indent=2) + "\n",
            encoding="utf-8",
        )
        print(f"写出 {args.json_path}")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
