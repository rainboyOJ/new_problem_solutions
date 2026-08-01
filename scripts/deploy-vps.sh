#!/usr/bin/env bash
set -euo pipefail

APP_DIR="${APP_DIR:-/srv/rbook}"
SERVICE_NAME="${SERVICE_NAME:-problems-solution}"
BRANCH="${BRANCH:-master}"
TARGET_REVISION="${TARGET_REVISION:-}"
NODE_ENV="${NODE_ENV:-production}"
COMPOSE_PROJECT_NAME="${COMPOSE_PROJECT_NAME:-problems-solution}"
IMAGE_REF="${IMAGE_REF:-ghcr.io/rainboyoj/new_problem_solutions:master}"
DEPLOY_IMAGE_REF="${DEPLOY_IMAGE_REF:-problems-solution:deploy}"
GHCR_USERNAME="${GHCR_USERNAME:-}"
GHCR_TOKEN_B64="${GHCR_TOKEN_B64:-}"
CONTENT_HEALTH_TOKEN_B64="${CONTENT_HEALTH_TOKEN_B64:-}"
PULL_TIMEOUT="${PULL_TIMEOUT:-300}"
SKIP_IMAGE_PULL="${SKIP_IMAGE_PULL:-false}"
HEALTH_URL="${HEALTH_URL:-http://127.0.0.1:3300}"
CONTENT_DRAIN_TIMEOUT="${CONTENT_DRAIN_TIMEOUT:-10}"
CONTENT_REFRESH_TIMEOUT="${CONTENT_REFRESH_TIMEOUT:-35}"

usage() {
  cat <<'EOF'
Usage: deploy-vps.sh [--help]

Deploy RBook on a VPS. Content-only deploys update the Git worktree and reload
the in-memory catalog without pulling an image or recreating the container.

Environment variables:
  APP_DIR, SERVICE_NAME, BRANCH, TARGET_REVISION
  IMAGE_REF, DEPLOY_IMAGE_REF, GHCR_USERNAME, GHCR_TOKEN_B64
  CONTENT_HEALTH_TOKEN_B64, SKIP_IMAGE_PULL, HEALTH_URL
  PULL_TIMEOUT, CONTENT_DRAIN_TIMEOUT, CONTENT_REFRESH_TIMEOUT
EOF
}

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  usage
  exit 0
fi

command -v curl >/dev/null 2>&1 || {
  echo "curl is required for deployment health checks." >&2
  exit 1
}
command -v python3 >/dev/null 2>&1 || {
  echo "python3 is required for deployment health checks." >&2
  exit 1
}

cd "$APP_DIR"

if docker compose version >/dev/null 2>&1; then
  compose=(docker compose)
elif command -v docker-compose >/dev/null 2>&1; then
  compose=(docker-compose)
else
  echo "Docker Compose is not installed." >&2
  exit 1
fi

if [[ -n "$CONTENT_HEALTH_TOKEN_B64" ]]; then
  CONTENT_HEALTH_TOKEN="$(printf '%s' "$CONTENT_HEALTH_TOKEN_B64" | base64 -d)"
else
  CONTENT_HEALTH_TOKEN=""
fi
export SERVICE_NAME NODE_ENV COMPOSE_PROJECT_NAME CONTENT_HEALTH_TOKEN

git fetch origin "$BRANCH"
if [[ -z "$TARGET_REVISION" ]]; then
  TARGET_REVISION="$(git rev-parse "origin/$BRANCH")"
fi
git cat-file -e "${TARGET_REVISION}^{commit}"

health_payload() {
  curl --silent --show-error --max-time 5 "$HEALTH_URL/api/health/content" 2>/dev/null || true
}

health_values() {
  python3 -c '
import json, sys
try:
    value = json.load(sys.stdin)
except Exception:
    print("invalid\t\t\t-1")
else:
    print("{}\t{}\t{}\t{}".format(
        value.get("state", ""),
        value.get("targetRevision") or "",
        value.get("activeRevision") or "",
        value.get("inFlightRequests", -1),
    ))
'
}

write_revision_handoff() {
  mkdir -p .runtime
  local target_file=".runtime/content-revision.json"
  local temp_file="${target_file}.tmp.$$"
  local updated_at
  updated_at="$(date -u +'%Y-%m-%dT%H:%M:%SZ')"
  printf '{"targetRevision":"%s","updatedAt":"%s"}\n' \
    "$TARGET_REVISION" "$updated_at" > "$temp_file"
  chmod 644 "$temp_file"
  mv -f "$temp_file" "$target_file"
}

print_detailed_health() {
  if [[ -z "$CONTENT_HEALTH_TOKEN" ]]; then
    echo "Content health is degraded; CONTENT_HEALTH_TOKEN is not configured." >&2
    return
  fi
  curl --silent --show-error --max-time 10 \
    -H "Authorization: Bearer $CONTENT_HEALTH_TOKEN" \
    "$HEALTH_URL/api/health/content/details" \
    | python3 -m json.tool >&2 || true
}

wait_for_drain() {
  local deadline=$((SECONDS + CONTENT_DRAIN_TIMEOUT))
  while (( SECONDS < deadline )); do
    local payload state target active in_flight
    payload="$(health_payload)"
    IFS=$'\t' read -r state target active in_flight <<< "$(printf '%s' "$payload" | health_values)"
    if [[ "$state" == "switching" && "$in_flight" == "0" ]]; then
      return 0
    fi
    sleep 0.25
  done
  return 1
}

