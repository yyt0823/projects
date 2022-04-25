SELECT name FROM
(SELECT artists.name as artist_name, songs.name FROM songs JOIN artists ON artists.id = songs.artist_id)
WHERE artist_name = "Post Malone";