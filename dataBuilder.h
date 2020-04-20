/**
  *  dataBuilder.h
  *
  *  This file build data structure for
  *  entire project
 */

#include "mainAuction.h"

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
