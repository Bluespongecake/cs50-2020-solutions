SELECT movies.title
FROM people
INNER JOIN stars ON people.id = stars.person_id
INNER JOIN movies ON stars.movie_id = movies.id --apparently according to w3schools.com, INNER JOIN is better syntactically as it is more clear
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"          --who the hell is Chadwick Boseman
ORDER BY rating DESC                            --nevermind I looked him up ive seen him before
LIMIT 5;

