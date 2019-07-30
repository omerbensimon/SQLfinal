
#include <iostream>
#include "DB.hpp"
    
    using namespace std;
    
    int main(int argc, const char * argv[]) {
        bool flag = true;
        int option;
        cout << "Hello, Please wait while database is loading..." << endl;
        Database& db = Database::getInstance();
        cout << "Database ready !" << endl;
        while(flag) {
            cout << "Please choose an option from the menu followed by enter:" << endl << "1.  how many albums were recorded in date range" << endl << "2.  how many songs were recorded by musician recorded in date range" << endl << "3.  how many albums were recorded by musician in date range" << endl << "4.  what is the most popular instrument in all times" << endl << "5.  all instruments in some album" << endl << "6.  most busy producer in date range" << endl << "7.  most busy manafacturer" << endl << "8.  how many musicians recorded in all times" << endl << "9.  the most coporative musician" << endl << "10. most popular genere" << endl << "11. the most busy record technician who recorded the most songs in date range" << endl << "12. first album recorded in studio" << endl << "13. all the songs that is in two albums or more" << endl << "14. technician who participated in recording a whole album" << endl << "15. the most versitaile musician" <<endl<<"16. exit"<< endl;
            cin >> option;
            switch (option) {
                case 1: {
                    db.AlbumsInDateRange();
                    break;
                }
                case 2: {
                    db.songsPerMusicianInDateRange();
                    break;
                }
                case 3: {
                    db.AlbumsPerMusicianInDateRange(); 
                    break;
                }
                case 4: {
                    db.TheMostPopularInstrument();
                    break;
                }
                case 5: {
                    db.AllInstumentsInsomeAlbum();
                    break;
                }
                case 6: {
                    db.MostBusyProducer();
                    break;
                }
                case 7: {
                    db.MostBusyManafacturer();
                    break;
                }
                case 8: {
                    db.MusiciansInALLtimes();
                    break;
                }
                case 9: {
                    db.mostCopoMusician();
                    break;
                }
                case 10: {
                    db.MostPopularGenereInALLtimes();
                    break;
                }
                case 11: {
                    db.MostBusyTechInDateRange();
                    break;
                }
                case 12: {
                    db.firstAlbum();
                    break;
                }
                case 13: {
                    db.AllAlbumsInTwoORmore();
                    break;
                }
                case 14: {
                    db.TechnicianInAllAlbum(); 
                    break;
                }
                case 15: {
                    db.mostVers();
                    break;
                }
             
                case 16: {
                    cout << "Bye!" << endl << endl;
                    flag = false;
                    break;
                }
                default:
                    cout << "This is not an available option" << endl;
                    option = 11111;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
            }
        }
        return 0;
    }


