/**
  *  dataBuilder.c
  *
  *  This file build data structure for
  *  entire project
 */

#include "dataBuilder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

USER_T * users_by_id; /*keep entire users sort by id*/
USER_T * users_by_email; /*keep entire users sort by email*/

PRODUCT_T * products; /*keep entire product*/
PRODUCT_T ** lProduct; /*keep entire location of products*/
PRODUCT_IN_CAT product_in_cat[7]; /*all product in 7 category*/

HISTORY_T * histories; /*keep entire histories for all users*/

int totalUsersByEmail =0;
int totalProductsLocation =0;

/******************************************************************************
 * serch for users by ID
 * using binary search
 *
 * Return USER_T - if user is exist
 *        NULL - if user is not exist
 */
USER_T * searchUserById(int userId)
{
    USER_T* user = NULL;
    user = &users_by_id[userId-1];
    
    return user;
}

/******************************************************************************
 * Compares two dates. Returns 1 if the
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
 *            min2   - minute of second date 
 */
int bidTimeCompare(int year1, int month1, int day1, int hour1, int min1,
                   int year2, int month2, int day2, int hour2, int min2)
{
    int compareValue = 0;
    if (year1 > year2)
       {
       compareValue = 1;
       }
    else if (year1 < year2)
       {
       compareValue = -1;
       }
    else if (month1 > month2)
       {
       compareValue = 1;
       }
    else if (month1 < month2)
       {
       compareValue = -1;
       }
    else if (day1 > day2)
       {
       compareValue = 1;
       }
    else if (day1 < day2)
       {
       compareValue = -1;
       }
       else if(hour1 > hour2)
        {
        compareValue = 1;
        }
    else if(hour1 < hour2)
        {
        compareValue = -1;
        }
    else if(min1 > min2)
        {
        compareValue = 1;
        }
    else if(min1 < min2)
        {
        compareValue =-1;
        }

    /* otherwise they are the same */

    return compareValue;
}

/******************************************************************************
 * Compares two dates. Returns 1 if the
 * first date is later than the second, -1 if the
 * first date is earlier than the second, and 0 if
 * they are the same.
 *
 * Created by Sally Goldin (Edit by permission)
 * Edit by Narapathra Morakrant 62070503464
 *
 * Arguments: day1   - day of first date
 *            month1 - month of first date
 *            year1  - year of first date
 *            day2   - day of second date
 *            month2 - month of second date
 *            year2  - year of second date
 */
int bidTimeCompare2(int year1, int month1, int day1, int year2, int month2, int day2)
{
    int compareValue = 0;
    if (year1 > year2)
       {
       compareValue = 1;
       }
    else if (year1 < year2)
       {
       compareValue = -1;
       }
    else if (month1 > month2)
       {
       compareValue = 1;
       }
    else if (month1 < month2)
       {
       compareValue = -1;
       }
    else if (day1 > day2)
       {
       compareValue = 1;
       }
    else if (day1 < day2)
       {
       compareValue = -1;
       }

    /* otherwise they are the same */

    return compareValue;
}

/***********************************************************************
*  printCatagory
*  - for display product category in the terminal
*  - no return
* created by Narapathra Morakrant 62070503464
*/
void printCategory(int category)
{
    switch (category) {
        case 1:
            printf("\tCategory: Home & Garden\n");
            break;
        case 2:
            printf("\tCategory: Collectibles\n");
            break;
        case 3:
            printf("\tCategory: Sport\n");
            break;
        case 4:
            printf("\tCategory: Electronic\n");
            break;
        case 5:
            printf("\tCategory: Fashion\n");
            break;
        case 6:
            printf("\tCategory: Health & Beauty\n");
            break;
        case 7:
            printf("\tCategory: Motor\n");
            break;
        default:
            break;
    }
}

/***********************************************************************
*  checkProductStatus
*  - check does this auction are not close or currently open
*  - 0 for close auction, 1 for open auction
* created by Narapathra Morakrant 62070503464
*/
int checkProductStatus(PRODUCT_T* product,DATE_T currentDate)
{
    int status = 1;
    
    if(bidTimeCompare(currentDate.year,currentDate.month,currentDate.day,currentDate.hour,currentDate.minute,
    product->dateClose.year,product->dateClose.month,product->dateClose.day,product->dateClose.hour,product->dateClose.minute) == 1)
    {
        product->status = 0;
        status = 0;
    }
    
    return status;
}

/***********************************************************************
 *  printProduct
 *  - for display product in the terminal
 *  - no return
 * created by Narapathra Morakrant 62070503464
 */
