#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
WORK_DIR=""
RELEASE_SHA=""
CONTENT_SHA=""
DEPLOY_MODE=""
CANDIDATE_PID=""

die() {
  echo "[release] $*" >&2
  exit 1
}

cleanup() {
  if [[ -n "$CANDIDATE_PID" ]]; then
    kill "$CANDIDATE_PID" >/dev/null 2>&1 || true
    wait "$CANDIDATE_PID" >/dev/null 2>&1 || true
  fi
}
trap cleanup EXIT

while (( $# > 0 )); do
  case "$1" in
    --work-dir)
      WORK_DIR="${2:?missing value for --work-dir}"
      shift 2
      ;;
    --commit)
      RELEASE_SHA="${2:?missing value for --commit}"
      shift 2
      ;;
    --mode)
      DEPLOY_MODE="${2:?missing value for --mode}"
      shift 2
      ;;
    --content-sha)
      CONTENT_SHA="${2:?missing value for --content-sha}"
      shift 2
      ;;
    *)
      die "unknown argument: $1"
      ;;
  esac
done

[[ -n "$WORK_DIR" ]] || die "--work-dir is required"
[[ "$RELEASE_SHA" =~ ^[0-9a-f]{40}$ ]] || die "--commit must be a full Git SHA"
[[ "$CONTENT_SHA" =~ ^[0-9a-f]{40}$ ]] || die "--content-sha must be a full Git SHA"
[[ "$DEPLOY_MODE" == content || "$DEPLOY_MODE" == application ]] \
  || die "--mode must be content or application"

for command_name in git npm node tar zstd sha256sum curl python3; do
  command -v "$command_name" >/dev/null 2>&1 || die "missing command: $command_name"
done

SOURCE_DIR="$WORK_DIR/source"
APP_DIR="$WORK_DIR/app"
CONTENT_DIR="$WORK_DIR/content"
CANDIDATE_DIR="$WORK_DIR/candidate"
APP_ARCHIVE="$WORK_DIR/problems-solution-app-${RELEASE_SHA:0:12}.tar.zst"
LOCK_HASH="$(sha256sum "$ROOT_DIR/package-lock.json" | cut -d' ' -f1)"
PLATFORM_KEY="$(node -p "[process.platform, process.arch].join('-')")"
NODE_ABI="$(node -p 'process.versions.modules')"
DEPENDENCY_PLATFORM_KEY="$PLATFORM_KEY-node$NODE_ABI"
DEPENDENCY_CACHE_ROOT="$ROOT_DIR/.git/problems-solution-native-dependencies"
DEPENDENCY_DIR="$DEPENDENCY_CACHE_ROOT/$LOCK_HASH/$DEPENDENCY_PLATFORM_KEY"
DEPENDENCY_ARCHIVE="$WORK_DIR/problems-solution-dependencies-${LOCK_HASH:0:16}-${DEPENDENCY_PLATFORM_KEY}.tar.zst"
CONTENT_INDEX="$WORK_DIR/content-index-${CONTENT_SHA:0:12}-v1.json"
CONTENT_INDEX_ARCHIVE="$CONTENT_INDEX.zst"

mkdir -p "$SOURCE_DIR" "$APP_DIR" "$CONTENT_DIR" "$CANDIDATE_DIR"

# Export the committed tree. Ignored problem-analysis workspaces and other
# local files must never enter either the app release or the content snapshot.
git -C "$ROOT_DIR" archive --format=tar "$RELEASE_SHA" | tar -xf - -C "$SOURCE_DIR"

# relations3-graph 的静态资源是 Vite 构建产物，已被 .gitignore 排除，
# git archive 导不出来；发布前必须用本地 node_modules 现场构建，
# 并把产物放进 app release 的 public/，否则线上 /relations 页面 JS 404。
echo "[release] build relations3-graph assets"
npm run build:relations3 >/dev/null
[[ -f "$ROOT_DIR/public/relations3-graph/assets/index.js" ]] \
  || die "relations3-graph build output is missing: public/relations3-graph/assets/index.js"
