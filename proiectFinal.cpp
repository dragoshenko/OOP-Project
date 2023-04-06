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
    string getGen(){
        return Denumire;
    }
};

class Album{

private:
    string Nume_Album;
    string Nume_Artist;
    vector<Melodie> tracks;
    int Streams_Album = 0;
    int Durata_Totala = 0;
    string Gen;

public:
    Album(string nume_album, string nume_artist){
        Nume_Album = nume_album;
        Nume_Artist = nume_artist;
    }

    Album(){}
    
    void addGenre(Gen_Muzical obj){
        Gen = obj.getGen();        
    }

    void addMelodie(Melodie track){
        tracks.push_back(track);
        Streams_Album += track.getStreams();
        Durata_Totala += track.getDurata();
    }

    int getTotalStreams(){
        return Streams_Album;
    }

    void printTracklisting() const {
        cout << "Tracklistul albumului " << "'" << Nume_Album << "'" << " (" << Gen << ")" << " (" << Durata_Totala << " de " << "secunde" << ")" << " de " << Nume_Artist << " :" << endl;
        for (int i = 0; i < tracks.size(); i++){
            cout << i+1 << ". " << tracks[i] << endl;
        }
    }
    
    string getNumeAlbum(){
        return Nume_Album;
    }

    string getNumeArtist(){
        return Nume_Artist;
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
    

    void addAlbum(Album album, int min_Streams);
    void printAlbums();

};

void Playlist::addAlbum(Album album, int min_Streams){
        if (album.getAlbumStreams() > min_Streams && count_albums < Max_Albums){
            albums[count_albums] = album;
            count_albums++;
        }
    }

void Playlist::printAlbums() {
        cout << "Albums in playlist \"" << Nume_Playlist << "\":" << endl;
        for (int i = 0; i < count_albums; i++) {
            cout << "- " << albums[i].getNumeAlbum() << " by " << albums[i].getNumeArtist() << endl;
        }
    }

class StreamingPlatform{

private:
    string Nume_Platforma;
    int Streams;

public:
    string& getNume(){
        return Nume_Platforma;
    }
    friend istream& operator>>(istream& in, StreamingPlatform& s){
        in >> s.Nume_Platforma;
        return in;
    }

    void addStreams(Album obj);
    void Pay_Per_Stream();
        
};

void StreamingPlatform::addStreams(Album obj){
        Streams = obj.getTotalStreams();
    }

void StreamingPlatform::Pay_Per_Stream(){
        if(Nume_Platforma == "Spotify")
            cout << "Albumul a produs " << Streams * 0.0033 << "$" << endl;
        else if(Nume_Platforma == "Apple_Music")
                cout << "Albumul a produs " << Streams * 0.01 << "$" << endl;
            else if(Nume_Platforma == "Tidal")
                    cout << "Albumul a produs " << Streams * 0.013 << "$" << endl;
                else if(Nume_Platforma == "Amazon_Music")
                        cout << "Albumul a produs " << Streams * 0.004 << "$" << endl;
                    else 
                        cout << "Aceasta platforma de streaming nu se afla in baza de date." << endl;
    }




int main()
{

    Playlist myPlaylist("Charts");
    Album A("TLOP", "Kanye West");  
    

    A.addGenre(Gen_Muzical("Experimental Hip Hop"));
    A.addMelodie(Melodie("Ultralight Beam", 190, 13000200));
    A.addMelodie(Melodie("Father Stretch My Hands Pt. 1", 190, 9482739));
    A.addMelodie(Melodie("Pt. 2", 210, 32198590));
    A.addMelodie(Melodie("Famous", 150, 9828235));
    myPlaylist.addAlbum(A, 1000000);
    A.printTracklisting();

    cout << endl;
    StreamingPlatform Platforma;
    cout << "Platforma : "; cin >> Platforma; cout << endl;
    Platforma.addStreams(A);
    Platforma.Pay_Per_Stream();
    
    cout << endl;

    Album B("Blonde", "Frank Ocean");
    B.addGenre(Gen_Muzical("Alternative R&B"));
    B.addMelodie(Melodie("Nikes", 190, 500300));
    B.addMelodie(Melodie("Ivy", 190, 120009));
    B.addMelodie(Melodie("Pink + White", 210, 3220));
    B.addMelodie(Melodie("Nights", 150, 98223));
    myPlaylist.addAlbum(B, 1000000);
    B.printTracklisting();

    cout << endl;
    StreamingPlatform Platforma2;
    cout << "Platforma : "; cin >> Platforma2; cout << endl;
    Platforma2.addStreams(B);
    Platforma2.Pay_Per_Stream();

    cout << endl;

    myPlaylist.printAlbums();
    
    return 0;
}