void printProduct(PRODUCT_T* product,DATE_T currentDate)
{
    int status = product->status;
    
    if(status == 1)
    {
        status = checkProductStatus(product,currentDate);
        if(status == 0)
        {
            product->finalPrice = product->nowPrice;
            insertfinalPriceSort(product);
        }
    }
    
    
    if(status == 0)
    {

        printf("-------------------------------------------------------------------------------------------------------------------\n");
        printf("\t| PRODUCT ID %d |\n\n", product->idProduct);
        printf("\t>> CLOSED NOW <<\n");
        printf("\t%s - %s \n",product->name,product->description);
        printCategory(product->category);
        printf("\n");
        
        printf("\tFinal Price: %.2f\n", product->nowPrice);
        printf("\tClose date: %d-%d-%d %d:%d\n",product->dateClose.day,product->dateClose.month,product->dateClose.year,product->dateClose.hour,product->dateClose.minute);
        printf("\tOpen date: %d-%d-%d %d:%d\n",product->dateOpen.day,product->dateOpen.month,product->dateOpen.year,product->dateOpen.hour,product->dateOpen.minute);
    }
    else
    {
        printf("-------------------------------------------------------------------------------------------------------------------\n");
        printf("\t| PRODUCT ID %d |\n\n", product->idProduct);
        printf("\t>> CURRENTLY OPEN <<\n");
        printf("\t%s - %s \n",product->name,product->description);
        printCategory(product->category);
        printf("\n");
        
        printf("\tClose date: %d-%d-%d %d:%d\n",product->dateClose.day,product->dateClose.month,product->dateClose.year,product->dateClose.hour,product->dateClose.minute);
        printf("\tOpen date: %d-%d-%d %d:%d\n",product->dateOpen.day,product->dateOpen.month,product->dateOpen.year,product->dateOpen.hour,product->dateOpen.minute);
        printf("\tCurrent price: %.2f \n",product->nowPrice);
        printf("\tMinimum bid %.2f\n", product->minbid);
    }
    printf("\n");
}

/***********************************************************************
 *  printProduct
 *  - for display product history in the terminal
 *  - no return
 * created by Narapathra Morakrant 62070503464
 */
void printProductHistory(PRODUCT_T* product,DATE_T currentDate,int userId)
{
    int status = product->status;
    
    if(status == 1)
    {
        status = checkProductStatus(product,currentDate);
        if(status == 0)
        {
            product->finalPrice = product->nowPrice;
            insertfinalPriceSort(product);
        }
    }
    
    if(status == 0)
    {
        printf("-------------------------------------------------------------------------------------------------------------------\n");
        printf("\t| PRODUCT ID %d |\n\n", product->idProduct);
        if(product->userAuthorityId == userId)
        {
            printf("\tYOU WON THE AUCTION !!\n\n");
        }
        else
        {
            printf("\tYOU LOSE THE AUCTION T_T\n\n");
        }
        printf("\t>> CLOSED NOW <<\n");
        printf("\t%s - %s \n",product->name,product->description);
        printCategory(product->category);
        printf("\n");
        
        printf("\tFinal Price: %.2f\n", product->nowPrice);
        printf("\tClose date: %d-%d-%d %d:%d\n",product->dateClose.day,product->dateClose.month,product->dateClose.year,product->dateClose.hour,product->dateClose.minute);
        printf("\tOpen date: %d-%d-%d %d:%d\n",product->dateOpen.day,product->dateOpen.month,product->dateOpen.year,product->dateOpen.hour,product->dateOpen.minute);
    }
    else
    {
        printf("-------------------------------------------------------------------------------------------------------------------\n");
        printf("\t| PRODUCT ID %d |\n\n", product->idProduct);
        printf("\t>> CURRENTLY OPEN <<\n");
        printf("\t%s - %s \n",product->name,product->description);
        printCategory(product->category);
        printf("\n");
        
        printf("\tClose date: %d-%d-%d %d:%d\n",product->dateClose.day,product->dateClose.month,product->dateClose.year,product->dateClose.hour,product->dateClose.minute);
        printf("\tOpen date: %d-%d-%d %d:%d\n",product->dateOpen.day,product->dateOpen.month,product->dateOpen.year,product->dateOpen.hour,product->dateOpen.minute);
        printf("\tCurrent price: %.2f \n",product->nowPrice);
        printf("\tMinimum bid %.2f\n", product->minbid);
    }
    printf("\n");
}

/******************************************************************************
 *  build data structure by reading data in the file
 *  return 0 - if success 
 *           - if error occur program will be close automatically
 *  
 *  Arguement current date
 *
 *  Created by Supakorn Srisawas 62070503449
 */
