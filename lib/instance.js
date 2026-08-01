import ProblemManager from './problem.js';
import ProblemSetManager from './problem-set.js';
import ContentService from './content-service.js';

const problemManager = new ProblemManager({ auto_load: false });
const problemSetManager = new ProblemSetManager(problemManager, { auto_load: false });
const contentService = new ContentService({ problemManager, problemSetManager });

await contentService.initialize();

export default problemManager;
export { problemManager, problemSetManager, contentService };