mkdir -p "$APP_DIR/public/relations3-graph"
cp -a "$ROOT_DIR/public/relations3-graph/." "$APP_DIR/public/relations3-graph/"

for source in app.js package.json package-lock.json config.yml bin lib routes views public; do
  [[ -e "$SOURCE_DIR/$source" ]] || die "app release source is missing: $source"
  cp -a "$SOURCE_DIR/$source" "$APP_DIR/"
done
for source in problems problem-sets; do
  [[ -d "$SOURCE_DIR/$source" ]] || die "content source is missing: $source"
  cp -a "$SOURCE_DIR/$source" "$CONTENT_DIR/"
done

cat > "$APP_DIR/app.env" <<EOF
PROBLEMS_SOLUTION_APP_SHA=$RELEASE_SHA
PROBLEMS_SOLUTION_DEPENDENCY_HASH=$LOCK_HASH
PROBLEMS_SOLUTION_PLATFORM=$PLATFORM_KEY
PROBLEMS_SOLUTION_NODE_ABI=$NODE_ABI
EOF
printf 'PROBLEMS_SOLUTION_CONTENT_SHA=%s\n' "$CONTENT_SHA" > "$CONTENT_DIR/content.env"

if [[ ! -d "$DEPENDENCY_DIR/node_modules" ]]; then
  echo "[release] build production dependencies for $LOCK_HASH ($PLATFORM_KEY)"
  DEPENDENCY_BUILD_DIR="$WORK_DIR/dependency-build"
  mkdir -p "$DEPENDENCY_BUILD_DIR"
  cp "$SOURCE_DIR/package.json" "$SOURCE_DIR/package-lock.json" "$DEPENDENCY_BUILD_DIR/"
  (
    cd "$DEPENDENCY_BUILD_DIR"
    npm ci --omit=dev --ignore-scripts --no-audit --no-fund
  )
  mkdir -p "$(dirname "$DEPENDENCY_DIR")"
  mv "$DEPENDENCY_BUILD_DIR" "$DEPENDENCY_DIR"
fi

echo "[release] build content index for ${CONTENT_SHA:0:12}"
node "$ROOT_DIR/scripts/build-content-index.js" \
  --root "$CONTENT_DIR" --content-sha "$CONTENT_SHA" --output "$CONTENT_INDEX"
zstd -T0 -3 -q -o "$CONTENT_INDEX_ARCHIVE" "$CONTENT_INDEX"

echo "[release] test the exact app and content combination"
ln -s "$APP_DIR" "$CANDIDATE_DIR/app"
ln -s "$CONTENT_DIR/problems" "$CANDIDATE_DIR/problems"
ln -s "$CONTENT_DIR/problem-sets" "$CANDIDATE_DIR/problem-sets"
ln -s "$APP_DIR/config.yml" "$CANDIDATE_DIR/config.yml"
mkdir -p "$CANDIDATE_DIR/.runtime"
updated_at="$(date -u +'%Y-%m-%dT%H:%M:%SZ')"
printf '{"targetRevision":"%s","updatedAt":"%s"}\n' \
  "$RELEASE_SHA" "$updated_at" > "$CANDIDATE_DIR/.runtime/content-revision.json"
ln -s "$DEPENDENCY_DIR/node_modules" "$APP_DIR/node_modules"

CANDIDATE_PORT="$(python3 - <<'PY'
import socket
with socket.socket() as sock:
    sock.bind(('127.0.0.1', 0))
    print(sock.getsockname()[1])
PY
)"

