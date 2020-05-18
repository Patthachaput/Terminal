/*
 * validate.c
 *
 *      contains all validate functions
 *          - email
 *          - password
 *          - name(no title)
 *          - thai phone number
 *          - bank account number
 *          - home address
 *          - date time (dd-mm-yyyy hh:tt)
 *
 *
 *  Project CPE111 Data structure - TEAM TERMINAL
 *  Member: Natacha Punyathanasub       (Nut)       62070503415
 *          Patthachaput Thanesmaneerat (Jui)       62070503432
 *          Supakorn Srisawas           (Field)     62070503464
 *          Narapathra Morakrant        (Foremost)  62070503464
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAXLEN 128

/*********************************************************************************
 * CheckSpcae
 *  - function which determine is the input start with space
 *  - get the string input from the user
 *  - return 0 for space found and 1 for no space found
 *  created by Narapathra Morakrant 62070503464
 */
int checkSpace(char input[MAXLEN])
{
    int correctness =0;
    
    if (isspace(input[0]) != 0)
    {
        printf("\tNot valid - spaces before input found\n");
    }
    else
    {
        correctness =1;
    }
    
    return correctness;
}

/*********************************************************************************
 * CheckDigit
 *  - function which determine how many digits are in the string
 *  - get the string input from the user
 *  - return the amount of digits found
 *  created by Narapathra Morakrant 62070503464
 */
int checkDigits(char input[MAXLEN])
{
    int i =0;       //variable use in loop
    int digits =0;  //variable for keeping the amount of digits
    
    //loop for finding digits
    for (i =0; i <= strlen(input); i++)
    {
        if (isdigit(input[i])!=0)
        {
            digits++;
        }
    }
    return digits;
}

/*********************************************************************************
 * CheckAlphabet
 *  - function which determine how many alphabet are in the string
 *  - get the string input from the user
 *  - return the amount of alphabet found
 *  created by Narapathra Morakrant 62070503464
 */
int checkAlphabet(char input[MAXLEN])
{
    int i =0;           //variable use in loop
    int alphabet =0;    //variable for keeping the amount of alphabets
    
    //loop for finding alphabets
    for (i =0; i <= strlen(input); i++)
    {
        if (isalpha(input[i])!=0)
        {
            alphabet++;
        }
    }
    return alphabet;
}

/**********************************************************************************
 * checkUpperCase.
 * - A function to check how many upper case alphabetic character does it have.
 * - 'password' is the password put in by the user.
 * - This function returns number of upper case alphabetic character.
 * Created by Narapathra Morakrant 62070503464
 */
int checkUpperCase(char password[MAXLEN])
{
    int i = 0;                /* variable which is used in loop.*/
    int upperCase = 0;        /* counter for each upper case alphabetic character detected.*/
    int stringLength = 0;
    
    stringLength = strlen(password);
    
    for (i=0; i<=stringLength; i++)
    {
        if (isupper(password[i]))
        {
            upperCase++;
        }
    }
    
    return upperCase;
}

/**********************************************************************************
 * checkLowerCase.
 * - A function to check how many lower case alphabetic character does it have.
 * - 'password' is the password put in by the user.
 * - This function returns number of lower case alphabetic character.
 * Created by Narapathra Morakrant 62070503464
 */
int checkLowerCase(char password[MAXLEN])
{
    int i = 0;                /* variable which is used in loop.*/
    int lowerCase = 0;        /* counter for each upper case alphabetic character detected.*/
    int stringLength = 0;
    
    stringLength = strlen(password);
    
    for (i=0; i<=stringLength; i++)
    {
        if (islower(password[i]))
        {
            lowerCase++;
        }
    }
    
    return lowerCase;
}

/**********************************************************************************
 * checkSymbol.
 * - A function to check how many upper case alphabetic character does it have.
 * - 'password' is the password put in by the user.
 * - This function returns number of upper case alphabetic character.
 * Created by Narapathra Morakrant 62070503464
 */
