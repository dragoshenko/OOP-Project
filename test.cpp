#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Melodie{

private:
    string Titlu;
    int Durata;
    int Streams;

public:
    Melodie(string titlu, int durata, int streams){
        Titlu = titlu;
        Durata = durata;
        Streams = streams;
    }

    string getTitlu(){
        return Titlu;
    }

    int getDurata(){
        return Durata;
    }

    int getStreams(){
        return Streams;
    }

    friend ostream& operator<<(ostream& os, const Melodie& track);

};

ostream& operator<<(ostream& os, const Melodie& track) {
    os << track.Titlu << " (" << track.Durata << " de " << "secunde)" << " - " << track.Streams << " streams" ;
    return os;
}

class Gen_Muzical{

private:
    string Denumire;

public:
    Gen_Muzical(string denumire){
        Denumire = denumire;
    }

};

class Album{

private:
    string Nume_Album;
    string Nume_Artist;
    vector<Melodie> tracks;
    int Streams_Album = 0;

public:
    Album(string nume_album, string nume_artist){
        Nume_Album = nume_album;
        Nume_Artist = nume_artist;
    }

    void addMelodie(Melodie track){
        tracks.push_back(track);
        Streams_Album += track.getStreams();
    }

    void printTracklisting() const {
        cout << "Tracklistul albumului " << Nume_Album << " de " << Nume_Artist << " :" << endl;
        for (int i = 0; i < tracks.size(); i++){
            cout << i+1 << ". " << tracks[i] << endl;
        }
    }

    int getAlbumStreams() const {
        return Streams_Album;
    }

};

class Playlist{

private:
    string Nume_Playlist;
    static const int Max_Albums = 100;
    Album albums[Max_Albums];
    int count_albums = 0;

public:
    Playlist(string nume_playlist) {
        Nume_Playlist = nume_playlist;
    }


    void addAlbum(Album album, int min_Streams){
        if (album.getAlbumStreams() > min_Streams && count_albums < Max_Albums){
            albums[count_albums] = album;
            count_albums++;
        }
    }

};
int main()
{
    //Melodie A = Melodie("WEED", 90, 1092);
    // A.Afisare();
    Album A("TLOP", "Kanye West");
    A.addMelodie(Melodie("Ultralight Beam", 190, 130002000));
    A.addMelodie(Melodie("Father Stretch My Hands Pt. 1", 190, 9482739));
    A.addMelodie(Melodie("Pt. 2", 210, 32198590));
    A.addMelodie(Melodie("Famous", 150, 9828235));

    A.printTracklisting();

    
    return 0;
}