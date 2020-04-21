/*
*
*  dataBuilder.h
*
*
*  Project CPE111 Data structure - TEAM TERMINAL
*  Member: Natacha Punyathanasub       (Nut)       62070503415
*          Patthachaput Thanesmaneerat (Jui)       62070503432
*          Supakorn Srisawas           (Field)     62070503464
*          Narapathra Morakrant        (Foremost)  62070503464
*
*/
//#ifndef validate_h
//#define validate_h

/*this structure sort by price*/
typedef struct
{
    double price;
    PRODUCT_T * pProduct;
}PRODUCT_PRICE;

/*this structure sort by date time*/
typedef struct
{
    DATE_T date;
    PRODUCT_T* pProduct;
}PRODUCT_DATE;

/*keep product in category*/
typedef struct
{
    PRODUCT_PRICE * minBidSort;
    PRODUCT_PRICE * finalPricesort;
    PRODUCT_DATE * openDateSort;
    PRODUCT_DATE * closeDateSort;

    /*counter for 4 sorts*/
    int minBidCount;
    int finalPriceCount;
    int openDateCount;
    int closeDateCount;
}PRODUCT_IN_CAT;

PRODUCT_T * products; /*keep entire product*/
USER_T * users; /*keep entire users*/

PRODUCT_IN_CAT product_in_cat[7];


/* build data structure by reading data in the file
 * No return - if error occur program will be close automatically
 */
int buildData();

/* insert users into data structure
 * No return
 */
int insertUser(USER_T user);

/* insert product into data structure
 * No return
 */
int insertProduct(PRODUCT_T product);

/* insert product and sort by minbid
 */
int insertMinbidSort(PRODUCT_T* product);

/* insert product and sort by final price
 */
int insertfinalPriceSort(PRODUCT_T* product);

/* close program and write all file into data
 * return 1- if close program and write file success
 * No return - in case error program will be closed automatically
 */
int closeProgram();

/* This function display all products in lists*/
int showProductByCat(int cat);

//#endif
