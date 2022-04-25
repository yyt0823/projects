--people.name -> people.id -> stars.movie_id -> stars.person_id -> people.name



select
    *
from
    (select
        name
    from
        people
    join
        (select
            distinct person_id
        from
            stars
        where
            movie_id
        in
            (select
                movie_id
            from
                stars
            join
                (select
                    id
                from
                    people
                where
                    name = "Kevin Bacon" and birth = 1958)
            where
                id = stars.person_id))
    where
        person_id = people.id)
where
    name != "Kevin Bacon";
