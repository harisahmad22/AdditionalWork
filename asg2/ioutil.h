/* ioutil.h

   a library of functions to reliably read specific types of data
*/
#ifndef IOUTIL_H
#define IOUTIL_H

/*
Function: readInt

Purpose:  Reliably reads one integer from the user. 

Input:
          prompt - a character string that will be printed to the screen
                   informing the user what is being read
Output:
          eof    - a boolean that will be set to true if the user enters ctrl-d;
                   otherwise it will be set to false
Return:
          a valid integer, which is a positive or negative value within the 
          allowable range of integers for this computer.

Details: 
          The function accepts exactly one valid integer followed immediately
          by a newline.

          An invalid integer, a non-integer, an integer preceded by whitespace 
          or an empty input are all errors and will result in a meaningful error
          message and the user being re-prompted for input.

          The function does not return until input of the required format is 
          provided or the end of the file is reached.

          If the user enters ctrl-d, the eof parameter will be set to true and 
          the reading process will terminate without reading a valid number.
          Since no input is read the calling program must handle this situation
          appropriately.
*/
int readInt (const char prompt[], bool& eof);

/*
Function: readBool

Purpose:  Reliably reads a true/false response from the user, which is represented
          by the characters 'y' and 'n', with upper or lower case both being
          valid.

Input:
          prompt - a character string that will be printed to the screen
                   informing the user what is being read
Output:
          eof    - a boolean that will be set to true if the user enters ctrl-d;
                   otherwise it will be set to false
Return:
          a boolean value, corresponding to the user's response.


Details: 
          The input must be a single character followed immediately by a newline.

          The only valid input values are 'y' and 'n', in either upper or lower
          case.

          Any other input value is considered invalid and the user is re-prompted.

          If the user enters ctrl-d, the eof parameter will be set to true and 
          the reading process will terminate without reading a valid number.
          Since no input is read the calling program must handle this situation
          appropriately.
*/
bool readBool(const char prompt[], bool& eof);

/*
Function: readString

Purpose:  Reliably reads a c-string, ending in newline, from the user.

Input:
          prompt - a character string that will be printed to the screen
                   informing the user what is being read
          maxlen - the maximum number of characters the user can enter for
                   a valid string, excluding the NULL. 
          minlen - the minimum number of characters the user must enter for
                   a valid string.
Output:
          str    - a c-string of at least maxlen where the user's input will be
                   stored, when valid
          eof    - a boolean that will be set to true if the user enters ctrl-d;
                   otherwise it will be set to false
Details:
          To be valid the string must have a length greater or equal to minlen
          and less than or equal to maxlen.

          If minlen = 0, the empty string is valid.
          If minlen == maxlen == 1 then a single character can be read. 
          Of course, the user will be required to assign the zeroth element of
          the c-string to the character variable.

          Entering a string with length less than minlen or more than maxlen
          characters is an error and the input will be discarded and the user 
          will be re-prompted and required to re-enter input.

          If the user enters ctrl-d, the eof parameter will be set to true and 
          the reading process will terminate without reading a valid string.
          Since no input is read the calling program must handle this situation
          appropriately.
*/
void readString(const char prompt[], char str[],
                int maxlen, int minlen, bool& eof);

#endif
