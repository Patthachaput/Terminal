/*
 * fileManager.c
 *
 *      impliment all function that importance for read and write database file
 *
 *  Project CPE111 Data structure - TEAM TERMINAL
 *  Member: Natacha Punyathanasub       (Nut)       62070503415
 *          Patthachaput Thanesmaneerat (Jui)       62070503432
 *          Supakorn Srisawas           (Field)     62070503464
 *          Narapathra Morakrant        (Foremost)  62070503464
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"mainAuction.h"

//Delete soon when done all
// int main(int argc, char const *argv[])
// {
// 	USER_T* user;
// 	PRODUCT_T* product;
// 	HISTORY_T* history;

// 	init();

// 	writeUser(user);

// 	writProduct(product);

// 	writeHistory(history);

// 	getUser();

// 	getProduct();

// 	getHistory();

// 	saveAllData(user, product, history);
	
// 	return 0;
// }

/*******************************************************************************
 * Init
 * - check if program open first time
 * - return 1 if default file is exist
 *        -1 || -2 || -3 || -4 if defaault not exit and create file
 * - initial all global value
 * created by Patthachaput Thanesmaneerat 62070503432
 */
int init()
{
	int status;

	FILE* pProduct = NULL;
	FILE* pUser = NULL;
	FILE* pHistory = NULL;
	FILE* pBackup = NULL;

	USER_T numUser;
	PRODUCT_T numProduct;
	int numHistory;
	BACKUP_T numBackUp;

	status = allFileExist();

	pUser = fopen("user.dat", "rb");
	if(pUser == NULL)
	{
		printf("Error to read user file in <init>!\n");
		return 0;
	}
	if(fseek(pUser, -sizeof(USER_T), SEEK_END) == 0)
	{
		fread(&numUser, sizeof(USER_T), 1, pUser);
		TOTALUSER = numUser.idUser;
	}
	else
	{
		TOTALUSER = 0;
	}
	fclose(pUser);

	pProduct = fopen("product.dat", "rb");
	if(pProduct == NULL)
	{
		printf("Error to read product file in <init>!\n");
		return 0;
	}
	if(fseek(pProduct, -sizeof(PRODUCT_T), SEEK_END) == 0)
	{
		fread(&numProduct, sizeof(PRODUCT_T), 1, pProduct);
		TOTALPRODUCT = numProduct.idProduct;
	}
	else
	{
		TOTALPRODUCT = 0;
	}
	fclose(pProduct);

	pHistory = fopen("history.dat", "rb");
	if(pHistory == NULL)
	{
		printf("Error to read history file in <init>!\n");
		return 0;
	}
	if(fseek(pHistory, -sizeof(int), SEEK_END) == 0)
	{
		fread(&numHistory, sizeof(int), 1, pHistory);
		TOTALHISTORY = numHistory;
	}
	else
	{
		TOTALHISTORY = 0;
	}
	fclose(pHistory);

	ADDNEWUSER = 0;
	ADDNEWPRODUCT = 0;

	return status;
}

/* this function will savw all file return 1 if done else return 0 */
int saveAllData(USER_T* user, PRODUCT_T* product, HISTORY_T* history)
{
	int status = 0;

	status = writeUser(user);
	if(status == 0)
	{
		return status;
	}
	status = writProduct(product);
	if(status == 0)
	{
		return status;
	}
	status = writeHistory(history);

	return status;
}

/*******************************************************************************
 * writeUser
 * - write array of all user to file user.dat
 * - if Success return 1
 * - else return 0
 * - argument is array of all user
 * created by Patthachaput Thanesmaneerat 62070503432
 */
int writeUser(USER_T* user)
{
	int newIdUser = 1;
	int newTotalUser = 0;

	FILE* pUser = NULL;

	newTotalUser = TOTALUSER + ADDNEWUSER;
	for(int i = 0; i < newTotalUser; i++)
	{
		user[i].idUser = i + newIdUser;
	}

	if(newTotalUser > 0)
	{
		pUser = fopen("user.dat", "wb");
		if(pUser == NULL)
		{
			printf("Erroe to open user file! in <writeUser>\n");
			return 0;
		}
		if(fwrite(user, sizeof(USER_T), newTotalUser, pUser) != newTotalUser)
		{
			printf("Erroe to add user! in <writeUser>\n");
			return 0;
		}
		fclose(pUser);
		return 1;
	}

	return 0;
}