int buildData(DATE_T currentDate)
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
    
    lProduct = calloc(TOTALPRODUCT,sizeof(PRODUCT_T*));
    if(lProduct == NULL)
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
	products = getProduct();

    users_by_id = calloc(TOTALUSER,sizeof(USER_T));
    if(users_by_id == NULL)
    {
        printf("Error allocating memories\n");
        exit(1);
    }

    users_by_email = calloc(TOTALUSER,sizeof(USER_T));
    if(users_by_email==NULL)
    {
        printf("Error allocating memories\n");
        exit(1);
    }

    users_by_id = getUser();

    histories = calloc(TOTALUSER,sizeof(HISTORY_T));
    if(histories == NULL)
    {
    	printf("Error allocating memories\n");
    	exit(1);
    }
    histories = getHistory();

    for(i=0;i<TOTALPRODUCT;i++)
    {
    	/*create new memory for searching array*/
    	PRODUCT_T* p = calloc(1,sizeof(PRODUCT_T));
    	if(p==NULL)
    	{
	    	printf("Error allocating memories\n");
    		exit(1);
    	}
    	*p=products[i];

    	/*keep products location in list*/
    	lProduct[totalProductsLocation] = p;
    	totalProductsLocation++;
        
        if(p->status == 1)
        {
            p->status = checkProductStatus(p,currentDate);
        }
        if(p->status == 0)
        {
            insertfinalPriceSort(p);
        }

    	insertMinbidSort(p);
    	insertOpenDateSort(p);
    	insertCloseDateSort(p);

        writeProduct(products);

    }

    for(i=0;i<TOTALUSER;i++)
    {
        insertUserSortByEmail(users_by_id[i]);
    }

   return 0;
}

/******************************************************************************
 * insert users into data structure
 * return 0 - if successs
 *          - if error occur program will be close automatically
 *
 *  Argument user
 *  Created by Supakorn Srisawas 62070503449
 */
int insertUser(USER_T user)
{
    ADDNEWUSER++;
    user.idUser =TOTALUSER+ADDNEWUSER;
    users_by_id = realloc(users_by_id,(TOTALUSER+ADDNEWUSER)*sizeof(USER_T));
    users_by_email = realloc(users_by_email,(TOTALUSER+ADDNEWUSER)*sizeof(USER_T));
    if(users_by_id == NULL || users_by_email == NULL)
    {
		printf("Error reallocating memories\n");
        exit(0);
    }

    HISTORY_T user_history;
    user_history.idUser = user.idUser;
    user_history.sizeofProductBit = 0;
    user_history.sizeofSealAuction = 0;
    user_history.productBid = calloc(user_history.sizeofProductBit,sizeof(int));
    user_history.sealAuction = calloc(user_history.sizeofSealAuction,sizeof(int));
    
    if(user_history.productBid==NULL || user_history.sealAuction==NULL)
    {
		printf("Error allocating memories\n");
		exit(1);
    }

    histories = realloc(histories,(TOTALUSER+ADDNEWUSER)*sizeof(HISTORY_T));
    if(histories == NULL)
    {
		printf("Error reallocating memories\n");
        exit(0);
    }

    histories[TOTALUSER+ADDNEWUSER-1] = user_history;

    users_by_id[TOTALUSER+ADDNEWUSER-1] = user;
    insertUserSortByEmail(user);
    writeUser(users_by_id);
    writeHistory(histories);

    return 0;
}

/******************************************************************************
 * insert users into data structure sort by email
 * return 0 - if success
 *
 * Arguement user
 *
 * Created by Supakorn Srisawas 62070503449
 */
int insertUserSortByEmail(USER_T user)
{
	int i;/*counter*/
	totalUsersByEmail++;
    for (i = totalUsersByEmail-2;(i >=0 && strcmp(users_by_email[i].email,user.email)>0); i--)
    {
    	users_by_email[i+1] = users_by_email[i];
    }
    users_by_email[i+1] = user;
    
    return 0;
}

/******************************************************************************
 * serch for users by email 
 * using binary search
 *
 * Return USER_T - if user is exist
 *        NULL - if user is not exist
 *
 * Created by Supakorn Srisawas 62070503449
 */
USER_T * searchUserByEmail(char* email)
{
	int lowest = 0;
	int highest = TOTALUSER+ADDNEWUSER-1;
	int middle = highest/2;
	USER_T *user = NULL;
	
	while(lowest <= highest)
	{
		if(strcasecmp(users_by_email[middle].email,email)<0)
		{
			lowest = middle +1;

		}
		else if(strcasecmp(users_by_email[middle].email,email)==0)
		{
			user = &users_by_email[middle];
			return user;
		}
		else 
		{
			highest = middle -1;
		}

		middle = (lowest+highest)/2;

	}
    
	return NULL;
}

/******************************************************************************
 * insert product into data structure
 * return 0 - if success
 *          - if error oucure program will close automatically
 * 
 * Argurment - prouduct user created
 *           - user 
 *           - current date
 *
 * Created by Supakorn Srisawas 62070503449
 */
