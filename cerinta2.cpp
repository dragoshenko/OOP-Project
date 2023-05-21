#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <utility>
#include <memory>
#include <algorithm>
using namespace std;

class Exception1 : exception{
private:
    string Mesaj;

public:
    Exception1(string m) : Mesaj(m){}

    const char* what() const throw() override{
        return Mesaj.c_str();
    }
};


class interfataMelodie{
public:

    virtual string getTitlu() = 0;

    virtual int getDurata() = 0;

    virtual int getStreams() = 0;

    virtual ~interfataMelodie(){}
};


class Melodie : public interfataMelodie{

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
    
    virtual ~Melodie(){}

    string getTitlu() override{
        return Titlu;
    }

    int getDurata() override{
        if(Durata <= 0)
            throw Exception1("Durata nu poate fi mai mica sau egala cu 0.");
        return Durata;
    }

    int getStreams() override {
        if(Streams < 0)
            throw Exception1("Streams nu pot fi mai mici decat 0.");
        return Streams;
    }

    friend ostream& operator<<(ostream& os, const Melodie& track);

};

ostream& operator<<(ostream& os, const Melodie& track) {
    os << track.Titlu << " (" << track.Durata << " de " << "secunde)" << " - " << track.Streams << " streams" ;
    return os;
}



template <typename t> class Gen_Muzical{

private:
    t Denumire;

public:
    Gen_Muzical(t denumire){
        Denumire = denumire;
    }
    t getGen(){
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
    static int Numar_Albume;
    string Gen;
    static int Numar_Melodii;

public:
    Album(string nume_album, string nume_artist){
        Nume_Album = nume_album;
        Nume_Artist = nume_artist;
    }

    Album(){}

    static void printHeader() {
        cout << "-------------------------------------------------------------------------------------" << endl;
    }
    
    static void printFooter() {
        cout << "-------------------------------------------------------------------------------------" << endl;
    }

    static int getNumarAlbume(){
        return Numar_Albume;
    }

    static int incNumarAlbume(){
        Numar_Albume++;
    }

    static int getNumarMelodii(){
        return Numar_Melodii;
    }

    static int incNumarMelodii(){
        Numar_Melodii++;
    }

    void addGenre(Gen_Muzical<string> obj){
        Gen = obj.getGen();        
    }

    void addMelodie(Melodie track){
        incNumarMelodii();
        tracks.push_back(track);
        Streams_Album += track.getStreams();
        Durata_Totala += track.getDurata();
        if(Durata_Totala <= 0)
            throw Exception1("Durata nu poate fi mai mica sau egala cu 0.");
        if(getNumarMelodii() > 200)
            throw out_of_range("Numar maxim de melodii a fost intrecut.");
    }
       

    int getTotalStreams(){
        if(Streams_Album < 0)
            throw Exception1("Streams nu pot fi mai mici decat 0.");
        return Streams_Album;
    }

    void printTracklisting() const {
        printHeader();
        cout << "Tracklistul albumului" << " " << Numar_Albume << " " << "'" << Nume_Album << "'" << " (" << Gen << ")" << " (" << Durata_Totala << " de " << "secunde" << ")" << " de " << Nume_Artist << " :" << endl;
        for (int i = 0; i < tracks.size(); i++){
            cout << i+1 << ". " << tracks[i] << endl;
        }
        printFooter();
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

int Album::Numar_Albume = 0;

int Album::Numar_Melodii = 0;

class ExtendedAlbum : public Album {
private:
    int Year;

public:
    ExtendedAlbum(string nume_album, string nume_artist, int year) : Album(nume_album, nume_artist) {
        Year = year;
    }

    int getYear() const {
        return Year;
    }

    virtual void printExtended() = 0;
};

class ExtendedGenuri : public ExtendedAlbum {
private:
    string Genuri;

public:
    ExtendedGenuri(string nume_album, string nume_artist, int year, string genuri) : ExtendedAlbum(nume_album, nume_artist, year) {
        Genuri = genuri;
    }
    
    string getGenuri() {
        return Genuri;
    }
    void printExtended() override {
        cout << "Extended album: " << getNumeAlbum() << " by " << getNumeArtist() << " (" << getYear() << ")" << " (" << getGenuri() << ")" << endl;
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





bool comparareStreams(const unique_ptr<interfataMelodie>& melodie1, const unique_ptr<interfataMelodie>& melodie2) {
    return melodie1->getStreams() > melodie2->getStreams();
}

int main()
{


    Playlist myPlaylist("Charts");
    //Album A("TLOP", "Kanye West");  
    
    ExtendedGenuri A("TLOP", "Kanye West", 2016, "Experimental Hip Hop, Trap");
    A.incNumarAlbume();
    A.addGenre(Gen_Muzical<string>("Experimental Hip Hop"));
    try {
        A.addMelodie(Melodie("Ultralight Beam", 190, 13000200));
        A.addMelodie(Melodie("Father Stretch My Hands Pt. 1", 190, 9482739));
        A.addMelodie(Melodie("Pt. 2", 210, 32198590));
        A.addMelodie(Melodie("Famous", 150, 9828235));

    }catch (Exception1& e){
        cout << "Eroare" << e.what() << endl;

    }

    myPlaylist.addAlbum(A, 1000000);
    A.printExtended();
    A.printTracklisting();

    cout << endl;
    StreamingPlatform Platforma;
    cout << "Platforma : "; cin >> Platforma; cout << endl;
    Platforma.addStreams(A);
    Platforma.Pay_Per_Stream();
    
    cout << endl;

    //Album B("Blonde", "Frank Ocean");

    ExtendedGenuri B("Blonde", "Frank Ocean", 2016, "Alternative R&B, Art Pop");
    B.incNumarAlbume();
    B.addGenre(Gen_Muzical<string>("Alternative R&B"));
    try{
        B.addMelodie(Melodie("Nikes", 190, 500300));
        B.addMelodie(Melodie("Ivy", 190, 120009));
        B.addMelodie(Melodie("Pink + White", 210, 3220));
        B.addMelodie(Melodie("Nights", 150, 98223));
    }catch (Exception1& e){
        cout << "Eroare" << e.what() << endl;

    }
    myPlaylist.addAlbum(B, 1000000);
    B.printExtended();
    B.printTracklisting();

    cout << endl;
    StreamingPlatform Platforma2;
    cout << "Platforma : "; cin >> Platforma2; cout << endl;
    Platforma2.addStreams(B);
    Platforma2.Pay_Per_Stream();

    cout << endl;

    myPlaylist.printAlbums();

    vector<unique_ptr<interfataMelodie>> melodii;
    melodii.push_back(make_unique<Melodie>("Blood On The Leaves",100,150000000));
    melodii.push_back(make_unique<Melodie>("On Sight",150,48000000));
    melodii.push_back(make_unique<Melodie>("Send It Up",120,26528198));

    cout << endl;
    sort(melodii.begin(), melodii.end(), comparareStreams);

    for(auto& m : melodii){
        cout << m->getTitlu() << endl;
    }
    
    return 0;
}
