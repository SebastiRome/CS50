SELECT title FROM
(SELECT movies.id FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON people.id = stars.person_id WHERE people.name = "Johnny Depp")
AS depp_movie JOIN movies ON movies.id = depp_movie.id JOIN stars ON stars.movie_id = movies.id JOIN people ON people.id = stars.person_id
WHERE people.name = "Helena Bonham Carter";