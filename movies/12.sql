select
    title
from
    movies
join
    (select
        movie_id
    from
        (select
            movie_id
        from
            stars
        join
            people on stars.person_id = people.id where name = "Johnny Depp")
    where
        movie_id
    in
        (select
            movie_id
        from
            stars
        join people on stars.person_id = people.id where name = "Helena Bonham Carter"))
where
    movie_id = movies.id;
