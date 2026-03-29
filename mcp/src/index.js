import { loadConfig } from "./config.js";
import { createGatewayServer } from "./server.js";

const config = loadConfig();
const gateway = createGatewayServer({ config });

await gateway.start();

process.stdout.write(`MCP LAN gateway started at ${gateway.baseUrl}\n`);

const shutdown = async () => {
  await gateway.stop();
  process.exit(0);
};

process.on("SIGINT", shutdown);
process.on("SIGTERM", shutdown);
