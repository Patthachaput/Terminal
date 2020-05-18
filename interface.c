/*
 * interface.c
 *
 *      the main file that interact with user and call other functions
 *  from other file to process the program
 *
 *
 *  Project CPE111 Data structure - TEAM TERMINAL
 *  Member: Natacha Punyathanasub       (Nut)       62070503415
 *          Patthachaput Thanesmaneerat (Jui)       62070503432
 *          Supakorn Srisawas           (Field)     62070503449
 *          Narapathra Morakrant        (Foremost)  62070503464
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "validate.h"
#include "dataBuilder.h"

#define NLOGIN 0
#define LOGIN 1
#define GUEST 2


int loginStatus = 0; /* 0 for not log in, 1 for login with account, 2 for guest */
USER_T* loginUser;
DATE_T currentDate;

DATE_T createDateStruct(char input[64])
{
    DATE_T dateInput;
    char date[32];
    char time[32];
    int day=0;
    int month=0;
    int year=0;
    int hour=0;
    int minute=0;
    
    sscanf(input,"%s %s",date,time);
    sscanf(date,"%d-%d-%d",&day,&month,&year);
    sscanf(time,"%d:%d", &hour, &minute);
    
    dateInput.hour = hour;
    dateInput.minute = minute;
    dateInput.day = day;
    dateInput.month = month;
    dateInput.year = year;
    
    return dateInput;
}