int checkSymbol(char password[MAXLEN])
{
    int i=0;
    int j=0;
    int symbolLength=0;
    int stringLength=0;
    int countSymbol=0;
    char symbol[MAXLEN] = {'?','@','%','$','#'};     /* array that contains a set of symbol to check. */
    
    stringLength = strlen(password);
    symbolLength = strlen(symbol);
    
    for(i=0; i<=stringLength; i++)
    {
        for(j=0;j<symbolLength;j++)
        {
            if(password[i] == symbol[j]) /* If the character is the same as the symbolic character.*/
            {
                countSymbol++;
            }
        }
    }
    return countSymbol;
}

/*check Email function
 *
 *
 *
 * created by Natacha Punyathanasub 62070503415
 */
int checkEmail(char email[])
{
    int i;
    int valid=1;
    char *after;
    char *tld;

    //after variable is use for the @ (at-sign symbol) to cut into the two section
    //before-at and after-at by the way after at will be use to correct the tld that is 4-6
    //from the last position of input information.
    after = strrchr(email,'@');
    tld=&after[strlen(after)-6];

    //check for tld process.
    if (strcmp(tld,".ac.th")==0 || strcmp(tld,".co.th")==0 || strcmp(&tld[2],".com")==0 || strcmp(&tld[2],".net")==0)
    {
        valid=1;
    }
    else
    {
        printf("%s",tld);
        valid=-6;
    }

    for (i=0;i<strlen(after)-1;i++)
    {
        //check double period.
        if(after[i]=='.' && after[i+1]=='.')
        {
            valid=-7;
            break;
        }
        //check _ in after @ section.
        else if(after[i]=='_')
        {
            valid=-8;
            break;
        }
    }
    return valid;
}

/*
 * Continue function from Check email This function is
 * checking for case of special character in email.
 * created by Natacha Punyathanasub 62070503415
 */
int validEmail(char email[])
{
    int i;
    int at=0;
    int valid=0;

    for (i=0;i<strlen(email)-1;i++)
    {
        if (isspace(email[i])!=0)
        {
            valid=-1;
            break;
        }
        else if (ispunct(email[i]) != 0)
        {
            if (i == 0)
            {
                valid=-2;
                break;
            }
            else if (email[i]=='.'||email[i]=='_'||email[i]=='-'||email[i]=='/')
            {
                valid=0;
            }
            else if (email[i] =='@')
            {
                valid=0;
                at++;
                if (isalpha(email[i-1])==0 && isalpha(email[i+1])==0)
                {
                    valid=-3;
                    break;
                }
            }
            else
            {
                valid=-4;
                break;
            }
        }
    }
    if (valid == 0 && at != 1)
    {
        valid=-5;
    }
    if (valid==0)
    {
        valid=checkEmail(email);
    }
    
    return valid;
}

/* Control email function that check email result from the
 * email validation and it will be return 1 if it true.
 * and 0 if it not following the condition.(passing to the
 * validate function in validation.c(source file)
 * created by Natacha Punyathanasub 62070503415
 */
int validateEmail(char email[])
{
    int valid;
    int emailResult=0;
    char input[MAXLEN];
    if (strlen(email)<2)
    {
        return emailResult;
    }
    valid=validEmail(email);
    if (valid==1)
    {
        //printf("\tValid\n");
        emailResult = 1;
    }
    else
    {
        printf("\tInvalid\n");
        emailResult = 0;
    }
    
    return emailResult;
}

/**********************************************************************************
 * validatePassword.
 * A function to validate password with the following rules.
 * - At least 8 characters long and no longer than 12 characters.
 * - Contain at least one upper and lower case character.
 * - Contain at least 2 digits.
 * - Contain at least one of '? @ % $ #' and must not contain any other special characters.
 * return 0 for invalid date and 1 for valid date
 * Created by Narapathra Morakrant 62070503464
 */
