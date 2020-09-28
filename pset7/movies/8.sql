SELECT name 
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = "Toy Story";

--okey this one was a little harder but nothing compared to the rest of this course so far...