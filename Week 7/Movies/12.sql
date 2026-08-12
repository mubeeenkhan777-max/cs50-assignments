-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT title
FROM movies
WHERE EXISTS (
    SELECT 1
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE stars.movie_id = movies.id
      AND people.name = 'Jennifer Lawrence'
)
AND EXISTS (
    SELECT 1
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE stars.movie_id = movies.id
      AND people.name = 'Bradley Cooper'
);
