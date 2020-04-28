/**
  *  dataBuilder.h
  *
  *  This file build data structure for
  *  entire project
 */

#include "dataBuilder.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/*this structure sort by price*/
typedef struct{
    double price;
    PRODUCT_T* pProduct;
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

USER_T * users_by_id; /*keep entire users sort by id*/
USER_T * users_by_email; /*keep entire users sort by email*/

PRODUCT_T * products; /*keep entire product*/
PRODUCT_T ** lProduct; /*keep entire location of products*/
PRODUCT_IN_CAT product_in_cat[7]; /*all product in 7 category*/

HISTORY_T * histories; /*keep entire histories for all users*/

int totalUsersByEmail =0;
int totalProductsLocation =0;
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
    users_by_email = calloc(TOTALUSER,sizeof(USER_T));
    if(users_by_id == NULL || users_by_email==NULL)
    {
        printf("Error allocating memories\n");
        exit(1);
    }
    users_by_id = getUser();

    histories = calloc(TOTALHISTORY,sizeof(HISTORY_T));
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
    	*p=products[i];

    	/*keep products location in list*/
    	lProduct[totalProductsLocation] = p;
    	totalProductsLocation++;

    	insertMinbidSort(p);
    	insertfinalPriceSort(p);
    	insertOpenDateSort(p);
    	insertCloseDateSort(p);
    }
    
    for(i=0;i<TOTALUSER;i++)
    {
    	insertUserSortByEmail(users_by_id[i]);
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
    users_by_id = realloc(users_by_id,(TOTALUSER+ADDNEWUSER)*sizeof(USER_T));
    users_by_email = realloc(users_by_email,(TOTALUSER+ADDNEWUSER)*sizeof(USER_T));
    
    ADDNEWHISTORY++;
    HISTORY_T user_history;
    user_history.idUser = user.idUser;
    user_history.sizeofProductBit = 0;
    user_history.sizaofSealAuction = 0;
    user_history.productBid = calloc(user_history.sizeofProductBit,sizeof(int));
    user_history.sealAuction = calloc(user_history.sizaofSealAuction,sizeof(int));

    histories[TOTALHISTORY+ADDNEWHISTORY-1] = user_history;

    users_by_id[TOTALUSER+ADDNEWUSER-1] = user;
    insertUserSortByEmail(user);
}

/* insert users into data structure sort by name
 * No return
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
}

/* serch for users by email 
 * using binary search
 *
 * Return USER_T - if user is exist
 *        NULL - if user is not exist
 */
USER_T * searchUserByEmail(char* email)
{
	int l = 0; /*lowest*/
	int h = TOTALUSER+ADDNEWUSER-1; /*heighest*/
	int m = h/2; /*middle*/
	USER_T *u = NULL;
	
	while(l <= h)
	{
		if(strcmp(users_by_email[m].email,email)<0)
		{
			l = m +1;

		}
		else if(strcmp(users_by_email[m].email,email)==0)
		{
			u = &users_by_email[m];
			return u;
		}
		else 
		{
			h = m -1;
		}

		m = (l+h)/2;

	}
	return NULL;
}

/* insert product into data structure
 * No return
 */
int insertProduct(PRODUCT_T product, USER_T * user)
{
    ADDNEWPRODUCT++;
    product.idProduct = TOTALPRODUCT + ADDNEWPRODUCT;
    product.nowPrice = 0; /*set default bid price*/
	products = realloc(products,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_T));

    /*create new memmory for searching*/
	PRODUCT_T* p = calloc(1,sizeof(PRODUCT_T));
	*p = product;

    /*dynamic allocation for searching*/
    product_in_cat[product.category].finalPricesort = realloc(product_in_cat[product.category].finalPricesort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_PRICE));
    product_in_cat[product.category].minBidSort = realloc(product_in_cat[product.category].minBidSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_PRICE));
    product_in_cat[product.category].openDateSort = realloc(product_in_cat[product.category].openDateSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_DATE));
    product_in_cat[product.category].closeDateSort = realloc(product_in_cat[product.category].closeDateSort,(TOTALPRODUCT+ADDNEWPRODUCT)*sizeof(PRODUCT_DATE));
    
    lProduct = realloc(lProduct,sizeof(PRODUCT_T*));

    products[TOTALPRODUCT+ADDNEWPRODUCT-1] = product;

    lProduct[totalProductsLocation] = p;
    totalProductsLocation++;

    user->history->sizaofSealAuction++;
    user->history->sealAuction = realloc(user->history->sealAuction,user->history->sizaofSealAuction);
    user->history->sealAuction[user->history->sizaofSealAuction-1] = product.idProduct;

   	insertMinbidSort(p);
    insertfinalPriceSort(p);
	insertOpenDateSort(p);
	insertCloseDateSort(p);


}	

