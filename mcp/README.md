# MCP LAN Gateway

Standalone MCP-oriented LAN gateway for the existing problem APIs:

- `GET /api/problems`
- `GET /api/problems/:oj/:id`

This service exposes:

- MCP protocol endpoint: `/mcp` (SDK Streamable HTTP transport)
- LAN fallback tool HTTP endpoints: `/tools/search_problems`, `/tools/get_problem_detail`
- Optional stdio MCP runtime for local MCP clients

## Requirements

- Node.js 18+ (fetch support)

## Install

```bash
cd mcp
npm install
```

## Configuration

Environment variables:

- `MCP_HOST` default `0.0.0.0`
- `MCP_PORT` default `3333`
- `TARGET_API_BASE_URL` required, for example `http://192.168.1.10:3000`
- `UPSTREAM_TIMEOUT_MS` default `5000`
- `MCP_AUTH_TOKEN` optional

Example:

```bash
MCP_HOST=0.0.0.0 \
MCP_PORT=3333 \
TARGET_API_BASE_URL=http://192.168.1.10:3000 \
UPSTREAM_TIMEOUT_MS=5000 \
npm start
```

Run stdio MCP transport:

```bash
TARGET_API_BASE_URL=http://127.0.0.1:3000 npm run start:stdio
```

## LAN Usage

### Health

```bash
curl http://127.0.0.1:3333/health
```

### JSON fallback endpoints

Search:

```bash
curl -X POST http://127.0.0.1:3333/tools/search_problems \
  -H 'content-type: application/json' \
  -d '{"query":"dp","oj":"poj","page":1,"limit":20}'
```

Detail:

```bash
curl -X POST http://127.0.0.1:3333/tools/get_problem_detail \
  -H 'content-type: application/json' \
  -d '{"oj":"poj","id":"3061"}'
```

Generic RPC form:

```bash
curl -X POST http://127.0.0.1:3333/rpc \
  -H 'content-type: application/json' \
  -d '{"tool":"search_problems","input":{"query":"dp"}}'
```

`/rpc` canonical payload uses `input`. `arguments` is still accepted for compatibility.

### SSE-style one-shot response

```bash
curl -N -X POST 'http://127.0.0.1:3333/tools/search_problems?sse=1' \
  -H 'content-type: application/json' \
  -H 'accept: text/event-stream' \
  -d '{"query":"dp"}'
```

### MCP protocol endpoint

The SDK MCP Streamable HTTP transport is mounted at `/mcp`.

- `POST /mcp` initialize/session messages
- `GET /mcp` SSE stream behavior handled by SDK transport
- `DELETE /mcp` session close handled by SDK transport

For clients that prefer stdio transport, use `npm run start:stdio`.

### Optional token auth

If `MCP_AUTH_TOKEN` is set, send either:

- `Authorization: Bearer <token>`
- or `x-mcp-auth-token: <token>`

## Output shape

`search_problems` returns exactly:

```json
{
  "items": [
    {
      "oj": "poj",
      "problem_id": "3061",
      "title": "Subsequence",
      "tags": ["two-pointers"],
      "url": "https://example.com/3061"
    }
  ],
  "pagination": {
    "total": 1,
    "page": 1,
    "limit": 20,
    "totalPages": 1
  }
}
```

`get_problem_detail` returns exactly:

```json
{
  "oj": "poj",
  "problem_id": "3061",
  "title": "Subsequence",
  "tags": ["two-pointers"],
  "url": "https://example.com/3061",
  "md_content": "# Subsequence",
  "html_content": "<p>body</p>"
}
```

## Errors and logs

- Error payload shape: `{ code, message, trace_id, details? }`
- Every tool request emits a log line with: `trace_id`, `tool`, `upstream`, `status`, `latency_ms`

## Test

```bash
npm test
```
