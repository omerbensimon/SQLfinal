

#ifndef DB_h
#define DB_h
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iostream>

using namespace sql;
using namespace std;
#define DB_NAME "Music_Manage"
#define DB_HOST "tcp://127.0.0.1/"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASS "Shenkar2019"

class Database {
private:
    static Database *instance;
    
    Driver *driver;
    ConnectOptionsMap connection_properties;
    Database();
    
public:
    static Database& getInstance();
    Connection *getConnection();
    virtual ~Database() {}
    void AlbumsInDateRange();
    void songsPerMusicianInDateRange();
    void AlbumsPerMusicianInDateRange();
    void TheMostPopularInstrument();
    void AllInstumentsInsomeAlbum();
    void MostBusyProducer();
    void MostBusyManafacturer();
    void MusiciansInALLtimes();
    void mostCopoMusician();
    void MostPopularGenereInALLtimes();
    void MostBusyTechInDateRange();
    void firstAlbum();
    void AllAlbumsInTwoORmore();
    void TechnicianInAllAlbum();
    void mostVers();
};


#endif /* DB_h */
