import express from 'express';
import path from 'path';
import ProblemManager from '../lib/problem.js';
import MarkdownRenderer from '../lib/markdown.js';

const router = express.Router();
const problemManager = new ProblemManager({ auto_load: true });

router.get('/', (req, res, next) => {
  const { q, oj, tag, page } = req.query;
  
  let problems = problemManager.getAll();
  
  if (q) {
    problems = problemManager.search(q);
  }
  
  if (oj) {
    problems = problems.filter(p => p.oj === oj);
  }
  
  if (tag) {
    problems = problems.filter(p => p.tags && p.tags.includes(tag));
  }
  
  const currentPage = parseInt(page) || 1;
  const { data, pagination } = paginate(problems, currentPage, 20);
  
  const tags = problemManager.getAllTags();
  const ojs = problemManager.getAllOJs();
  
  const current_filters = {
    query: q || '',
    currentOJ: oj || '',
    currentTag: tag || ''
  };
  
  res.render('index', {
    problems: data,
    pagination,
    tags,
    ojs,
    ...current_filters
  });
});

function paginate(problems, page, limit) {
  const offset = (page - 1) * limit;
  const total = problems.length;
  const totalPages = Math.ceil(total / limit);
  const data = problems.slice(offset, offset + limit);
  
  return {
    data,
    pagination: {
      total,
      page,
      limit,
      totalPages
    }
  };
}

router.get('/problems/:oj/:id', (req, res, next) => {
  const { oj, id } = req.params;
  
  const problem = problemManager.find(oj, id);
  
  if (!problem) {
    return next();
  }
  
  const md_path = path.join(process.cwd(), 'problems', problem.md_path);
  const renderer = new MarkdownRenderer(md_path);
  const html_content = renderer.toHTML();
  
  res.render('problem', {
    problem,
    content: html_content
  });
});

export default router;