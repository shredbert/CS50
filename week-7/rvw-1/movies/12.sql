-- SELECT title FROM movies
-- JOIN stars ON movies.id = stars.movie_id
-- -- JOIN people ON stars.movie_id = people.id
-- WHERE EXISTS (
--     SELECT person_id FROM stars
--     JOIN people ON stars.person_id = people.id
--     WHERE stars.movie_id = movies.id
--     AND people.name IN ('Johnny Depp', 'Helena Bonham Carter')
-- );

SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE EXISTS (
    SELECT 
);