/*******************************************************************************
 * writProduct
 * - write array of all product to file product.dat
 * - if Success return 1
 * - else return 0
 * - argument is array of all product
 * created by Patthachaput Thanesmaneerat 62070503432
 */
int writProduct(PRODUCT_T* product)
{
	int newIdProduct = 1;
	int newTotalProduct = 0;

	FILE* pProduct = NULL;

	newTotalProduct = TOTALPRODUCT + ADDNEWPRODUCT;
	for(int i = 0; i < newTotalProduct; i++)
	{
		product[i].idProduct = i + newIdProduct;
	}

	if(newTotalProduct > 0)
	{
		
		pProduct = fopen("product.dat", "wb");
		if(pProduct == NULL)
		{
			printf("Error to open product file! in <writProduct>\n");
			return 0;
		}
		if(fwrite(product, sizeof(PRODUCT_T), newTotalProduct, pProduct) != newTotalProduct)
		{
			printf("Error to add product! in <writProduct>\n");
			return 0;
		}
		fclose(pProduct);
		
		TOTALPRODUCT = newTotalProduct;
		ADDNEWPRODUCT = 0;
		
		return 1;
	}

	return 0;
}

/*******************************************************************************
 * writeHistory
 * - write array of all history to file history.dat
 * - if Success return 1
 * - else return 0
 * - argument is array of all history
 * created by Patthachaput Thanesmaneerat 62070503432
 */
