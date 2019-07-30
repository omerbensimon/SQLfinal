

#include "DB.hpp"
#include <string>

void cinClearing () {
    string temp;
    getline(cin, temp);
}

Database *Database::instance = 0;

Database::Database() : driver(get_driver_instance()) {
    connection_properties["hostName"] = DB_HOST;
    connection_properties["port"] = DB_PORT;
    connection_properties["userName"] = DB_USER;
    connection_properties["password"] = DB_PASS;
    connection_properties["OPT_RECONNECT"] = true;
    // use database
    try {
        Connection *con = driver->connect(connection_properties);
        try {
            con->setSchema(DB_NAME);
        }
        catch (SQLException &e) {
            Statement *stmt = con->createStatement();
            string q = "CREATE DATABASE IF NOT EXISTS ";
            q.append(DB_NAME);
            stmt->execute(q);
            con->setSchema(DB_NAME); // switch database
  
            //create Musician Table
            stmt->execute("CREATE TABLE IF NOT EXISTS Musician( "
                          "musician_ID INT(9) NOT NULL PRIMARY KEY, "
                          "musician_name VARCHAR(45) NOT NULL, "
                          "address VARCHAR(45) NOT NULL, "
                          "phone_number INT(10) NOT NULL"
                          ") ENGINE=InnoDB");
            
            //fill Musician table
            
            stmt->execute("INSERT INTO Musician VALUES ('312111111', 'Idan Raichel', '12 Bograshov Street, Tel Aviv', 0539894441)");
            stmt->execute("INSERT INTO Musician VALUES ('312222222', 'David Broza', '123 Basel Street, Tel Aviv', 0540987654)");
            stmt->execute("INSERT INTO Musician VALUES ('312333333', 'Aviv Geffen', '111 Yafe Nof Street, Haifa', 0510957463)");
            stmt->execute("INSERT INTO Musician VALUES ('312444444', 'Ester Rada', '8 Yehodit Street, Ramat Gan', 0500987680)");
            stmt->execute("INSERT INTO Musician VALUES ('312555555', 'Nathan Goshen', '60 Tchernikhovski Street, Tel Aviv', 0501234321)");
            stmt->execute("INSERT INTO Musician VALUES ('312666666', 'Omer Adam', '9 Sgula Street, Tel Aviv', 0520987654)");
            stmt->execute("INSERT INTO Musician VALUES ('312777777', 'Aviv Alush', '12 Nakhmani Street, Tel Aviv', 0509899768)");
            stmt->execute("INSERT INTO Musician VALUES ('312888888', 'Meir Ariel', '13 Herzl Street, Tel Aviv', 0598766789)");
            stmt->execute("INSERT INTO Musician VALUES ('312999999', 'Yoni Bloch', '54 Dizengoff Street, Tel Aviv', 0512343211)");
            stmt->execute("INSERT INTO Musician VALUES ('312000000', 'Asaf Avidan', '8 Barzilai Street, Tel Aviv', 0587655678)");
            
            //create Player Table
           stmt->execute ("CREATE TABLE IF NOT EXISTS Player ("
                          "musicianID INT(9) NOT NULL PRIMARY KEY,"
                          "FOREIGN KEY (`musicianID`) REFERENCES `Musician` (`musician_ID`)"
                          "ON DELETE CASCADE"
                          ") ENGINE=InnoDB");
            
                //fill Player table
            stmt->execute("INSERT INTO Player VALUES ('312000000')");
            stmt->execute("INSERT INTO Player VALUES ('312111111')");
            stmt->execute("INSERT INTO Player VALUES ('312222222')");
            stmt->execute("INSERT INTO Player VALUES ('312333333')");
            stmt->execute("INSERT INTO Player VALUES ('312888888')");
            stmt->execute("INSERT INTO Player VALUES ('312999999')");

            
            
            
            //create Singer Table
            stmt->execute ("CREATE TABLE IF NOT EXISTS Singer ("
                           "musicianID INT(9) NOT NULL PRIMARY KEY,"
                           "FOREIGN KEY (`musicianID`) REFERENCES `Musician` (`musician_ID`)"
                           "ON DELETE CASCADE"
                           ") ENGINE=InnoDB");
            
            //fill Singer table
            stmt->execute("INSERT INTO Singer VALUES ('312000000')");
            stmt->execute("INSERT INTO Singer VALUES ('312111111')");
            stmt->execute("INSERT INTO Singer VALUES ('312222222')");
            stmt->execute("INSERT INTO Singer VALUES ('312333333')");
            stmt->execute("INSERT INTO Singer VALUES ('312444444')");
            stmt->execute("INSERT INTO Singer VALUES ('312555555')");
            stmt->execute("INSERT INTO Singer VALUES ('312999999')");
            stmt->execute("INSERT INTO Singer VALUES ('312666666')");
            stmt->execute("INSERT INTO Singer VALUES ('312888888')");

         
            
            //create instrument Table
            stmt->execute("CREATE TABLE IF NOT EXISTS Instrument( "
                          "instrument_code INT(9) NOT NULL,"
                          "instrument_ID INT(9) NOT NULL , "
                          "typeName VARCHAR(10) NOT NULL, "
                          "manuName VARCHAR(45) NOT NULL,"
                          "PRIMARY KEY (instrument_code)"
                          ") ENGINE=InnoDB");
            
            
            //fill instrument Table
            stmt->execute("INSERT INTO Instrument VALUES ('1','1', 'Guitar', 'yamaha')");
            stmt->execute("INSERT INTO Instrument VALUES ('2','1', 'Guitar', 'pioneer')");
            stmt->execute("INSERT INTO Instrument VALUES ('3','2', 'Piano', 'pioneer')");
            stmt->execute("INSERT INTO Instrument VALUES ('4','3', 'Drums', 'pioneer')");
            stmt->execute("INSERT INTO Instrument VALUES ('5','3', 'Drums', 'yamaha')");
            stmt->execute("INSERT INTO Instrument VALUES ('6','4', 'Bass', 'yamaha')");
            stmt->execute("INSERT INTO Instrument VALUES ('7','5', 'Violin', 'yamaha')");
            stmt->execute("INSERT INTO Instrument VALUES ('8','6', 'Cello', 'yamaha')");
            stmt->execute("INSERT INTO Instrument VALUES ('9','7', 'Piccolo', 'yamaha')");
            stmt->execute("INSERT INTO Instrument VALUES ('10','8', 'Saxophone', 'yamaha')");
            stmt->execute("INSERT INTO Instrument VALUES ('11','9', 'Clarinet', 'pioneer')");
            stmt->execute("INSERT INTO Instrument VALUES ('12','10', 'Tuba', 'pioneer')");

            
            //create Musician_Instrument Table
            stmt->execute ("CREATE TABLE IF NOT EXISTS Musician_Instrument ("
                           "musicianID INT(9) NOT NULL,"
                           "instrumentCode INT(9) NOT NULL,"
                           "FOREIGN KEY (`musicianID`) REFERENCES `Musician` (`musician_ID`)"
                           "ON DELETE CASCADE,"
                           "FOREIGN KEY (`instrumentCode`) REFERENCES `Instrument` (`instrument_code`)"
                           "ON DELETE CASCADE,"
                           "PRIMARY KEY (musicianID,instrumentCode)"
                           ") ENGINE=InnoDB");
            
            //fill Musician_Instrument Table
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312000000', '1')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312111111', '1')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312222222', '3')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312333333', '4')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312555555', '3')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312888888', '9')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312999999', '7')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312000000', '2')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312555555', '7')");
            stmt->execute("INSERT INTO Musician_Instrument VALUES ('312999999', '5')");

            
            //create Album Table
            stmt->execute("CREATE TABLE IF NOT EXISTS Album( "
                          "album_ID INT(9) NOT NULL PRIMARY KEY, "
                          "album_name VARCHAR(45) NOT NULL, "
                          "RecordStartDate DATETIME NOT NULL, "
                          "RecordEndDate DATETIME NOT NULL"
                          ") ENGINE=InnoDB");
            
            //fill Album Table
                stmt->execute("INSERT INTO Album VALUES ('1', 'Now 19', '2019-3-9', '2019-5-9')");
                stmt->execute("INSERT INTO Album VALUES ('2', 'israeli Songs', '2012-3-9', '2012-4-9')");
                stmt->execute("INSERT INTO Album VALUES (3, 'collection', '1997-9-24', '1997-10-10')");
                stmt->execute("INSERT INTO Album VALUES ('4', 'IDF Songs', '1973-9-24', '1973-9-28')");
                stmt->execute("INSERT INTO Album VALUES ('5', 'indie folk', '1973-9-27', '1973-9-29')");
                stmt->execute("INSERT INTO Album VALUES ('6', 'Holiday Edition', '2012-3-10', '2012-3-11')");
                stmt->execute("INSERT INTO Album VALUES ('7', 'Circles', '2012-3-11', '2012-3-12')");
                stmt->execute("INSERT INTO Album VALUES ('8', 'Love Songs', '2012-3-12', '2012-3-13')");
                stmt->execute("INSERT INTO Album VALUES ('9', 'classics', '2012-3-13', '2012-3-14')");
                stmt->execute("INSERT INTO Album VALUES ('10', 'The 80s', '2012-3-14', '2012-3-15')");

        
            //create Producer Table
            stmt->execute("CREATE TABLE IF NOT EXISTS Producer( "
                          "producer_ID INT(9) NOT NULL PRIMARY KEY, "
                          "proname VARCHAR(45) NOT NULL "
                          ") ENGINE=InnoDB");
            
            
            //fill Producer Table
            stmt->execute("INSERT INTO Producer VALUES (311111111 , 'Gad Fra')");
            stmt->execute("INSERT INTO Producer VALUES (311111112 , 'Nurit Fra')");
            stmt->execute("INSERT INTO Producer VALUES (311111113 , 'Maya Shaan')");
            stmt->execute("INSERT INTO Producer VALUES (311111114 , 'Ariel Zev')");
            stmt->execute("INSERT INTO Producer VALUES (311111116 , 'Tal Cohen')");
            stmt->execute("INSERT INTO Producer VALUES (311111117 , 'Danielle levi')");
            stmt->execute("INSERT INTO Producer VALUES (311111118 , 'Yossi levi')");
            stmt->execute("INSERT INTO Producer VALUES (311111119 , 'Hila dudo')");
            stmt->execute("INSERT INTO Producer VALUES (311111120 , 'Alon Abutbul')");


            //create Technician Table
            stmt->execute("CREATE TABLE IF NOT EXISTS Technician( "
                          "technician_ID INT(9) NOT NULL PRIMARY KEY, "
                          "techname VARCHAR(45) NOT NULL "
                          ") ENGINE=InnoDB");
            
            
            //fill Technician Table
            stmt->execute("INSERT INTO Technician VALUES (321111111 , 'Hili Doron')");
            stmt->execute("INSERT INTO Technician VALUES (321111112 , 'Roni reisman')");
            stmt->execute("INSERT INTO Technician VALUES (321111113 , 'Danielle lev')");
            stmt->execute("INSERT INTO Technician VALUES (321111114 , 'Sagi Shoshan')");
            stmt->execute("INSERT INTO Technician VALUES (321111115 , 'Or Abu')");
            stmt->execute("INSERT INTO Technician VALUES (321111116 , 'Yael Heker')");
            stmt->execute("INSERT INTO Technician VALUES (321111117 , 'Alon Zemer')");
            stmt->execute("INSERT INTO Technician VALUES (321111118 , 'Ron Ziper')");
            stmt->execute("INSERT INTO Technician VALUES (321111119 , 'Yael Fra')");
            stmt->execute("INSERT INTO Technician VALUES (321111120 , 'Aviv leibo')");

            
            //create Album_Producer Table
            stmt->execute ("CREATE TABLE IF NOT EXISTS Album_Producer ("
                           "albumID INT(9) NOT NULL,"
                           "producerID INT(9) NOT NULL,"
                           "FOREIGN KEY (`albumID`) REFERENCES `Album` (`album_ID`)"
                           "ON DELETE CASCADE,"
                           "FOREIGN KEY (`producerID`) REFERENCES `Producer` (`producer_ID`)"
                           "ON DELETE CASCADE,"
                           "PRIMARY KEY(albumID,producerID)"
                           ") ENGINE=InnoDB");
            
            //fill Album_Producer Table
            stmt->execute("INSERT INTO Album_Producer VALUES (1 ,  311111111)");
            stmt->execute("INSERT INTO Album_Producer VALUES (2 ,  311111112)");
            stmt->execute("INSERT INTO Album_Producer VALUES (2 ,  311111113)");
            stmt->execute("INSERT INTO Album_Producer VALUES (3 ,  311111114)");
            stmt->execute("INSERT INTO Album_Producer VALUES (3 ,  311111116)");
            stmt->execute("INSERT INTO Album_Producer VALUES (4 ,  311111116)");
            stmt->execute("INSERT INTO Album_Producer VALUES (4 ,  311111117)");
            stmt->execute("INSERT INTO Album_Producer VALUES (4 ,  311111118)");
            stmt->execute("INSERT INTO Album_Producer VALUES (5 ,  311111118)");
            stmt->execute("INSERT INTO Album_Producer VALUES (6 ,  311111118)");
            stmt->execute("INSERT INTO Album_Producer VALUES (7 ,  311111118)");
            stmt->execute("INSERT INTO Album_Producer VALUES (8 ,  311111118)");
            stmt->execute("INSERT INTO Album_Producer VALUES (9 ,  311111118)");
            stmt->execute("INSERT INTO Album_Producer VALUES (10 ,  311111111)");


            

            //create MusicalNumber
            stmt->execute("CREATE TABLE IF NOT EXISTS MusicalNumber( "
                          "musical_ID INT(9) NOT NULL PRIMARY KEY, "
                          "musical_name VARCHAR(45) NOT NULL, "
                          "author_name VARCHAR(45) NOT NULL, "
                          "compsure_name VARCHAR(45) NOT NULL, "
                          "genere VARCHAR(10) NOT NULL, "
                          "RecordDate DATETIME NOT NULL, "
                          "length_sec INT(9) NOT NULL, "
                          "technicianID INT(9) NOT NULL,"
                          "FOREIGN KEY (`technicianID`) REFERENCES `Technician` (`technician_ID`)"
                          "ON DELETE CASCADE"
                          ") ENGINE=InnoDB");
            
           //fill MusicalNumber

            stmt->execute("INSERT INTO MusicalNumber VALUES ('1','Mimaamakim', 'john mayer','shlomo arzi', 'Classic','2019-3-10','186','321111111')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('2','IDF march', 'john mayer','shlomo arzi', 'Indie','2012-4-10','190','321111112')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('3','Love is all you need', 'john mayer','john mayer', 'Classic','2012-3-11 ','194','321111113')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('4','beautiful song', 'john mayer','john mayer', 'Classic','2012-3-13 ','198','321111112')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('5','someone  to love', 'john mayer','john mayer', 'Indie','2012-3-14 ','202','321111113')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('6','Tik Tok', 'elthon john','shlomo arzi', 'Rock','2012-3-15 ','202','321111111')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('7','children of 73', 'elthon john','shlomo arzi', 'Classic','1975-3-10 ','210','321111111')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('8','everything', 'elthon john','shlomo arzi', 'Classic','2012-3-12 ','214','321111114')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('9','colors of the wind', 'elthon john','shlomo arzi', 'Classic','2012-3-13 ','218','321111116')");
            stmt->execute("INSERT INTO MusicalNumber VALUES ('10','gravity', 'elthon john','shlomo arzi', 'Pop','1999-3-14 ','222','321111116')");
            
            //create MusicalNumber_Player_Instrument
            stmt->execute("CREATE TABLE IF NOT EXISTS MusicalNumber_Player_Instrument( "
                          "musicalID INT(9) NOT NULL, "
                          "musicianID INT(9) NOT NULL, "
                          "instrumentCode INT(9) NOT NULL, "
                          "FOREIGN KEY (`musicalID`) REFERENCES `MusicalNumber` (`musical_ID`)"
                          "ON DELETE CASCADE,"
                          "FOREIGN KEY (`musicianID`) REFERENCES `Musician` (`musician_ID`)"
                          "ON DELETE CASCADE,"
                          "FOREIGN KEY (`instrumentCode`) REFERENCES `Instrument` (`instrument_code`)"
                          "ON DELETE CASCADE,"
                          "PRIMARY KEY(musicalID,musicianID,instrumentCode)"
                          ") ENGINE=InnoDB");
            
            //fill MusicalNumber_Player_Instrument
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (1,312000000, 1)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (1,312111111, 2)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (1,312888888, 11)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (2,312000000, 2)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (2,312555555, 9)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (2,312111111, 1)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (3,312888888, 11)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (4,312555555, 4)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (5,312000000, 3)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (6,312555555, 4)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (6,312888888, 11)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (7,312888888, 11)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (8,312999999, 9)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (9,312000000 , 2)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (10,312111111, 2)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (10,312222222, 4)");
                    stmt->execute("INSERT INTO MusicalNumber_Player_Instrument VALUES (10,312555555, 9)");


            
            

            //create MusicalNumber_Singer
            stmt->execute("CREATE TABLE IF NOT EXISTS MusicalNumber_Singer( "
                          "musicalID INT(9) NOT NULL, "
                          "musicianID INT(9) NOT NULL, "
                          "FOREIGN KEY (`musicalID`) REFERENCES `MusicalNumber` (`musical_ID`)"
                          "ON DELETE CASCADE,"
                          "FOREIGN KEY (`musicianID`) REFERENCES `Musician` (`musician_ID`)"
                          "ON DELETE CASCADE,"
                          "PRIMARY KEY(musicalID,musicianID)"
                          ") ENGINE=InnoDB");
            
            
            //fill MusicalNumber_Singer
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (1 ,  312000000)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (2 ,  312111111)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (2 ,  312222222)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (3 ,  312333333)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (4 ,  312444444)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (4 ,  312555555)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (5 ,  312666666)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (6 ,  312000000)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (6 ,  312111111)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (7 ,  312999999)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (7 ,  312777777)");
            stmt->execute("INSERT INTO MusicalNumber_Singer VALUES (7 ,  312555555)");


            //create Album_MusicalNumber
            
            stmt->execute("CREATE TABLE IF NOT EXISTS Album_MusicalNumber( "
                          "albumID INT(9) NOT NULL, "
                          "musicalID INT(9) NOT NULL, "
                          "FOREIGN KEY (`albumID`) REFERENCES `Album` (`album_ID`)"
                          "ON DELETE CASCADE,"
                          "FOREIGN KEY (`musicalID`) REFERENCES `MusicalNumber` (`musical_ID`)"
                          "ON DELETE CASCADE,"
                          "PRIMARY KEY(musicalID,albumID)"
                          ") ENGINE=InnoDB");
            
            //fill Album_MusicalNumber
            
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (1 ,  1)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (1 ,  2)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (1 ,  3)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (2 ,  7)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (3 ,  7)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (4 ,  7)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (5 ,  7)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (6 ,  7)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (7 ,  3)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (8 ,  8)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (9 ,  5)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (10 ,  9)");
            stmt->execute("INSERT INTO Album_MusicalNumber VALUES (10 ,  10)");

            delete stmt;
        }
        
        delete con;
    }
    
    
    
    catch (SQLException &e) {
        cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
        throw e;
    }
}



