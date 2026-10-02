import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const root = path.dirname(fileURLToPath(import.meta.url));
export default defineConfig({
  plugins: [react()],
  root,
  base: '/relations3-graph/',
  build: {
    outDir: path.resolve(root, '../public/relations3-graph'),
    emptyOutDir: true,
    manifest: true,
    rollupOptions: { output: {
      entryFileNames: 'assets/index.js',
      chunkFileNames: 'assets/[name]-[hash].js',
      assetFileNames: 'assets/[name][extname]',
    } },
  },
  server: { proxy: { '/api': 'http://127.0.0.1:3000' } },
});
