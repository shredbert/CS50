SELECT DISTINCT(movies.title) FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE stars.movie_id IN (
    SELECT movie_id FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Johnny Depp'
)
AND stars.movie_id IN (
    SELECT movie_id FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Helena Bonham Carter'
);
