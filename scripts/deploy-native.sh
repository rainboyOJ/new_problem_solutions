#!/usr/bin/env bash
set -euo pipefail

BASE_DIR="/opt/problems-solution"
DEPLOYMENT_SHA="${RELEASE_SHA:?missing RELEASE_SHA}"
APP_SHA="${APP_SHA:?missing APP_SHA}"
CONTENT_SHA="${CONTENT_SHA:?missing CONTENT_SHA}"
LOCK_HASH="${LOCK_HASH:?missing LOCK_HASH}"
PLATFORM_KEY="${PLATFORM_KEY:?missing PLATFORM_KEY}"
NODE_ABI="${NODE_ABI:?missing NODE_ABI}"
DEPLOY_MODE="${DEPLOY_MODE:?missing DEPLOY_MODE}"
UPLOAD_APP="${UPLOAD_APP:?missing UPLOAD_APP}"
UPLOAD_CONTENT="${UPLOAD_CONTENT:?missing UPLOAD_CONTENT}"
INCOMING_DIR="${INCOMING_DIR:?missing INCOMING_DIR}"
DEPLOY_ACTOR="${DEPLOY_ACTOR:-unknown}"
DEPLOY_SOURCE_HOST="${DEPLOY_SOURCE_HOST:-unknown}"
PUBLIC_HEALTH_URL="${PUBLIC_HEALTH_URL:-https://pcs2.roj.ac.cn/api/health/content}"
SERVICE_NAME="problems-solution.service"

for value in "$DEPLOYMENT_SHA" "$APP_SHA" "$CONTENT_SHA"; do
  [[ "$value" =~ ^[0-9a-f]{40}$ ]] || { echo "invalid Git SHA: $value" >&2; exit 2; }
done
[[ "$LOCK_HASH" =~ ^[0-9a-f]{64}$ ]] || { echo "invalid LOCK_HASH" >&2; exit 2; }
[[ "$PLATFORM_KEY" =~ ^[a-zA-Z0-9._-]+$ ]] || { echo "invalid PLATFORM_KEY" >&2; exit 2; }
[[ "$NODE_ABI" =~ ^[0-9]+$ ]] || { echo "invalid NODE_ABI" >&2; exit 2; }
[[ "$DEPLOY_MODE" == content || "$DEPLOY_MODE" == application ]] \
  || { echo "invalid DEPLOY_MODE" >&2; exit 2; }
[[ "$UPLOAD_APP" == true || "$UPLOAD_APP" == false ]] || { echo "invalid UPLOAD_APP" >&2; exit 2; }
[[ "$UPLOAD_CONTENT" == true || "$UPLOAD_CONTENT" == false ]] || { echo "invalid UPLOAD_CONTENT" >&2; exit 2; }
[[ "$(id -u)" == 0 ]] || { echo "deploy-native.sh must run as root" >&2; exit 2; }

APPS_DIR="$BASE_DIR/apps"
CONTENTS_DIR="$BASE_DIR/contents"
DEPENDENCIES_DIR="$BASE_DIR/dependencies"
DEPLOYMENTS_DIR="$BASE_DIR/deployments"
CURRENT_LINK="$BASE_DIR/current"
CONFIG_FILE="$BASE_DIR/deploy.env"
AUDIT_LOG="$BASE_DIR/deployments.log"
BIN_DIR="$BASE_DIR/bin"
LOCK_FILE="$BASE_DIR/.deploy.lock"
APP_DIR="$APPS_DIR/$APP_SHA"
CONTENT_DIR="$CONTENTS_DIR/$CONTENT_SHA"
DEPENDENCY_PLATFORM_KEY="$PLATFORM_KEY-node$NODE_ABI"
DEPENDENCY_DIR="$DEPENDENCIES_DIR/$LOCK_HASH/$DEPENDENCY_PLATFORM_KEY"
DEPLOYMENT_DIR="$DEPLOYMENTS_DIR/$DEPLOYMENT_SHA"
SERVICE_FILE="$INCOMING_DIR/problems-solution.service"
APP_ARCHIVE="$INCOMING_DIR/problems-solution-app-${APP_SHA:0:12}.tar.zst"
DEPENDENCY_ARCHIVE="$INCOMING_DIR/problems-solution-dependencies-${LOCK_HASH:0:16}-${DEPENDENCY_PLATFORM_KEY}.tar.zst"
INCOMING_CONTENT_DIR="$INCOMING_DIR/content"
STARTED_AT="$(date --iso-8601=seconds)"
RESULT="failed"
DETAIL="unexpected-error"
CANDIDATE_PID=""
OLD_DEPLOYMENT=""
LEGACY_CONTAINER_RUNNING=false
PUBLIC_WAS_HEALTHY=false