int validatePassword(char password[MAXLEN])
{
    int stringLength = 0;
    int upperCase = 0;
    int lowerCase = 0;
    int digit = 0;
    int symbol = 0;
    int correctness = 0;
    
    stringLength = strlen(password);
    upperCase = checkUpperCase(password);
    lowerCase = checkLowerCase(password);
    digit = checkDigits(password);
    symbol = checkSymbol(password);
    
    if ((stringLength>=8) && (stringLength<=12))
    {
        if(upperCase>=1)
        {
            if (lowerCase>=1)
            {
                if (digit>=2)
                {
                    if (symbol>=1)
                    {
                        if (stringLength-digit-upperCase-lowerCase-symbol == 0)
                        {
                            //printf("\tValid\n");
                            correctness = 1;
                        }
                        else
                        {
                            printf("\tNot valid - contains other special character that is not allow\n");
                        }
                    }
                    else
                    {
                        printf("\tNot valid - does not contain special characters\n");
                    }
                }
                else
                {
                    printf("\tNot valid - less than 2 digits in the password\n");
                }
            }
            else
            {
                printf("\tNot valid - does not contain lower case\n");
            }
        }
        else
        {
            printf("\tNot valid - does not contain upper case\n");
        }
    }
    else
    {
        printf("\tNot valid - the password is too short or too long\n");
    }
    
    return correctness;
}

/**********************************************************************************
 * validateName
 * - This is checkNameTitle function.
 * - It use for check first and last name with title is valid or not.
 *  Created by Narapathra Morakrant 62070503464
 */
int validateName(char nameInput[])
{
    int countNameInput = 0;     /* for count total name input */
    int countFirstName = 0;     /* for count FirstName input */
    int countLastName = 0;      /* for count LastName input */
    int countSpace = 0;
    char *firstName, *lastName; /* for hold title,firstname,lastname in char */
    
    countNameInput = strlen(nameInput); /* measure length of name input */
    if( nameInput[countNameInput - 1] == '\n')
    {
        nameInput[countNameInput - 1] = '\0';
    }
   
    
    if(checkSpace(nameInput) != 1)
    {
        return 0;
    }
    
    /* count space */
    for(int i = 0; i < countNameInput; i++)
    {
        if(isspace(nameInput[i]) != 0)
        {
            countSpace++;
        }
    }

    if(countSpace == 1)
    {
        firstName = strtok(nameInput, " ");
        countFirstName = strlen(firstName);
        lastName = strtok(NULL, " ");
        countLastName = strlen(lastName);
        
        if((checkAlphabet(firstName) != countFirstName) || (checkAlphabet(lastName) != countLastName))
        {
            //printf("%d %d\n", countFirstName, countLastName);
            printf("\tNot valid - Must contains only alphabet\n");
            return 0;
        }
        
        /* check the input is first or last names too short or too long or not*/
        if(countFirstName < 2 || countLastName-1 < 2)
        {
            printf("\tNot valid - first or last names too short\n");
        }
        else if(countFirstName > 30 || countLastName-1 > 30)
        {
            printf("\tNot valid - first or last names too long\n");
        }
        else
        {
            //printf("\tValid\n");
            nameInput[countFirstName] = ' ';
            return 1;
        }
    }
    else
    {
        printf("\tNot valid - missing last name or have too many spaces\n");
    }
    
    return 0;
}

/**********************************************************************************
 * validatePhoneNumThai
 * - This is checkPhoneNumThai function.
 * - It use for check Thai mobile phone number is valid or not.
 *  Created by Patthachaput Thanesmaneerat 62070503432
 *  Edited by Narapathra Morakrant 62070503464
 */
