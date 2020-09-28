SELECT DISTINCT(people.name)        --found DISTINCT operator on w3schools.com (again!!)
FROM stars
JOIN people ON stars.person_id = people.id
JOIN movies on stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY birth;
