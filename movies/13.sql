SELECT distinct(people.name) FROM (SELECT movies.id FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON people.id = stars.person_id WHERE people.name = "Kevin Bacon" AND people.birth = "1958") AS bacon_film
JOIN movies ON movies.id = bacon_film.id
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name != "Kevin Bacon";