int validatePhoneNumThai(char phoneNumInput[], char fromkeyboard[])
{
    int countInput = 0;     /* for count total input */
    int countPhoneNum = 0;  /* for count phone number input */
    int countDigit = 0;     /* for count digit */
    int countDashes = 0;    /* for count dashe */
    int doubleDash = 0;     /* for doubleDash value */
    
    /* measure length of input */
    countInput = strlen(fromkeyboard);
    countPhoneNum = strlen(phoneNumInput);
    
    /* check the input has space or not */
    if ((countInput - 1) == countPhoneNum)
    {
        countDigit = checkDigits(phoneNumInput);
        
        /* check the input has 10 digit or not */
        if(countDigit == 10)
        {
            /* count dashe and check the input is an alphabetic or not */
            for(int i = 0; i < countPhoneNum; i++)
            {
                if(isalpha(phoneNumInput[i]) != 0)
                {
                    if(phoneNumInput[i] == '-')
                    {
                        countDashes++;
                    }
                    else
                    {
                        printf("\tNot valid - have alphabetic in phone number\n");
                        return 0;
                    }
                }
             }
            
            if(countDashes >= 0 && countDashes <= 2)
            {
                /* chack the input has '--' or not */
                for (int i = 0; i < countPhoneNum; i++)
                {
                    if((phoneNumInput[i] == '-') && (phoneNumInput[i + 1] == '-'))
                    {
                        printf("\tNot valid - have two dashes together\n");
                        return 0;
                    }
                }
                
                /* chack the input is correct on condition '-' or not */
                if(phoneNumInput[0] == '-' || phoneNumInput[1] == '-')
                {
                    printf("\tNot valid - dash in wrong place (First or second character can't be dash)\n");
                }
                else if(phoneNumInput[countPhoneNum-1] == '-')
                {
                    printf("\tNot valid - Last character must not be dash\n");
                }
                /* chack the input is correct on condition first two digits or not */
                else if(phoneNumInput[0] != '0' || (phoneNumInput[1] != '1' && phoneNumInput[1] != '5' && phoneNumInput[1] != '6' && phoneNumInput[1] != '8' && phoneNumInput[1] != '9'))
                {
                    printf("\tNot valid - First two digits must be: 01, 05, 06, 08 or 09\n");
                }
                else
                {
                    //printf("\tValid\n");
                    return 1;
                }
            }
            else
            {
                printf("\tNot valid - have more than two dashes (Max is two deshes)\n");
            }
            
        }
        else
        {
            printf("\tNot valid - Phone numner is too short or too long (Must have 10 digits)\n");
        }
    }
    else
    {
        printf("\tNot valid - have space in phone number\n");
    }
    
    return 0;
}

/*=========================== address validation ===========================*/

/**********************************************************************************
 * addressCheck
 * - check is all the house numbers are correct
 * - and does not contain anything other than number and '/'
 * - return 1 if invalid 0 if valid
 * Created by Natacha Punyathanasub 62070503415
 * Edited by Narapathra Morakrant 62070503464
 */
int addressCheck(char address[])
{
    int i = 0;
    int invalid=0;
    int midValue = 0;
    int slashCount=0;
    if(isdigit(address[0]) != 1)
    {
        invalid = 1;
    }

    for(i=1;i<(strlen(address)-1);i++)
    {
        if( (isdigit(address[i]) != 1) && (address[i] != '/')  )
        {
            midValue = 1;
        }
    }
    for(i=0;i<(strlen(address)-1);i++)
    {
        if( address[i] == '/' )
        {
            slashCount++ ;
            if(isdigit(address[i+1]) == 0)
            {
            midValue = 1;
            }
        }
    }
    if(midValue == 1)
    {
        invalid = 1;
    }
    if(isdigit(address[ strlen(address) -1 ])!=1 )
    {
        invalid = 1;
    }
    if(slashCount>1)
    {
        invalid = 1;
    }
    return invalid;
}

/***********************************************************
 * validateAddress
 * 	- this function validate address
 *
 * Argument address - address of user
 * RETURN -1 - house number fail
 * 		  -2 - street name fail
 * 		  -3 - optional fail
 * 		  -4 - postalCode fail 
 *  	   1 - if success
 **/
