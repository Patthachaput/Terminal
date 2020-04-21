/*
 * mainAuction.h
 *
 *      define all structures that are important to this project
 *
 *  Project CPE111 Data structure - TEAM TERMINAL
 *  Member: Natacha Punyathanasub       (Nut)       62070503415
 *          Patthachaput Thanesmaneerat (Jui)       62070503432
 *          Supakorn Srisawas           (Field)     62070503464
 *          Narapathra Morakrant        (Foremost)  62070503464
 */


int TOTALUSER;
int TOTALPRODUCT;
int TOTALHISTORY;
int TOTALBACKUP;
int ADDNEWUSER;
int ADDNEWPRODUCT;
int ADDNEWHISTORY;

typedef struct _date
{
    int hour;
    int minute;
    int day;
    int month;
    int year;
}DATE_T;

typedef struct _history
{
    int idUser;
    int* productBid;
    int sizeofProductBit;
    int* sealAuction;
    int sizaofSealAuction;
}HISTORY_T;

typedef struct _user
{
    int idUser;
    char email[120];
    char password[120];
    char name[120];         /*user full name*/
    char address[120];
    char phoneNumber[60];
    char bankAccNumber[60];
    HISTORY_T* history;
}USER_T;

typedef struct _product
{
    int idProduct;
    char name[60];          /*product name*/
    char description[120];  /*product description*/
    int category;           /*fixed category*/
    DATE_T dateOpen;
    DATE_T dateClose;
    double finalPrice;
    double nowPrice;
    double minbid;          /*minimum bid price*/
    int hostId;             /*user who created this product*/
    USER_T* host;
    int userAuthorityId;    /*user who have now authority*/
    USER_T* userAuthority;
    int winnerId;           /*winner*/
    USER_T* winner;
}PRODUCT_T;

typedef struct
{
    int idBackUp;
    int haveNewUser;
    int inProcessProduct;
    USER_T user;
    PRODUCT_T product;
}BACKUP_T;


/*******************************************************************************
* Init
* - check if program open first time
* - return 1 if default file is exist
*        -1 || -2 || -3 || -4 if defaault not exit and create file
* - initial all global value
* created by Patthachaput Thanesmaneerat 62070503432
*/
int init();

/*******************************************************************************
* writeUser
* - write array of all user to file user.dat
* - if Success return 1
* - else return 0
* - argument is array of all user
* created by Patthachaput Thanesmaneerat 62070503432
*/
int writeUser(USER_T* user);

/*******************************************************************************
* writProduct
* - write array of all product to file product.dat
* - if Success return 1
* - else return 0
* - argument is array of all product
* created by Patthachaput Thanesmaneerat 62070503432
*/
int writProduct(PRODUCT_T* product);

/*******************************************************************************
* writeHistory
* - write array of all history to file history.dat
* - if Success return 1
* - else return 0
* - argument is array of all history
* created by Patthachaput Thanesmaneerat 62070503432
*/
int writeHistory(HISTORY_T* history);

/*******************************************************************************
* writeBackup
* - write array of all backup case to file backup.dat
* - if Success return 1
* - else return 0
* - argument is array of all backup
* created by Patthachaput Thanesmaneerat 62070503432
*/
int writeBackUp(BACKUP_T* thisBackup); /* local function */

/*******************************************************************************
* getBackUp
* - return the backup if have one
* - return null for no backup
* created by Patthachaput Thanesmaneerat 62070503432
*/
BACKUP_T* getBackUp();

/*******************************************************************************
* getUser
* - get all user in file user.dat
* - if Success return array of all user
* - else return NULL
* created by Patthachaput Thanesmaneerat 62070503432
*/
USER_T* getUser();

/*******************************************************************************
* getProduct
* - get all product in file product.dat
* - if Success return array of all product
* - else return NULL
* created by Patthachaput Thanesmaneerat 62070503432
*/
PRODUCT_T* getProduct();

/*******************************************************************************
* getHistory
* - get all history in file history.dat
* - if Success return array of all history
* - else return NULL
* created by Patthachaput Thanesmaneerat 62070503432
*/
HISTORY_T* getHistory();

/*******************************************************************************
* allFileExist
* - Local function used dy init.
* - This function will check all file are exit or not,
* - if all file are exit will return 1 else return negative
* - number follow index of file and created it.
* created by Patthachaput Thanesmaneerat 62070503432
*/
int allFileExist(); /* local function */

/*******************************************************************************
* SaveBackUp
* - Save data to backup file
* - first argument is data that want to save
* - second is a struct mode 'U' for user 'P' for product
* return 1 if Success else return 0
* created by Patthachaput Thanesmaneerat 62070503432
*/
int saveBackUp(void* bata, char mode);

/*int saveAllData();*/ //comment out because function has not done yet.
