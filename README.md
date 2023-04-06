# Proiect Music Player

Nume Proiect : Online Music Services using classes in C++

Lista cu clasele :
* clasa Melodie - retine Titlul, Durata si numarul de Streamuri si contine supraincarcarea operatorului<<;
* clasa Gen_Muzical - retine denumirea genului muzical al albumului;
* clasa Album - preia din clasa Melodie toate obiectele, si face suma totala a Duratelor si Streamurilor;
* clasa Playlist - contine numele Playlistului si preia obiecte din clasa Album;
* clasa StreamingPlatform - contine supraincarcarea operatorului>> si preia numarul total de streamuri dintr-un album.

Lista cu functionalitati :
* prin clasa Album, putem afisa tracklistul unui album, alaturi de durata totala si genul muzical;
* prin clasa Playlist, daca un album are mai multe streamuri totale decat minimul streamurilor pentru un playlist, albumul este adaugat in playlist;
* prin clasa StreamingPlatform, citim de la tastatura o platforma de streaming, iar in output o sa se afiseze suma de bani ce a fost produs de album prin streamuri.