int validateAddress(char* address)
{
	char number[10];
	char streetName[32];
	char optional[32];
	char postalCode[10];

	int i; /*counter*/

    if(address[strlen(address) - 1] == '\n')
    {
        address[strlen(address) - 1] = '\0';
    }

	sscanf(address,"%s %s %s %s",number,streetName,optional,postalCode);

	if(!isdigit(number[0]))
	{
		return -1;
	}
	
	for(i=0;i<strlen(number);i++)
	{
		if(!isdigit(number[i]))
		{
			if(number[i] != '/')
			{
				return -1;
			}
		}
	}

	for(i=0;i<strlen(streetName);i++)
	{
		if(ispunct(streetName[i]))
		{
			return -2;
		}
	}

	if(!(strcmp(optional,"Road")==0 || strcmp(optional,"Street")==0 || strcmp(optional,"Lane")==0))
	{
		return -3;
	}

	for(i=0;i<strlen(postalCode);i++)
	{
		if(!isdigit(postalCode[i]))
		{
			return -4;
		}
	}

	if(!(postalCode[0] == '1' && postalCode[1] == '0'))
	{
		return -4;
	}

	if(strlen(postalCode)!=5)
	{
		return -4;
	}

	return 1;

}


/*=========================== bankAccount validation ===========================*/

/*********************************************************************************
 * CheckDashs
 *  - function which determine is the value should have dash or not
 *    determine from thr string lenght
 *  - get the string input from the user
 *  - return 0 for invalid dash and 1 for valid dash
 * created by Narapathra Morakrant 62070503464
 */
int checkDashs(char bankAcc[MAXLEN])
{
    int correctness =0;
    
    if ((strlen(bankAcc) ==13)||(strlen(bankAcc) ==12))
    {
        if ((bankAcc[3] == '-')&&(bankAcc[9] == '-'))
        {
            correctness =1;
        }
        else
        {
            printf("\tNot valid - missing dash or dash in wrong place\n");
            return correctness;
        }
    }
    
    if (strlen(bankAcc) == 11)
    {
        correctness =1;
    }
    
    return correctness;
}


/*********************************************************************************
 * CheckLast3Digits
 *  - function which determine is the last 3 digits are valid, having 0
 *  - get the string input from the user
 *  - return 0 for invalid last 3 digits and 1 for valid last 3 digits
 * created by Narapathra Morakrant 62070503464
 */
int checkLast3Digits(char bankAcc[MAXLEN])
{
    int i =0;               //variable use in loop
    int correctness =0;
    int length =0;          //keeping the leght of the string input
    
    length = strlen(bankAcc);
    
    //loop for check the 0 in the last 3 digits
    for (i =0; i <= 3; i++)
    {
        if (bankAcc[(length-1)-i] == '0') //check the value reverse from the last string
        {
            correctness =1;
            break;
        }
    }
    
    if(correctness == 0)
    {
        printf("\tNot valid - no zero in the ending triplet\n");
    }
    
    return correctness;
}



/*********************************************************************************
 * CheckFirst3digits
 *  - function which determine is the first 3 digits are valid
 *  - get the string input from the user
 *  - return 0 for invalid first 3 digits and 1 for valid first 3 digits
 * created by Narapathra Morakrant 62070503464
 */
int checkFirst3digits(char bankAcc[MAXLEN])
{
    int i =0;               //variable use in loop
    int correctness =0;
    char validFirst3[6][4] = {"206","209","128","921","403","421"}; //set of valid first 3 digits use for checking
    
    for (i =0; i <= 6; i++)
    {
        if (strncmp(bankAcc,validFirst3[i],3) == 0)
        {
            correctness =1;
            break;
        }
    }
    
    if(correctness == 0)
    {
        printf("\tNot valid - wrong prefix\n");
    }
    
    return correctness;
}


