/* ioutil.cpp

*/

#include "ioutil.h"
#include <iostream>
#include <cstring>
using namespace std;

void flush ();

int readInt(const char prompt[], bool& eof)
{
  int i;
  bool success = false;
  char ch, ch1;
  bool OK, negative = false;

  eof = false;

  do
  {
    cout << prompt;
    cin.get(ch);

    if (cin.eof())
    {
      cin.clear();
      cin.putback (' ');
      cin.get(ch);
      eof = true;
      success = true;
    }
    else if (ch == '\n')
    {
      cout << "INVALID INPUT - blank line entered -- please try again" << endl;
    }
    else if (ch != '-' && (ch < '0' || ch > '9'))
    {
      cout << "INVALID INPUT - input starts with non-numeric value -- please try again" 
           << endl;
      flush();
    }
    else
    {
      OK = true;
      if (ch == '-')
      {
        OK = false;
        cin.get(ch1);
        if (ch1 < '0' || ch1 > '9')
        {
          cout << "INVALID INPUT - input starts with non-numeric value -- please try again" 
               << endl;
          flush();
        }
        else
        {
          OK = true;
          negative = true;
          cin.putback(ch1);
        }
      }
      else
        cin.putback(ch);


      if (OK)
      {
        cin >> i;
        
        if (cin.fail())
        {
          cout << "INVALID INPUT - input value is ";
          if (negative)
          {
            cout << "less than minimum";
            negative = false;
          }
          else
          {
            cout << "greater than maximum";
          }
          cout << " allowed integer -- please try again" << endl;
          cin.clear();
          flush();
        }
        else
        {
          cin.get(ch);
          
          if (ch == '\n')
          {
            success = true;
            if (negative)
              i = -1*i;
          }
          else
          {
            cout << "INVALID INPUT - extra input after integer -- please try again" 
                 << endl;
            flush();
          }
        }
      }
    }
  } while (!success);
    
  return i;
}

bool readBool(const char prompt[], bool& eof)
{
  char  ch;
  bool  success = false,
        result = false;

  eof = false;

  do
  {
    cout << prompt;
    cin.get(ch);

    if (cin.eof())
    {
      cin.clear();
      cin.putback (' ');     /* needed to overwrite the EOF in the buffer */
      cin.get(ch);           /* needed to clear the buffer otherwise next */
                             /* attempted read will generate an error     */
      eof = true;
      success = true;
    }
    else
    {
      switch (ch)
      {
      case 'y':
      case 'Y':
        result = true;
        success = true;
        break;
      case 'n':
      case 'N':
        result = false;
        success = true;
        break;
      case '\n':
        cout << "INVALID - empty input  -- please try again" << endl;
        break;
      default:
        cout << "INVALID - (" << ch << ") is not y or n -- please try again" 
             << endl;
        flush();
        break;
      }
      if (success)
      {
        cin.get(ch);
        if (ch != '\n')
        {
          success = false;
          cout << "INVALID - characters following input are not allowed -- please try again"
               << endl;
          flush();
        }
      }
    }
  }
  while (!success);

  return result;
}


void readString(const char prompt[], char str[],
                int maxlen, int minlen, bool& eof)
{
  bool success = false;
  char ch;

  eof = false;
  do
  {
    cout << prompt;
    cin.getline (str, maxlen+1, '\n');

    if (cin.eof())
    {
      cin.clear();
      cin.putback (' ');     /* needed to overwrite the EOF in the buffer */
      cin.get(ch);           /* needed to clear the buffer otherwise next */
                             /* attempted read will generate an error     */
      eof = true;
      success = true;
    }
    else if (static_cast <int> (strlen(str)) < minlen)
    {
      cout << "INVALID - input string is < minimum length (" 
           << minlen << ") -- please try again." << endl;
    }
    else if (cin.fail())
    {
      cout << "INVALID - input string longer than allowed -- please try again." 
           << endl;
      cin.clear();
      flush();
    }
    else
    {
      success = true;
    }
  }
  while (!success);

  return;
}


void flush()
{
  char ch;

  do
  {
    cin.get(ch);
  } while (!cin.fail() && ch != '\n');

  return;
}