wait_for_revision() {
  local deadline=$((SECONDS + CONTENT_REFRESH_TIMEOUT))
  while (( SECONDS <= deadline )); do
    local payload state target active in_flight
    payload="$(health_payload)"
    IFS=$'\t' read -r state target active in_flight <<< "$(printf '%s' "$payload" | health_values)"
    if [[ "$active" == "$TARGET_REVISION" && "$state" == "healthy" ]]; then
      echo "Content revision $TARGET_REVISION is healthy."
      return 0
    fi
    if [[ "$active" == "$TARGET_REVISION" && "$state" == "degraded" ]]; then
      echo "Content revision $TARGET_REVISION activated with isolated errors." >&2
      print_detailed_health
      return 2
    fi
    if [[ "$target" == "$TARGET_REVISION" && "$state" == "unavailable" ]]; then
      echo "Content revision $TARGET_REVISION could not build a catalog." >&2
      print_detailed_health
      return 3
    fi
    sleep 0.5
  done
  echo "Timed out waiting for content revision $TARGET_REVISION." >&2
  print_detailed_health
  return 4
}

wait_for_restored_revision() {
  local expected_revision="$1"
  local deadline=$((SECONDS + CONTENT_REFRESH_TIMEOUT))
  while (( SECONDS <= deadline )); do
    local payload state target active in_flight
    payload="$(health_payload)"
    IFS=$'\t' read -r state target active in_flight <<< "$(printf '%s' "$payload" | health_values)"
    if [[ "$active" == "$expected_revision" && ( "$state" == "healthy" || "$state" == "degraded" ) ]]; then
      return 0
    fi
    sleep 0.5
  done
  return 1
}

existing_container_id="$(docker container inspect --format '{{.Id}}' "$SERVICE_NAME" 2>/dev/null || true)"
hot_reload_available=false
if [[ "$SKIP_IMAGE_PULL" == "true" && -n "$existing_container_id" ]]; then
  container_running="$(docker container inspect --format '{{.State.Running}}' "$existing_container_id" 2>/dev/null || true)"
  container_image="$(docker container inspect --format '{{.Image}}' "$existing_container_id" 2>/dev/null || true)"
  if [[ "$container_running" == "true" ]] && docker image inspect "$container_image" >/dev/null 2>&1; then
    hot_reload_available=true
  fi
fi

if [[ "$hot_reload_available" == "true" ]]; then
  echo "Preparing content-only deployment for $TARGET_REVISION."
  current_payload="$(health_payload)"
  IFS=$'\t' read -r current_state current_target previous_revision current_in_flight \
    <<< "$(printf '%s' "$current_payload" | health_values)"
  docker kill --signal=SIGUSR2 "$existing_container_id" >/dev/null

  if ! wait_for_drain; then
    echo "Content requests did not drain within ${CONTENT_DRAIN_TIMEOUT}s; Git was not modified." >&2
    docker kill --signal=SIGHUP "$existing_container_id" >/dev/null || true
    if [[ -n "$previous_revision" ]] && ! wait_for_restored_revision "$previous_revision"; then
      echo "The previous content revision did not recover after drain timeout." >&2
    fi
    exit 1
  fi

  git reset --hard "$TARGET_REVISION"
  write_revision_handoff
  docker kill --signal=SIGHUP "$existing_container_id" >/dev/null
  wait_for_revision
  exit $?
fi

if [[ "$SKIP_IMAGE_PULL" == "true" ]]; then
  echo "A running container and its local image are required for hot reload; using normal deployment."
  SKIP_IMAGE_PULL=false
fi

git reset --hard "$TARGET_REVISION"
write_revision_handoff

if [[ "$SKIP_IMAGE_PULL" != "true" && -n "$GHCR_USERNAME" && -n "$GHCR_TOKEN_B64" ]]; then
  printf '%s' "$GHCR_TOKEN_B64" | base64 -d \
    | docker login ghcr.io -u "$GHCR_USERNAME" --password-stdin
fi

if [[ "$SKIP_IMAGE_PULL" != "true" ]]; then
  pull_candidates=(
    "${IMAGE_REF/ghcr.io/ghcr.nju.edu.cn}"
    "gh-proxy.org/docker/$IMAGE_REF"
    "$IMAGE_REF"
  )
  pulled_image=""
  for candidate in "${pull_candidates[@]}"; do
    echo "Pulling image candidate: $candidate"
    if timeout "$PULL_TIMEOUT" docker pull "$candidate"; then
      pulled_image="$candidate"
      break
    fi
    echo "Failed to pull image candidate: $candidate" >&2
  done
  if [[ -z "$pulled_image" ]]; then
    echo "Failed to pull any image candidate for $IMAGE_REF" >&2
    exit 1
  fi
  docker tag "$pulled_image" "$DEPLOY_IMAGE_REF"
fi

export IMAGE_REF="$DEPLOY_IMAGE_REF"

if [[ -n "$existing_container_id" ]]; then
  existing_project="$(docker container inspect --format '{{ index .Config.Labels "com.docker.compose.project" }}' "$existing_container_id")"
  existing_service="$(docker container inspect --format '{{ index .Config.Labels "com.docker.compose.service" }}' "$existing_container_id")"
  if [[ "$existing_project" != "$COMPOSE_PROJECT_NAME" || "$existing_service" != "problems-solution" ]]; then
    echo "Removing container $SERVICE_NAME before Compose takes ownership."
    docker container rm -f "$existing_container_id"
  fi
fi

"${compose[@]}" up -d --force-recreate --remove-orphans
"${compose[@]}" ps
wait_for_revision