/*********************************************************************************
 * CheckBankAccLenght
 *  - function which determine the bank account number is in the right format
 *    as when the bank account has dashes its lenght should be 13
 *    and when does have dashes its lenght should be 11
 *  - get the string input from the user
 *  - return 0 for invalid format and 1 for valid format
 * created by Narapathra Morakrant 62070503464
 */
int checkBankAccLenght(char bankAcc[MAXLEN])
{
    int correctness = 0;
    
    if (strlen(bankAcc) > 13)
    {
        printf("\tNot valid - Too long for bank account number\n");
    }
    else if (strlen(bankAcc) < 11)
    {
        if (checkDigits(bankAcc) == 11)
        {
            printf("\tNot valid - Too long for bank account number\n");
        }
        else
        {
            printf("\tNot valid - Too short for bank accout number\n");
        }
    }
    else if((strlen(bankAcc) == 11)||(strlen(bankAcc) == 13)||(strlen(bankAcc) == 12))
    {
        if (checkDigits(bankAcc) != 11)
        {
            printf("\tNot valid - bank account should have 11 digits and not contains letters\n");
        }
        else
        {
            correctness =1;
        }
    }
    
    return correctness;
}


/*********************************************************************************
 * validateBankAcc
 *  - function which check the bank account number is valid
 *  - get the string input from the user
 *  - call others function to print error message if it is invalid
 *  - return 0 for invalid date and 1 for valid date
 * created by Narapathra Morakrant 62070503464
 */
int validateBankAcc(char bankAcc[MAXLEN], char buffer[MAXLEN])
{
    int correctness =0;
    
    if (checkSpace(buffer) == 1)
    {
        if (checkBankAccLenght(bankAcc) == 1)
        {
            if (checkFirst3digits(bankAcc) == 1)
            {
                if (checkDashs(bankAcc) == 1)
                {
                    if (checkLast3Digits(bankAcc) == 1)
                    {
                        correctness = 1;
                        //printf("\tValid\n");
                    }
                }
            }
        }
    }
    return correctness;
}

/*=========================== date/time validation ===========================*/

/*********************************************************************************
 * dateTimeToday
 *  - Sets the pointer for day, month, year and
 *    to the correct values for today.
 *  created by Narapathra Morakrant 62070503464
 */
void dateTimeToday(int* pDay, int *pMonth, int* pYear, int* pHour, int* pMinute)
{
    time_t seconds = 0;
    struct tm * pTime;
    
    seconds = time(&seconds);
    pTime = localtime(&seconds);
    *pDay = pTime->tm_mday;
    *pMonth = pTime->tm_mon + 1;
    *pYear = pTime->tm_year + 1900;
    *pHour = pTime->tm_hour;
    *pMinute = pTime->tm_min;
}

/*********************************************************************************
 * CheckYear
 *  - function which check the year getting from user is valid
 *  - also check if that year is a leap, or not
 *  - get the string input from the user
 *  - return 0 for invalid year and 1 for valid year
 *  - return the leap year in the address pointed to by 'leapCheck'.
 * created by Narapathra Morakrant 62070503464
 */
int leapYear(int year)
{
    int correctness =0;
    int leapyear =0;        //keep the leap year value 1 for yes and 0 for not
    
    //check for leap year
    if (year % 4 ==0)
    {
        leapyear = 1;
        if (year % 100 ==0)
        {
            leapyear = 0;
            if (year % 400 ==0)
            {
                leapyear = 1;
            }
        }
    }
    
    return leapyear;
}

/*********************************************************************************
 * CheckFebuary
 *  - function which check the day getting from user is valid in Febuary
 *  - get the string input from the user
 *    leapYear from checkDay
 *  - return 0 for invalid day and 1 for valid day
 * created by Narapathra Morakrant 62070503464
 */