mkdir -p "$BASE_DIR"
touch "$AUDIT_LOG"
chmod 600 "$AUDIT_LOG"
exec 9>"$LOCK_FILE"
flock -x -w 1800 9 || { echo "timed out waiting for $LOCK_FILE" >&2; exit 1; }

audit() {
  local ended_at
  ended_at="$(date --iso-8601=seconds)"
  printf '%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n' \
    "$STARTED_AT" "$ended_at" "$DEPLOYMENT_SHA" "$DEPLOY_MODE" \
    "$DEPLOY_ACTOR" "$DEPLOY_SOURCE_HOST" "$RESULT" "$DETAIL" >> "$AUDIT_LOG"
}

cleanup() {
  if [[ -n "$CANDIDATE_PID" ]]; then
    kill "$CANDIDATE_PID" >/dev/null 2>&1 || true
    wait "$CANDIDATE_PID" >/dev/null 2>&1 || true
  fi
  audit
}
trap cleanup EXIT

live_ok() {
  local url="$1"
  local attempts="${2:-30}"
  local response
  for _attempt in $(seq 1 "$attempts"); do
    if response="$(curl -fsS --max-time 5 "$url" 2>/dev/null)" \
      && printf '%s' "$response" | /usr/bin/node -e '
        let body = "";
        process.stdin.on("data", (chunk) => body += chunk);
        process.stdin.on("end", () => {
          if (JSON.parse(body).status !== "ok") process.exit(1);
        });
      ' >/dev/null 2>&1; then
      return 0
    fi
    sleep 2
  done
  return 1
}

health_ok() {
  local url="$1"
  local expected_revision="$2"
  local attempts="${3:-30}"
  local response
  for _attempt in $(seq 1 "$attempts"); do
    if response="$(curl -fsS --max-time 5 "$url" 2>/dev/null)"; then
      if printf '%s' "$response" | RELEASE_SHA="$expected_revision" /usr/bin/node -e '
        let body = "";
        process.stdin.on("data", (chunk) => body += chunk);
        process.stdin.on("end", () => {
          const health = JSON.parse(body);
          if (health.state !== "healthy"
              || health.ready !== true
              || health.errorCount !== 0
              || (process.env.RELEASE_SHA && health.activeRevision !== process.env.RELEASE_SHA)) {
            process.exit(1);
          }
        });
      ' >/dev/null 2>&1; then
        return 0
      fi
    fi
    sleep 2
  done
  return 1
}

read_env_value() {
  local file="$1"
  local name="$2"
  sed -n "s/^${name}=//p" "$file" | head -1
}

ensure_config() {
  if [[ -f "$CONFIG_FILE" ]]; then
    chmod 600 "$CONFIG_FILE"
    return
  fi

  local content_health_token=""
  if command -v docker >/dev/null 2>&1 && docker container inspect problems-solution >/dev/null 2>&1; then
    content_health_token="$(docker container inspect --format '{{range .Config.Env}}{{println .}}{{end}}' problems-solution \
      | sed -n 's/^CONTENT_HEALTH_TOKEN=//p' | head -1)"
  fi

  local previous_umask
  previous_umask="$(umask)"
  umask 077
  printf 'CONTENT_HEALTH_TOKEN=%q\n' "$content_health_token" > "$CONFIG_FILE"
  umask "$previous_umask"
}

assemble_dependency() {
  if [[ -d "$DEPENDENCY_DIR/node_modules" ]]; then
    return
  fi
  [[ -f "$DEPENDENCY_ARCHIVE" ]] || {
    echo "missing dependency archive $DEPENDENCY_ARCHIVE" >&2
    return 1
  }
  (cd "$INCOMING_DIR" && sha256sum -c "$(basename "$DEPENDENCY_ARCHIVE").sha256")
  local dependency_tmp="$DEPENDENCIES_DIR/$LOCK_HASH/.new-$DEPENDENCY_PLATFORM_KEY"
  rm -rf "$dependency_tmp"
  mkdir -p "$dependency_tmp"
  zstd -dc "$DEPENDENCY_ARCHIVE" | tar -xf - -C "$dependency_tmp"
  mv "$dependency_tmp" "$DEPENDENCY_DIR"
}