int insertProduct(PRODUCT_T product, USER_T * user, DATE_T currentDate)
{
    ADDNEWPRODUCT++;
    product.idProduct = TOTALPRODUCT + ADDNEWPRODUCT;
    product.hostId = user->idUser;
    product.nowPrice = 0; /*set default bid price*/
    
    product.userAuthorityId = -1;
    product.finalPrice = 0;

    product.dateOpen = currentDate;
    product.status = 1; /*assume the auction is currently open*/

	products = realloc(products,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_T));
    if(products == NULL)
    {
		printf("Error reallocating memories\n");
        exit(0);
    }

    /*create new memmory for searching*/
	PRODUCT_T* p = calloc(1,sizeof(PRODUCT_T));
	if(p==NULL)
	{
    	printf("Error allocating memories\n");
		exit(1);
	}
	*p = product;


    /*dynamic allocation for searching*/
    product_in_cat[product.category].finalPricesort = realloc(product_in_cat[product.category].finalPricesort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_PRICE));
    product_in_cat[product.category].minBidSort = realloc(product_in_cat[product.category].minBidSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_PRICE));
    product_in_cat[product.category].openDateSort = realloc(product_in_cat[product.category].openDateSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_DATE));
    product_in_cat[product.category].closeDateSort = realloc(product_in_cat[product.category].closeDateSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_DATE));
    lProduct = realloc(lProduct,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_T*));
    if(product_in_cat[product.category].finalPricesort==NULL || product_in_cat[product.category].minBidSort==NULL || product_in_cat[product.category].openDateSort==NULL || product_in_cat[product.category].closeDateSort==NULL || lProduct==NULL)
    {
		printf("Error reallocating memories\n");
        exit(0);
    }

    products[TOTALPRODUCT+ADDNEWPRODUCT-1] = product;

    lProduct[totalProductsLocation] = p;
    totalProductsLocation++;

	histories[user->idUser - 1].sizeofSealAuction++;
    histories[user->idUser - 1].sealAuction = realloc(histories[user->idUser - 1].sealAuction,histories[user->idUser - 1].sizeofSealAuction*sizeof(int));

   	if(histories[user->idUser - 1].sealAuction==NULL)
   	{
		printf("Error reallocating memories\n");
        exit(0);
    }

   	insertMinbidSort(p);
	insertOpenDateSort(p);
	insertCloseDateSort(p);
	if(p->status == 1)
    {
        p->status = checkProductStatus(p,currentDate);
    }
    if(p->status == 0)
    {
        p->finalPrice = p->nowPrice;
        insertfinalPriceSort(p);
    }
	insertSaleAuctionSort(p->idProduct,user);

	writeProduct(products);
    return 0;
}	

/******************************************************************************
 * insert sale aucion into history
 * 
 * return 0 - if success
 *
 * Argurment - product id
 *           - user
 *           
 * Created by Supakorn Srisawas 62070503449
 */
int insertSaleAuctionSort(int id, USER_T* user)
{
	histories[user->idUser - 1].sealAuction[histories[user->idUser - 1].sizeofSealAuction-1] = id;
    writeHistory(histories);

    return 0;
}

/******************************************************************************
 * insert product for searching by min bid price.
 * return 0 - if success
 *
 * Argurment - product
 * 
 * Created by Supakorn Srisawas 62070503449
 */
int insertMinbidSort(PRODUCT_T* product)
{
    int i; /*counter*/
    for (i = product_in_cat[product->category].minBidCount-1;(i >=0 && product_in_cat[product->category].minBidSort[i].price > product->minbid); i--)
    {
    	product_in_cat[product->category].minBidSort[i+1] = product_in_cat[product->category].minBidSort[i];
    }
    product_in_cat[product->category].minBidSort[i+1].pProduct = product;
    product_in_cat[product->category].minBidSort[i+1].price = product->minbid;
    product_in_cat[product->category].minBidCount++;
    
    return 0;
}

/******************************************************************************
 * insert product for searching by final price.
 * return 0 - if success
 *  
 * Argurment - product
 * 
 * Created by Supakorn Srisawas 62070503449
 */
int insertfinalPriceSort(PRODUCT_T* product)
{
    int i; /*counter*/
    for (i = product_in_cat[product->category].finalPriceCount-1;(i >=0 && product_in_cat[product->category].finalPricesort[i].price > product->finalPrice); i--)
    {
        product_in_cat[product->category].finalPricesort[i+1] = product_in_cat[product->category].finalPricesort[i];
    }
    product_in_cat[product->category].finalPricesort[i+1].pProduct = product;
    product_in_cat[product->category].finalPricesort[i+1].price = product->finalPrice;
    product_in_cat[product->category].finalPriceCount++;

    return 0;
}

/******************************************************************************
 * insert product for searching by open date.
 * return 0 - if success
 *
 * Argument - product
 * 
 * Created by Supakorn Srisawas 62070503449
 */
