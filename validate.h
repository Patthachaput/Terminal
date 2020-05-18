/*
* validate.h
*
*      contains all validate functions
*          - email [not finished]
*          - password
*          - name(no title)
*          - thai phone number
*          - bank account number
*          - home address [not finished]
*          - date time (dd-mm-yyyy hh:tt)
*
*
*  Project CPE111 Data structure - TEAM TERMINAL
*  Member: Natacha Punyathanasub       (Nut)       62070503415
*          Patthachaput Thanesmaneerat (Jui)       62070503432
*          Supakorn Srisawas           (Field)     62070503464
*          Narapathra Morakrant        (Foremost)  62070503464
*/

#ifndef validate_h
#define validate_h

#define MAXLEN 128

/*********************************************************************************
 * CheckSpcae
 *  - function which determine is the input start with space
 *  - get the string input from the user
 *  - return 0 for space found and 1 for no space found
 */
int checkSpace(char input[MAXLEN]);

/*********************************************************************************
 * CheckDigit
 *  - function which determine how many digits are in the string
 *  - get the string input from the user
 *  - return the amount of digits found
 */
int checkDigits(char input[MAXLEN]);

/*********************************************************************************
 * CheckAlphabet
 *  - function which determine how many alphabet are in the string
 *  - get the string input from the user
 *  - return the amount of alphabet found
 */
int checkAlphabet(char input[MAXLEN]);

/**********************************************************************************
 * checkUpperCase.
 * - A function to check how many upper case alphabetic character does it have.
 * - 'password' is the password put in by the user.
 * - This function returns number of upper case alphabetic character.
 */
int checkUpperCase(char password[MAXLEN]);

/**********************************************************************************
 * checkLowerCase.
 * - A function to check how many lower case alphabetic character does it have.
 * - 'password' is the password put in by the user.
 * - This function returns number of lower case alphabetic character.
 */
int checkLowerCase(char password[MAXLEN]);

/**********************************************************************************
 * checkSymbol.
 * - A function to check how many upper case alphabetic character does it have.
 * - 'password' is the password put in by the user.
 * - This function returns number of upper case alphabetic character.
 */
int checkSymbol(char password[MAXLEN]);

/**********************************************************************************
 * validatePassword.
 * A function to validate password with the following rules.
 * - At least 8 characters long and no longer than 12 characters.
 * - Contain at least one upper and lower case character.
 * - Contain at least 2 digits.
 * - Contain at least one of '? @ % $ #' and must not contain any other special characters.
 * return 0 for invalid date and 1 for valid date
 */
int validatePassword(char password[MAXLEN]);

/* This is checkNameTitle function. It use for check first and last name with title is valid or not.
 */
int validateName(char nameInput[]);

/* Control email function that check email result from the
 * email validation and it will be return 1 if it true.
 * and 0 if it not following the condition.(passing to the
 * validate function in validation.c(source file)
 * created by Natacha Punyathanasub 62070503415
 */
int validateEmail(char email[]);

/* This is checkPhoneNumThai function. It use for check Thai mobile phone number is valid or not.
 */
int validatePhoneNumThai(char phoneNumInput[], char fromkeyboard[]);

/***********************************************************
 * validateAddress
 *     - this function validate address
 *
 * Argument address - address of user
 * RETURN -1 - house number fail
 *           -2 - street name fail
 *           -3 - optional fail
 *           -4 - postalCode fail
 *         1 - if success
 **/
int validateAddress(char* address);

/*********************************************************************************
 * CheckDashs
 *  - function which determine is the value should have dash or not
 *    determine from thr string lenght
 *  - get the string input from the user
 *  - return 0 for invalid dash and 1 for valid dash
 */
int checkDashs(char bankAcc[MAXLEN]);

/*********************************************************************************
 * CheckLast3Digits
 *  - function which determine is the last 3 digits are valid, having 0
 *  - get the string input from the user
 *  - return 0 for invalid last 3 digits and 1 for valid last 3 digits
 */
int checkLast3Digits(char bankAcc[MAXLEN]);

/*********************************************************************************
 * CheckFirst3digits
 *  - function which determine is the first 3 digits are valid
 *  - get the string input from the user
 *  - return 0 for invalid first 3 digits and 1 for valid first 3 digits
 */
int checkFirst3digits(char bankAcc[MAXLEN]);

/*********************************************************************************
 * CheckBankAccLenght
 *  - function which determine the bank account number is in the right format
 *    as when the bank account has dashes its lenght should be 13
 *    and when does have dashes its lenght should be 11
 *  - get the string input from the user
 *  - return 0 for invalid format and 1 for valid format
 */
int checkBankAccLenght(char bankAcc[MAXLEN]);

/*********************************************************************************
 * validateBankAcc
 *  - function which check the bank account number is valid
 *  - get the string input from the user
 *  - call others function to print error message if it is invalid
 *  - return 0 for invalid date and 1 for valid date
 */
int validateBankAcc(char bankAcc[MAXLEN], char buffer[MAXLEN]);

/*********************************************************************************
 * dateTimeToday
 *  - Sets the pointer for day, month, year and
 *    to the correct values for today.
 *  created by Narapathra Morakrant 62070503464
 */
void dateTimeToday(int* pDay, int *pMonth, int* pYear, int* pHour, int* pMinute);

/*********************************************************************************
 * validateDateTime
 *  - function which check the date and time is valid
 *  - get the string input from the user
 *  - call others function to print error message if it is invalid
 *  - return 0 for invalid and 1 for valid
 * created by Narapathra Morakrant 62070503464
 */
int validateDateTime(char input[MAXLEN]);


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
int validateAddress(char* address);

#endif /* validate_h */
