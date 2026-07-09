let input = '';

process.stdin.on('data', (chunk) => {
  input += chunk;
});

process.stdin.on('end', () => {
  const nums = input.trim().split(/\s+/).map(Number);
  console.log(nums[0] + nums[1]);
});