int writeHistory(HISTORY_T* history)
{
	int idUser;
	int sizeofProductBit;
	int sizaofSealAuction;
	int* productBid = NULL;
	int* sealAuction = NULL;

	int newNumOfHis = 1;
	int newTotalNumOfHis = 0;

	FILE* pHistory = NULL;

	newTotalNumOfHis = TOTALHISTORY + ADDNEWUSER;
	if(newTotalNumOfHis > 0)
	{
		pHistory = fopen("history.dat", "wb");
		if(pHistory == NULL)
		{
			printf("Error to read history file in <getHistory>!\n");
			return 0;
		}

		for(int i; i < newTotalNumOfHis; i++)
		{
			idUser = i + newNumOfHis;
			sizeofProductBit = history[i].sizeofProductBit;
			sizaofSealAuction = history[i].sizaofSealAuction;
			productBid = history[i].productBid;
			sealAuction = history[i].sealAuction;

		    if(fwrite(&sizeofProductBit, sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct2>\n");
				return 0;
			}
		    if(fwrite(&sizaofSealAuction, sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct3>\n");
				return 0;
			}
		    if(fwrite(productBid, sizeofProductBit * sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct4>\n");
				return 0;
			}
		    if(fwrite(sealAuction, sizaofSealAuction * sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct5>\n");
				return 0;
			}
		   	if(fwrite(&idUser, sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct1>\n");
				return 0;
			}
		}
	    fclose(pHistory);
	    
	    TOTALHISTORY = newTotalNumOfHis;
	    TOTALUSER = newTotalNumOfHis;
	    ADDNEWUSER = 0;
	    
	    return 1;
	}

	return 0;
}

/*******************************************************************************
 * getUser
 * - get all user in file user.dat
 * - if Success return array of all user
 * - else return NULL
 * created by Patthachaput Thanesmaneerat 62070503432
 */
USER_T* getUser()
{
	FILE* pUser = NULL;
	USER_T* allUser = NULL;

	pUser = fopen("user.dat", "rb");
	if(pUser == NULL)
	{
		printf("Error to read user file in <getUser>!\n");
		return allUser;
	}
	if(TOTALUSER != 0)
	{
		allUser = calloc(TOTALUSER, sizeof(USER_T));
		if(allUser == NULL)
		{
			printf("Error with alocade memory in <getUser>\n");
			return allUser;
		}

		for(int i = 0; i < TOTALUSER; i++)
		{
			if(fread(&allUser[i], sizeof(USER_T), 1, pUser) != 1)
			{
				printf("Can't read all data from database, please try agin! <getUser>\n");
				return allUser;
			}
		}
	}
	fclose(pUser);

	return allUser;
}

/*******************************************************************************
 * getProduct
 * - get all product in file product.dat
 * - if Success return array of all product
 * - else return NULL
 * created by Patthachaput Thanesmaneerat 62070503432
 */
PRODUCT_T* getProduct()
{
	FILE* pProduct = NULL;
	PRODUCT_T* allProduct = NULL;

	pProduct = fopen("product.dat", "rb");
	if(pProduct == NULL)
	{
		printf("Error to read product file in <getProduct>!\n");
		return allProduct;
	}
	if(TOTALPRODUCT != 0)
	{
		allProduct = calloc(TOTALPRODUCT, sizeof(PRODUCT_T));
		if(allProduct == NULL)
		{
			printf("Error with alocade memory in <getProduct>\n");
			return allProduct;
		}

		for(int i = 0; i < TOTALPRODUCT; i++)
		{
			if(fread(&allProduct[i], sizeof(PRODUCT_T), 1, pProduct) != 1)
			{
				printf("Can't read all data from database, please try agin! <getProduct>\n");
				return allProduct;
			}
		}
	}
	fclose(pProduct);

	return allProduct;
}

/*******************************************************************************
 * getHistory
 * - get all history in file history.dat
 * - if Success return array of all history
 * - else return NULL
 * created by Patthachaput Thanesmaneerat 62070503432
 */
HISTORY_T* getHistory()
{
	int idUser;
	int sizeofProductBit;
	int sizaofSealAuction;  /* miss spelling from sizeofSaleAuction */
	int* productBid;
	int* sealAuction;

	FILE* pHistory = NULL;
	HISTORY_T* allHistory = NULL;

	pHistory = fopen("history.dat", "rb");
	if(pHistory == NULL)
	{
		printf("Error to read history file in <getHistory>!\n");
		return allHistory;
	}
	if(TOTALHISTORY != 0)
	{
		allHistory = calloc(TOTALHISTORY, sizeof(HISTORY_T));
		if(allHistory == NULL)
		{
			printf("Error with alocade memory in <getHistory1>\n");
			return allHistory;
		}

		for(int i = 0; i < TOTALHISTORY; i++)
		{
			if(fread(&sizeofProductBit, sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read sizeofProductBit, please try agin! <getHistory>\n");
				return allHistory;
			}
			if(fread(&sizaofSealAuction, sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read sizaofSealAuction, please try agin! <getHistory>\n");
				return allHistory;
			}

			productBid = calloc(sizeofProductBit, sizeof(int));
			if(allHistory == NULL)
			{
				printf("Error with alocade memory in <getHistory2>\n");
				return allHistory;
			}
			sealAuction = calloc(sizaofSealAuction, sizeof(int));
			if(allHistory == NULL)
			{
				printf("Error with alocade memory in <getHistory3>\n");
				return allHistory;
			}

			if(fread(productBid, sizeofProductBit * sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read productBid, please try agin! <getHistory>\n");
				return allHistory;
			}
			if(fread(sealAuction, sizaofSealAuction * sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read sealAuction, please try agin! <getHistory>\n");
				return allHistory;
			}
			if(fread(&idUser, sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read idUser, please try agin! <getHistory>\n");
				return allHistory;
			}
			allHistory[i].idUser = idUser;
			allHistory[i].productBid = productBid;
			allHistory[i].sealAuction = sealAuction;
			allHistory[i].sizeofProductBit = sizeofProductBit;
			allHistory[i].sizaofSealAuction = sizaofSealAuction;
		}
	}
	fclose(pHistory);

	return allHistory;
}


/*******************************************************************************
 * allFileExist
 * - Local function used dy init.
 * - This function will check all file are exit or not,
 * - if all file are exit will return 1 else return negative
 * - number follow index of file and created it.
 * created by Patthachaput Thanesmaneerat 62070503432
 */
int allFileExist()
{
	int status = 1;
	int userExist = 0;
	int productExist = 0;
	int historyExist = 0;

	FILE* pProduct = NULL;
	FILE* pUser = NULL;
	FILE* pHistory = NULL;

	userExist = access("user.dat", F_OK);
	if(userExist < 0)
	{
		pUser = fopen("user.dat", "wb");
		if(pUser == NULL)
		{
			printf("Error with created user file! in <allFileExit>\n");
			exit(1);
		}
		fclose(pUser);
		status = -1;
	}

	productExist = access("product.dat", F_OK);
	if(productExist < 0)
	{
		pProduct = fopen("product.dat", "wb");
		if(pProduct == NULL)
		{
			printf("Error with created product file! in <allFileExit>\n");
			exit(2);
		}
		fclose(pProduct);
		status = -2;
	}

	historyExist = access("history.dat", F_OK);
	if(historyExist < 0)
	{
		pHistory = fopen("history.dat", "wb");
		if(pHistory == NULL)
		{
			printf("Error with created history file! in <allFileExit>\n");
			exit(3);
		}
		fclose(pHistory);
		status = -3;
	}

	return status;
}
