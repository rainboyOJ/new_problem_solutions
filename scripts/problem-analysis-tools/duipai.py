#!/usr/bin/env python3
"""Non-interactive stress testing script.

The generator is run with no input. Its stdout becomes the test input for both
the user solution and the brute solution. On the first mismatch, this script
saves the failing case and exits with a non-zero status.
"""

from __future__ import annotations

import argparse
import dataclasses
import datetime as dt
import difflib
import hashlib
import json
import math
import os
from pathlib import Path
import random
import shlex
import subprocess
import sys
import tempfile
import time


REPO_ROOT = Path(__file__).resolve().parents[2]

# 直接以脚本方式运行时脚本目录已在 sys.path 上；被 import 时要手动补，
# 否则找不到同目录的 compiler 模块。
_SCRIPT_DIR = str(Path(__file__).resolve().parent)
if _SCRIPT_DIR not in sys.path:
    sys.path.insert(0, _SCRIPT_DIR)

from compiler import find_cxx  # noqa: E402  （必须在 sys.path 调整之后导入）


@dataclasses.dataclass
class RunResult:
    returncode: int
    stdout: str
    stderr: str
    elapsed: float
    peak_mb: float | None
    timed_out: bool
    memory_exceeded: bool

    @property
    def status(self) -> str:
        if self.timed_out:
            return "TIMEOUT"
        if self.memory_exceeded:
            return "MEMORY_LIMIT"
        if self.returncode != 0:
            return "RUNTIME_ERROR"
        return "OK"


@dataclasses.dataclass
class CompareResult:
    ok: bool
    method: str
    reason: str
    checker_stdout: str = ""
    checker_stderr: str = ""


