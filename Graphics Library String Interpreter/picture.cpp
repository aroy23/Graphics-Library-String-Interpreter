#include "grid.h"
#include <iostream>
#include <cctype>
#include <cassert>
using namespace std;
const int HORIZ = 0;
const int VERT = 1;
const int FG = 0;
const int BG = 1;

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
void plotHorizontalLine(int r, int c, int distance, char ch);
void plotHorizontalLineBackwards(int r, int c, int distance, char ch);
void plotVerticalLine(int r, int c, int distance, char ch);
void plotVerticalLineUpwards(int r, int c, int distance, char ch);
void plotHorizontalLineBG(int r, int c, int distance, char ch);
void plotHorizontalLineBackwardsBG(int r, int c, int distance, char ch);
void plotVerticalLineBG(int r, int c, int distance, char ch);
void plotVerticalLineUpwardsBG(int r, int c, int distance, char ch);
int performCommands(string commandString, char& plotChar, int& mode, int& badPos);

int main()
{
    setSize(30, 30);
    char pc = '*';
    int m = FG;
    int bad = 0;
    assert(performCommands("H2V5cCB H1F*H4B h-4F*v2H4B H-4F*V2H4B H2F*V-4H1B H1V1F*V0B H1V1F*V0B V-1H1F*V-0B H1V-1F*V-0H1V4B H2F*V-4H1B H1V1F*V0b H1V1F*V0B V-1H1F*V-0B H1V-1F*V-0H1V4B H2f*V-4H4V2H-3B H3F*V2", pc, m, bad) == 0 && getChar(1, 2) == '*' && bad == 0); 
    draw();
    cout << "success" << endl;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    int r = 1;
    int c = 1;
    //Checks if plot char is printable and mode is either FG or BG
    if(!isprint(plotChar) || (mode != FG && mode != BG))
    {
        return 2;
    }
    //Returns 0 as a successful command for an empty string
    if(commandString == "")
    {
        return 0;
    }
    //Toggles to true if plotting command causes a character to fall outside the grid
    bool isOutOfBounds = false;
    //While loop to iterate through command
    int i = 0;
    while(i != commandString.size())
    {
        //cout << "1" << endl;
        //If commandString at index i is h or H
        if(i < commandString.size() && (commandString.at(i) == 'h' || commandString.at(i) == 'H'))
        {
            //cout << "2" << endl;
            //e.g. H-
            if(i+1 < commandString.size() && commandString.at(i+1) == '-')
            {
                //cout << "3" << endl;
                i+= 1;
                //e.g. H-2
                if(i+1 < commandString.size() && isdigit(commandString.at(i+1)))
                {
                    //cout << "4" << endl;
                    i+= 1;
                    //e.g. H-22
                    if(i+1 < commandString.size() && isdigit(commandString.at(i+1)))
                    {
                        //cout << "5" << endl;
                        int distance = stoi(commandString.substr(i, 2));
                        i+= 2;
                        //Sets badPos and toggles bool if char is plotted out of bounds
                        if(!isOutOfBounds && c - distance < 1)
                        {
                            //cout << "bounds 1" << endl;
                            badPos = i-4;
                            isOutOfBounds = true;
                        }
                        else if(!isOutOfBounds)
                        {
                            //cout << "plot 1" << endl;
                            assert(plotLine(r, c, (-1) * distance, HORIZ, plotChar, mode));
                            c -= distance;
                        }
                    }
                    //e.g. H-2
                    else
                    {
                        //cout << "6" << endl;
                        int distance = (commandString.at(i) - '0');
                        i+= 1;
                        //Sets badPos and toggles bool if char is plotted out of bounds
                        if(!isOutOfBounds && c - distance < 1)
                        {
                            //cout << "bounds 2" << endl;
                            badPos = i-3;
                            isOutOfBounds = true;
                        }
                        else if(!isOutOfBounds)
                        {
                            //cout << "plot 2" << endl;
                            assert(plotLine(r, c, (-1) * distance, HORIZ, plotChar, mode));
                            c -= distance;
                        }
                    }
                }
                //e.g. H-Q
                else
                {
                    //cout << "7" << endl;
                    badPos = i+1;
                    return 1;
                }
                
            }
            //e.g. H2
            else if(i+1 < commandString.size() && isdigit(commandString.at(i+1)))
            {
                //cout << "8" << endl;
                i+= 1;
                //e.g. H22
                if(i+1 < commandString.size() && isdigit(commandString.at(i+1)))
                {
                    //cout << "9" << endl;
                    int distance = stoi(commandString.substr(i, 2));
                    i+= 2;
                    //Sets badPos and toggles bool if char is plotted out of bounds
                    if(!isOutOfBounds && c + distance > getCols())
                    {
                        //cout << "bounds 3" << endl;
                        badPos = i-3;
                        isOutOfBounds = true;
                    }
                    else if(!isOutOfBounds)
                    {
                        //cout << "plot 3" << endl;
                        assert(plotLine(r, c, distance, HORIZ, plotChar, mode));
                        c += distance;
                    }
                }
                //e.g. H2
                else
                {
                    //cout << "10" << endl;
                    int distance = (commandString.at(i) - '0');
                    i+= 1;
                    //Sets badPos and toggles bool if char is plotted out of bounds
                    if(!isOutOfBounds && c + distance > getCols())
                    {
                        //cout << "bounds 4" << endl;
                        badPos = i-2;
                        isOutOfBounds = true;
                    }
                    else if(!isOutOfBounds)
                    {
                        //cout << "plot 4" << endl;
                        assert(plotLine(r, c, distance, HORIZ, plotChar, mode));
                        c += distance;
                    }
                }
            }
            //e.g. HQ
            else
            {
                //cout << "11" << endl;
                badPos = i+1;
                return 1;
            }
        }
        //If commandString at index i is v or V
        if(i < commandString.size() && (commandString.at(i) == 'v' || commandString.at(i) == 'V'))
        {
            //cout << "12" << endl;
            //e.g. V-
            if(i+1 < commandString.size() && commandString.at(i+1) == '-')
            {
                //cout << "13" << endl;
                i+= 1;
                //e.g. V-2
                if(i+1 < commandString.size() && isdigit(commandString.at(i+1)))
                {
                    //cout << "14" << endl;
                    i+= 1;
                    //e.g. V-22
                    if(i+1 < commandString.size() && isdigit(commandString.at(i+1)))
                    {
                        //cout << "15" << endl;
                        int distance = stoi(commandString.substr(i, 2));
                        i+= 2;
                        //Sets badPos and toggles bool if char is plotted out of bounds
                        if(!isOutOfBounds && r - distance < 1)
                        {
                            //cout << "bounds 5" << endl;
                            badPos = i-4;
                            isOutOfBounds = true;
                        }
                        else if(!isOutOfBounds)
                        {
                            //cout << "plot 5" << endl;
                            assert(plotLine(r, c, (-1) * distance, VERT, plotChar, mode));
                            r -= distance;
                        }
                    }
                    //e.g. V-2
                    else
                    {
                        //cout << "16" << endl;
                        int distance = (commandString.at(i) - '0');
                        i+= 1;
                        //Sets badPos and toggles bool if char is plotted out of bounds
                        if(!isOutOfBounds && r - distance < 1)
                        {
                            //cout << "bounds 6" << endl;
                            badPos = i-3;
                            isOutOfBounds = true;
                        }
                        else if(!isOutOfBounds)
                        {
                            //cout << "plot 6" << endl;
                            assert(plotLine(r, c, (-1) * distance, VERT, plotChar, mode));
                            r -= distance;
                        }
                    }
                }
                //e.g. V-Q
                else
                {
                    //cout << "17" << endl;
                    badPos = i+1;
                    return 1;
                }
                
            }
            //e.g. V2
            else if(i+1 < commandString.size() && isdigit(commandString.at(i+1)))
            {
                //cout << "18" << endl;
                i+= 1;
                //e.g. V22
                if(i+1 < commandString.size() && isdigit(commandString.at(i+1)))
                {
                    //cout << "19" << endl;
                    int distance = stoi(commandString.substr(i, 2));
                    i+= 2;
                    //Sets badPos and toggles bool if char is plotted out of bounds
                    if(!isOutOfBounds && r + distance > getRows())
                    {
                        //cout << "bounds 7" << endl;
                        badPos = i-3;
                        isOutOfBounds = true;
                    }
                    else if(!isOutOfBounds)
                    {
                        //cout << "plot 7" << endl;
                        assert(plotLine(r, c, distance, VERT, plotChar, mode));
                        r += distance;
                    }
                }
                //e.g. V2
                else
                {
                    //cout << "20" << endl;
                    int distance = (commandString.at(i) - '0');
                    i+= 1;
                    //Sets badPos and toggles bool if char is plotted out of bounds
                    if(!isOutOfBounds && r + distance > getRows())
                    {
                        //cout << "bounds 8" << endl;
                        badPos = i-2;
                        isOutOfBounds = true;
                    }
                    else if(!isOutOfBounds)
                    {
                        //cout << "plot 8" << endl;
                        assert(plotLine(r, c, distance, VERT, plotChar, mode));
                        r += distance;
                    }
                }
            }
            //e.g. VQ
            else
            {
                //cout << "21" << endl;
                badPos = i+1;
                return 1;
            }
        }
        //If commandString at index i is B
        if(i < commandString.size() && (commandString.at(i) == 'b' || commandString.at(i) == 'B'))
        {
            //cout << "22" << endl;
            //If B ollowed by non printable character return 1 (syntax error)
            if(i+1 < commandString.size() && !isprint(commandString.at(i+1)))
            {
                //cout << "23" << endl;
                badPos = i+1;
                return 1;
            }
            //e.g. B2
            else if(i+1 < commandString.size() && isprint(commandString.at(i+1)))
            {
                //cout << "24" << endl;
                mode = BG;
                plotChar = commandString.at(i+1);
                i+= 2;
            }
            //e.g. BBB
            else
            {
                //cout << "25" << endl;
                badPos = i+1;
                return 1;
            }
        }
        //If commandString at index i is F
        if(i < commandString.size() && (commandString.at(i) == 'f' || commandString.at(i) == 'F'))
        {
            //cout << "26" << endl;
            //If F ollowed by non printable character return 1 (syntax error)
            if(i+1 < commandString.size() && !isprint(commandString.at(i+1)))
            {
                //cout << "27" << endl;
                badPos = i+1;
                return 1;
            }
            //e.g. F2
            else if(i+1 < commandString.size() && isprint(commandString.at(i+1)))
            {
                //cout << "28" << endl;
                mode = FG;
                plotChar = commandString.at(i+1);
                i+= 2;
            }
            //e.g. FFF
            else
            {
                //cout << "29" << endl;
                badPos = i+1;
                return 1;
            }
        }
        //If commandString at index i is C
        if(i < commandString.size() && (commandString.at(i) == 'c' || commandString.at(i) == 'C'))
        {
            //cout << "30" << endl;
            i+= 1;
            clearGrid();
            mode = FG;
            plotChar = '*';
            r = 1;
            c = 1;
        }
        //Checks if there is character where there isn't supposed to be and returns 1 (syntax error) if true
        if(i < commandString.size() && commandString.at(i) != 'h' && commandString.at(i) != 'H' && commandString.at(i) != 'v' && commandString.at(i) != 'V' && commandString.at(i) != 'b' && commandString.at(i) != 'B' && commandString.at(i) != 'f' && commandString.at(i) != 'F' && commandString.at(i) != 'c' && commandString.at(i) != 'C')
        {
            //cout << "31" << endl;
            badPos = i;
            return 1;
        }
    }
    //If a plotting command ever attempted to plot of of bounds, return 3 (out of bounds error).
    //badPos will be set to the first command which attempted to plot of of bounds
    if(isOutOfBounds)
    {
        //cout << "32" << endl;
        return 3;
    }
    //cout << "33" << endl;
    return 0;
}
//plotLine function
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)
{
    //plotLine only runs if plotChar is printable
    if(isprint(plotChar))
    {
        //foreground mode plotting
        if(fgbg == FG)
        {
            if(dir == HORIZ)
            {
                if(distance >= 0)
                {
                    //stops plotting if distance causes char to fall outside of grid
                    if(c+abs(distance) > getCols())
                    {
                        return false;
                    }
                    else
                    {
                        plotHorizontalLine(r, c, abs(distance), plotChar);
                    }
                }
                else
                {
                    //stops plotting if distance causes char to fall outside of grid
                    if(c-abs(distance) < 1)
                    {
                        return false;
                    }
                    else
                    {
                        plotHorizontalLineBackwards(r, c, abs(distance), plotChar);
                    }
                }
                return true;
            }
            else if(dir == VERT)
            {
                if(distance >= 0)
                {
                    //stops plotting if distance causes char to fall outside of grid
                    if(r+abs(distance) > getRows())
                    {
                        return false;
                    }
                    else
                    {
                        plotVerticalLine(r, c, abs(distance), plotChar);
                    }
                }
                else
                {
                    //stops plotting if distance causes char to fall outside of grid
                    if(r-abs(distance) < 1)
                    {
                        return false;
                    }
                    else
                    {
                        plotVerticalLineUpwards(r, c, abs(distance), plotChar);
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        //background mode plotting
        else if(fgbg ==  BG)
        {
            //horizontal line
            if(dir == HORIZ)
            {
                //Forward line plotting
                if(distance >= 0)
                {
                    //stops plotting if distance causes char to fall outside of grid
                    if(c+abs(distance) > getCols())
                    {
                        return false;
                    }
                    else
                    {
                        plotHorizontalLineBG(r, c, abs(distance), plotChar);
                    }
                }
                //Backwards line plotting
                else
                {
                    //stops plotting if distance causes char to fall outside of grid
                    if(c-abs(distance) < 1)
                    {
                        return false;
                    }
                    else
                    {
                        plotHorizontalLineBackwardsBG(r, c, abs(distance), plotChar);
                    }
                }
                return true;
            }
            //vertical line
            else if(dir == VERT)
            {
                //Forward line plotting
                if(distance >= 0)
                {
                    //stops plotting if distance causes char to fall outside of grid
                    if(r+abs(distance) > getRows())
                    {
                        return false;
                    }
                    else
                    {
                        plotVerticalLineBG(r, c, abs(distance), plotChar);
                    }
                }
                //Backwards line plotting
                else
                {
                    //stops plotting if distance causes char to fall outside of grid
                    if(r-abs(distance) < 1)
                    {
                        return false;
                    }
                    else
                    {
                        plotVerticalLineUpwardsBG(r, c, abs(distance), plotChar);
                    }
                }
                return true;;
            }
            //If direction is not HORIZ or VERT return false
            else
            {
                return false;
            }
        }
        //If mode is not foreground or background return false
        else
        {
            return false;
        }
    }
    //if plotChar is not printable return false
    else
    {
        return false;
    }
}
//plotHorizontalLine function
void plotHorizontalLine(int r, int c, int distance, char ch)
{
    //only works for positive distance
    if(distance < 0)
    {
        return;
    }
    for(int i = 0; i <= distance; i++)
    {
        //Plots all chars inside grid horizontally forwards
        if(r <= getRows() && (c+i) <= getCols() && r >= 1 && (c+i) >= 1)
        {
            setChar(r, (c+i), ch);
        }
    }
}
//plotHorizontalLineBackwards function
void plotHorizontalLineBackwards(int r, int c, int distance, char ch)
{
    //only works for positive distance
    if(distance < 0)
    {
        return;
    }
    for(int i = 0; i <= distance; i++)
    {
        //Plots all chars inside grid horizontally backwards
        if(r <= getRows() && (c-i) <= getCols() && r >= 1 && (c-i) >= 1)
        {
            setChar(r, (c-i), ch);
        }
    }
}
//plotVerticalLine function
void plotVerticalLine(int r, int c, int distance, char ch)
{
    //only works for positive distance
    if(distance < 0)
    {
        return;
    }
    //Plots all chars inside grid vertically downwards
    for(int i = 0; i <= distance; i++)
    {
        if((r+i) <= getRows() && c <= getCols() && (r+i) >= 1 && c >= 1)
        {
            setChar((r+i), c, ch);
        }
    }
}
//plotVerticalLineBackwards function
void plotVerticalLineUpwards(int r, int c, int distance, char ch)
{
    //only works for positive distance
    if(distance < 0)
    {
        return;
    }
    //Plots all chars inside grid vertically upwards
    for(int i = 0; i <= distance; i++)
    {
        if((r-i) <= getRows() && c <= getCols() && (r-i) >= 1 && c >= 1)
        {
            setChar((r-i), c, ch);
        }
    }
}
//plotHorizontalLineBG function (Background)
void plotHorizontalLineBG(int r, int c, int distance, char ch)
{
    //only works for positive distance
    if(distance < 0)
    {
        return;
    }
    //Plots all chars inside grid horizontally forwards
    for(int i = 0; i <= distance; i++)
    {
        if(r <= getRows() && (c+i) <= getCols() && r >= 1 && (c+i) >= 1)
        {
            //Only plots a char if the grid is ' ' at the cursor
            if(getChar(r, c+i) == ' ')
            {
                setChar(r, (c+i), ch);
            }
        }
    }
}
//plotHorizontalBackwardsLineBG function (Background)
void plotHorizontalLineBackwardsBG(int r, int c, int distance, char ch)
{
    //only works for positive distance
    if(distance < 0)
    {
        return;
    }
    //Plots all chars inside grid horizontally backwards
    for(int i = 0; i <= distance; i++)
    {
        if(r <= getRows() && (c-i) <= getCols() && r >= 1 && (c-i) >= 1)
        {
            //Only plots a char if the grid is ' ' at the cursor
            if(getChar(r, c-i) == ' ')
            {
                setChar(r, (c-i), ch);
            }
        }
    }
}
//plotVerticalLineBG function (Background)
void plotVerticalLineBG(int r, int c, int distance, char ch)
{
    //only works for positive distance
    if(distance < 0)
    {
        return;
    }
    //Plots all chars inside grid vertically upwards
    for(int i = 0; i <= distance; i++)
    {
        if((r+i) <= getRows() && c <= getCols() && (r+i) >= 1 && c >= 1)
        {
            //Only plots a char if the grid is ' ' at the cursor
            if(getChar(r+i, c) == ' ')
            {
                setChar(r+i, c, ch);
            }
        }
    }
}
//plotVerticalLineBackwardsBG function (Background)
void plotVerticalLineUpwardsBG(int r, int c, int distance, char ch)
{
    //only works for positive distance
    if(distance < 0)
    {
        return;
    }
    //Plots all chars inside grid vertically downwards
    for(int i = 0; i <= distance; i++)
    {
        if((r-i) <= getRows() && c <= getCols() && (r-i) >= 1 && c >= 1)
        {
            //Only plots a char if the grid is ' ' at the cursor
            if(getChar(r-i, c) == ' ')
            {
                setChar(r-i, c, ch);
            }
        }
    }
}
