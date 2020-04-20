/**
  *  dataBuilder.h
  *
  *  This file build data structure for
  *  entire project
 */

#include "dataBuilder.h"
#include<stdio.h>
#include<stdlib.h>

/*this structure sort by price*/
typedef struct{
    double price;
    PRODUCT_T * pProduct;
}PRODUCT_PRICE;

/*this structure sort by date time*/
typedef struct{
    DATE_T date;
    PRODUCT_T* pProduct;
}PRODUCT_DATE;

/*keep product in category*/
typedef struct {
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
int buildData()
{
    int i;/*counter*/

    /*start open file*/
    init();

    products = calloc(TOTALPRODUCT,sizeof(PRODUCT_T));
    if(products == NULL)
    {
        printf("Error allocating memories\n");
        exit(1);
    }
    /**==================for searching=============================*/
    for (int i = 0; i < 7; i++)
    {
        product_in_cat[i].minBidSort = calloc(TOTALPRODUCT,sizeof(PRODUCT_PRICE));
        if(product_in_cat[i].minBidSort == NULL)
        {
            printf("Error allocating memories\n");
            exit(1);
        }
        product_in_cat[i].finalPricesort = calloc(TOTALPRODUCT,sizeof(PRODUCT_PRICE));
        if(product_in_cat[i].finalPricesort == NULL)
        {
            printf("Error allocating memories\n");
            exit(1);
        }
        product_in_cat[i].openDateSort = calloc(TOTALPRODUCT,sizeof(PRODUCT_DATE));
        if(product_in_cat[i].openDateSort == NULL)
        {
            printf("Error allocating memories\n");
            exit(1);
        }
        product_in_cat[i].closeDateSort = calloc(TOTALPRODUCT,sizeof(PRODUCT_DATE));
        if(product_in_cat[i].closeDateSort == NULL)
        {
            printf("Error allocating memories\n");
            exit(1);
        }

        product_in_cat[i].minBidCount = 0;
        product_in_cat[i].finalPriceCount = 0;
        product_in_cat[i].openDateCount = 0;
        product_in_cat[i].closeDateCount =0;
    }

    /**============================================================*/

    users = calloc(TOTALUSER,sizeof(USER_T));
    if(users == NULL)
    {
        printf("Error allocating memories\n");
        exit(1);
    }

    products = getProduct();
    users = getUser();

    for(i=0;i<TOTALPRODUCT;i++)
    {
        insertMinbidSort(&products[i]);
        insertfinalPriceSort(&products[i]);
    }

    /*check will be delete soon*/
    printf("total users:%d\n",TOTALUSER);
    printf("total products:%d\n",TOTALPRODUCT);
}

/* insert users into data structure
 * No return
 */
int insertUser(USER_T user)
{
    ADDNEWUSER++;
    user.idUser =TOTALUSER+ADDNEWUSER;
    user.history = NULL;
    users = realloc(users,(TOTALUSER+ADDNEWUSER)*sizeof(USER_T));
    users[TOTALUSER+ADDNEWUSER-1] = user;
}

/* insert product into data structure
 * No return
 */
int insertProduct(PRODUCT_T product)
{
    ADDNEWPRODUCT++;
    product.idProduct = TOTALPRODUCT + ADDNEWPRODUCT;/*set auto increment id*/

    products = realloc(products,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_T));

    /*dynamic allocation for searching*/
    product_in_cat[product.category].minBidSort = realloc(product_in_cat[product.category].minBidSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_PRICE));
    product_in_cat[product.category].finalPricesort = realloc(product_in_cat[product.category].finalPricesort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_PRICE));
    product_in_cat[product.category].openDateSort = realloc(product_in_cat[product.category].openDateSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_DATE));
    product_in_cat[product.category].closeDateSort = realloc(product_in_cat[product.category].closeDateSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_DATE));

    products[TOTALPRODUCT+ADDNEWPRODUCT-1] = product;
    printf("Insert %s\n", product.name);
    insertMinbidSort(&product);
    insertfinalPriceSort(&product);
}

/* insert product and sort by product final price
 * No return
 */
int insertfinalPriceSort(PRODUCT_T* product)
{
    int i;/*counter*/
    for(i=product_in_cat[product->category].finalPriceCount-1;(i>=0 && product_in_cat[product->category].finalPricesort[i].price > product->finalPrice);i--)
    {
       product_in_cat[product->category].finalPricesort[i+1] = product_in_cat[product->category].finalPricesort[i];
    }
    PRODUCT_PRICE finalPrice;
    finalPrice.price = product->finalPrice;
    finalPrice.pProduct = product;

    product_in_cat[product->category].finalPricesort[i+1] = finalPrice;

    product_in_cat[product->category].finalPriceCount++;
}

/* insert product and sort by minbid
 * No return
 */
int insertMinbidSort(PRODUCT_T* product)
{
    int i;/*counter*/
    for(i=product_in_cat[product->category].minBidCount-1;(i>=0 && product_in_cat[product->category].minBidSort[i].price > product->minbid);i--)
    {
       product_in_cat[product->category].minBidSort[i+1] = product_in_cat[product->category].minBidSort[i];
    }
    PRODUCT_PRICE minBid;
    minBid.price = product->minbid;
    minBid.pProduct = product;

    product_in_cat[product->category].minBidSort[i+1] = minBid;

    product_in_cat[product->category].minBidCount++;
}

/*This function display all products in lists*/
int showProductByCat(int cat)
{
    printf("final price %d\n",product_in_cat[cat].finalPriceCount);
    int i;
    for (i = 0; i < product_in_cat[cat].finalPriceCount; i++)
    {
        printf("Name %s\n",product_in_cat[cat].finalPricesort[i].pProduct->name);
        printf("Final price %.2f\n\n",product_in_cat[cat].finalPricesort[i].pProduct->finalPrice);
    }
}

/*close program and write all file into data
 * No return
 */
int closeProgram()
{
    writProduct(products);
    writeUser(users);
}


