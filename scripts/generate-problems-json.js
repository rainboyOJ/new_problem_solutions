import ProblemManager from '../lib/problem.js';

const manager = new ProblemManager({ auto_load: false });

manager.init();
manager.save_problems();

console.log(`Generated problems.json with ${manager.getAll().length} problems.`);