assemble_app() {
  if [[ -d "$APP_DIR" ]]; then
    grep -qx "PROBLEMS_SOLUTION_APP_SHA=$APP_SHA" "$APP_DIR/app.env"
    grep -qx "PROBLEMS_SOLUTION_DEPENDENCY_HASH=$LOCK_HASH" "$APP_DIR/app.env"
    grep -qx "PROBLEMS_SOLUTION_PLATFORM=$PLATFORM_KEY" "$APP_DIR/app.env"
    grep -qx "PROBLEMS_SOLUTION_NODE_ABI=$NODE_ABI" "$APP_DIR/app.env"
    return
  fi
  [[ "$UPLOAD_APP" == true ]] || { echo "app release does not exist: $APP_SHA" >&2; return 1; }
  assemble_dependency
  (cd "$INCOMING_DIR" && sha256sum -c "$(basename "$APP_ARCHIVE").sha256")
  local app_tmp="$APPS_DIR/.new-$APP_SHA"
  rm -rf "$app_tmp"
  mkdir -p "$app_tmp"
  zstd -dc "$APP_ARCHIVE" | tar -xf - -C "$app_tmp"
  grep -qx "PROBLEMS_SOLUTION_APP_SHA=$APP_SHA" "$app_tmp/app.env"
  grep -qx "PROBLEMS_SOLUTION_DEPENDENCY_HASH=$LOCK_HASH" "$app_tmp/app.env"
  grep -qx "PROBLEMS_SOLUTION_PLATFORM=$PLATFORM_KEY" "$app_tmp/app.env"
  grep -qx "PROBLEMS_SOLUTION_NODE_ABI=$NODE_ABI" "$app_tmp/app.env"
  cp -al "$DEPENDENCY_DIR/node_modules" "$app_tmp/node_modules"
  mv "$app_tmp" "$APP_DIR"
  chown -R root:problems-solution "$APP_DIR" "$DEPENDENCY_DIR"
  chmod -R a=rX,u+w "$APP_DIR" "$DEPENDENCY_DIR"
}

assemble_content() {
  if [[ "$UPLOAD_CONTENT" == true ]]; then
    [[ -d "$INCOMING_CONTENT_DIR/problems" && -d "$INCOMING_CONTENT_DIR/problem-sets" ]] \
      || { echo "incoming content is incomplete" >&2; return 1; }
    grep -qx "PROBLEMS_SOLUTION_CONTENT_SHA=$CONTENT_SHA" "$INCOMING_CONTENT_DIR/content.env"
    rm -rf "$CONTENT_DIR"
    mv "$INCOMING_CONTENT_DIR" "$CONTENT_DIR"
    chmod -R a=rX,u+w "$CONTENT_DIR"
  fi
  [[ -d "$CONTENT_DIR/problems" && -d "$CONTENT_DIR/problem-sets" ]] \
    || { echo "content snapshot does not exist: $CONTENT_SHA" >&2; return 1; }
  grep -qx "PROBLEMS_SOLUTION_CONTENT_SHA=$CONTENT_SHA" "$CONTENT_DIR/content.env"
}

assemble_deployment() {
  local deployment_tmp="$DEPLOYMENTS_DIR/.new-$DEPLOYMENT_SHA"
  rm -rf "$deployment_tmp" "$DEPLOYMENT_DIR"
  mkdir -p "$deployment_tmp/.runtime"
  ln -s "$APP_DIR" "$deployment_tmp/app"
  ln -s "$CONTENT_DIR/problems" "$deployment_tmp/problems"
  ln -s "$CONTENT_DIR/problem-sets" "$deployment_tmp/problem-sets"
  ln -s "$APP_DIR/config.yml" "$deployment_tmp/config.yml"
  local updated_at
  updated_at="$(date -u +'%Y-%m-%dT%H:%M:%SZ')"
  printf '{"targetRevision":"%s","updatedAt":"%s"}\n' \
    "$DEPLOYMENT_SHA" "$updated_at" > "$deployment_tmp/.runtime/content-revision.json"
  cat > "$deployment_tmp/deployment.env" <<EOF
PROBLEMS_SOLUTION_DEPLOYMENT_SHA=$DEPLOYMENT_SHA
PROBLEMS_SOLUTION_APP_SHA=$APP_SHA
PROBLEMS_SOLUTION_CONTENT_SHA=$CONTENT_SHA
PROBLEMS_SOLUTION_DEPENDENCY_HASH=$LOCK_HASH
PROBLEMS_SOLUTION_PLATFORM=$PLATFORM_KEY
PROBLEMS_SOLUTION_NODE_ABI=$NODE_ABI
EOF
  chown -R root:problems-solution "$deployment_tmp"
  chmod -R a=rX,u+w "$deployment_tmp"
  mv "$deployment_tmp" "$DEPLOYMENT_DIR"
}

