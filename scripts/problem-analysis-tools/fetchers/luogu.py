from __future__ import annotations

import re
from typing import Any

from .base import (
    BaseFetcher,
    FetchError,
    FetchResult,
    ProblemData,
    Sample,
    extract_json_script,
    markdown_section,
)


class LuoguFetcher(BaseFetcher):
    name = "luogu"
    aliases = ("lg",)
    site_prefixes = ("https://www.luogu.com.cn", "https://www.luogu.com")

    def real_id(self, problem_id: str) -> str:
        return f"P{problem_id}" if problem_id[:1].isdigit() else problem_id.upper()

    def dir_id(self, problem_id: str) -> str:
        real = self.real_id(problem_id)
        if re.fullmatch(r"P\d+", real, flags=re.IGNORECASE):
            return real.upper()
        return real.lower()

    def problem_link(self, problem_id: str) -> str:
        return f"https://www.luogu.com.cn/problem/{self.real_id(problem_id)}"

    def parse_url(self, url: str) -> tuple[str, str]:
        parts = [part for part in url.split("?")[0].split("#")[0].split("/") if part]
        if "problem" not in parts:
            raise FetchError(f"无法从 Luogu URL 解析题号：{url}")
        idx = parts.index("problem")
        if idx + 1 >= len(parts):
            raise FetchError(f"无法从 Luogu URL 解析题号：{url}")
        return self.name, parts[idx + 1]

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        display_id = self.real_id(problem_id)
        return ProblemData(
            oj=self.name,
            problem_id=display_id,
            problem_dir_id=self.dir_id(problem_id),
            source=self.problem_link(problem_id),
            title=display_id,
        )

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        data = self.build_data_from_id(oj, problem_id)
        html = self.http_get(data.source)
        fetched_data = self.parse_html(html, problem_id)
        fetched_data.source = data.source
        return FetchResult(data=fetched_data, fetched=True, warnings=list(fetched_data.warnings))

    def fetch_by_url(self, url: str) -> FetchResult:
        oj, problem_id = self.parse_url(url)
        result = self.fetch(oj, problem_id)
        result.data.source = url
        return result

    def parse_html(self, html: str, problem_id: str) -> ProblemData:
        # Luogu 把题目信息塞在 #lentille-context 这个 application/json script 中。
        raw = extract_json_script(html, "lentille-context")
        data = raw.get("data") or {}
        problem = data.get("problem") or {}
        if not isinstance(problem, dict):
            raise FetchError("Luogu JSON 中缺少 problem 对象。")
        return self.problem_from_luogu_json(problem, problem_id)

    def problem_from_luogu_json(self, problem: dict[str, Any], problem_id: str) -> ProblemData:
        display_id = self.real_id(problem_id)
        content = self.problem_content(problem)
        title = str(
            problem.get("title")
            or problem.get("name")
            or content.get("name")
            or display_id
        ).strip()
        samples = self.parse_samples(problem.get("samples"))
        return ProblemData(
            oj=self.name,
            problem_id=display_id,
            problem_dir_id=self.dir_id(problem_id),
            source=self.problem_link(problem_id),
            title=title,
            statement_md=self.problem_statement_markdown(display_id, title, content, samples),
            samples=samples,
            difficulty=self.difficulty_from_id(problem.get("difficulty")),
        )

    def difficulty_from_id(self, raw: Any) -> str:
        # 洛谷官方 difficulty 字段是数字 id（2026-08 新版映射，已无 NOI/NOI+/CTSC 档）。
        mapping = {
            0: "未知",
            1: "入门",
            2: "普及-",
            3: "普及",
            4: "普及+/提高-",
            5: "提高",
            6: "提高+/省选-",
            7: "省选/NOI-",
        }
        try:
            difficulty_id = int(raw)
        except (TypeError, ValueError):
            return ""
        return mapping.get(difficulty_id, "")

    def problem_content(self, problem: dict[str, Any]) -> dict[str, Any]:
        # Luogu 新页面把题面正文放在 content/contenu 中；旧数据可能仍在 problem 顶层。
        content = problem.get("content") or problem.get("contenu")
        if isinstance(content, dict):
            merged = dict(problem)
            merged.update(content)
            return merged
        return problem

    def first_text_field(self, problem: dict[str, Any], *keys: str) -> str | None:
        for key in keys:
            value = problem.get(key)
            if isinstance(value, str) and value.strip():
                return value
        return None

    def parse_samples(self, raw_samples: Any) -> list[Sample]:
        samples: list[Sample] = []
        if not isinstance(raw_samples, list):
            return samples
        for item in raw_samples:
            input_data = ""
            output_data = ""
            # Luogu 历史数据有数组和对象两种形态，这里都兼容。
            if isinstance(item, list) and len(item) >= 2:
                input_data = str(item[0])
                output_data = str(item[1])
            elif isinstance(item, dict):
                input_data = str(item.get("input") or "")
                output_data = str(item.get("output") or "")
            if input_data or output_data:
                samples.append(Sample(input=input_data, output=output_data))
        return samples

    def problem_statement_markdown(
        self,
        display_id: str,
        title: str,
        problem: dict[str, Any],
        samples: list[Sample],
    ) -> str:
        sections = [f"# {display_id} {title}".strip(), ""]
        sections.append(markdown_section("题目背景", problem.get("background")))
        sections.append(markdown_section("题目描述", problem.get("description")))
        sections.append(markdown_section("输入格式", self.first_text_field(problem, "inputFormat", "input", "formatI")))
        sections.append(markdown_section("输出格式", self.first_text_field(problem, "outputFormat", "output", "formatO")))
        if samples:
            sample_parts = []
            for index, sample in enumerate(samples, start=1):
                sample_parts.append(
                    "\n".join(
                        [
                            f"## 输入输出样例 #{index}",
                            "",
                            f"### 输入 #{index}",
                            "",
                            "```",
                            sample.input.rstrip(),
                            "```",
                            "",
                            f"### 输出 #{index}",
                            "",
                            "```",
                            sample.output.rstrip(),
                            "```",
                        ]
                    )
                )
            sections.append("\n\n".join(sample_parts) + "\n")
        sections.append(markdown_section("说明/提示", problem.get("hint")))
        return "\n".join(part for part in sections if part != "").rstrip() + "\n"