Database & Database::getInstance() {
    if (Database::instance == 0) {
        instance = new Database();
    }
    return *instance;
}

Connection * Database::getConnection() {
    try {
        Connection *con = driver->connect(connection_properties);
        con->setSchema(DB_NAME);
        return con;
    } catch (SQLException &e) {
        cout << e.what();
    }
    
    
    return 0;
}

void Database::AlbumsInDateRange() {
    string d1, d2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> d1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cin >> d2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT count(*) as album_num FROM Album where RecordEndDate between ? and ?");
    pstmt->setString(1, d1);
    pstmt->setString(2, d2);
    ResultSet *row = pstmt->executeQuery();
    if(row->first()) {
        cout <<"\n"<<"Albums Recorded between "+d1+" and "+d2+": "<<"\n"<<row->getUInt(1) << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}



void Database::songsPerMusicianInDateRange() {
    string d1, d2,name;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> d1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cin >> d2;
    cout << "please enter musician name" << endl;
    cinClearing();
    getline(cin,name);
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT Count(*) "+"\n";
    stat = stat +"FROM   (SELECT recorddate "+"\n";
    stat = stat +"        FROM   musicalnumber "+"\n";
    stat = stat +"        WHERE  musical_id IN (SELECT musicalid "+"\n";
    stat = stat +"                              FROM   (SELECT musicalid, "+"\n";
    stat = stat +"                                             musicianid "+"\n";
    stat = stat +"                                      FROM   musicalnumber_player_instrument "+"\n";
    stat = stat +"                                      UNION "+"\n";
    stat = stat +"                                      SELECT musicalid, "+"\n";
    stat = stat +"                                             musicianid "+"\n";
    stat = stat +"                                      FROM   musicalnumber_singer) A "+"\n";
    stat = stat +"                              WHERE  A.musicianid = (SELECT musician_id "+"\n";
    stat = stat +"                                                     FROM   musician "+"\n";
    stat = stat +"                                                     WHERE "+"\n";
    stat = stat +"                                     musician_name = ?))) S "+"\n";
    stat = stat +"WHERE  S.recorddate BETWEEN ? AND ?;";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    pstmt->setString(1, name);
    pstmt->setString(2, d1);
    pstmt->setString(3, d2);
    ResultSet *row = pstmt->executeQuery();
    if(row->first()) {
        cout <<"\n"<<"Songs Recorded between "+d1+" and "+d2+" by "+name+": "<<"\n"<<row->getUInt(1) << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}



void Database:: AlbumsPerMusicianInDateRange()
{
    string d1, d2,name;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> d1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cin >> d2;
    cout << "please enter musician name" << endl;
    cinClearing();
    getline(cin,name);
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT COUNT(*) FROM (SELECT distinct albumID FROM Album_MusicalNumber WHERE musicalID IN (SELECT musical_ID FROM   (SELECT * FROM   musicalnumber "+"\n";
    stat = stat +"WHERE  musical_id IN (SELECT musicalid "+"\n";
    stat = stat +"                              FROM   (SELECT musicalid, "+"\n";
    stat = stat +"                                             musicianid "+"\n";
    stat = stat +"                                      FROM   musicalnumber_player_instrument "+"\n";
    stat = stat +"                                      UNION "+"\n";
    stat = stat +"                                      SELECT musicalid, "+"\n";
    stat = stat +"                                             musicianid "+"\n";
    stat = stat +"                                      FROM   musicalnumber_singer) A "+"\n";
    stat = stat +"                              WHERE  A.musicianid = (SELECT musician_id "+"\n";
    stat = stat +"                                                     FROM   musician "+"\n";
    stat = stat +"                                                     WHERE "+"\n";
    stat = stat +"                                     musician_name = ?))) S "+"\n";
    stat = stat +"WHERE  S.recorddate BETWEEN ? AND ? ))B;";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    pstmt->setString(1, name);
    pstmt->setString(2, d1);
    pstmt->setString(3, d2);
    ResultSet *row = pstmt->executeQuery();
    if(row->first()) {
        cout <<"\n"<<"Albums Recorded between "+d1+" and "+d2+" by "+name+": "<<"\n"<<row->getUInt(1) << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database:: TheMostPopularInstrument()
{

    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT distinct typeName FROM Instrument where instrument_code=(SELECT instrument_code most_comm FROM ( "+"\n";
    stat = stat +"SELECT  instrument_id, COUNT(*) songs_sum FROM "+"\n";
    stat = stat +"(SELECT musicalid, i.instrument_code FROM instrument as i "+"\n";
    stat = stat +"join MusicalNumber_Player_Instrument as mnpi ON mnpi.instrumentcode=i.instrument_code "+"\n";
    stat = stat +") sum_s "+"\n";
    stat = stat +"GROUP BY instrument_code "+"\n";
    stat = stat +" ORDER BY songs_sum DESC "+"\n";
    stat = stat +") most LIMIT 1)";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    if(row->first()) {
        cout <<"\n"<<"Most popular instrument of all times:"<<"\n"<<row->getString(1) << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database:: AllInstumentsInsomeAlbum()
{
    string name;
    cout << "please enter album name:" << endl;
    cinClearing();
    getline(cin,name);
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT distinct typeName FROM instrument as i "+"\n";
    stat = stat +"join MusicalNumber_Player_Instrument as mnpi ON mnpi.instrumentcode=i.instrument_code "+"\n";
    stat = stat +"join album_musicalnumber as amn ON amn.musicalID=mnpi.musicalID "+"\n";
    stat = stat +"JOIN album as a ON a.album_id=amn.albumid "+"\n";
    stat = stat +"WHERE album_name= ?;";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    pstmt->setString(1, name);
    ResultSet *row = pstmt->executeQuery();
    int count=1;
    if(!(row))
        cout <<"No instruments in the album"<< endl;
    else{
        cout <<"\n"<<"Instruments in "+name+":"<<endl;
    while(row->next())
    {
        cout<<count++<<". "<<row->getString(1)<<endl;
    }
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database:: MostBusyProducer(){
    string d1, d2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> d1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cin >> d2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT proname FROM Producer WHERE producer_ID= (SELECT producer_ID as most_productive_pro FROM( "+"\n";
    stat = stat +"SELECT producer_ID ,COUNT(*) as most_productive_pro FROM( "+"\n";
    stat = stat +"SELECT a.album_id, p.producer_ID, a.RecordStartDate, a.RecordEndDate, p.proname FROM producer as p "+"\n";
    stat = stat +"join album_producer as aap ON aap.producerid=p.producer_ID "+"\n";
    stat = stat +"JOIN album as a ON a.album_id=aap.albumid "+"\n";
    stat = stat +"WHERE a.RecordStartDate < ? and a.RecordEndDate > ?) as summm "+"\n";
    stat = stat +"    GROUP BY producer_ID "+"\n";
    stat = stat +"    ORDER BY most_productive_pro DESC LIMIT 1) as pro);";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    pstmt->setString(1, d2);
    pstmt->setString(2, d1);
    ResultSet *row = pstmt->executeQuery();
  
    if(row->first()) {
        cout <<"\n"<<"Most busy producer between "+d1+" and "+d2+": "<<"\n"<<row->getString(1) << endl;
    }
    
    else
            cout<<"No albums were produced in this time range"<<endl;
    
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
    
}

void Database:: MostBusyManafacturer(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT distinct manuName FROM Instrument where instrument_code=(SELECT instrument_code most_comm FROM ( "+"\n";
    stat = stat +"SELECT  instrument_id, COUNT(*) songs_sum FROM "+"\n";
    stat = stat +"(SELECT musicalid, i.instrument_code FROM instrument as i "+"\n";
    stat = stat +"join MusicalNumber_Player_Instrument as mnpi ON mnpi.instrumentcode=i.instrument_code "+"\n";
    stat = stat +") sum_s "+"\n";
    stat = stat +"GROUP BY instrument_code "+"\n";
    stat = stat +" ORDER BY songs_sum DESC "+"\n";
    stat = stat +") most LIMIT 1)";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    
    if(row->first()) {
        cout <<"\n"<<"Most busy manafacturer:"<<"\n"<<row->getString(1) << endl;
    }
    
    else
        cout<<"There is no instruments in the album-> no manufacturers"<<endl;
    
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database:: MusiciansInALLtimes(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT COUNT(*) FROM( SELECT  musicianid "+"\n";
    stat = stat +"FROM   musicalnumber_player_instrument "+"\n";
    stat = stat +"UNION "+"\n";
    stat = stat +"SELECT  musicianid "+"\n";
    stat = stat +"FROM   musicalnumber_singer) A";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    
    if(row->first()) {
        cout <<"\n"<<"Total musicians recorded in the studio:"<<"\n"<<row->getUInt(1) << endl;
    }
    
    else
        cout<<"There is no instruments in the album-> no manufacturers"<<endl;
    
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::mostCopoMusician()
{
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"select musician_name from Musician where musician_ID=(SELECT musicianID from (SELECT  pop,musicianID FROM (select musicianid ,musicalID as mid "+"\n";
    stat = stat +"FROM   musicalnumber_player_instrument "+"\n";
    stat = stat +"UNION "+"\n";
    stat = stat +"SELECT  musicianid,musicalID "+"\n";
    stat = stat +"FROM   musicalnumber_singer "+"\n";
    stat = stat +"ORDER BY musicianid)A "+"\n";
    stat = stat +"JOIN (select  musicalID,COUNT(*)-1 as pop from (select musicianid ,musicalID "+"\n";
    stat = stat +"FROM   musicalnumber_player_instrument "+"\n";
    stat = stat +"UNION "+"\n";
    stat = stat +"SELECT  musicianid,musicalID "+"\n";
    stat = stat +"FROM   musicalnumber_singer "+"\n";
    stat = stat +"ORDER BY musicianid) a GROUP BY musicalID)B on a.mid=b.musicalid)c group by musicianID ORDER BY sum(pop) DESC LIMIT 1) ;";

    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    while(row->next()) {
        cout <<"\n"<<"Most coporative musician:"<<"\n"<<row->getString(1) << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}


void Database:: MostPopularGenereInALLtimes(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);

    string stat = "";
    stat = stat +"SELECT genere,count(*) "+"\n";
    stat = stat +"from MusicalNumber "+"\n";
    stat = stat +"group by genere "+"\n";
    stat = stat +"ORDER BY count(*) DESC"+"\n";
    stat = stat +"LIMIT 1;";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    while(row->next()) {
        cout <<"\n"<<"Most popular genere:"<<"\n"<<row->getString(1) << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database:: MostBusyTechInDateRange(){
    string d1, d2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> d1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cin >> d2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT techname from Technician where technician_ID=(select technicianID from "+"\n";
    stat = stat +"(select technicianID,count(*) "+"\n";
    stat = stat +"from(SELECT  *  from MusicalNumber "+"\n";
    stat = stat +"where RecordDate>?  AND RecordDate<?) as songsINdate "+"\n";
    stat = stat +"group by technicianID "+"\n";
    stat = stat +"ORDER BY count(*) DESC "+"\n";
    stat = stat +"LIMIT 1 ) as techID);";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    pstmt->setString(1, d1);
    pstmt->setString(2, d2);
    ResultSet *row = pstmt->executeQuery();
    while(row->next()) {
        cout <<"\n"<<"Most busy Technician between "+d1+" and "+d2+": "<<"\n"<<row->getString(1) << endl;

    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database:: firstAlbum(){

    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"select album_name from Album "+"\n";
    stat = stat +"order BY RecordEndDate ASC LIMIT 1";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    while(row->next()) {
        cout<<"first album recorded in studio:\n"<<row->getString(1)<<endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database:: AllAlbumsInTwoORmore(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"select musical_name from MusicalNumber where musical_ID IN (SELECT musicalID "+"\n";
    stat = stat +"from Album_MusicalNumber "+"\n";
    stat = stat +"group by musicalID "+"\n";
    stat = stat +"HAVING count(*)>1)";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    int count=1;
    if(!(row))
        cout <<"No such Albums"<< endl;
    else{
        cout <<"\n"<<"All albums participated in 2 or more albums:"<<endl;
    while(row->next()) {
        cout<<count++<<". "<<row->getString(1)<<endl;
    }
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::TechnicianInAllAlbum()
{
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT Technician.techname from Technician where technician_ID in(SELECT distinct MusicalNumber.technicianID FROM MusicalNumber where MusicalNumber.musical_ID in (select distinct musicalID from Album_MusicalNumber INNER JOIN (select albumID as album_id from (select albumID,count(*) from (SELECT distinct technicianID,albumID FROM MusicalNumber "+"\n";
    stat = stat +"join Album_MusicalNumber ON Album_MusicalNumber.musicalID=MusicalNumber.musical_ID)a group by albumID "+"\n";
    stat = stat +"HAVING COUNT(*)=1)b)c ON Album_MusicalNumber.albumID=c.album_ID));";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    int count=1;
    if(!(row))
        cout <<"No such Technicians"<< endl;
    else{
        cout <<"\n"<<"All technicians participated in a whole album:"<<endl;
        while(row->next()) {
            cout<<count++<<". "<<row->getString(1)<<endl;
        }
        cout <<"\n";

    }
}
void Database::mostVers()
{
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    string stat = "";
    stat = stat +"SELECT musician_name FROM Musician WHERE musician_ID =(select musicianID from (SELECT musicianID, count(*) from(SELECT distinct genere ,musicianID FROM "+"\n";
    stat = stat +"(SELECT  musicianid,musicalID "+"\n";
    stat = stat +"FROM   musicalnumber_player_instrument "+"\n";
    stat = stat +"UNION "+"\n";
    stat = stat +"SELECT  musicianid,musicalID "+"\n";
    stat = stat +"FROM   musicalnumber_singer) as A inner join MusicalNumber  ON A.musicalid=MusicalNumber.musical_ID "+"\n";
    stat = stat +"ORDER BY musicianID) a group by musicianID ORDER BY count(*) DESC "+"\n";
    stat = stat +"LIMIT 1) as mostVarmusician);";
    PreparedStatement *pstmt = con->prepareStatement(stat);
    ResultSet *row = pstmt->executeQuery();
    if(row->next())
        cout<<"most versitaile musician is:\n"<<row->getString(1)<<"\n"<<endl;
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