(
  cd "$CANDIDATE_DIR"
  env \
    NODE_ENV=production \
    HOST=127.0.0.1 \
    PORT="$CANDIDATE_PORT" \
    CONTENT_REVISION_PATH="$CANDIDATE_DIR/.runtime/content-revision.json" \
    CONTENT_INDEX_PATH="$CONTENT_INDEX" \
    PROBLEMS_SOLUTION_CONTENT_SHA="$CONTENT_SHA" \
    node "$CANDIDATE_DIR/app/bin/www"
) >"$WORK_DIR/candidate.log" 2>&1 &
CANDIDATE_PID=$!

candidate_ok=false
for _attempt in $(seq 1 60); do
  if curl -fsS --max-time 3 "http://127.0.0.1:$CANDIDATE_PORT/api/health/live" >/dev/null 2>&1 \
    && curl -fsS --max-time 5 "http://127.0.0.1:$CANDIDATE_PORT/api/health/content" 2>/dev/null \
      | RELEASE_SHA="$RELEASE_SHA" node -e '
        let body = "";
        process.stdin.on("data", (chunk) => body += chunk);
        process.stdin.on("end", () => {
          const health = JSON.parse(body);
          if (health.state !== "healthy"
              || health.ready !== true
              || health.errorCount !== 0
              || health.activeRevision !== process.env.RELEASE_SHA) process.exit(1);
        });
      ' >/dev/null 2>&1; then
    candidate_ok=true
    break
  fi
  if ! kill -0 "$CANDIDATE_PID" >/dev/null 2>&1; then
    break
  fi
  sleep 1
done

if [[ "$candidate_ok" != true ]]; then
  cat "$WORK_DIR/candidate.log" >&2 || true
  die "candidate release failed its local health check"
fi

kill "$CANDIDATE_PID" >/dev/null 2>&1 || true
wait "$CANDIDATE_PID" >/dev/null 2>&1 || true
CANDIDATE_PID=""
rm "$APP_DIR/node_modules"

echo "[release] compress app release"
tar -C "$APP_DIR" -cf - . | zstd -T0 -3 -q -o "$APP_ARCHIVE"

if [[ ! -f "$DEPENDENCY_DIR/dependencies.tar.zst" ]]; then
  echo "[release] compress production dependencies"
  tar -C "$DEPENDENCY_DIR" -cf - node_modules \
    | zstd -T0 -3 -q -o "$DEPENDENCY_DIR/dependencies.tar.zst"
fi
cp "$DEPENDENCY_DIR/dependencies.tar.zst" "$DEPENDENCY_ARCHIVE"

(
  cd "$WORK_DIR"
  sha256sum "$(basename "$APP_ARCHIVE")" > "$(basename "$APP_ARCHIVE").sha256"
  sha256sum "$(basename "$DEPENDENCY_ARCHIVE")" > "$(basename "$DEPENDENCY_ARCHIVE").sha256"
  sha256sum "$(basename "$CONTENT_INDEX_ARCHIVE")" > "$(basename "$CONTENT_INDEX_ARCHIVE").sha256"
)

{
  printf 'APP_DIR=%q\n' "$APP_DIR"
  printf 'CONTENT_DIR=%q\n' "$CONTENT_DIR"
  printf 'APP_ARCHIVE=%q\n' "$APP_ARCHIVE"
  printf 'DEPENDENCY_ARCHIVE=%q\n' "$DEPENDENCY_ARCHIVE"
  printf 'CONTENT_INDEX_ARCHIVE=%q\n' "$CONTENT_INDEX_ARCHIVE"
  printf 'LOCK_HASH=%q\n' "$LOCK_HASH"
  printf 'PLATFORM_KEY=%q\n' "$PLATFORM_KEY"
  printf 'NODE_ABI=%q\n' "$NODE_ABI"
  printf 'RELEASE_SHA=%q\n' "$RELEASE_SHA"
} > "$WORK_DIR/artifacts.env"

echo "[release] app=$(du -h "$APP_ARCHIVE" | cut -f1) dependencies=$(du -h "$DEPENDENCY_ARCHIVE" | cut -f1)"