int insertOpenDateSort(PRODUCT_T* product)
{
	int i; /*counter*/
    for (i = product_in_cat[product->category].openDateCount-1;
    	(i >= 0 && bidTimeCompare(product_in_cat[product->category].openDateSort[i].date.year,
    							product_in_cat[product->category].openDateSort[i].date.month,
    							product_in_cat[product->category].openDateSort[i].date.day,
    							product_in_cat[product->category].openDateSort[i].date.hour,
    							product_in_cat[product->category].openDateSort[i].date.minute,
    							product->dateOpen.year,
    							product->dateOpen.month,
    							product->dateOpen.day,
    							product->dateOpen.hour,
    							product->dateOpen.minute) > 0); 
    	i--)
    {
    	product_in_cat[product->category].openDateSort[i+1] = product_in_cat[product->category].openDateSort[i];
    }
    product_in_cat[product->category].openDateSort[i+1].pProduct = product;
    product_in_cat[product->category].openDateSort[i+1].date = product->dateOpen;
    product_in_cat[product->category].openDateCount++;
    
    return 0;
}

/******************************************************************************
 * insert product for searching by close date. 
 * return 0 - if success
 *
 * Argument - product
 * 
 * Created by Supakorn Srisawas 62070503449
 */
int insertCloseDateSort(PRODUCT_T* product)
{
	int i; /*counter*/
    for (i = product_in_cat[product->category].closeDateCount-1;
    	(i >= 0 && bidTimeCompare(product_in_cat[product->category].closeDateSort[i].date.year,
    							product_in_cat[product->category].closeDateSort[i].date.month,
    							product_in_cat[product->category].closeDateSort[i].date.day,
    							product_in_cat[product->category].closeDateSort[i].date.hour,
    							product_in_cat[product->category].closeDateSort[i].date.minute,
    							product->dateClose.year,
    							product->dateClose.month,
    							product->dateClose.day,
    							product->dateClose.hour,
    							product->dateClose.minute) > 0); 
    	i--)
    {
    	product_in_cat[product->category].closeDateSort[i+1] = product_in_cat[product->category].closeDateSort[i];
    }
    product_in_cat[product->category].closeDateSort[i+1].pProduct = product;
    product_in_cat[product->category].closeDateSort[i+1].date = product->dateClose;
    product_in_cat[product->category].closeDateCount++;	
    
    return 0;
}

/******************************************************************************
 * searching for product by product id
 * Return  PRODUCT_T - in case found
 * 		   NULL - in case not found 
 * 
 * Argument - product id
 * 
 * Created by Supakorn Srisawas 62070503449
 */
PRODUCT_T* searchProductById(int id)
{
	
	PRODUCT_T *p = NULL;
	
	if(id<=totalProductsLocation)
	{
		p = lProduct[id-1];
		return p;
	}
	
	return NULL;
}

/******************************************************************************
 * searching for product by minimum bid
 * using binary search
 *
 * Arguments cat - category of product
 *           bid - amount of bid price 
 *           
 * Return NULL - 1 success
 * 			   - 0 in case fail
 *                 
 * Created by Supakorn Srisawas 62070503449
 */
int searchByMinbid(int cat, double bid, DATE_T currentDate)
{
    int l = 0; /*lowest*/
    int i; /*counter*/
    int h = product_in_cat[cat].minBidCount-1; /*heighest*/
    int m = h/2; /*middle*/
    int count =0;
    PRODUCT_T *p = NULL;
    
    while(l <= h)
    {
        if(product_in_cat[cat].minBidSort[m].price < bid)
        {
            l = m +1;
        }
        else if(product_in_cat[cat].minBidSort[m].price == bid)
        {
            for(i=m;i>=0;i--)
            {
                if(product_in_cat[cat].minBidSort[i].price == bid)
                {
                    printProduct(product_in_cat[cat].minBidSort[i].pProduct,currentDate);
                    count = 1;
                }
                else
                {
                    i=-1;
                }

            }
            for(i=m+1;i<product_in_cat[cat].minBidCount;i++)
            {
                if(product_in_cat[cat].minBidSort[i].price == bid)
                {
                    printProduct(product_in_cat[cat].minBidSort[i].pProduct,currentDate);
                    count = 1;
                }
                else
                {
                    i= product_in_cat[cat].minBidCount;
                }
            }
            return count;
            // p = product_in_cat[cat].minBidSort[m].pProduct;
            // return p;
        }
        else 
        {
            h = m -1;
        }

        m = (l+h)/2;

    }
    return count;
}

/******************************************************************************
 * searching for product by final price
 * using binary search
 *
 * Arguments cat - category of product
 *           bid - amount of bid price 
 *           currentDate - current date
 *  
 * Return NULL - 1 success
 * 			   - 0 in case fail 
 *                
 * Created by Supakorn Srisawas 62070503449
 */