int logInMenu()
{
    char buffer[32];
    int choice = 0;
    
    printf("================================================== LOGIN PAGE =====================================================\n\n");
    printf("                                            1.Log in                             \n");
    printf("                                            2.Log in as guest                    \n");
    printf("                                            3.Register                           \n");
    printf("                                            4.Exit program                       \n\n");
    printf("===================================================================================================================\n\n");

    do
    {
        loginStatus = NLOGIN;
        choice = 0;
        printf("How do you want to login? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);

        if((choice > 4)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
    
    }while ((choice > 4)||(choice < 1));
    
    printf("\n");
    
    return choice;
}

int loginInput()
{
    char buffer[64];
    char email[64];
    char password[64];
    int len = 0;
    int validate = 0;
    USER_T* bufferUser;
    
    
    do
    {
        printf("Please enter your email and password to login\n");
        printf("Email: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", email);
        printf("Password: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", password);
        
        if ((strcmp(email,"\0")==1)&&(strcmp(password,"\0")==1))
        {
            loginStatus = NLOGIN;
            break;
        }
        
        validate = validateEmail(email);
        if(validate == 1)
        {
            bufferUser = searchUserByEmail(email);
            
            if(bufferUser == NULL)
            {
                printf("There is no assosiate account with this email! Please go to register\n\n");
            }
            else
            {
                if(strcmp(bufferUser->password,password)==0)
                {
                    loginStatus = LOGIN;
                    loginUser = bufferUser;
                    printf("Successful login!\n\n");
                    break;
                }
                else
                {
                    loginUser = NULL;
                    printf("Incorrect email or password! please try again\n\n");
                }
            }

        }
        
    }while (loginStatus != 1);
    
    /*
    printf("=========== Personal Info =========\n\n");
    printf("\t Email: %s\n",loginUser->email);
    printf("\t Password: %s\n",loginUser->password);
    printf("\t Full name (No title): %s\n",loginUser->name);
    printf("\t Address: %s\n",loginUser->address);
    printf("\t Phone Number (Thai): %s\n",loginUser->phoneNumber);
    printf("\t Bank Account: %s\n",loginUser->bankAccNumber);
    printf("\n");
    printf("===================================\n\n");
    printf("\n");
    */
    return loginStatus;
}

int registration()
{
    char buffer[64];
    char email[64];
    char password[64];
    char name[64];
    char address[64];
    char phoneNumber[64];
    char bankAccNumber[64];
    int validate = 0;
    USER_T newUser;
    
    do
    {
        printf("Please enter your information\n");

        do
        {
            printf("\n");
            memset(email,0, sizeof(email));
            printf("Email: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", email);
            validate = validateEmail(email);
            if(validate == 1)
            {
                strcpy(newUser.email,email);
                break;
            }
        }while (validate != 1);
    
        do
        {
            printf("\n");
            memset(password,0, sizeof(password));
            printf("Please enter password following to these rules\n");
            printf("- At least 8 characters long and no longer than 12 characters\n");
            printf("- MUST contain at least one upper case letter\n");
            printf("- MUST contain at least one lower case letter\n");
            printf("- MUST contain at least two digits\n");
            printf("- MUST contain at least one of the following special characters: ? @ %% $ #\n");
            printf("- MUST not contain any other special characters not in the list above\n");
            printf("Password: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", password);
            validate = validatePassword(password);
            if(validate == 1)
            {
                strcpy(newUser.password,password);
                break;
            }
        }while (validate != 1);
        
        do
        {
            printf("\n");
            memset(name,0, sizeof(name));
            printf("Full name (No title): ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%[^\n]", name);
            validate = validateName(name);
            if(validate == 1)
            {
                printf("\t\t%s\n",name);
                strcpy(newUser.name,name);
                break;
            }
        }while (validate != 1);
        
        do
        {
            printf("\n");
            memset(address,0, sizeof(address));
            printf("Please enter address following to these rules\n");
            printf("- Begins with a number (the house number) which can include a slash, e.g. “34/12”\n");
            printf("but must have at least one digit before and one digit after the slash.\n");
            printf("- Next a street name which can include numbers as well as letters\n");
            printf("- Next an optional label “Road”, “Street” or “Lane”\n");
            printf("- a postal code must be five digits and which must begin with “10”\n");
            printf("Address (Bangkok): ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%[^\n]", address);
            validate = validateAddress(address);
            if(validate == 1)
            {
                strcpy(newUser.address,address);
                break;
            }
        }while (validate != 1);
        
        do
        {
            printf("\n");
            memset(phoneNumber,0, sizeof(phoneNumber));
            printf("Phone Number (Thai): ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", phoneNumber);
            validate = validatePhoneNumThai(phoneNumber,buffer);
            if(validate == 1)
            {
                strcpy(newUser.phoneNumber,phoneNumber);
                break;
            }
        }while (validate != 1);
        
        do
        {
            printf("\n");
            memset(bankAccNumber,0, sizeof(bankAccNumber));
            printf("Bank Account: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", bankAccNumber);
            validate = validateBankAcc(bankAccNumber,buffer);
            if(validate == 1)
            {
                strcpy(newUser.bankAccNumber,bankAccNumber);
                break;
            }
        }while (validate != 1);
        
        if(validate == 1)
        {
            printf("\n");
            if(registerNewUser(newUser) == 0)
            {
                printf("The user with this email is already exist\n");
                printf("Please try again\n");
            }
            else
            {
                printf("\nThis your information\n");
                printf("\tEmail: %s\n",email);
                printf("\tPassword: %s\n",password);
                printf("\tFull name (No title): %s\n",name);
                printf("\tAddress: %s\n",address);
                printf("\tPhone Number (Thai): %s\n",phoneNumber);
                printf("\tBank Account: %s\n",bankAccNumber);
                printf("Successful registered!\n\n");
                break;
            }
        }
        
    }while (validate != 1);
    
    printf("\n");
    
    return validate;
}

int bidMenu()
{
    PRODUCT_T* product;
    char buffer[64];
    int productId= -1;
    int validate = 0;
    double bidAmount = 0;
    
    do
    {
        productId = -1;
        printf("Type the product ID that you want to bid (if none, type negative number) : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &productId);
        printf("\n");
        if(productId <= 0)
        {
            return 0;
        }
          
    }while (productId <= 0);
    
    product = searchProductById(productId);
    if(product == NULL)
    {
        printf("Cannot find any product with this ID\n");
    }
    else
    {
        dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
        if(checkProductStatus(product,currentDate) == 0)
        {
            printProduct(product,currentDate);
            printf("Sorry, you cannot bid this auction. It is already close.\n");
        }
        else
        {
            printProduct(product,currentDate);
            do
            {
                bidAmount = 0;
                printf("Type the amount that you want to bid : ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%lf", &bidAmount);
                
                dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                validate = bidProduct(product,loginUser,currentDate,bidAmount);
                
                if(bidAmount > 0 )
                {
                    if(validate == 1)
                    {
                        printf("Bid Success!\n\n");
                    }
                    else if(validate == -1)
                    {
                        printf("Unsuccesful, The bid price is less than minimum bid.\n\n");
                    }
                    else if(validate == -2)
                    {
                        printf("Unsuccesful, The bid price is less than or equal to current bid.\n\n");
                    }
                    else if(validate == -4)
                    {
                        printf("Unsuccesful, You cannot bid your our product.\n\n");
                    }
                    break;
                }

            } while (bidAmount <= 0);
        }
    }
    
    return 0;
    
}

int subBrowse(int category)
{
    DATE_T inputDate;
    char buffer[64];
    char date[64];
    double minBid = 0;
    double finalPrice = 0;
    int choice = 0;
    int validate = 0;
    
    printf("========================================= SERACH FOR SPECIFIC ITEM ===============================================\n\n");
    printf("                                          1.Date Open                                                         \n");
    printf("                                          2.Date Close                                                        \n");
    printf("                                          3.Minimum Bid                                                       \n");
    printf("                                          4.Final Price (closed auction only)                                 \n");
    printf("                                          5.Back to homepage                                                  \n\n");
    printf("===================================================================================================================\n\n");
       
    do
    {
        choice = 0;
        printf("Choose your category to browse : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
          
        if((choice > 5)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
          
    }while ((choice > 5)||(choice < 1));
    
    switch (choice) {
        case 1:
            do
            {
                memset(date,0,sizeof(date));
                printf("Type open date you want to search (dd-mm-yyyy hh:tt) : ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%[^\n]", date);
                validate = validateDateTime(date);
                if(validate == 0)
                {
                    printf("\tInvalid Date - please try again\n");
                }
                else
                {
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    inputDate = createDateStruct(date);
                    searchByOpenDate(category, inputDate, currentDate);
                    bidMenu();
                    break;
                }
            } while (validate == 0);
            break;
        case 2:
            do
            {
                memset(date,0,sizeof(date));
                printf("Type close date you want to search (dd-mm-yyyy hh:tt) : ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%[^\n]", date);
                validate = validateDateTime(date);
                if(validate == 0)
                {
                    printf("\tInvalid Date - please try again\n");
                }
                else
                {
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    inputDate = createDateStruct(date);
                    searchByCloseDate(category, inputDate, currentDate);
                    break;
                }
            } while (validate == 0);
            break;
        case 3:
            do
            {
                minBid = 0;
                printf("Type amount of minimum bid you want to searh: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%lf", &minBid);
                if(minBid <= 0)
                {
                    printf("\tInvalid amount - please try again\n");
                }
                else
                {
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    searchByMinbid(category, minBid, currentDate);
                    break;
                }
            } while (minBid <= 0);
            break;
        case 4:
            do
            {
                finalPrice = 0;
                printf("Type amount of final price you want to searh (Closed Auction only): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%lf", &finalPrice);
                if(finalPrice <= 0)
                {
                    printf("\tInvalid amount - please try again\n");
                }
                else
                {
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    searchByFinalPrice(category, finalPrice, currentDate);
                    break;
                }
            } while (finalPrice <= 0);
            break;
        default:
            break;
    }
    
    if(choice != 5)
    {
        bidMenu();
    }
    
    return 0;
}

int browseByCategory()
{
    char buffer[32];
    int choice = 0;
    
    printf("=============================================== BROWSE BY CATEGORY ===============================================\n\n");
    printf("                                              1.Home & Garden                                            \n");
    printf("                                              2.Collectibles                                             \n");
    printf("                                              3.Sport                                                    \n");
    printf("                                              4.Electronic                                               \n");
    printf("                                              5.Fashion                                                  \n");
    printf("                                              6.Health & Beauty                                          \n");
    printf("                                              7.Motor                                                    \n");
    printf("                                              8.print all product                                        \n");
    printf("                                              9.Back to homepage                                         \n\n");
    printf("===================================================================================================================\n\n");
    
    do
    {
        choice = 0;
        printf("Choose a category to browse : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
        printf("\n");
       
        if((choice > 9)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
       
    }while ((choice > 9)||(choice < 1));
    
    if(choice == 9)
    {
        return 0; /* back to home page */
    }
    else if (choice == 8)
    {
        showProductByCat(choice,currentDate);  /* print all the product in ID sequence */
        bidMenu();
    }
    else
    {
        subBrowse(choice);
    }
    
    return 0;
}

int browse()
{
    char buffer[32];
    char choice[2];
    int continues = 0;
    
    printf("====================================================== BROWSE =====================================================\n\n");
    printf("                Browse Instruction                                                                                 \n");
    printf("                Firstly  - Choose your categories or print all the products in ID sequence                         \n");
    printf("                Secondly - Choose how you want to seach the product in that category                               \n");
    printf("                                > Open Date                                                                        \n");
    printf("                                > Close Date                                                                       \n");
    printf("                                > Minimum Bid                                                                      \n");
    printf("                                > Final Price (Closed Auction only)                                                \n\n");
    printf("===================================================================================================================\n\n");

    do
    {
        memset(choice,0,sizeof(choice));
        printf("Do you want to continue (Y/N) ? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", choice);
       
        if((choice[0] != 'Y')&&(choice[0] != 'N'))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else if(choice[0] == 'Y')
        {
            continues = 1;
            break;
        }
        else
        {
            break;
        }
        
    }while ((choice[0] != 'Y')&&(choice[0] != 'N'));
    
    printf("\n");
    
    return continues;
}

void bidHistory()
{
    char buffer[32];
    int choice = 0;
    int userId = -1;
    int productId = -1;
    int validate = 0;
    
    printf("================================================= BID HISTORY =====================================================\n\n");
    printf("                                          1.View all bid history                                              \n");
    printf("                                          2.Search bid history by product ID                                  \n");
    printf("                                          3.Back to homepage                                                  \n\n");
    printf("===================================================================================================================\n\n");
    
    do
    {
        choice = 0;
        printf("How do you want to view your bid history : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
          
        if((choice > 3)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
          
    }while ((choice > 5)||(choice < 1));
    
    userId = loginUser->idUser;
    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
    
    if(choice == 1)
    {
        showbidHistory(userId,currentDate);
    }
    else if(choice == 2)
    {
        printf("Please type the product ID : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &productId);
        if(searchProductBid(productId,loginUser,currentDate) == 0)
        {
            printf("You haven't bid this product yet\n\n");
        }
    }
}

void saleHistory()
{
    char buffer[32];
    int choice = 0;
    int userId = -1;
    int productId = -1;
    int validate = 0;
    
    printf("================================================= BID HISTORY =====================================================\n\n");
    printf("                                          1.View all sell history                                              \n");
    printf("                                          2.Search sell history by product ID                                  \n");
    printf("                                          3.Back to homepage                                                  \n\n");
    printf("===================================================================================================================\n\n");
    
    do
    {
        choice = 0;
        printf("How do you want to view your sell history : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
          
        if((choice > 3)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
          
    }while ((choice > 5)||(choice < 1));
    
    userId = loginUser->idUser;
    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
    
    if(choice == 1)
    {
        showsellHistory(userId,currentDate);
    }
    else if(choice == 2)
    {
        printf("Please type the product ID : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &productId);
        if(searchSaleAuction(productId,loginUser,currentDate) == 0)
        {
            printf("You are not selling any product with this ID\n\n");
        }
    }
}

int createAuction()
{
    char buffer[64];
    char buffer2[64];
    int choice = 0;
    char name[64];
    char description[120];      /*product description*/
    int category = 0;           /*fixed category*/
    char dateClose[64];
    double minBid = 0;          /*minimum bid price*/
    int validate = 0;
    PRODUCT_T newProduct;
    
    do
    {
        printf("Please enter the product information\n");
        memset(name,0, sizeof(name));
        printf("Name: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", name);
        strcpy(newProduct.name,name);
        
        memset(description,0, sizeof(description));
        printf("Description: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", description);
        strcpy(newProduct.description,description);
        
        do
        {
            category = 0;
            printf("Category: \n");
            printf("\t1.Home & Garden\n");
            printf("\t2.Collectibles\n");
            printf("\t3.Sport\n");
            printf("\t4.Electronic\n");
            printf("\t5.Fashion\n");
            printf("\t6.Health & Beauty\n");
            printf("\t7.Motor\n");
            printf("Choose your category ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%d", &category);
            if((category > 7)||(category < 1))
            {
               validate = 0;
               printf("Invalid choice! please try again\n\n");
            }
            else
            {
                newProduct.category = category;
                break;
            }
        }while (validate != 1);
        
        do
        {
            memset(buffer2,0, sizeof(buffer2));
            minBid =0;
            printf("Minimum Bid: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", buffer2);
            validate = 0;
            if(strlen(buffer2) == checkDigits(buffer2))
            {
                sscanf(buffer2,"%lf", &minBid);
                newProduct.minbid = minBid;
                validate = 1;
                break;
            }
        }while (validate != 1);
        
        do
        {
            memset(dateClose,0, sizeof(dateClose));
            printf("Date Close (dd-mm-yyyy hh:tt) : ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%[^\n]", dateClose);
            validate = validateDateTime(dateClose);
            if(validate == 1)
            {
                newProduct.dateClose = createDateStruct(dateClose);
                break;
            }
        }while (validate != 1);
        
        if(validate == 1)
        {
            insertProduct(newProduct,loginUser);
            printf("\nThis is your product information\n");
            printf("\tName: %s\n",name);
            printf("\tDescription: %s\n",description);
            printCategory(category);
            printf("\tMinimum Bid: %0.2lf\n",minBid);
            printf("\tDate Close: %s\n",dateClose);
            printf("Successful created the auction!\n\n");
            break;
        }
        
    }while (validate != 1);
    
    return 1;
}

int personalInfo()
{
    char buffer[32];
    int choice = 0;
    
    printf("=================================================== PERSONAL INFO =================================================\n\n");
    printf("                    1. Email: %s                      \n",loginUser->email);
    printf("                    2. Password: %s                   \n",loginUser->password);
    printf("                    3. Full name (No title): %s       \n",loginUser->name);
    printf("                    4. Address: %s                    \n",loginUser->address);
    printf("                    5. Phone Number (Thai): %s        \n",loginUser->phoneNumber);
    printf("                    6. Bank Account: %s               \n",loginUser->bankAccNumber);
    printf("                    7. Back to homepage               \n\n");
    printf("===================================================================================================================\n\n");
   
    do
    {
        choice = 0;
        printf("What do you want to edit? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
       
        if((choice > 7)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
       
    }while ((choice > 7)||(choice < 1));
           
    return choice;

}

int editInfo(int choice)
{
    char buffer[64];
    char email[64];
    char password[64];
    char name[64];
    char address[64];
    char phoneNumber[64];
    char bankAccNumber[64];
    int validate = 0;
    
    switch (choice) {
        case 1:
            do
            {
                printf("\n");
                memset(email,0, sizeof(email));
                printf("Email: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", email);
                validate = validateEmail(email);
                if(validate == 1)
                {
                    strcpy(loginUser->email,email);
                    break;
                }
            }while (validate != 1);
            break;
        case 2:
            do
            {
                printf("\n");
                memset(password,0, sizeof(password));
                printf("Please enter password following to these rules\n");
                printf("- At least 8 characters long and no longer than 12 characters\n");
                printf("- MUST contain at least one upper case letter\n");
                printf("- MUST contain at least one lower case letter\n");
                printf("- MUST contain at least two digits\n");
                printf("- MUST contain at least one of the following special characters: ? @ %% $ #\n");
                printf("- MUST not contain any other special characters not in the list above\n");
                printf("Password: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", password);
                validate = validatePassword(password);
                if(validate == 1)
                {
                    strcpy(loginUser->password,password);
                    break;
                }
            }while (validate != 1);
            break;
        case 3:
            do
            {
                printf("\n");
                memset(name,0, sizeof(name));
                printf("Full name (No title): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%[^\n]", name);
                validate = validateName(name);
                if(validate == 1)
                {
                    printf("\t\t%s\n",name);
                    strcpy(loginUser->name,name);
                    break;
                }
            }while (validate != 1);
            break;
        case 4:
            do
            {
                printf("\n");
                memset(address,0, sizeof(address));
                printf("Please enter address following to these rules\n");
                printf("- Begins with a number (the house number) which can include a slash, e.g. “34/12”\n");
                printf("but must have at least one digit before and one digit after the slash.\n");
                printf("- Next a street name which can include numbers as well as letters\n");
                printf("- Next an optional label “Road”, “Street” or “Lane”\n");
                printf("- a postal code must be five digits and which must begin with “10”\n");
                printf("Address (Bangkok): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%[^\n]", address);
                validate = validateAddress(address);
                if(validate == 1)
                {
                    strcpy(loginUser->address,address);
                    break;
                }
            }while (validate != 1);
            break;
        case 5:
            do
            {
                printf("\n");
                memset(phoneNumber,0, sizeof(phoneNumber));
                printf("Phone Number (Thai): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", phoneNumber);
                validate = validatePhoneNumThai(phoneNumber,buffer);
                if(validate == 1)
                {
                    strcpy(loginUser->phoneNumber,phoneNumber);
                    break;
                }
            }while (validate != 1);
            break;
        case 6:
            do
            {
                printf("\n");
                memset(bankAccNumber,0, sizeof(bankAccNumber));
                printf("Bank Account: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", bankAccNumber);
                validate = validateBankAcc(bankAccNumber,buffer);
                if(validate == 1)
                {
                    strcpy(loginUser->bankAccNumber,bankAccNumber);
                    break;
                }
            }while (validate != 1);
            break;
        default:
            break;

    }
    
    return 0;
}

int homePage()
{
    char buffer[32];
    int choice = 0;

    printf("==================================================== Homepage =====================================================\n\n");
    printf("                                             1.Browse                                                    \n");
    printf("                                             2.Bid history                                               \n");
    printf("                                             3.Sale history                                              \n");
    printf("                                             4.Create new auction                                        \n");
    printf("                                             5.Edit personal info                                        \n");
    printf("                                             6.Log out                                                   \n\n");
    printf("===================================================================================================================\n\n");
    
    do
    {
        choice = 0;
        printf("What do you want to do? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
        
        if((choice > 6)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
        
    }while ((choice > 6)||(choice < 1));
    
    printf("\n");
    
    return choice;
}

int main()
{
    int choice = 0;
    
    buildData();   /* build data structure by reading data in the file */
    
    printf("+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n");
    printf("===================================================================================================================\n");
    printf("                                          ONLINE    AUCTION    PROGRAM                                             \n");
    printf("===================================================================================================================\n");
    printf("+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n\n");
    printf("                                     !! WELCOME TO ONLINE AUCTION PROGRAM !!                                       \n\n");
    printf("                      An online market for you to open auctions or you can be the one to bid!                      \n");
    printf("                 Hope you like our program, instruction guidelines are down below. Have fun bidding                \n\n");
    printf("                                        >>>>>>> GUIDE FOR ALL USER <<<<<<<                                         \n");
    printf("                  For Guest                                                                                        \n");
    printf("                      - Login as guest to browse through our product list, however you need to                     \n");
    printf("                      login to bid and sell item. (A detailed instruction for browsing will be                     \n");
    printf("                      state in the browse option)                                                                  \n");
    printf("                      - You can register by choosing 'register' option in login page.                              \n\n");
    printf("                  For Seller                                                                                       \n");
    printf("                      - You can create an auction by choosing 'create new auction' in our homepage.                \n");
    printf("                      - View all the products you sell in 'Sell history.'                                          \n\n");
    printf("                  For Buyer/Bidder                                                                                 \n");
    printf("                      - You can browse through our product list in 'browse' option in our homepage.                \n");
    printf("                      (A detailed instruction for browsing will be state in the browse option)                     \n");
    printf("                      - View all the products you have bid in 'Bid history.'                                       \n");
    printf("                      - For checking, if you win the auction or not, you have to go to 'Bid history'               \n");
    printf("                      to check you winning status will be show there.                                              \n\n\n");
    
    do
    {
        choice = logInMenu();
        
        if (choice == 1)
        {
            choice = loginInput();
            do
            {
                if(choice == LOGIN)
                {
                    choice = homePage();
                    switch (choice) {
                        case 1:
                            choice = browse();
                            if(choice == 1)
                            {
                                browseByCategory();
                            }
                            choice = 1;
                            break;
                        case 2:
                            bidHistory();
                            choice = 1;
                            break;
                        case 3:
                            saleHistory();
                            choice = 1;
                            break;
                        case 4:
                            if (createAuction() == 1)
                            {
                                choice = 1;
                            }
                            break;
                        case 5:
                            choice = personalInfo();
                            editInfo(choice);
                            choice = 1;
                            break;
                        default:
                            break;
                    }
                }
            }while (choice == 1);
        }
        else if (choice == 2)
        {
            do
            {
                choice = browse();
                if(choice == 1)
                {
                    browseByCategory();
                }
                else
                {
                    break;
                }
            } while (choice == 1);
        }
        else if (choice == 3)
        {
            registration();
        }
        else
        {
            closeProgram();
            break;
        }
        
    }while (choice != 4);
    
    return 0;
}
