import matter from 'gray-matter';

export default function parseFrontmatter(source) {
  // gray-matter caches every full source string forever when options are omitted.
  // Passing options disables that cache; ContentService owns the bounded cache.
  return matter(source, {});
}