/* insert product for searching by min bid price.
 * No return
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
}

/* insert product for searching by final price.
 * No return
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

}

/* insert product for searching by open date.
 * No return
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
}

/* insert product for searching by close date. 
 * No return
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
}

/* searching for product by product id
 * Return  PRODUCT_T - in case found
 * 		   NULL - in case not found 
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

/* searching for product by minimum bid
 * using binary search
 *
 * Arguments cat - category of product
 * 			 bid - amount of bid price 
 * 			 
 * Return  PRODUCT_T* - in case found
 * 		   NULL - in case not found 
 */
PRODUCT_T* searchByMinbid(int cat, double bid)
{
	int l = 0; /*lowest*/
	int h = product_in_cat[cat].minBidCount-1; /*heighest*/
	int m = h/2; /*middle*/
	PRODUCT_T *p = NULL;
	
	while(l <= h)
	{
		if(product_in_cat[cat].minBidSort[m].price < bid)
		{
			l = m +1;
		}
		else if(product_in_cat[cat].minBidSort[m].price == bid)
		{
			p = product_in_cat[cat].minBidSort[m].pProduct;
			return p;
		}
		else 
		{
			h = m -1;
		}

		m = (l+h)/2;

	}
	return NULL;
}

/* searching for product by final price
 * using binary search
 *
 * Arguments cat - category of product
 * 			 bid - amount of bid price 
 * 	
 * Return  PRODUCT_T - in case found
 * 		   NULL - in case not found 
 */
PRODUCT_T* searchByFinalPrice(int cat, double bid)
{
	int l = 0; /*lowest*/
	int h = product_in_cat[cat].finalPriceCount-1; /*heighest*/
	int m = h/2; /*middle*/
	PRODUCT_T *p = NULL;
	
	while(l <= h)
	{
		if(product_in_cat[cat].finalPricesort[m].price < bid)
		{
			l = m +1;
		}
		else if(product_in_cat[cat].finalPricesort[m].price == bid)
		{
			p = product_in_cat[cat].finalPricesort[m].pProduct;
			return p;
		}
		else 
		{
			h = m -1;
		}

		m = (l+h)/2;

	}
	return NULL;
}

/* searching for product by close date
 * using binary search
 *
 * Arguments cat - category of product
 * 			 bid - amount of bid price 
 * 	
 * Return  PRODUCT_T - in case found
 * 		   NULL - in case not found 
 */
PRODUCT_T* searchByCloseDate(int cat, DATE_T date)
{
	int l = 0; /*lowest*/
	int h = product_in_cat[cat].closeDateCount -1; /*heighest*/
	int m = h/2; /*middle*/
	PRODUCT_T *p = NULL;
	
	while(l <= h)
	{
		if(bidTimeCompare(product_in_cat[cat].closeDateSort[m].date.year,
    							product_in_cat[cat].closeDateSort[m].date.month,
    							product_in_cat[cat].closeDateSort[m].date.day,
    							product_in_cat[cat].closeDateSort[m].date.hour,
    							product_in_cat[cat].closeDateSort[m].date.minute,
    							date.year,
    							date.month,
    							date.day,
    							date.hour,
    							date.minute) < 0)
		{
			l = m +1;
		}
		else if(bidTimeCompare(product_in_cat[cat].closeDateSort[m].date.year,
    							product_in_cat[cat].closeDateSort[m].date.month,
    							product_in_cat[cat].closeDateSort[m].date.day,
    							product_in_cat[cat].closeDateSort[m].date.hour,
    							product_in_cat[cat].closeDateSort[m].date.minute,
    							date.year,
    							date.month,
    							date.day,
    							date.hour,
    							date.minute) == 0)
		{
			p = product_in_cat[cat].closeDateSort[m].pProduct;
			return p;
		}
		else 
		{
			h = m -1;
		}

		m = (l+h)/2;

	}
	return NULL;
}

