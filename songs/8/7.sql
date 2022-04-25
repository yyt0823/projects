SELECT avg(energy) FROM
(SELECT artists.name as artist_name, songs.energy FROM songs JOIN artists ON artists.id = songs.artist_id)
WHERE artist_name = "Drake";