import test from 'node:test';
import assert from 'node:assert/strict';
import { spawnSync } from 'node:child_process';

const pythonScript = String.raw`
import copy
import importlib.util
import io
import json
import sys
import tempfile
import threading
from contextlib import redirect_stdout
from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path

script_path = Path("scripts/generate-luogu-official-training-set.py")
spec = importlib.util.spec_from_file_location("luogu_training_generator", script_path)
module = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = module
spec.loader.exec_module(module)

fixture_dir = Path("scripts/problem-analysis-tools/tests/fixtures")
list_payload = json.loads((fixture_dir / "luogu_training_list.json").read_text(encoding="utf-8"))
detail_100 = json.loads((fixture_dir / "luogu_training_100.json").read_text(encoding="utf-8"))
detail_101 = json.loads((fixture_dir / "luogu_training_101.json").read_text(encoding="utf-8"))

summaries = module.parse_training_list(list_payload)
trainings = [
    module.parse_training_detail(detail_100, summaries[0]),
    module.parse_training_detail(detail_101, summaries[1]),
]
basic_config = module.COLLECTIONS["basic"]
advanced_config = module.COLLECTIONS["advanced"]
markdown = module.render_markdown(trainings, basic_config, 35.0)
advanced_markdown = module.render_markdown(trainings, advanced_config, 36.0)
stats = module.problem_stats(trainings)

errors = {}

def capture_error(name, callback):
    try:
        callback()
    except module.GenerationError as exc:
        errors[name] = str(exc)

duplicate_lists = copy.deepcopy(list_payload)
duplicate_lists["data"]["trainings"]["result"][1]["id"] = 100
capture_error("duplicate_training", lambda: module.parse_training_list(duplicate_lists))

bad_list_count = copy.deepcopy(list_payload)
bad_list_count["data"]["trainings"]["count"] = 1
capture_error("bad_list_count", lambda: module.parse_training_list(bad_list_count))

bad_count = copy.deepcopy(detail_100)
bad_count["data"]["training"]["problemCount"] = 3
capture_error("bad_count", lambda: module.parse_training_detail(bad_count, summaries[0]))

bad_pid = copy.deepcopy(detail_100)
bad_pid["data"]["training"]["problems"][0]["pid"] = "bad pid"
capture_error("bad_pid", lambda: module.parse_training_detail(bad_pid, summaries[0]))

duplicate_problem = copy.deepcopy(detail_100)
duplicate_problem["data"]["training"]["problems"][1]["pid"] = "B2002"
capture_error("duplicate_problem", lambda: module.parse_training_detail(duplicate_problem, summaries[0]))

paged_list_1 = copy.deepcopy(list_payload)
paged_list_1["data"]["trainings"]["perPage"] = 1
paged_list_1["data"]["trainings"]["result"] = [
    paged_list_1["data"]["trainings"]["result"][0]
]
paged_list_2 = copy.deepcopy(list_payload)
paged_list_2["data"]["trainings"]["perPage"] = 1
paged_list_2["data"]["trainings"]["result"] = [
    paged_list_2["data"]["trainings"]["result"][1]
]

class FixtureClient:
    def __init__(self):
        self.paths = []

    def get_json(self, path):
        self.paths.append(path)
        if "/training/list" in path:
            return paged_list_2 if "page=2" in path else paged_list_1
        if "/training/100" in path:
            return detail_100
        if "/training/101" in path:
            return detail_101
        raise AssertionError(path)

fixture_client = FixtureClient()
with redirect_stdout(io.StringIO()):
    paged_trainings = module.load_trainings(fixture_client, advanced_config)

selected_all = [item.key for item in module.selected_collection_configs("all")]
selected_basic = [item.key for item in module.selected_collection_configs("basic")]
capture_error("invalid_collection", lambda: module.selected_collection_configs("missing"))

class CookieHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/invalid":
            body = b"not-json"
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Content-Length", str(len(body)))
            self.end_headers()
            self.wfile.write(body)
            return
        if "session=ok" not in (self.headers.get("Cookie") or ""):
            self.send_response(302)
            self.send_header("Location", self.path)
            self.send_header("Set-Cookie", "session=ok; Path=/")
            self.end_headers()
            return
        body = json.dumps({"template": "test", "status": 200, "data": {"cookie": True}}).encode()
        self.send_response(200)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def log_message(self, format, *args):
        pass

server = HTTPServer(("127.0.0.1", 0), CookieHandler)
thread = threading.Thread(target=server.serve_forever, daemon=True)
thread.start()
client = module.LuoguClient(f"http://127.0.0.1:{server.server_port}", max_attempts=1)
cookie_payload = client.get_json("/cookie")
capture_error("invalid_json", lambda: client.get_json("/invalid"))
server.shutdown()
thread.join()

with tempfile.TemporaryDirectory() as tmp:
    destination = Path(tmp) / "set.md"
    missing_order = module.existing_order(destination)
    destination.write_text("---\norder: 42.5\n---\n", encoding="utf-8")
    preserved_order = module.existing_order(destination)

print(json.dumps({
    "summary_ids": [item["id"] for item in summaries],
    "training_ids": [item.training_id for item in trainings],
    "paged_training_ids": [item.training_id for item in paged_trainings],
    "problem_ids": [[problem.pid for problem in item.problems] for item in trainings],
    "stats": stats,
    "markdown": markdown,
    "advanced_markdown": advanced_markdown,
    "configs": {
        key: {
            "training_type": value.training_type,
            "output": value.output.name,
            "title": value.title,
            "description": value.description,
            "default_order": value.default_order,
            "source_url": value.source_url,
        }
        for key, value in module.COLLECTIONS.items()
    },
    "selected_all": selected_all,
    "selected_basic": selected_basic,
    "fixture_paths": fixture_client.paths,
    "errors": errors,
    "cookie_payload": cookie_payload,
    "missing_order": missing_order,
    "preserved_order": preserved_order,
}, ensure_ascii=False))
`;