start_candidate() {
  local candidate_port
  candidate_port="$(python3 - <<'PY'
import socket
with socket.socket() as sock:
    sock.bind(('127.0.0.1', 0))
    print(sock.getsockname()[1])
PY
)"

  set -a
  # shellcheck disable=SC1090
  source "$CONFIG_FILE"
  set +a

  runuser -u problems-solution --preserve-environment -- \
    env \
      NODE_ENV=production \
      HOST=127.0.0.1 \
      PORT="$candidate_port" \
      CONTENT_REVISION_PATH="$DEPLOYMENT_DIR/.runtime/content-revision.json" \
      bash -c 'cd "$1" && exec /usr/bin/node "$1/app/bin/www"' _ "$DEPLOYMENT_DIR" \
    >"$INCOMING_DIR/candidate.log" 2>&1 &
  CANDIDATE_PID=$!

  if ! live_ok "http://127.0.0.1:$candidate_port/api/health/live" 30 \
    || ! health_ok "http://127.0.0.1:$candidate_port/api/health/content" "$DEPLOYMENT_SHA" 1; then
    cat "$INCOMING_DIR/candidate.log" >&2 || true
    return 1
  fi

  kill "$CANDIDATE_PID" >/dev/null 2>&1 || true
  wait "$CANDIDATE_PID" >/dev/null 2>&1 || true
  CANDIDATE_PID=""
}

point_current_at() {
  local target="$1"
  local next_link="$BASE_DIR/.current-$DEPLOYMENT_SHA"
  rm -f "$next_link"
  ln -s "$target" "$next_link"
  mv -Tf "$next_link" "$CURRENT_LINK"
}

rollback() {
  echo "[native-deploy] rolling back" >&2
  systemctl stop "$SERVICE_NAME" >/dev/null 2>&1 || true

  if [[ -n "$OLD_DEPLOYMENT" && -d "$OLD_DEPLOYMENT" ]]; then
    point_current_at "$OLD_DEPLOYMENT"
    systemctl restart "$SERVICE_NAME"
    local old_revision
    old_revision="$(read_env_value "$OLD_DEPLOYMENT/deployment.env" PROBLEMS_SOLUTION_DEPLOYMENT_SHA 2>/dev/null || true)"
    [[ "$old_revision" =~ ^[0-9a-f]{40}$ ]] || old_revision="$(basename "$OLD_DEPLOYMENT")"
    health_ok http://127.0.0.1:3300/api/health/content "$old_revision" 30 || true
    DETAIL="rolled-back-to-$old_revision"
    return
  fi

  if [[ "$LEGACY_CONTAINER_RUNNING" == true ]]; then
    docker update --restart=unless-stopped problems-solution >/dev/null 2>&1 || true
    docker start problems-solution >/dev/null
    DETAIL="rolled-back-to-docker"
    return
  fi

  DETAIL="rollback-unavailable"
}

deployment_references() {
  local kind="$1"
  local candidate file variable
  case "$kind" in
    app) variable=PROBLEMS_SOLUTION_APP_SHA ;;
    content) variable=PROBLEMS_SOLUTION_CONTENT_SHA ;;
    *) return 2 ;;
  esac
  while IFS= read -r candidate; do
    file="$candidate/deployment.env"
    [[ -f "$file" ]] && read_env_value "$file" "$variable"
  done < <(find "$DEPLOYMENTS_DIR" -mindepth 1 -maxdepth 1 -type d ! -name '.new-*' -print)
}

prune_old_versions() {
  local candidate name
  while IFS= read -r candidate; do
    [[ "$candidate" == "$DEPLOYMENT_DIR" || "$candidate" == "$OLD_DEPLOYMENT" ]] && continue
    rm -rf "$candidate"
  done < <(find "$DEPLOYMENTS_DIR" -mindepth 1 -maxdepth 1 -type d ! -name '.new-*' -print)

  while IFS= read -r candidate; do
    name="$(basename "$candidate")"
    deployment_references app | grep -qx "$name" || rm -rf "$candidate"
  done < <(find "$APPS_DIR" -mindepth 1 -maxdepth 1 -type d ! -name '.new-*' -print)

  while IFS= read -r candidate; do
    name="$(basename "$candidate")"
    deployment_references content | grep -qx "$name" || rm -rf "$candidate"
  done < <(find "$CONTENTS_DIR" -mindepth 1 -maxdepth 1 -type d ! -name '.new-*' -print)
}

for command_name in curl zstd tar sha256sum systemctl runuser python3 flock getent groupadd useradd usermod; do
  command -v "$command_name" >/dev/null 2>&1 || { echo "missing command: $command_name" >&2; exit 1; }
