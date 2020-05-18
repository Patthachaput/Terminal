/**
  *  dataBuilder.h
  *
  *  This file build data structure for
  *  entire project
 */

#ifndef dataBuilder_h
#include "mainAuction.h"

/*this structure sort by price*/
typedef struct
{
    double price;
    PRODUCT_T* pProduct;
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

/* Compares two dates. Returns 1 if the
 * first date is later than the second, -1 if the
 * first date is earlier than the second, and 0 if
 * they are the same.
 *
 * Created by Sally Goldin (Edit by permission)
 * Edit by Supakorn Srisawast 3449
 *
 * Arguments: day1   - day of first date
 *            month1 - month of first date
 *            year1  - year of first date
 *            hour1  - hour of first date
 *            min1   - minute of first date
 *            day2   - day of second date
 *            month2 - month of second date
 *            year2  - year of second date
 *            hour2  - hour of second date
 *            min2   - minute of second date */
int bidTimeCompare(int year1, int month1, int day1, int hour1, int min1,
                   int year2, int month2, int day2, int hour2, int min2);

/***********************************************************************
*  checkProductStatus
*  - check does this auction are not close or currently open
*  - 0 for close auction, 1 for open auction
* created by Narapathra Morakrant 62070503464
*/
int checkProductStatus(PRODUCT_T* product,DATE_T currentDate);

/***********************************************************************
*  printCatagory
*  - for display product category in the terminal
*  - no return
* created by Narapathra Morakrant 62070503464
*/
void printCategory(int category);

/***********************************************************************
 *  printProduct
 *  - for display product in the terminal
 *  - no return
 * created by Narapathra Morakrant 62070503464
 */
void printProduct(PRODUCT_T* product,DATE_T currentDate);

/* build data structure by reading data in the file
 * No return - if error occur program will be close automatically
 */
int buildData();

/* insert users into data structure
 * No return
 */
int insertUser(USER_T user);

/* insert users into data structure sort by name
 * No return
 */
int insertUserSortByEmail(USER_T user);

/* serch for users by email 
 * using binary search
 *
 * Return USER_T - if user is exist
 *        NULL - if user is not exist
 */
USER_T * searchUserByEmail(char* email);

/* insert product into data structure
 * No return
 */
int insertProduct(PRODUCT_T product, USER_T * user);

/* insert product and sort by minbid
 * No return
 */
int insertMinbidSort(PRODUCT_T* product);

/* insert product and sort by final price
 * No return
 */
int insertfinalPriceSort(PRODUCT_T* product);

/* insert product for searching by open date. 
 * No return
 */
int insertOpenDateSort(PRODUCT_T* product);

/* insert product for searching by close date. 
 * No return
 */
int insertCloseDateSort(PRODUCT_T* product);

/* insert sale aucion into history
 * No return
 */
int insertSaleAuctionSort(int id, USER_T* user);

/* insert product bit into history
 * No return
 */
int insertProductBidSort(int id, USER_T* user);

/* searching for product by product id
 * Return  PRODUCT_T - in case found
 * 		   NULL - in case not found 
 */
PRODUCT_T* searchProductById(int id);


/* searching for product by minimum bid
 * using binary search
 *
 * Arguments cat - category of product
 *       bid - amount of bid price 
 *       
 * Return NULL - in case not found 
 */
PRODUCT_T* searchByMinbid(int cat, double bid, DATE_T currentDate);


/* searching for product by final price
 * using binary search
 *
 * Arguments cat - category of product
 *       bid - amount of bid price 
 *  
 * Return  NULL - in case not found
 */
PRODUCT_T* searchByFinalPrice(int cat, double bid, DATE_T currentDate);

/* searching for product by close date
 * using binary search
 *
 * Arguments cat - category of product
 *       bid - amount of bid price 
 *  
 * Return  NULL - in case not found 
 */
PRODUCT_T* searchByCloseDate(int cat, DATE_T date, DATE_T currentDate);

/* searching for product by open date
 * using binary search
 *
 * Arguments cat - category of product
 *       bid - amount of bid price 
 *  
 * Return  NULL - in case not found 
 */
PRODUCT_T* searchByOpenDate(int cat, DATE_T date,DATE_T currentDate);

/* search for sale auction using binary search
 * Return 1 - if product exist 
 *        0 - if product does not exist
 */
int searchSaleAuction(int id, USER_T* user,DATE_T currentDate);

/* search for product bid using binary search
 * Return 1 - if product exist 
 *        0 - if product does not exist
 */
int searchProductBid(int id, USER_T* user, DATE_T currentDate);

/* this function bid product by insert price and user
 * into product struct
 *
 * Argument USER_T* user
 * 			PRODUCT_T* product
 * 		 	double price
 *
 * Return  1 if bid auction success
 * 		  -1 if the auction is expired
 *        -2 if bid price is less than or equal to current price
 */
int bidProduct(PRODUCT_T* product, USER_T* user, DATE_T currentDate, double price);

/* free all memories all close program
 * return 1- if close program and write file success
 * No return - in case error program will be closed automatically
 */
int closeProgram();

/* This function display all products in lists*/
int showProductByCat(int cat,DATE_T currentDate);

void showbidHistory(int userId,DATE_T currentDate);

void showsellHistory(int userId,DATE_T currentDate);

/*This function register new user and add user
 * into data structure 
 * 
 * Return 1 - if register success
 *        0 - in case user already exist*/
int registerNewUser(USER_T user);

/*This function login and return USER
 * 
 * Return USER_T* - if login success
 * 		  NULL    - if login fail
 * 		  
 * Output argument int* status
 * 		  -1 - if user does not exit 
 *        -2 - password does not match
 *         1 - if login success */
USER_T* login(char *email, char* password, int* status);
#endif
