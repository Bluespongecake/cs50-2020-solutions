SELECT movies.title 
FROM people
INNER JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Johnny Depp" 
AND movies.title IN(
    SELECT movies.title FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    WHERE people.name LIKE "Helena Bonham Carter"
);