test('Luogu official training generator validates, renders, and reuses cookies', () => {
  const result = spawnSync('python3', ['-c', pythonScript], {
    cwd: process.cwd(),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.deepEqual(payload.summary_ids, [100, 101]);
  assert.deepEqual(payload.training_ids, [100, 101]);
  assert.deepEqual(payload.paged_training_ids, [100, 101]);
  assert.deepEqual(payload.problem_ids, [['B2002', 'P1001'], ['P1001', 'P5710']]);
  assert.deepEqual(payload.stats, {
    training_count: 2,
    entry_count: 4,
    distinct_count: 3,
    repeated_id_count: 1,
    extra_occurrence_count: 1,
  });
  assert.match(payload.markdown, /order: 35/);
  assert.match(payload.markdown, /type=srqc-jc/);
  assert.match(payload.advanced_markdown, /洛谷官方深入浅出进阶篇题单/);
  assert.match(payload.advanced_markdown, /order: 36/);
  assert.match(payload.advanced_markdown, /type=srqc-jj/);
  assert.doesNotMatch(payload.advanced_markdown, /入门与基础算法训练题单/);
  assert.match(payload.markdown, /共收录 \*\*2\*\* 个官方子题单、\*\*4\*\* 个题目条目、\*\*3\*\* 道不同题目/);
  assert.ok(payload.markdown.indexOf('training/100') < payload.markdown.indexOf('training/101'));
  assert.ok(payload.markdown.indexOf('luogu,B2002') < payload.markdown.indexOf('luogu,P1001'));
  assert.equal((payload.markdown.match(/\[\[problem: luogu,P1001\]\]/g) || []).length, 2);
  assert.ok(payload.markdown.includes('## 【入门2】分支 \\[结构\\]'));
  assert.match(payload.markdown, /https:\/\/www\.luogu\.com\.cn\/problem\/P5710/);
  assert.match(payload.errors.duplicate_training, /子题单 ID 重复/);
  assert.match(payload.errors.bad_list_count, /count 与当前页数据不一致/);
  assert.match(payload.errors.bad_count, /题目数不一致/);
  assert.match(payload.errors.bad_pid, /无效题号/);
  assert.match(payload.errors.duplicate_problem, /题号重复/);
  assert.match(payload.errors.invalid_json, /不是有效 JSON/);
  assert.match(payload.errors.invalid_collection, /未知 collection/);
  assert.deepEqual(payload.selected_all, ['basic', 'advanced']);
  assert.deepEqual(payload.selected_basic, ['basic']);
  assert.ok(payload.fixture_paths.some((path) => path.includes('type=srqc-jj')));
  assert.equal(payload.configs.basic.output, 'luogu-official-basic-training.md');
  assert.equal(payload.configs.basic.default_order, 35);
  assert.equal(payload.configs.advanced.training_type, 'srqc-jj');
  assert.equal(payload.configs.advanced.output, 'luogu-official-advanced-training.md');
  assert.equal(payload.configs.advanced.title, '洛谷官方深入浅出进阶篇题单');
  assert.equal(payload.configs.advanced.default_order, 36);
  assert.match(payload.configs.advanced.source_url, /type=srqc-jj$/);
  assert.deepEqual(payload.cookie_payload, { template: 'test', status: 200, data: { cookie: true } });
  assert.equal(payload.missing_order, null);
  assert.equal(payload.preserved_order, 42.5);
});