int checkFebuary(int dayCompare, int leapYear)
{
    int correctness =0;
    
    if (leapYear == 1)
    {
        if ((dayCompare < 1)||(dayCompare > 29))
        {
            printf("\tNot valid - day not in range (not a leap year)\n");
        }
        else if ((dayCompare >= 1)&&(dayCompare <= 29))
        {
            correctness =1;
        }
    }
    else
    {
        if ((dayCompare < 1)||(dayCompare > 28))
        {
            printf("\tNot valid - day not in range\n");
        }
        else if ((dayCompare >= 1)&&(dayCompare <= 28))
        {
            correctness =1;
        }
    }
    
    return correctness;
}


/*********************************************************************************
 * CheckDay
 *  - function which check the day getting from user is valid
 *  - get the string input from the user month and leapCheck
 *  - return 0 for invalid day and 1 for valid day
 * created by Narapathra Morakrant 62070503464
 */
int checkDay(int day ,int month, int leapyear)
{
    int correctness =0;
    
    //check for month that has maximum 31 days
    if ((month == 1)||(month == 3)||(month == 5)||(month == 7)||(month == 8)||(month == 10)||(month == 12))
    {
        if ((day < 1)||(day > 31))
        {
            printf("\tNot valid - day not in range\n");
        }
        else if ((day >= 1)&&(day <= 31))
        {
            correctness =1;
        }
    }
    //check for month that has maximum 30 days
    else if ((month == 4)||(month == 6)||(month == 9)||(month == 11))
    {
        if ((day < 1)||(day > 30))
        {
            printf("\tNot valid - day not in range\n");
        }
        else if ((day >= 1)&&(day <= 30))
        {
            correctness =1;
        }
    }
    //check for Febuary
    else if (month == 2)
    {
        if (checkFebuary(day, leapyear) == 1)
        {
            correctness =1;
        }
    }
    
    return correctness;
}

/*********************************************************************************
 * dateCompare
 *  - function which check the date getting from user is not in past
 *  - get the string input from the user day, month, year
 *  - return 0 for invalid date and 1 for future date, 2 for the same date and 3 for past
 * created by Narapathra Morakrant 62070503464
 */
int dateCompare(int day, int month, int year)
{
    int dayToday;          //variable for day today
    int monthToday;        //variable for month today
    int yearToday;         //variable for year today
    int hrsToday;          //variable for hour today
    int minToday;          //variable for minute today
    int validity = 0;
    
    dateTimeToday(&dayToday,&monthToday,&yearToday,&hrsToday,&minToday);
    
    if (year > yearToday)
    {
        validity = 1;
    }
    else if (year == yearToday)
    {
        if (month > monthToday)
        {
            validity = 1;
        }
        else if (month == monthToday)
        {
            if (day > dayToday)
            {
                validity = 1;
            }
            else if (day == dayToday)
            {
                validity = 2;
            }
            else if (day < dayToday)
            {
                validity = 3;
            }
        }
    }
    
    if (validity == 0)
    {
        printf("\tNot Valid - date cannot be in the past \n");
    }
    
    return validity;
}

/*********************************************************************************
 * timeCompare
 *  - function which check the time getting from user is not in past
 *  - get the string input from the user hh:tt
 *  - return 0 for invalid time and 1 for future time, 2 for the same date and 3 for the past
 * created by Narapathra Morakrant 62070503464
 */
int timeCompare (char time[MAXLEN])
{
    int dayToday;          //variable for day today
    int monthToday;        //variable for month today
    int yearToday;         //variable for year today
    int hrsToday;          //variable for hour today
    int minToday;          //variable for minute today
    int validity = 0;
    int hrs;               //variable for hour of input
    int min;               //variable for minute of input
    int correctness =0;
    
    dateTimeToday(&dayToday,&monthToday,&yearToday,&hrsToday,&minToday);
    
    sscanf(time,"%d:%d", &hrs, &min);
    if (hrs > hrsToday)
    {
        correctness = 1;
    }
    else if (hrs == hrsToday)
    {
        if (min > minToday)
        {
            correctness = 1;
        }
        else if( min == minToday)
        {
            correctness = 2;
        }
        else
        {
            correctness = 3;
        }
    }
    
    if (correctness == 0)
    {
        printf("\tNot Valid - time cannot be in the past \n");
    }
    
    return correctness;
}