done
[[ -x /usr/bin/node ]] || { echo "system Node.js is missing at /usr/bin/node" >&2; exit 1; }
remote_platform="$(/usr/bin/node -p "[process.platform, process.arch].join('-')")"
[[ "$remote_platform" == "$PLATFORM_KEY" ]] \
  || { echo "dependency platform mismatch: release=$PLATFORM_KEY VPS=$remote_platform" >&2; exit 1; }

if health_ok "$PUBLIC_HEALTH_URL" "" 2; then
  PUBLIC_WAS_HEALTHY=true
fi

if ! getent group problems-solution >/dev/null 2>&1; then
  groupadd --system problems-solution
fi
if ! id problems-solution >/dev/null 2>&1; then
  useradd --system --gid problems-solution --home-dir "$BASE_DIR" --shell /usr/sbin/nologin problems-solution
else
  usermod --home "$BASE_DIR" --shell /usr/sbin/nologin --gid problems-solution --groups '' --lock problems-solution
fi

mkdir -p "$APPS_DIR" "$CONTENTS_DIR" "$DEPENDENCIES_DIR/$LOCK_HASH" "$DEPLOYMENTS_DIR" "$BIN_DIR"
chmod 755 "$BASE_DIR" "$APPS_DIR" "$CONTENTS_DIR" "$DEPENDENCIES_DIR" \
  "$DEPENDENCIES_DIR/$LOCK_HASH" "$DEPLOYMENTS_DIR" "$BIN_DIR"
ensure_config
assemble_app
if find "$DEPENDENCY_DIR/node_modules" -type f -name '*.node' -print -quit | grep -q .; then
  remote_node_abi="$(/usr/bin/node -p 'process.versions.modules')"
  [[ "$remote_node_abi" == "$NODE_ABI" ]] \
    || { echo "native dependency ABI mismatch: release=$NODE_ABI VPS=$remote_node_abi" >&2; exit 1; }
fi
assemble_content
assemble_deployment

install -m 0644 "$SERVICE_FILE" "/etc/systemd/system/$SERVICE_NAME"
install -m 0755 "$INCOMING_DIR/deploy-native.sh" "$BIN_DIR/deploy-native.sh"
systemctl daemon-reload
systemctl enable "$SERVICE_NAME" >/dev/null

if [[ -L "$CURRENT_LINK" ]]; then
  OLD_DEPLOYMENT="$(readlink -f "$CURRENT_LINK")"
fi
if command -v docker >/dev/null 2>&1 && docker container inspect problems-solution >/dev/null 2>&1; then
  docker container inspect problems-solution > "$BASE_DIR/legacy-container.json"
  if [[ "$(docker container inspect --format '{{.State.Running}}' problems-solution)" == true ]]; then
    LEGACY_CONTAINER_RUNNING=true
  fi
fi

echo "[native-deploy] candidate check"
start_candidate

if [[ "$LEGACY_CONTAINER_RUNNING" == true ]]; then
  docker update --restart=no problems-solution >/dev/null
  docker stop -t 20 problems-solution >/dev/null
else
  systemctl stop "$SERVICE_NAME" >/dev/null 2>&1 || true
fi

point_current_at "$DEPLOYMENT_DIR"
systemctl restart "$SERVICE_NAME"

if ! live_ok http://127.0.0.1:3300/api/health/live 30 \
  || ! health_ok http://127.0.0.1:3300/api/health/content "$DEPLOYMENT_SHA" 1; then
  journalctl -u "$SERVICE_NAME" -n 120 --no-pager >&2 || true
  rollback
  exit 1
fi

if [[ "$PUBLIC_WAS_HEALTHY" == true ]] \
  && ! health_ok "$PUBLIC_HEALTH_URL" "$DEPLOYMENT_SHA" 15; then
  echo "[native-deploy] public health check failed" >&2
  rollback
  exit 1
fi
if [[ "$PUBLIC_WAS_HEALTHY" != true ]]; then
  echo "[native-deploy] public endpoint was already unhealthy; local health is authoritative" >&2
fi

if command -v docker >/dev/null 2>&1 && docker container inspect problems-solution >/dev/null 2>&1; then
  docker container rm problems-solution >/dev/null
fi

prune_old_versions
rm -rf "$INCOMING_DIR"
RESULT="success"
DETAIL="app=$APP_SHA content=$CONTENT_SHA"
echo "[native-deploy] deployed $DEPLOYMENT_SHA app=$APP_SHA content=$CONTENT_SHA"
