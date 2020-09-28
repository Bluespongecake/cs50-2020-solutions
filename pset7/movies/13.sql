SELECT distinct(name)
FROM people
INNER JOIN stars on people.id = stars.person_id
Inner JOIN movies ON stars.movie_id = movies.id
WHERE movies.title IN(
    SELECT distinct(movies.title)
    FROM people
    Inner JOIN stars oN people.id = stars.person_id
    INNER JOIN movies on stars.movie_id = movies.id
    WHERE people.name = "Kevin Bacon" AND people.birth = 1958
        )
AND people.name != "Kevin Bacon";