/*********************************************************************************
 * validateDate
 *  - function which check the date is valid
 *  - get the string input from the user
 *  - call others function to print error message if it is invalid
 *  - return 0 for invalid date and 1 for valid date
 * created by Narapathra Morakrant 62070503464
 */
int validateDate(char date[MAXLEN])
{
    int day;
    int month;
    int year;
    int leapyear =0;
    int correctness = 0;
    
    if(strlen(date) == 10)
    {
        if ((date[2] == '-') && (date[5] == '-'))
        {
            if (checkDigits(date) == 8)
            {
                sscanf(date,"%d-%d-%d",&day, &month, &year);
                if ((year <= 2120)&&(year >= 1920))
                {
                    if ((month <=12)&&(month >= 1))
                    {
                        leapyear = leapYear(year);
                        if (checkDay(day,month,leapyear) == 1)
                        {
                            correctness =1;
                        }
                    }
                    else
                    {
                        printf("\tNot Valid - not an existing month  \n");
                    }
                }
                else
                {
                    printf("\tNot Valid - year out of range \n");
                }
            }
            else
            {
                printf("\tNot Valid - contain character other than '-' \n");
            }
        }
        else
        {
            printf("\tNot Valid - wrong date format as dashes not in the right position\n");
        }
    }
    else
    {
        printf("\tNot Valid - wrong date format\n");
    }
    
    return correctness;
}

/*********************************************************************************
 * validateTime
 *  - function which check the time is valid
 *  - get the string input from the user
 *  - call others function to print error message if it is invalid
 *  - return 0 for invalid and 1 for valid
 * created by Narapathra Morakrant 62070503464
 */
int validateTime(char time[MAXLEN])
{
    int correctness =0;
    int hrs = -1;
    int min = -1;
    
    if (strlen(time) == 5)
    {
        if (time[2] == ':')
        {
            if (checkDigits(time) == 4)
            {
                sscanf(time,"%d:%d", &hrs, &min);
                if ((hrs>=0)&&(hrs<=23))
                {
                    if ((min >=0)&&(min<=59))
                    {
                        correctness = 1;
                    }
                    else
                    {
                        printf("\tNot Valid - minute not in range\n");
                    }
                }
                else
                {
                    printf("\tNot Valid - hour not in range\n");
                }
            }
            else
            {
                printf("\tNot Valid - contain character other than ':' \n");
            }
        }
        else
        {
            printf("\tNot Valid - wrong time format as ':' not in the right position\n");
        }
    }
    else
    {
        printf("\tNot Valid - wrong time format\n");
    }
    
    return correctness;
    
}

/*********************************************************************************
 * validateDateTime
 *  - function which check the date and time is valid
 *  - get the string input from the user
 *  - call others function to print error message if it is invalid
 *  - return 0 for invalid, 1 for future, 2 for valid past
 * created by Narapathra Morakrant 62070503464
 */
int validateDateTime(char input[MAXLEN])
{
    char time[MAXLEN];
    char date[MAXLEN];
    int validate = 0;
    int correctness =0;
    int day=0;
    int month=0;
    int year=0;
    
    sscanf(input,"%s %s",date,time);
    sscanf(date,"%d-%d-%d",&day,&month,&year);
    if ((validateDate(date) == 1)&&(validateTime(time)==1))
    {
        validate = dateCompare(day,month,year);
        if (validate == 1)
        {
            correctness = 1;
        }
        else if (validate == 2)
        {
            validate = timeCompare(time);
            if(validate == 1)
            {
                correctness = 1;
            }
            else if(validate == 3)
            {
                correctness = 2;
            }
        }
        else if (validate == 3)
        {
            correctness = 2;
        }
    }
    
    return correctness;
}

