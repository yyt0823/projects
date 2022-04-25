select title from movies
join
(select rating, movie_id
from ratings
join
(select name, movie_id as Chad_movie_id from stars join people on stars.person_id = people.id where name = "Chadwick Boseman")
where ratings.movie_id = Chad_movie_id order by rating desc)
on movies.id = movie_id limit 5;