int searchByFinalPrice(int cat, double bid, DATE_T currentDate)
{
    int l = 0; /*lowest*/
    int i; /*counter*/
    int h = product_in_cat[cat].finalPriceCount-1; /*heighest*/
    int m = h/2; /*middle*/
    int count =0;
    PRODUCT_T *p = NULL;
    
    while(l <= h)
    {
        if(product_in_cat[cat].finalPricesort[m].price < bid)
        {
            l = m +1;
        }
        else if(product_in_cat[cat].finalPricesort[m].price == bid)
        {
            for(i=m;i>=0;i--)
            {
                if(product_in_cat[cat].finalPricesort[i].price == bid)
                {
                    printProduct(product_in_cat[cat].finalPricesort[i].pProduct,currentDate);
                    count = 1;
                }
                else
                {
                    i=-1;
                }

            }
            for(i=m+1;i<product_in_cat[cat].finalPriceCount;i++)
            {
                if(product_in_cat[cat].finalPricesort[i].price == bid)
                {
                    printProduct(product_in_cat[cat].finalPricesort[i].pProduct,currentDate);
                    count = 1;
                }
                else
                {
                    i= product_in_cat[cat].finalPriceCount;
                }
            }
            return count;
        }
        else
        {
            h = m -1;
        }

        m = (l+h)/2;

    }
    return count;
}

/******************************************************************************
 * searching for product by close date
 * using binary search
 *
 * Arguments cat - category of product
 *           bid - amount of bid price 
 *           currentDate - current date
 *           
 * Return NULL - 1 success
 * 			   - 0 in case fail 
 *                
 * Created by Supakorn Srisawas 62070503449
 */
int searchByCloseDate(int cat, DATE_T date, DATE_T currentDate)
{
    int l = 0; /*lowest*/
    int h = product_in_cat[cat].closeDateCount -1; /*heighest*/
    int m = h/2; /*middle*/
    int i;/*counter*/
    int count =0;

    PRODUCT_T *p = NULL;

    while(l <= h)
    {
        if(bidTimeCompare2(product_in_cat[cat].closeDateSort[m].date.year,
                                product_in_cat[cat].closeDateSort[m].date.month,
                                product_in_cat[cat].closeDateSort[m].date.day,
                                date.year,
                                date.month,
                                date.day) < 0)
        {
            l = m +1;
        }
        else if(bidTimeCompare2(product_in_cat[cat].closeDateSort[m].date.year,
                                product_in_cat[cat].closeDateSort[m].date.month,
                                product_in_cat[cat].closeDateSort[m].date.day,
                                date.year,
                                date.month,
                                date.day) == 0)
        {
            for(i=m;i>=0;i--)
            {
                if(bidTimeCompare2(product_in_cat[cat].closeDateSort[i].date.year,
                                product_in_cat[cat].closeDateSort[i].date.month,
                                product_in_cat[cat].closeDateSort[i].date.day,
                                date.year,
                                date.month,
                                date.day) == 0)
                {
                    printProduct(product_in_cat[cat].closeDateSort[i].pProduct,currentDate);
                    count = 1;
                }
                else
                {
                    i=-1;
                }
            }

            for(i=m+1;i<product_in_cat[cat].closeDateCount;i++)
            {
                if(bidTimeCompare2(product_in_cat[cat].closeDateSort[i].date.year,
                                product_in_cat[cat].closeDateSort[i].date.month,
                                product_in_cat[cat].closeDateSort[i].date.day,
                                date.year,
                                date.month,
                                date.day) == 0)
                {
                    printProduct(product_in_cat[cat].closeDateSort[i].pProduct,currentDate);
                    count = 1;
                }
                else
                {
                    i=product_in_cat[cat].closeDateCount;
                }
            }

            return count;
            // p = product_in_cat[cat].closeDateSort[m].pProduct;
            // return p;
        }
        else 
        {
            h = m -1;
        }

        m = (l+h)/2;

    }
    return 0;
}

/******************************************************************************
 * searching for product by open date
 * using binary search
 *
 * Arguments cat - category of product
 *           bid - amount of bid price 
 *           currentDate - current Date
 *           
 * Return NULL - 1 if found
 * 			   - 0 cannot find any product
 *                
 * Created by Supakorn Srisawas 62070503449
 */
