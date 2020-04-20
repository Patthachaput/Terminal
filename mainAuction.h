/*********************************************************************************
 *
 *mainAuction.h
 *
 *define all struct that importance with this project 
 *
 *
 *
 *********************************************************************************
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
	char name[120];   /*user full name*/
	char address[120];
	char phoneNumber[60];
	char bankAccNumber[60];
	HISTORY_T* history;
}USER_T;

typedef struct _product 
{
	int idProduct;
	char name[60];   /*product name*/
	char description[120];  /*product description*/
	int category;    /*fixed category*/
	DATE_T dateOpen;
	DATE_T dateClose;
	double finalPrice;
	double nowPrice;
	double minbid;   /*minimum bid price*/
	int hostId;	/* user who created this product */
	USER_T* host;
	int userAuthorityId; /*user who have now authority*/
	USER_T* userAuthority;
	int winnerId; /*winner*/
	USER_T* winner;
}PRODUCT_T;

typedef struct _backUp
{
	int idBackUp;
	int haveNewUser;
	int inProcessProduct;
	USER_T user;
	PRODUCT_T product;
}BACKUP_T;


int init();

int writeUser(USER_T* user);

int writProduct(PRODUCT_T* product);

int writeHistory(HISTORY_T* history);

int writeBackUp(BACKUP_T* thisBackup);

BACKUP_T* getBackUp();

USER_T* getUser();

PRODUCT_T* getProduct();

HISTORY_T* getHistory();

int allFileExist(); /* local function */

int saveBackUp(void* bata, char mode);

/*int saveAllData();*/