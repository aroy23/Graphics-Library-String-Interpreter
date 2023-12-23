An implementation of a graphics plotting function with a built in string interpreter for command inputs

**The parameters for the function are:**
 
  - a command string with plotting commands for a line or multiple lines to be plotted

  - a reference parameter that specifies the character with which lines will be plotted with on the grid

  - a reference parameter indicating wheter the current line being plotted should be plotted in the foreground or background
    - The value 0 indicates that the line should be plotted in the foreground: At every position in the line, the plot character replaces whatever character is in the grid at that point.
    
    - The value 1 indicates the line is to be plotted in the background: At every position in the line, if the character in the grid at that point is a space character (' '), then the plot character replaces it; otherwise, the character at that position is left unchanged.

  - a reference parameter which is set to the first index in the command string of an invalid plotting command if applicable

**Sample call of the function render:**

int performCommands(string commandString, char& plotChar, int& mode, int& badPos)

  - Returns if 0 plotting is successful

  - Returns 1 if command string is syntactically invalid

  - Returns 2 if plotting mode is not foreground or background mode (o or 1)

  - Returns 3 if plotting is attempted outside specified grid boundaries

**Sample Main Function**

    int main()
    {
        setSize(7, 25);
        char pc = '*';
        int m = FG;
        int bad = 0;
        assert(performCommands("b h3v2f*v3h4v-3b h5f*h-3v3h3b h2v-3f*v3h3b h2f*v-3h3v3v-1h-2", pc, m, bad) == 0 && bad == 0);
        draw();
    }

Output:

               1111111111222222
      1234567890123456789012345
     +-------------------------+
    1|                         |
    2|                         |
    3|   *   * **** *    ****  |
    4|   *   * *    *    *  *  |
    5|   *   * *    *    ****  |
    6|   ***** **** **** *  *  |
    7|                         |
     +-------------------------+

**Plotting Command Syntax**

Plotting starts at (1,1) in the specified grid

**Horizontal Line command**
- This command consists of an upper or lower case H immediately followed by an argument in one of the following forms:
  - one digit character
  - two digit characters
  - a minus sign followed by one digit character
  - a minus sign followed by two digit characters

- This command sets characters in the grid to form a horizontal line segment, one of whose endpoints is the current position. If the command does not contain a minus sign, the line extends rightward from the current position; if the command contains a minus sign, the line extends leftward. The one or two digits in the command indicate the distance from the current position to the other endpoint of the line. Notice that the plotting commands H3 and H03 have the same effect. If the one or two digits are 0 or 00, the "line" consists only of the current position.

- If the current mode is foreground mode, the character in the grid at every position in the line is replaced by the current character. If the current mode is background mode, only the space characters in the grid that are at positions in the line are replaced by the current character. After this plotting command is performed, the current position is the position of the other endpoint of the line; unless the digits in the command were 0 or 00, this will be a different position from what it was before performing the command.

- If performing this command would attempt to plot a character outside the grid, then this command must not modify any characters in the grid and must not change the current position. For example, if the grid has 20 columns and the current position is (13, 19), you would not plot any characters for the plotting command H3, and the current position would remain (13, 19). Notice that the command H76 is a syntactically valid plotting command, but performing this command could never result in any characters being plotted, since setSize does not allow you to create a grid with more than MAXCOLS (30) columns.

**Vertical Line command**
- This command consists of an upper or lower case V immediately followed by an argument in one of the same four forms as for the H command.

- This command sets characters in the grid to form a vertical line segment, one of whose endpoints is the current position. If the command does not contain a minus sign, the line extends downward from the current position; if the command contains a minus sign, the line extends upward. The one or two digits in the command indicate the distance from the current position to the other endpoint of the line. Notice that the plotting commands V3 and V03 have the same effect. If the one or two digits are 0 or 00, the "line" consists only of the current position.

- If the current mode is foreground mode, the character in the grid at every position in the line is replaced by the current character. If the current mode is background mode, only the space characters in the grid that are at positions in the line are replaced by the current character. After this plotting command is performed, the current position is the position of the other endpoint of the line; unless the digits in the command were 0 or 00, this will be a different position from what it was before performing the command.

- If performing this command would attempt to plot a character outside the grid, then this command must not modify any characters in the grid and must not change the current position. For example, if the grid has 20 rows and the current position is (13, 19), you would not plot any characters for the plotting command V8, and the current position would remain (13, 19). Notice that the command V76 is a syntactically valid plotting command, but performing this command could never result in any characters being plotted, since setSize does not allow you to create a grid with more than MAXROWS (30) rows.

**Foreground command**
- This command consists of an upper or lower case F immediately followed by one character. That character must be one for which the library function isprint returns a value that tests as true.

- Executing this command sets the mode to foreground mode and the current character to the character that follows the upper or lower case F.

**Background command**
- This command consists of an upper or lower case B immediately followed by one character. That character must be one for which the library function isprint returns a value that tests as true.

- Executing this command sets the mode to background mode and the current character to the character that follows the upper or lower case B.

**Clear command**
- This command consists of an upper or lower case C.

- This command sets every character of the grid to be a space character and sets the current position to (1, 1), the current character to *, and the current mode to foreground mode.

**This Project Was Created as a Project for CS 31 at UCLA During the Fall 2023 Quarter**
