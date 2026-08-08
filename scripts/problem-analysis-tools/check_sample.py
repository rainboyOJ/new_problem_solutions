#!/usr/bin/env python3
"""Check problem samples and local data against a solution.

这个脚本服务于手写题解时的快速自测：
1. 找到题目目录下的样例/本地数据。
2. 编译或定位待测程序。
3. 带时间/内存限制运行每组数据。
4. 有答案就 diff，没有答案就打印程序输出。

Examples:
  check_sample.py
  check_sample.py problems/luogu/P1001
  check_sample.py problems/luogu/P1001 --source main.cpp
"""

from __future__ import annotations

import argparse
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys
import tempfile
import time


REPO_ROOT = Path(__file__).resolve().parents[2]


class SampleCase:
    def __init__(self, name: str, input_path: Path, answer_path: Path | None) -> None:
        self.name = name
        self.input_path = input_path
        self.answer_path = answer_path


def rel(path: Path) -> str:
    """尽量把路径显示成相对仓库根目录，输出更短、更稳定。"""
    try:
        return str(path.resolve().relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def shell_join(cmd: list[str]) -> str:
    return " ".join(shlex.quote(item) for item in cmd)


def compile_cpp(src: Path) -> Path:
    """编译 C++ 源文件，并复用未过期的临时可执行文件。"""
    build_dir = Path(tempfile.gettempdir()) / "problem-analysis-sample"
    build_dir.mkdir(parents=True, exist_ok=True)
    digest = hashlib.sha1(str(src.resolve()).encode()).hexdigest()[:12]
    out = build_dir / f"{src.stem}-{digest}"
    if out.exists() and out.stat().st_mtime >= src.stat().st_mtime:
        return out
    cmd = ["g++", "-std=c++17", "-O2", str(src), "-o", str(out)]
    print("编译：", shell_join(cmd))
    subprocess.run(cmd, check=True)
    return out


def command_for(source: Path) -> list[str]:
    """把源文件转换为实际运行命令；编译只发生在这里，不进入内存限制。"""
    if not source.exists():
        raise FileNotFoundError(source)
    if source.suffix == ".cpp":
        return [str(compile_cpp(source))]
    if source.suffix == ".py":
        return [sys.executable, str(source)]
    if os.access(source, os.X_OK):
        return [str(source)]
    raise ValueError(f"不支持的源文件或不可执行文件：{source}")


def resolve_source(problem_dir: Path, source_arg: str | None) -> Path:
    """确定待测程序，默认优先使用 main.cpp，兼容旧题解里的 1.cpp。"""
    if source_arg:
        source = Path(source_arg)
        return source if source.is_absolute() else problem_dir / source

    for name in ["main.cpp", "1.cpp"]:
        candidate = problem_dir / name
        if candidate.exists():
            return candidate

    raise FileNotFoundError("未找到 main.cpp 或 1.cpp，请用 --source 指定。")


def natural_key(path: Path) -> tuple[int, str]:
    """让 in, in1, in2 按自然数字顺序排列，而不是字典序。"""
    match = re.fullmatch(r"in(\d*)", path.name)
    if not match:
        return (10**9, path.name)
    suffix = match.group(1)
    return (int(suffix) if suffix else 0, path.name)


def answer_for_root_input(input_path: Path) -> Path | None:
    match = re.fullmatch(r"in(\d*)", input_path.name)
    if not match:
        return None
    suffix = match.group(1)
    answer = input_path.with_name(f"out{suffix}")
    return answer if answer.exists() else None


def answer_for_data_input(input_path: Path) -> Path | None:
    for ext in [".out", ".ans"]:
        answer = input_path.with_suffix(ext)
        if answer.exists():
            return answer
    return None


def discover_cases(problem_dir: Path) -> list[SampleCase]:
    """收集题目数据：根目录 in/out 系列 + data/*.in 系列。"""
    cases: list[SampleCase] = []
    seen: set[Path] = set()

    # 兼容老 rbook 题目常见格式：in/out, in1/out1, in2/out2。
    root_inputs = sorted(
        [p for p in problem_dir.iterdir() if p.is_file() and re.fullmatch(r"in(\d*)", p.name)],
        key=natural_key,
    )
    for input_path in root_inputs:
        seen.add(input_path.resolve())
        cases.append(SampleCase(input_path.name, input_path, answer_for_root_input(input_path)))

    data_dir = problem_dir / "data"
    if data_dir.is_dir():
        # 新工具生成的数据放在 data/ 下，答案可以是同名 .out 或 .ans。
        for input_path in sorted(data_dir.glob("*.in")):
            if input_path.resolve() in seen:
                continue
            cases.append(
                SampleCase(
                    f"data/{input_path.name}",
                    input_path,
                    answer_for_data_input(input_path),
                )
            )

    return cases


def normalize_output(data: str) -> str:
    """评测式比较：忽略行尾空白和末尾多余空行。"""
    lines = [line.rstrip() for line in data.replace("\r\n", "\n").splitlines()]
    while lines and lines[-1] == "":
        lines.pop()
    return "\n".join(lines) + ("\n" if lines else "")


def run_limited_command(
    cmd: list[str],
    input_data: str,
    timeout: float,
    memory_mb: int | None,
    memory_guard_mb: int,
) -> tuple[int, str, str, float, float | None, bool]:
    # 用一个独立 Python wrapper 运行用户程序，原因有两个：
    # 1. resource.getrusage(RUSAGE_CHILDREN) 能拿到目标程序的 peak RSS。
    # 2. resource.setrlimit 只通过 preexec_fn 作用到目标程序，不限制本脚本自身。
    wrapper = r'''
import json
import os
import resource
import subprocess
import sys
import time

cmd = json.loads(os.environ["CHECK_SAMPLE_CMD"])
timeout = float(os.environ["CHECK_SAMPLE_TIMEOUT"])
hard_bytes = int(os.environ.get("CHECK_SAMPLE_HARD_BYTES", "0"))
meta_path = os.environ["CHECK_SAMPLE_META"]
input_data = sys.stdin.read()

def limit_memory():
    if hard_bytes > 0:
        # RLIMIT_AS 限制虚拟地址空间。这里使用 memory_mb + guard，
        # 最终判定仍按用户传入的 memory_mb 与 peak RSS 比较。
        resource.setrlimit(resource.RLIMIT_AS, (hard_bytes, hard_bytes))

start = time.time()
timed_out = False
returncode = 0
stdout = ""
stderr = ""

try:
    result = subprocess.run(
        cmd,
        input=input_data,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        timeout=timeout,
        preexec_fn=limit_memory if hard_bytes > 0 else None,
    )
    returncode = result.returncode
    stdout = result.stdout
    stderr = result.stderr
except subprocess.TimeoutExpired as exc:
    timed_out = True
    returncode = 124
    stdout = exc.stdout or ""
    stderr = exc.stderr or ""

elapsed = time.time() - start
ru = resource.getrusage(resource.RUSAGE_CHILDREN)
maxrss = ru.ru_maxrss
if sys.platform == "darwin":
    # macOS 返回字节，Linux 返回 KB；统一换算成 KB 写入元数据。
    maxrss_kb = maxrss / 1024
else:
    maxrss_kb = maxrss

# wrapper 通过临时 JSON 文件把运行元数据传回父进程；
# stdout/stderr 仍走标准管道，保持和普通 subprocess.run 一样的语义。
with open(meta_path, "w", encoding="utf-8") as f:
    json.dump(
        {
            "returncode": returncode,
            "elapsed": elapsed,
            "maxrss_kb": maxrss_kb,
            "timed_out": timed_out,
        },
        f,
    )

sys.stdout.write(stdout)
sys.stderr.write(stderr)
raise SystemExit(returncode)
'''
    hard_bytes = 0
    if memory_mb is not None:
        # 硬限制比判定线略高，模拟常见 OJ 的“先允许跑完，再按峰值判定”。
        hard_bytes = (memory_mb + memory_guard_mb) * 1024 * 1024

    with tempfile.NamedTemporaryFile(delete=False) as meta_file:
        meta_path = Path(meta_file.name)

    env = os.environ.copy()
    env.update(
        {
            "CHECK_SAMPLE_CMD": json.dumps(cmd),
            "CHECK_SAMPLE_TIMEOUT": str(timeout),
            "CHECK_SAMPLE_HARD_BYTES": str(hard_bytes),
            "CHECK_SAMPLE_META": str(meta_path),
        }
    )

    start = time.time()
    try:
        wrapper_result = subprocess.run(
            [sys.executable, "-c", wrapper],
            input=input_data,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=timeout + 2,
            env=env,
        )
    except subprocess.TimeoutExpired as exc:
        # 这是 wrapper 自身的兜底超时；正常超时会由 wrapper 内部记录。
        return (124, exc.stdout or "", exc.stderr or "", time.time() - start, None, True)

    try:
        meta = json.loads(meta_path.read_text(encoding="utf-8"))
    except (FileNotFoundError, json.JSONDecodeError):
        # 如果目标程序异常导致 wrapper 没写元数据，仍尽量保留输出并给出结果。
        meta = {
            "returncode": wrapper_result.returncode,
            "elapsed": time.time() - start,
            "maxrss_kb": None,
            "timed_out": False,
        }
    finally:
        try:
            meta_path.unlink()
        except FileNotFoundError:
            pass

    peak_mb = None
    if meta.get("maxrss_kb") is not None:
        peak_mb = float(meta["maxrss_kb"]) / 1024

    return (
        int(meta.get("returncode", wrapper_result.returncode)),
        wrapper_result.stdout,
        wrapper_result.stderr,
        float(meta.get("elapsed", time.time() - start)),
        peak_mb,
        bool(meta.get("timed_out", False)),
    )


def print_diff(expected: str, actual: str) -> None:
    diff = difflib.unified_diff(
        expected.splitlines(keepends=True),
        actual.splitlines(keepends=True),
        fromfile="expected",
        tofile="actual",
    )
    print("".join(diff), end="")


def run_case(
    cmd: list[str],
    case: SampleCase,
    timeout: float,
    memory_mb: int | None,
    memory_guard_mb: int,
) -> tuple[str, float, str, str, float | None]:
    """运行单个样例，并按约定优先级给出状态。"""
    input_data = case.input_path.read_text(encoding="utf-8")
    returncode, stdout, stderr, elapsed, peak_mb, timed_out = run_limited_command(
        cmd,
        input_data,
        timeout,
        memory_mb,
        memory_guard_mb,
    )

    if timed_out:
        return ("TIMEOUT", elapsed, stdout, stderr, peak_mb)

    # 内存超过判定线时，即使输出正确也标记 MEMORY_LIMIT。
    memory_exceeded = memory_mb is not None and peak_mb is not None and peak_mb > memory_mb
    if memory_exceeded:
        return ("MEMORY_LIMIT", elapsed, stdout, stderr, peak_mb)

    if returncode != 0:
        return ("RUNTIME_ERROR", elapsed, stdout, stderr, peak_mb)

    if case.answer_path is None:
        return ("NO_ANSWER", elapsed, stdout, stderr, peak_mb)

    expected = normalize_output(case.answer_path.read_text(encoding="utf-8"))
    actual = normalize_output(stdout)
    if expected == actual:
        return ("PASS", elapsed, stdout, stderr, peak_mb)
    return ("FAIL", elapsed, stdout, expected, peak_mb)


def run_samples(
    problem_dir: Path,
    source_arg: str | None,
    timeout: float,
    memory_mb: int | None,
    memory_guard_mb: int,
) -> int:
    """主流程：准备程序、发现数据、逐个运行并汇总结果。"""
    if not problem_dir.exists() or not problem_dir.is_dir():
        print(f"题目目录不存在：{rel(problem_dir)}", file=sys.stderr)
        return 2

    try:
        source = resolve_source(problem_dir, source_arg)
        cmd = command_for(source)
    except (FileNotFoundError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"准备失败：{exc}", file=sys.stderr)
        return 2

    cases = discover_cases(problem_dir)
    if not cases:
        print(f"未找到样例数据：{rel(problem_dir)}", file=sys.stderr)
        print("支持：in/out, in1/out1, data/*.in + .out/.ans", file=sys.stderr)
        return 2

    print(f"题目目录：{rel(problem_dir)}")
    print(f"测试程序：{rel(source)}")
    print(f"运行命令：{shell_join(cmd)}")
    print(f"时间限制：{timeout:.3f}s")
    if memory_mb is not None:
        print(f"内存限制：{memory_mb}MB (hard: {memory_mb + memory_guard_mb}MB)")
    else:
        print("内存限制：未设置")
    print(f"样例数量：{len(cases)}")
    print("-" * 60)

    passed = 0
    failed = 0
    no_answer = 0

    for idx, case in enumerate(cases, 1):
        answer_text = rel(case.answer_path) if case.answer_path else "无答案"
        print(f"[{idx}/{len(cases)}] {case.name}")
        print(f"  input : {rel(case.input_path)}")
        print(f"  answer: {answer_text}")

        status, elapsed, stdout, extra, peak_mb = run_case(
            cmd,
            case,
            timeout,
            memory_mb,
            memory_guard_mb,
        )
        peak_text = f", peak={peak_mb:.1f}MB" if peak_mb is not None else ""

        if status == "PASS":
            passed += 1
            print(f"  result: PASS ({elapsed:.3f}s{peak_text})")
        elif status == "NO_ANSWER":
            no_answer += 1
            print(f"  result: NO_ANSWER ({elapsed:.3f}s{peak_text})")
            if stdout:
                print("  output:")
                print(stdout.rstrip())
        elif status == "TIMEOUT":
            failed += 1
            print(f"  result: TIMEOUT > {timeout:.3f}s{peak_text}")
        elif status == "MEMORY_LIMIT":
            failed += 1
            assert memory_mb is not None
            print(
                "  result: "
                f"MEMORY_LIMIT (peak: {peak_mb:.1f}MB > limit: {memory_mb}MB, "
                f"hard: {memory_mb + memory_guard_mb}MB)"
            )
        elif status == "RUNTIME_ERROR":
            failed += 1
            print(f"  result: RUNTIME_ERROR ({elapsed:.3f}s{peak_text})")
            if extra:
                print("  stderr:")
                print(extra.rstrip())
        else:
            failed += 1
            print(f"  result: FAIL ({elapsed:.3f}s{peak_text})")
            print("  diff:")
            print_diff(extra, normalize_output(stdout))

    print("-" * 60)
    print(f"总结：PASS={passed}, FAIL={failed}, NO_ANSWER={no_answer}")
    return 1 if failed else 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Check samples for one OJ problem directory")
    parser.add_argument("problem_dir", nargs="?", type=Path, default=Path.cwd())
    parser.add_argument("--source", default=None, help="source file relative to problem_dir")
    parser.add_argument("--timeout", type=float, default=2.0)
    parser.add_argument("-m", "--memory-mb", type=int, default=None)
    parser.add_argument("--memory-guard-mb", type=int, default=16)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.timeout <= 0:
        print("--timeout must be positive", file=sys.stderr)
        return 2
    if args.memory_mb is not None and args.memory_mb <= 0:
        print("--memory-mb must be positive", file=sys.stderr)
        return 2
    if args.memory_guard_mb < 0:
        print("--memory-guard-mb must be non-negative", file=sys.stderr)
        return 2
    return run_samples(
        args.problem_dir.resolve(),
        args.source,
        args.timeout,
        args.memory_mb,
        args.memory_guard_mb,
    )


if __name__ == "__main__":
    raise SystemExit(main())