int searchByOpenDate(int cat, DATE_T date,DATE_T currentDate)
{
    int l = 0; /*lowest*/
    int i;/*counter*/
    int h = product_in_cat[cat].openDateCount -1; /*heighest*/
    int m = h/2; /*middle*/
    int count = 0;
    PRODUCT_T *p = NULL;
    while(l <= h)
    {
        if(bidTimeCompare2(product_in_cat[cat].openDateSort[m].date.year,
                                product_in_cat[cat].openDateSort[m].date.month,
                                product_in_cat[cat].openDateSort[m].date.day,
                                date.year,
                                date.month,
                                date.day) < 0)
        {
            l = m +1;
        }
        else if(bidTimeCompare2(product_in_cat[cat].openDateSort[m].date.year,
                               product_in_cat[cat].openDateSort[m].date.month,
                               product_in_cat[cat].openDateSort[m].date.day,
                               date.year,
                               date.month,
                               date.day) == 0)
        {
            for(i=m;i>=0;i--)
            {
                if(bidTimeCompare2(product_in_cat[cat].openDateSort[i].date.year,
                                product_in_cat[cat].openDateSort[i].date.month,
                                product_in_cat[cat].openDateSort[i].date.day,
                                date.year,
                                date.month,
                                date.day) == 0)
                {
                    printProduct(product_in_cat[cat].openDateSort[i].pProduct,currentDate);
                    count = 1;
                }
                else
                {
                    i=-1;
                }
            }

            for(i=m+1;i<product_in_cat[cat].openDateCount;i++)
            {
                if(bidTimeCompare2(product_in_cat[cat].openDateSort[i].date.year,
                                product_in_cat[cat].openDateSort[i].date.month,
                                product_in_cat[cat].openDateSort[i].date.day,
                                date.year,
                                date.month,
                                date.day) == 0)
                {
                    printProduct(product_in_cat[cat].openDateSort[i].pProduct,currentDate);
                    count = 1;
                }
                else
                {
                    i=product_in_cat[cat].openDateCount;
                }
            }

            return count;
        }
        else 
        {
            h = m -1;
        }

        m = (l+h)/2;

    }
    return count;
}

/******************************************************************************
 * search for product bid using binary search
 * Return 1 - if product exist
 *        0 - if product does not exist
 *
 * Argument id - product id
 *          user - current user
 *          curerntDate - current date
 *          
 * Created by Supakorn Srisawas 62070503449
 */
int searchProductBid(int id, USER_T* user, DATE_T currentDate)
{
    int l = 0; /*lowest*/
    int h = histories[user->idUser -1].sizeofProductBit - 1; /*heighest*/
    int m = h/2; /*middle*/

    while(l <= h)
    {
        if(histories[user->idUser -1].productBid[m] < id)
        {
            l = m +1;
        }
        else if(histories[user->idUser -1].productBid[m] == id)
        {
            return 1;
        }
        else
        {
            h = m -1;
        }

        m = (l+h)/2;

    }
    return 0;
}

/******************************************************************************
 * this function bid product by insert price and user
 * into product struct
 *
 * Argument USER_T* user
 * 			PRODUCT_T* product
 * 		 	double price
 *
 * Return  1 if bid auction success
 * 		  -1 if the auction is expired
 *        -2 if bid price is less than minimum bid
 *        -3 if bid price is less than or equal to current price
 *        -4 if user try to bid his/her product
 *        -5 if user try to bid when he/she is current highest bid
 *        
 * Created by Supakorn Srisawas 62070503449
 */
int bidProduct(PRODUCT_T* product, USER_T* user, DATE_T currentDate, double price)
{	
	if(bidTimeCompare(currentDate.year,currentDate.month,currentDate.day,currentDate.hour,currentDate.minute,
	 				  product->dateClose.year,product->dateClose.month,product->dateClose.day,product->dateClose.hour,product->dateClose.minute) == 1)
    {
	 	return -1;
	}
	if((price - product->nowPrice) < product->minbid)
	{
		return -2;
	}
	if(price <= product->nowPrice)
	{
		return -3;
	}
	if(product->hostId == user->idUser)
	{
		return -4;
	}
	// if(products->userAuthorityId == user->idUser)
	// {
 //        return -5;
	// }

    if(searchProductBid(product->idProduct, user, currentDate)==0)
    {
        histories[user->idUser - 1].sizeofProductBit++;
        histories[user->idUser - 1].productBid = realloc(histories[user->idUser - 1].productBid,histories[user->idUser - 1].sizeofProductBit*sizeof(int));
        if(histories[user->idUser - 1].productBid == NULL)
        {
            printf("Error reallocating memories\n");
            exit(0);
        }
        insertProductBidSort(product->idProduct,user);     
    }

	product->nowPrice = price;
	product->userAuthorityId = user->idUser;

	products[product->idProduct -1].nowPrice = price;
	products[product->idProduct -1].userAuthorityId = user->idUser;

	writeProduct(products);
	return 1;
}

/******************************************************************************
 * insert product bit into history
 * return 1 - if success
 *
 * Arguement id - user id
 *           user - current user
 * 
 * Created by Supakorn Srisawas 62070503449
 */
