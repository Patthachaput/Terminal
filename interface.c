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

DATE_T createDateStruct2(char input[64])
{
    DATE_T dateInput;
    int day=0;
    int month=0;
    int year=0;
    int hour=0;
    int minute=0;
    
    dateInput.hour = 0;
    dateInput.minute = 0;
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
    printf("                                            1. Log in                             \n");
    printf("                                            2. Log in as guest                    \n");
    printf("                                            3. Register                           \n");
    printf("                                            4. Exit program                       \n\n");
    printf("===================================================================================================================\n\n");

    do
    {
        loginStatus = NLOGIN;
        choice = 0;
        printf(">>>>> How do you want to login? ");
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
        printf(">>>>> Please enter your email and password to login (leave blank to go back to login page)\n\n");
        printf("\tEmail: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", email);
        printf("\tPassword: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", password);
        
        if((strlen(email)==0)||(strlen(password)==0))
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
                printf("\n\tThere is no assosiate account with this email! Please go to register\n\n");
                break;
            }
            else
            {
                if(strcmp(bufferUser->password,password)==0)
                {
                    loginStatus = LOGIN;
                    loginUser = bufferUser;
                    printf("\n\tSuccessful login!\n\n");
                    break;
                }
                else
                {
                    loginUser = NULL;
                    printf("\n\tIncorrect email or password! please try again\n\n");
                }
            }
        }
        else
        {
            printf("\tInvalid email\n");
        }
        
    }while (loginStatus != 1);

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
    int checkBack = 0;
    USER_T newUser;
    
    do
    {
        printf(">>>>> Please enter your information\n");

        do
        {
            printf("\n");
            memset(email,0, sizeof(email));
            printf("\t* Please enter email following to these rules *\n");
            printf("\t- No embedded spaces or special characters anywhere in the email address, except . - @ _\n");
            printf("\t- Must begin with an alphanumeric (letter or digit) character.\n");
            printf("\t- Exactly one occurrence of the at­sign (@).\n");
            printf("\t- At least one alphabetic character before the at­sign.\n");
            printf("\t- Address must end in one of: .com, .net, .ac.th, or .co.th (top­level domains or TLD).\n");
            printf("\t- At least one alphanumeric character between the at­sign and the TLD.\n");
            printf("\t- No underscores after the at­sign.\n");
            printf("\t- At least one alphanumeric character between any periods that occur after the at­sign.\n\n");
            printf(">>>>> type ""BACK"" to go back to login page\n\n");
            printf("\tEmail: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", email);

            if(strcasecmp(email, "BACK") == 0)
            {
                printf("\n");
                return 0;
            }
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
            printf("\t* Please enter password following to these rules *\n");
            printf("\t- At least 8 characters long and no longer than 12 characters\n");
            printf("\t- MUST contain at least one upper case letter\n");
            printf("\t- MUST contain at least one lower case letter\n");
            printf("\t- MUST contain at least two digits\n");
            printf("\t- MUST contain at least one of the following special characters: ? @ %% $ #\n");
            printf("\t- MUST not contain any other special characters not in the list above\n\n");
            printf("\tPassword: ");
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
            printf("\t* Please enter your name following to these rules *\n");
            printf("\t- First and last names must be at least 2 characters long and no longer than 30 characters (each)\n");
            printf("\t- Do NOT include title.\n\n");
            printf("\tFull name (No title): ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%[^\n]", name);
            validate = validateName(name);
            if(validate == 1)
            {
                strcpy(newUser.name,name);
                break;
            }
        }while (validate != 1);

        do
        {
            printf("\n");
            memset(address,0, sizeof(address));
            printf("\t* Please enter address following to these rules *\n");
            printf("\t- Begins with a number (the house number) which can include a slash, e.g. “34/12”\n");
            printf("\tbut must have at least one digit before and one digit after the slash.\n");
            printf("\t- Next a street name which can include numbers as well as letters\n");
            printf("\t- Next an optional label “Road”, “Street” or “Lane”\n");
            printf("\t- a postal code must be five digits and which must begin with “10”\n\n");
            printf("\tAddress (Bangkok): ");
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
            printf("\t* Please enter phone number following to these rules *\n");
            printf("\t- Only digits and dashes allowed (no blanks)\n");
            printf("\t- Must include ten digits.\n");
            printf("\t- First two digits must be: 01, 05, 06, 08 or 09.\n\n");
            printf("\tPhone Number (Thai): ");
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
            printf("\t* Please enter bank account number following to these rules *\n");
            printf("\t- A bank account number is exactly 11 digits, with or without dashes.\n");
            printf("\t- If there are dashes, they must be type in like this: ddd­ddddd­ddd.\n");
            printf("\t- The first three digits must be one of the following: 206, 209, 128, 921, 403, 421.\n");
            printf("\t- The last three digits must include at least one zero.\n\n");
            printf("\tBank Account: ");
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
                printf("\tThe user with this email is already exist\n");
                printf("\tPlease try again\n");
            }
            else
            {
                printf("\n>>>>> This your information\n\n");
                printf("\tEmail: %s\n",email);
                printf("\tPassword: %s\n",password);
                printf("\tFull name (No title): %s\n",name);
                printf("\tAddress: %s\n",address);
                printf("\tPhone Number (Thai): %s\n",phoneNumber);
                printf("\tBank Account: %s\n",bankAccNumber);
                printf("\n\tSuccessful registeration!\n\n");
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
        printf(">>>>> Type the product ID that you want to bid (if none, type negative number) : ");
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
        printf("\tCannot find any product with this ID\n\n");
    }
    else
    {
        if(loginStatus == NLOGIN)
        {
            printf("\tSorry, you need to login to bid the product.\n\n");
        }
        else
        {
            printf("===================================================== BID PRODUCT =================================================\n\n");
            dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
            if(checkProductStatus(product,currentDate) == 0)
            {
                printProduct(product,currentDate);
                printf("\tSorry, you cannot bid this auction. It is already close.\n\n");
            }
            else
            {
                printProduct(product,currentDate);
                do
                {
                    bidAmount = 0;
                    printf(">>>>> Type the amount that you want to bid : ");
                    fgets(buffer,sizeof(buffer),stdin);
                    sscanf(buffer,"%lf", &bidAmount);
                    
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    validate = bidProduct(product,loginUser,currentDate,bidAmount);
                    
                    if(bidAmount > 0 )
                    {
                        if(validate == 1)
                        {
                            printf("\n\tBid Success!\n\n");
                        }
                        else if(validate == -2)
                        {
                            printf("\n\tUnsuccesful, The bid price is less than minimum bid.\n\n");
                        }
                        else if(validate == -3)
                        {
                            printf("\n\tUnsuccesful, The bid price is less than or equal to current bid.\n\n");
                        }
                        else if(validate == -4)
                        {
                            printf("\n\tUnsuccesful, You cannot bid your our product.\n\n");
                        }
                        else if(validate == -5)
                        {
                            printf("\n\tUnsuccesful, You are the current highest bid.\n\n");
                        }
                        break;
                    }

                } while (bidAmount <= 0);
            }
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
    int found = 1;
    
    printf("========================================= SERACH FOR SPECIFIC ITEM ===============================================\n\n");
    printf("                                         1. Date Open                                                         \n");
    printf("                                         2. Date Close                                                        \n");
    printf("                                         3. Minimum Bid                                                       \n");
    printf("                                         4. Final Price (closed auction only)                                 \n");
    printf("                                         5. Back to homepage                                                  \n\n");
    printf("===================================================================================================================\n\n");
       
    do
    {
        choice = 0;
        printf(">>>>> Choose your category to browse : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
          
        if((choice > 5)||(choice < 1))
        {
            printf("\tInvalid choice! please try again\n\n");
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
                printf(">>>>> Type open date you want to search (dd-mm-yyyy) : ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%[^\n]", date);
                printf("\n");
                validate = validateDateTime2(date);
                if(validate != 1)
                {
                    printf("\tInvalid Date - please try again\n");
                }
                else
                {
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    inputDate = createDateStruct2(date);
                    if(searchByOpenDate(category, inputDate, currentDate)==0)
                    {
                        found = 0;
                        printf("\tSorry, we cannot find any product with your specification.\n\n");
                    }
                    break;
                }
            } while (validate == 1);
            break;
        case 2:
            do
            {
                memset(date,0,sizeof(date));
                printf(">>>>> Type close date you want to search (dd-mm-yyyy) : ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%[^\n]", date);
                printf("\n");
                validate = validateDateTime2(date);
                if(validate == 0)
                {
                    printf("\tInvalid Date - please try again\n");
                }
                else
                {
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    inputDate = createDateStruct2(date);
                    if(searchByCloseDate(category, inputDate, currentDate)==0)
                    {
                        found = 0;
                        printf("\n\tSorry, we cannot find any product with your specification.\n\n");
                    }
                    break;
                }
            } while (validate == 0);
            break;
        case 3:
            do
            {
                minBid = 0;
                printf(">>>>> Type amount of minimum bid you want to searh: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%lf", &minBid);
                printf("\n");
                if(minBid <= 0)
                {
                    printf("\tInvalid amount - please try again\n");
                }
                else
                {
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    if(searchByMinbid(category, minBid, currentDate) == 0)
                    {
                        found = 0;
                        printf("\n\tSorry, we cannot find any product with your specification.\n\n");
                    }
                    break;
                }
            } while (minBid <= 0);
            break;
        case 4:
            do
            {
                finalPrice = 0;
                printf(">>>>> Type amount of final price you want to searh (Closed Auction only): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%lf", &finalPrice);
                printf("\n");
                if(finalPrice < 0)
                {
                    printf("\tInvalid amount - please try again\n");
                }
                else
                {
                    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
                    if(searchByFinalPrice(category, finalPrice, currentDate)==0)
                    {
                        found = 0;
                        printf("\n\tSorry, we cannot find any product with your specification.\n\n");
                    }
                    break;
                }
            } while (finalPrice <= 0);
            break;
        default:
            break;
    }
    
    if((choice != 5)&&(found != 0))
    {
        bidMenu();
    }
    
    return 0;
}

int browseByCategory()
{
    char buffer[32];
    int choice = 0;
    int validate = 0;
    
    printf("=============================================== BROWSE BY CATEGORY ===============================================\n\n");
    printf("                                              1. Home & Garden                                            \n");
    printf("                                              2. Collectibles                                             \n");
    printf("                                              3. Sport                                                    \n");
    printf("                                              4. Electronic                                               \n");
    printf("                                              5. Fashion                                                  \n");
    printf("                                              6. Health & Beauty                                          \n");
    printf("                                              7. Motor                                                    \n");
    printf("                                              8. Print all products                                       \n");
    printf("                                              9. Back to homepage                                         \n\n");
    printf("===================================================================================================================\n\n");
    
    do
    {
        choice = 0;
        printf(">>>>> Choose a category to browse : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
        printf("\n");
       
        if((choice > 9)||(choice < 1))
        {
            printf("\tInvalid choice! please try again\n\n");
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
        validate = showProductByCat(choice,currentDate);  /* print all the product in ID sequence */
        if(validate == 1)
        {
            bidMenu();
        }
        else
        {
            printf("\tSorry, There is currently no product in the market.\n\n");
        }
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
    printf("                * Browse Instruction *                                                                             \n");
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
        printf(">>>>> Do you want to continue (Y/N) ? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", choice);
       
        if((choice[0] != 'Y')&&(choice[0] != 'N') && (choice[0] != 'y')&&(choice[0] != 'n'))
        {
            printf("\tInvalid choice! please try again\n\n");
        }
        else if(choice[0] == 'Y' || choice[0] == 'y')
        {
            continues = 1;
            break;
        }
        else
        {
            break;
        }
        
    }while ((choice[0] != 'Y')&&(choice[0] != 'N') && (choice[0] != 'y')&&(choice[0] != 'n'));
    
    printf("\n");
    
    return continues;
}

void bidHistory()
{
    char buffer[32];
    int userId = -1;
    int productId = -1;
    int validate = 0;
    
    printf("================================================= BID HISTORY =====================================================\n\n");

    userId = loginUser->idUser;
    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);

    validate = showbidHistory(userId,currentDate);
    if(validate == 0)
    {
        printf("\tYou haven't bid any product yet.\n\n");
    }
    
    printf("===================================================================================================================\n\n");
    
}

void saleHistory()
{
    char buffer[32];
    int choice = 0;
    int userId = -1;
    int productId = -1;
    int validate = 0;
    
    printf("================================================ SALE HISTORY =====================================================\n\n");
    
    userId = loginUser->idUser;
    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);

    validate = showsellHistory(userId,currentDate);
    if(validate == 0)
    {
        printf("\tYou haven't sold any product yet.\n\n");
    }
    
    printf("===================================================================================================================\n\n");

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
        printf(">>>>> Please enter the product information\n");
        memset(name,0, sizeof(name));
        printf("\tName: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", name);
        strcpy(newProduct.name,name);
        
        memset(description,0, sizeof(description));
        printf("\tDescription: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", description);
        strcpy(newProduct.description,description);
        
        do
        {
            category = 0;
            printf("\tCategory: \n");
            printf("\t\t1.Home & Garden\n");
            printf("\t\t2.Collectibles\n");
            printf("\t\t3.Sport\n");
            printf("\t\t4.Electronic\n");
            printf("\t\t5.Fashion\n");
            printf("\t\t6.Health & Beauty\n");
            printf("\t\t7.Motor\n");
            printf("\tChoose your category ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%d", &category);
            if((category > 7)||(category < 1))
            {
               validate = 0;
               printf("\tInvalid choice! please try again\n\n");
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
            printf("\tMinimum Bid: ");
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
            printf("\tDate Close (dd-mm-yyyy hh:tt) : ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%[^\n]", dateClose);
            validate = validateDateTime(dateClose);
            if(validate == 1)
            {
                newProduct.dateClose = createDateStruct(dateClose);
                break;
            }
            else
            {
                printf("\tInvalid input please type agian\n");
            }
        }while (validate != 1);
        
        dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
        
        if(validate == 1)
        {
            insertProduct(newProduct,loginUser,currentDate);
            printf("\n>>>>> This is your product information\n\n");
            printf("\tName: %s\n",name);
            printf("\tDescription: %s\n",description);
            printCategory(category);
            printf("\tMinimum Bid: %0.2lf\n",minBid);
            printf("\tDate Close: %s\n",dateClose);
            printf("\n\tSuccessful created the auction!\n\n");
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
    printf("                           1. Email: %s                      \n",loginUser->email);
    printf("                           2. Password: %s                   \n",loginUser->password);
    printf("                           3. Full name (No title): %s       \n",loginUser->name);
    printf("                           4. Address: %s                    \n",loginUser->address);
    printf("                           5. Phone Number (Thai): %s        \n",loginUser->phoneNumber);
    printf("                           6. Bank Account: %s               \n",loginUser->bankAccNumber);
    printf("                           7. Back to homepage               \n\n");
    printf("===================================================================================================================\n\n");
   
    do
    {
        choice = 0;
        printf(">>>>> What do you want to edit? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
       
        if((choice > 7)||(choice < 1))
        {
            printf("\tInvalid choice! please try again\n\n");
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
    USER_T* bufferUser;
    char buffer[64];
    char email[64];
    char password[64];
    char name[64];
    char address[64];
    char phoneNumber[64];
    char bankAccNumber[64];
    int validate = 0;
    
    bufferUser = searchUserById(loginUser->idUser);
    if(bufferUser == NULL)
    {
        printf("\tCannot find user by ID\n");
        return 0;
    }

    switch (choice) {
        case 1:
            do
            {
                printf("\n");
                memset(email,0, sizeof(email));
                printf("\t* Please enter email following to these rules *\n");
                printf("\t- No embedded spaces or special characters anywhere in the email address, except . - @ _\n");
                printf("\t- Must begin with an alphanumeric (letter or digit) character.\n");
                printf("\t- Exactly one occurrence of the at­sign (@).\n");
                printf("\t- At least one alphabetic character before the at­sign.\n");
                printf("\t- Address must end in one of: .com, .net, .ac.th, or .co.th (top­level domains or TLD).\n");
                printf("\t- At least one alphanumeric character between the at­sign and the TLD.\n");
                printf("\t- No underscores after the at­sign.\n");
                printf("\t- At least one alphanumeric character between any periods that occur after the at­sign.\n\n");
                printf("\tEmail: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", email);
                validate = validateEmail(email);
                if(validate == 1)
                {
                    strcpy(bufferUser->email,email);
                    break;
                }
            }while (validate != 1);
            break;
        case 2:
            do
            {
                printf("\n");
                memset(password,0, sizeof(password));
                printf("\t* Please enter password following to these rules *\n");
                printf("\t- At least 8 characters long and no longer than 12 characters\n");
                printf("\t- MUST contain at least one upper case letter\n");
                printf("\t- MUST contain at least one lower case letter\n");
                printf("\t- MUST contain at least two digits\n");
                printf("\t- MUST contain at least one of the following special characters: ? @ %% $ #\n");
                printf("\t- MUST not contain any other special characters not in the list above\n\n");
                printf("\tPassword: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", password);
                validate = validatePassword(password);
                if(validate == 1)
                {
                    strcpy(bufferUser->password,password);
                    break;
                }
            }while (validate != 1);
            break;
        case 3:
            do
            {
                printf("\n");
                memset(name,0, sizeof(name));
                printf("\t* Please enter your name following to these rules *\n");
                printf("\t- First and last names must be at least 2 characters long and no longer than 30 characters (each)\n");
                printf("\t- Do NOT include title.\n\n");
                printf("\tFull name (No title): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%[^\n]", name);
                validate = validateName(name);
                if(validate == 1)
                {
                    strcpy(bufferUser->name,name);
                    break;
                }
            }while (validate != 1);
            break;
        case 4:
            do
            {
                printf("\n");
                memset(address,0, sizeof(address));
                printf("\t* Please enter address following to these rules *\n");
                printf("\t- Begins with a number (the house number) which can include a slash, e.g. “34/12”\n");
                printf("\tbut must have at least one digit before and one digit after the slash.\n");
                printf("\t- Next a street name which can include numbers as well as letters\n");
                printf("\t- Next an optional label “Road”, “Street” or “Lane”\n");
                printf("\t- a postal code must be five digits and which must begin with “10”\n\n");
                printf("\tAddress (Bangkok): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%[^\n]", address);
                validate = validateAddress(address);
                if(validate == 1)
                {
                    strcpy(bufferUser->address,address);
                    break;
                }
            }while (validate != 1);
            break;
        case 5:
            do
            {
                printf("\n");
                memset(phoneNumber,0, sizeof(phoneNumber));
                printf("\t* Please enter phone number following to these rules *\n");
                printf("\t- Only digits and dashes allowed (no blanks)\n");
                printf("\t- Must include ten digits.\n");
                printf("\t- First two digits must be: 01, 05, 06, 08 or 09.\n\n");
                printf("\tPhone Number (Thai): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", phoneNumber);
                validate = validatePhoneNumThai(phoneNumber,buffer);
                if(validate == 1)
                {
                    strcpy(bufferUser->phoneNumber,phoneNumber);
                    break;
                }
            }while (validate != 1);
            break;
        case 6:
            do
            {
                printf("\n");
                memset(bankAccNumber,0, sizeof(bankAccNumber));
                printf("\t* Please enter bank account number following to these rules *\n");
                printf("\t- A bank account number is exactly 11 digits, with or without dashes.\n");
                printf("\t- If there are dashes, they must be type in like this: ddd­ddddd­ddd.\n");
                printf("\t- The first three digits must be one of the following: 206, 209, 128, 921, 403, 421.\n");
                printf("\t- The last three digits must include at least one zero.\n\n");
                printf("\tBank Account: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", bankAccNumber);
                validate = validateBankAcc(bankAccNumber,buffer);
                if(validate == 1)
                {
                    strcpy(bufferUser->bankAccNumber,bankAccNumber);
                    break;
                }
            }while (validate != 1);
            break;
        default:
            break;

    }

    loginUser = bufferUser;
    saveEditInfo();
    if(validate == 1)
    {
        printf("Succressfull Edit!\n");
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
        printf(">>>>> What do you want to do? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
        
        if((choice > 6)||(choice < 1))
        {
            printf("\tInvalid choice! please try again\n\n");
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
    
    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
    buildData(currentDate);   /* build data structure by reading data in the file */
    
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
        loginUser = NULL;
        loginStatus = NLOGIN;
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
                            loginUser = NULL;
                            loginStatus = NLOGIN;
                            break;
                    }
                }
            }while (choice == 1);
        }
        else if (choice == 2)
        {
            loginUser = NULL;
            loginStatus = NLOGIN;
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
            loginUser = NULL;
            loginStatus = NLOGIN;
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