def rel(path: Path) -> str:
    try:
        return str(path.resolve().relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def shell_join(cmd: list[str]) -> str:
    return " ".join(shlex.quote(x) for x in cmd)


def compile_cpp(src: Path, build_dir: Path) -> Path:
    digest = hashlib.sha1(str(src.resolve()).encode()).hexdigest()[:12]
    out = build_dir / f"{src.stem}-{digest}"
    if out.exists() and out.stat().st_mtime >= src.stat().st_mtime:
        return out
    cmd = [*find_cxx(), "-std=c++17", "-O2", str(src), "-o", str(out)]
    subprocess.run(cmd, check=True)
    return out


def command_for(path: Path, build_dir: Path) -> list[str]:
    if not path.exists():
        raise FileNotFoundError(path)
    if path.suffix == ".cpp":
        return [str(compile_cpp(path, build_dir))]
    if path.suffix == ".py":
        return [sys.executable, str(path)]
    if os.access(path, os.X_OK):
        return [str(path)]
    raise ValueError(f"Unsupported or non-executable file: {path}")


def run_limited_command(
    cmd: list[str],
    input_data: str | None,
    timeout: float,
    memory_mb: int | None = None,
    memory_guard_mb: int = 16,
    env_extra: dict[str, str] | None = None,
) -> RunResult:
    wrapper = r'''
import json
import os
import resource
import subprocess
import sys
import time

cmd = json.loads(os.environ["DUPAI_CMD"])
timeout = float(os.environ["DUPAI_TIMEOUT"])
hard_bytes = int(os.environ.get("DUPAI_HARD_BYTES", "0"))
meta_path = os.environ["DUPAI_META"]
input_data = sys.stdin.read()
input_value = input_data if os.environ.get("DUPAI_HAS_INPUT") == "1" else None

def limit_memory():
    if hard_bytes > 0:
        resource.setrlimit(resource.RLIMIT_AS, (hard_bytes, hard_bytes))

start = time.time()
timed_out = False
returncode = 0
stdout = ""
stderr = ""

try:
    result = subprocess.run(
        cmd,
        input=input_value,
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
    maxrss_kb = maxrss / 1024
else:
    maxrss_kb = maxrss

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
        hard_bytes = (memory_mb + memory_guard_mb) * 1024 * 1024

    env = os.environ.copy()
    if env_extra:
        env.update(env_extra)
    with tempfile.NamedTemporaryFile(delete=False) as meta_file:
        meta_path = Path(meta_file.name)
    env.update(
        {
            "DUPAI_CMD": json.dumps(cmd),
            "DUPAI_TIMEOUT": str(timeout),
            "DUPAI_HARD_BYTES": str(hard_bytes),
            "DUPAI_META": str(meta_path),
            "DUPAI_HAS_INPUT": "1" if input_data is not None else "0",
        }
    )

    start = time.time()
    try:
        wrapper_result = subprocess.run(
            [sys.executable, "-c", wrapper],
            input=input_data or "",
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=timeout + 2,
            env=env,
        )
    except subprocess.TimeoutExpired as exc:
        return RunResult(124, exc.stdout or "", exc.stderr or "", time.time() - start, None, True, False)

    try:
        meta = json.loads(meta_path.read_text(encoding="utf-8"))
    except (FileNotFoundError, json.JSONDecodeError):
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
    memory_exceeded = memory_mb is not None and peak_mb is not None and peak_mb > memory_mb
    return RunResult(
        int(meta.get("returncode", wrapper_result.returncode)),
        wrapper_result.stdout,
        wrapper_result.stderr,
        float(meta.get("elapsed", time.time() - start)),
        peak_mb,
        bool(meta.get("timed_out", False)),
        memory_exceeded,
    )


def normalize_output(data: str, strict: bool) -> str:
    if strict:
        return data
    lines = [line.rstrip() for line in data.splitlines()]
    while lines and lines[-1] == "":
        lines.pop()
    return "\n".join(lines) + ("\n" if lines else "")


def compare_with_eps(user_out: str, brute_out: str, eps: float) -> CompareResult:
    user_tokens = user_out.split()
    brute_tokens = brute_out.split()
    if len(user_tokens) != len(brute_tokens):
        return CompareResult(False, "eps", f"token count differs: user={len(user_tokens)}, brute={len(brute_tokens)}")

    for idx, (user_token, brute_token) in enumerate(zip(user_tokens, brute_tokens), 1):
        try:
            user_value = float(user_token)
            brute_value = float(brute_token)
        except ValueError:
            if user_token != brute_token:
                return CompareResult(False, "eps", f"token {idx} differs: {user_token!r} != {brute_token!r}")
            continue
        if not math.isclose(user_value, brute_value, rel_tol=eps, abs_tol=eps):
            return CompareResult(False, "eps", f"token {idx} differs: {user_value} vs {brute_value}, eps={eps}")

    return CompareResult(True, "eps", "outputs match within eps")


def compare_outputs(
    input_data: str,
    user_out: str,
    brute_out: str,
    strict: bool,
    eps: float | None,
    checker_cmd: list[str] | None,
) -> CompareResult:
    if checker_cmd is not None:
        with tempfile.TemporaryDirectory(prefix="duipai-checker-") as tmp:
            tmp_dir = Path(tmp)
            input_path = tmp_dir / "input.txt"
            user_path = tmp_dir / "user.out"
            brute_path = tmp_dir / "brute.out"
            input_path.write_text(input_data, encoding="utf-8")
            user_path.write_text(user_out, encoding="utf-8")
            brute_path.write_text(brute_out, encoding="utf-8")
            result = subprocess.run(
                [*checker_cmd, str(input_path), str(user_path), str(brute_path)],
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                check=False,
            )
        return CompareResult(
            result.returncode == 0,
            "checker",
            f"checker exited with {result.returncode}",
            result.stdout,
            result.stderr,
        )

    if eps is not None:
        return compare_with_eps(user_out, brute_out, eps)

    user_norm = normalize_output(user_out, strict)
    brute_norm = normalize_output(brute_out, strict)
    if user_norm == brute_norm:
        return CompareResult(True, "strict" if strict else "normalized", "outputs match")
    return CompareResult(False, "strict" if strict else "normalized", "outputs differ")


def infer_problem_dir(user_path: Path) -> Path:
    return user_path.resolve().parent


def default_report_path(problem_dir: Path) -> Path:
    return problem_dir / "problem-analysis-workspace" / "duipai-report.md"


def default_failed_dir(problem_dir: Path) -> Path:
    return problem_dir / "duipai-failed"


def write_report(
    report_path: Path,
    command_line: str,
    count: int,
    result: str,
    failed_dir: Path | None,
    meta: dict,
) -> None:
    report_path.parent.mkdir(parents=True, exist_ok=True)
    now = dt.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    failed_text = rel(failed_dir) if failed_dir else "无"
    meta_text = json.dumps(meta, ensure_ascii=False, indent=2)
    report_path.write_text(
        "\n".join(
            [
                "# 对拍记录",
                "",
                f"- 运行命令：`{command_line}`",
                f"- 测试次数：{count}",
                f"- 结果：{result}",
                f"- 失败样例位置：{failed_text}",
                f"- 时间：{now}",
                "",
                "## 配置",
                "",
                "```json",
                meta_text,
                "```",
                "",
            ]
        ),
        encoding="utf-8",
    )


def save_failure(
    failed_dir: Path,
    input_data: str,
    user: RunResult | None,
    brute: RunResult | None,
    meta: dict,
) -> None:
    failed_dir.mkdir(parents=True, exist_ok=True)
    user_out = user.stdout if user else ""
    brute_out = brute.stdout if brute else ""
    (failed_dir / "input.txt").write_text(input_data, encoding="utf-8")
    (failed_dir / "user.out").write_text(user_out, encoding="utf-8")
    (failed_dir / "brute.out").write_text(brute_out, encoding="utf-8")
    (failed_dir / "user.err").write_text(user.stderr if user else "", encoding="utf-8")
    (failed_dir / "brute.err").write_text(brute.stderr if brute else "", encoding="utf-8")
    diff = difflib.unified_diff(
        brute_out.splitlines(keepends=True),
        user_out.splitlines(keepends=True),
        fromfile="brute.out",
        tofile="user.out",
    )
    (failed_dir / "diff.txt").write_text("".join(diff), encoding="utf-8")
    (failed_dir / "meta.json").write_text(
        json.dumps(meta, ensure_ascii=False, indent=2),
        encoding="utf-8",
    )


def run_once(
    gen_cmd: list[str],
    user_cmd: list[str],
    brute_cmd: list[str],
    checker_cmd: list[str] | None,
    case_id: int,
    case_seed: int,
    timeout: float,
    memory_mb: int | None,
    memory_guard_mb: int,
    strict: bool,
    eps: float | None,
) -> tuple[str, str, RunResult | None, RunResult | None, CompareResult | None, dict]:
    env = {
        "DUPAI_CASE_ID": str(case_id),
        "DUPAI_SEED": str(case_seed),
    }
    gen = run_limited_command(gen_cmd, None, timeout, None, memory_guard_mb, env)
    meta = {
        "case": case_id,
        "seed": case_seed,
        "gen_status": gen.status,
        "gen_returncode": gen.returncode,
        "gen_elapsed": gen.elapsed,
    }
    if gen.status != "OK":
        meta["gen_stderr"] = gen.stderr
        return ("GENERATOR_ERROR", gen.stdout, None, None, None, meta)

    user = run_limited_command(user_cmd, gen.stdout, timeout, memory_mb, memory_guard_mb, env)
    brute = run_limited_command(brute_cmd, gen.stdout, timeout, memory_mb, memory_guard_mb, env)
    meta.update(
        {
            "user_status": user.status,
            "brute_status": brute.status,
            "user_returncode": user.returncode,
            "brute_returncode": brute.returncode,
            "user_elapsed": user.elapsed,
            "brute_elapsed": brute.elapsed,
            "user_peak_mb": user.peak_mb,
            "brute_peak_mb": brute.peak_mb,
        }
    )

    status_priority = ["TIMEOUT", "MEMORY_LIMIT", "RUNTIME_ERROR"]
    for status in status_priority:
        if user.status == status or brute.status == status:
            return (status, gen.stdout, user, brute, None, meta)

    compare = compare_outputs(gen.stdout, user.stdout, brute.stdout, strict, eps, checker_cmd)
    meta.update(
        {
            "compare_method": compare.method,
            "compare_reason": compare.reason,
            "checker_stdout": compare.checker_stdout,
            "checker_stderr": compare.checker_stderr,
        }
    )
    if not compare.ok:
        return ("WRONG_ANSWER", gen.stdout, user, brute, compare, meta)
    return ("PASS", gen.stdout, user, brute, compare, meta)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Non-interactive OJ stress tester")
    parser.add_argument("--gen", required=True, help="generator source/script/executable")
    parser.add_argument("--user", required=True, help="user solution, usually main.cpp")
    parser.add_argument("--brute", required=True, help="brute force trusted solution")
    parser.add_argument("-n", "--count", type=int, default=200)
    parser.add_argument("--timeout", type=float, default=2.0, help="timeout per program run")
    parser.add_argument("-m", "--memory-mb", type=int, default=None)
    parser.add_argument("--memory-guard-mb", type=int, default=16)
    parser.add_argument("--checker", default="", help="checker program: checker input.txt user.out brute.out")
    parser.add_argument("--eps", type=float, default=None, help="floating point compare tolerance")
    parser.add_argument("--seed", type=int, default=None, help="base seed exposed as DUPAI_SEED")
    parser.add_argument("--report", default="", help="duipai report markdown path")
    parser.add_argument("--failed-dir", default="", help="directory for first failing case")
    parser.add_argument("--strict", action="store_true", help="compare output byte-for-byte")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.count <= 0:
        raise ValueError("--count must be positive")
    if args.timeout <= 0:
        raise ValueError("--timeout must be positive")
    if args.memory_mb is not None and args.memory_mb <= 0:
        raise ValueError("--memory-mb must be positive")
    if args.memory_guard_mb < 0:
        raise ValueError("--memory-guard-mb must be non-negative")
    if args.eps is not None and args.eps < 0:
        raise ValueError("--eps must be non-negative")

    gen_path = Path(args.gen)
    user_path = Path(args.user)
    brute_path = Path(args.brute)
    checker_path = Path(args.checker) if args.checker else None
    problem_dir = infer_problem_dir(user_path)
    report_path = Path(args.report) if args.report else default_report_path(problem_dir)
    failed_dir = Path(args.failed_dir) if args.failed_dir else default_failed_dir(problem_dir)
    command_line = shell_join([sys.executable, rel(Path(__file__)), *sys.argv[1:]])
    base_seed = args.seed if args.seed is not None else random.SystemRandom().randrange(1, 2**63)

    build_dir = Path(tempfile.gettempdir()) / "problem-analysis-duipai"
    build_dir.mkdir(parents=True, exist_ok=True)

    report_meta = {
        "timeout": args.timeout,
        "memory_mb": args.memory_mb,
        "memory_guard_mb": args.memory_guard_mb,
        "checker": str(checker_path) if checker_path else "",
        "eps": args.eps,
        "strict": args.strict,
        "base_seed": base_seed,
    }

    try:
        gen_cmd = command_for(gen_path, build_dir)
        user_cmd = command_for(user_path, build_dir)
        brute_cmd = command_for(brute_path, build_dir)
        checker_cmd = command_for(checker_path, build_dir) if checker_path else None
    except (FileNotFoundError, ValueError, subprocess.CalledProcessError) as exc:
        write_report(report_path, command_line, 0, f"失败：{exc}", None, report_meta)
        print(f"duipai setup failed: {exc}", file=sys.stderr)
        return 2

    report_meta.update(
        {
            "gen_cmd": gen_cmd,
            "user_cmd": user_cmd,
            "brute_cmd": brute_cmd,
            "checker_cmd": checker_cmd,
        }
    )

    for case_id in range(1, args.count + 1):
        case_seed = base_seed + case_id - 1
        status, input_data, user, brute, compare, meta = run_once(
            gen_cmd,
            user_cmd,
            brute_cmd,
            checker_cmd,
            case_id,
            case_seed,
            args.timeout,
            args.memory_mb,
            args.memory_guard_mb,
            args.strict,
            args.eps,
        )

        if status != "PASS":
            failure_meta = {**report_meta, **meta, "status": status}
            save_failure(failed_dir, input_data, user, brute, failure_meta)
            write_report(report_path, command_line, case_id, "失败", failed_dir, failure_meta)
            print(f"Failed on case {case_id}: {status}")
            if compare and compare.reason:
                print(compare.reason)
            print(f"Saved failure to {failed_dir}")
            return 1

        if case_id % 100 == 0:
            print(f"Passed {case_id} tests")

    write_report(report_path, command_line, args.count, "通过", None, report_meta)
    print(f"Passed {args.count} tests")
    print(f"Report written to {report_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