int insertProductBidSort(int id, USER_T* user)
{
	int i; /*counter*/
	for(i = histories[user->idUser - 1].sizeofProductBit-2;(i >= 0 && histories[user->idUser - 1].productBid[i] > id); i--)
	{
		histories[user->idUser - 1].productBid[i+1] = histories[user->idUser - 1].productBid[i];
	}
	histories[user->idUser - 1].productBid[i+1] = id;
    
    writeHistory(histories);
    return 0;
}


/******************************************************************************
 * This function register new user and add user
 * into data structure 
 * 
 * Return 1 - if register success
 *        0 - in case user already exist
 *
 * Argument user - current user
 * 
 * Created by Supakorn Srisawas 62070503449
 */
int registerNewUser(USER_T user)
{
	USER_T * u = searchUserByEmail(user.email);
	if(u == NULL)
	{
		insertUser(user);
		return 1;
	}
	return 0;
}

/******************************************************************************
 * This function login and return USER
 * 
 * Return USER_T* - if login success
 * 		  NULL    - if login fail
 * 		  
 * Output argument int* status
 * 		  -1 - if user does not exit 
 *        -2 - password does not match
 *         1 - if login success 
 * Argument email - email of user
 *          password - password of user
 *
 * Created by Supakorn Srisawas 62070503449
 */
USER_T* login(char *email, char* password, int* status)
{
	USER_T * user = NULL;
	user = searchUserByEmail(email);
	if(user == NULL)
	{
		*status = -1;
		return NULL;
	}
	else
	{
		if(strcmp(user->password,password)!=0)
		{
			*status = -2;
			return NULL;
		}
	}
	*status = 1;
	return user;
}

/******************************************************************************
 *This function display all products in lists
 * return 1 - if found product
 *        0 - if not founr
 *
 * Argument cat - category of product
 *          currentDate - current date
 *          
 * created by Narapathra Morakrant 62070503464
 */
int showProductByCat(int cat,DATE_T currentDate)
{    
	int i;
    int count = 0;
    
    for (i = 0; i < totalProductsLocation; i++)
    {
        printProduct(lProduct[i],currentDate);
        count = 1;
    }
    
    return count;
}

/******************************************************************************
 * display history of product user had bid
 *
 *  return 0 - if not found
 *  return 1 - if found
 *
 *  Argument userId - user id
 *           currentDate - current date
 *  Created by Narapathra Morakrant 62070503464
 */
int showbidHistory(int userId, DATE_T currentDate)
{
    int lproductId;
    int count = 0;

    HISTORY_T thisHistory = histories[userId - 1];

    for(int i = 0; i < thisHistory.sizeofProductBit; i++)
    {
        lproductId = thisHistory.productBid[i] - 1;
        printProductHistory(lProduct[lproductId],currentDate,userId);
        count = 1;
    }
    
    return count;
}

/******************************************************************************
 * display all auctions user had created
 *
 * return 1 - if found auctions
 *        0 - not found
 * 
 * Argument userId - user id
 *          currentDate - current date 
 * 
 * Created by Narapathra Morakrant 62070503464
 */
int showsellHistory(int userId,DATE_T currentDate)
{
    int lproductId;
    int count = 0;

    HISTORY_T thisHistory = histories[userId - 1];

    for(int i = 0; i < thisHistory.sizeofSealAuction; i++)
    {         
        lproductId = thisHistory.sealAuction[i] - 1;
        printProduct(lProduct[lproductId],currentDate);
        count = 1;
    }
    
    return count;
}

/******************************************************************************
 * save user information when user edited
 * 
 * return 1 - if success
 *        0 - if fail
 *        
 *  Created by Narapathra Morakrant 62070503464
 */
int saveEditInfo()
{
    if(writeUser(users_by_id) == 1)
    {
        return 1;
    }
    
    return 0;
}

/******************************************************************************
 * close program and write all file into data
 * 
 * return - if finished
 *
 * Created by Supakorn Srisawas 62070503449
 */
int closeProgram()
{
    if(saveAllDatas(users_by_id,products,histories)==0)
    {
        printf("\nFailed to write file before closing the program\n");
    }
    
    free(products);
    int i;
    for(i=0;i<totalProductsLocation;i++)
    {
    	free(lProduct[i]);
    }
    free(lProduct);
    
    for(i=0;i<7;i++)
    {
	    free(product_in_cat[i].minBidSort);
	    free(product_in_cat[i].finalPricesort);
	    free(product_in_cat[i].closeDateSort);
	    free(product_in_cat[i].openDateSort);
    }
    
    for(i=0;i<TOTALHISTORY;i++)
    {
    	free(histories[i].productBid);
    	free(histories[i].sealAuction);
    }
    free(histories);
    
    return 0;
}

