select name from people join (select person_id from stars join movies on stars.movie_id = movies.id where year = 2004) on person_id = people.id order by birth;