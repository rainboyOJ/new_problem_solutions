import { loadConfig } from "./config.js";
import { createGatewayServer } from "./server.js";

// HTTP/LAN 启动入口：面向局域网中的 AI 客户端。
const config = loadConfig();
const gateway = createGatewayServer({ config });

await gateway.start();

process.stdout.write(`MCP LAN gateway started at ${gateway.baseUrl}\n`);

const shutdown = async () => {
  // 优雅退出，确保会话和端口都被正确释放。
  await gateway.stop();
  process.exit(0);
};

process.on("SIGINT", shutdown);
process.on("SIGTERM", shutdown);