/* searching for product by open date
 * using binary search
 *
 * Arguments cat - category of product
 * 			 bid - amount of bid price 
 * 	
 * Return  PRODUCT_T - in case found
 * 		   NULL - in case not found 
 */
PRODUCT_T* searchByOpenDate(int cat, DATE_T date)
{
	int l = 0; /*lowest*/
	int h = product_in_cat[cat].openDateCount -1; /*heighest*/
	int m = h/2; /*middle*/
	PRODUCT_T *p = NULL;
	
	while(l <= h)
	{
		if(bidTimeCompare(product_in_cat[cat].openDateSort[m].date.year,
    							product_in_cat[cat].openDateSort[m].date.month,
    							product_in_cat[cat].openDateSort[m].date.day,
    							product_in_cat[cat].openDateSort[m].date.hour,
    							product_in_cat[cat].openDateSort[m].date.minute,
    							date.year,
    							date.month,
    							date.day,
    							date.hour,
    							date.minute) < 0)
		{
			l = m +1;
		}
		else if(bidTimeCompare(product_in_cat[cat].openDateSort[m].date.year,
    							product_in_cat[cat].openDateSort[m].date.month,
    							product_in_cat[cat].openDateSort[m].date.day,
    							product_in_cat[cat].openDateSort[m].date.hour,
    							product_in_cat[cat].openDateSort[m].date.minute,
    							date.year,
    							date.month,
    							date.day,
    							date.hour,
    							date.minute) == 0)
		{
			p = product_in_cat[cat].openDateSort[m].pProduct;
			return p;
		}
		else 
		{
			h = m -1;
		}

		m = (l+h)/2;

	}
	return NULL;
}

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
int bidProduct(PRODUCT_T* product, USER_T* user, DATE_T currentDate, double price)
{	
	if(bidTimeCompare(currentDate.year,currentDate.month,currentDate.day,currentDate.hour,currentDate.minute,
					  product->dateClose.year,product->dateClose.month,product->dateClose.day,product->dateClose.hour,product->dateClose.minute) == 1)
	{
		return -1;
	}
	if(price <= product->nowPrice)
	{
		return -2;
	}

	product->nowPrice = price;
	product->userAuthority = user;
	product->userAuthorityId = user->idUser;

	products[product->idProduct].nowPrice = price;
	products[product->idProduct].userAuthorityId = user->idUser;

	return 1;
}

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

/*This function register new user and add user
 * into data structure 
 * 
 * Return 1 - if register success
 *        0 - in case user already exist*/

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

/*This function login and return USER
 * 
 * Return USER_T* - if login success
 * 		  NULL    - if login fail
 * 		  
 * Output argument int* status
 * 		  -1 - if user does not exit 
 *        -2 - password does not match
 *         1 - if login success */
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
	user->history = &histories[user->idUser - 1];
	return user;
}
/*This function display all products in lists*/
int showProductByCat(int cat)
{    
	int i;
    for (i = 0; i < totalProductsLocation; i++)
    {
    	printf("Id: %d\n", lProduct[i]->idProduct);
        printf("Name: %s\n",lProduct[i]->name);
        printf("Minbid %.2f\n", lProduct[i]->minbid);
        printf("Now price: %.2f \n\n",lProduct[i]->nowPrice );
    }
}

int showUsers()
{
	int i;
	for(i=0;i<TOTALUSER+ADDNEWUSER;i++)
	{
		printf("Id: %d\n",users_by_id[i].idUser);
		printf("Name: %s\n",users_by_id[i].name );
		printf("Email: %s\n", users_by_id[i].email);
		printf("Password: %s\n\n", users_by_id[i].password);
	}
}

/*close program and write all file into data
 * No return
 */
int closeProgram()
{
    writProduct(products);
    writeUser(users_by_id);
    writeHistory(histories);
}

USER_T* testUser(int id)
{
	return &users_by_id[id-1];
}