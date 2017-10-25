/* --------------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * -------------------------------------------------------------------------- */

/*! \file parser.hpp
 *
 *  \author BroFreedom <jdoe1337@gmx.fr>
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \author Adnan44 <adnane.mounassib@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__UTILS__
#define __ASMX__UTILS__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

/* --------------------------------------------------------------------------
 *  Functions
 * -------------------------------------------------------------------------- */

/*! Remove trailing spaces
 *
 * \param str the string to reduce
 * \param whitespace the whitespace declaration
 *
 * \return a trimed string
 *
 * \note https://stackoverflow.com/a/1798170
 */
inline std::string trim(
    const std::string& str,
    const std::string& whitespace = " \t")
{
    const std::size_t begin = str.find_first_not_of(whitespace);

    // No content available
    if (begin == std::string::npos)
        return "";

    return str.substr(begin, str.find_last_not_of(whitespace) - begin + 1);
}

/*! Remove trailing spaces and reduce string
 *
 * \param str the string to reduce
 * \param fill the string using to reduce
 * \param whitespace the whitespace declaration
 *
 * \return a reduced string
 *
 * \note https://stackoverflow.com/a/1798170
 */
inline std::string reduce(
    const std::string& str,
    const std::string& fill = " ",
    const std::string& whitespace = " \t")
{
    std::string result = trim(str, whitespace);

    std::size_t begin = result.find_first_of(whitespace);

    while (begin != std::string::npos) {
        result.replace(
            begin, result.find_first_not_of(whitespace, begin) - begin, fill);

        begin = result.find_first_of(whitespace, begin + fill.length());
    }

    return result;
}

/*! Split a string with a specific separator
 *
 * \param str the string to split
 * \param separator the separator using to split the string
 *
 * \return a vector of string
 */
inline std::vector<std::string> split(
    const std::string& str,
    const std::string& separator = " ")
{
    std::vector<std::string> data;

    std::string result = reduce(str);

    std::size_t begin = 0;
    std::size_t end = result.find_first_of(separator);

    if(end != std::string::npos) {
        while(end != std::string::npos) {
            data.push_back(result.substr(begin, end - begin));

            begin = end + separator.length();
            end = result.find_first_of(separator, begin);
        }

        data.push_back(result.substr(begin, end - begin));
    }
    else {
        data.push_back(result);
    }

    return data;
}

/*! Join strings between quotation from a vector of string
 *
 *  \param data a vector of parameters
 *
 *  \return a vector of string
 */
inline std::vector<std::string> asm_join_message(std::vector<std::string> & data)
{
    std::vector<std::string> new_data;

    std::string message = "";

    for(std::string element : data) {
        std::size_t quotation = element.find_first_of('"');

        // A quotation has been found
        if(quotation != std::string::npos) {
            // The quotation is place at the beggining
            if(quotation == 0) {
                message += element + " ";
            }
            /// The quotation is place at the end
            else if (quotation == element.size() - 1) {
                message += element;

                new_data.push_back(message);
                message = "";
            }
        }
        // No quotation but still between quotations
        else if (message.size() > 0) {
            message += element;
        }
        // No quotation at all
        else {
            new_data.push_back(element);
        }
    }

    return new_data;
}
/*! Verify if it is a memory address
 *
 *  \param data a string
 *
 *  \return true if the string is a memory address 
 */
inline bool ifMemory(std::string str)
	{
		return str.find("[")!=std::string::npos;
	}

/*! Verify if it is a integer
 *
 *  \param data a string
 *
 *  \return true if the string is a nomber
 */

/*AsmStack toMemory(std::string str)
	{
		
	}*/

/*! Verify if it is a integer
 *
 *  \param data a string
 *
 *  \return true if the string is a nomber
 */

inline bool ifInt(std::string str)
	{
		int i;
   		std::istringstream istr(str);
 		return (istr >> i) && !(istr >> str);

	}

inline int toInt(std::string str)
	{
		int src = std::stoi(str);
		return src;

	}

/*! Verify if it is a Register
 *
 *  \param data a string
 *
 *  \return true if the string it's a register  
 */


/*AsmRegister toRegister(std::string str, AsmRegister reg)
	{
            switch (str) {
		case "ax": return tab[0]; 
		case "bx": return tab[1];
		case "cx": return tab[2];
		case "dx": return tab[3];
		case "eax": return tab[4];
		case "ebx": return tab[5];
		case "ecx": return tab[6];
		case "edx": return tab[7];
		case "rax": return tab[8];
		case "rbx": return tab[9];
		case "rcx": return tab[10];
		case "rdx": return tab[11];

		if (str == reg.get_label()){
			return reg;
             }
	}*/

inline bool ifRegister(std::string str)
	{
		return !ifMemory(str)&&!ifInt(str);
	}


inline int extractSize(std::string str)
{
	std::size_t foundP = str.find_first_of("+");
	std::size_t foundM = str.find_first_of("-");
        std::string n;		
	int i;
	if( foundP!=std::string::npos){ 
		n = str.substr(foundP+1, (str.size()-1)-(foundP+1));		
		i=toInt(n);
		return i; }
	else if(foundM!=std::string::npos){ 
		n = str.substr(foundM+1, (str.size()-1)-(foundM+1));		
		i=toInt(n);
		return -i;}
	else {return 0;}
}

inline std::string extractVariable(std::string str)
{
	std::string s;
	std::size_t search = str.find_first_of("[");
	if( search!=std::string::npos){	
		s = str.substr(1,(str.size()-1)-1);				
	}
	return s;
}


inline bool ifStack(std::string str)
{
	return str.find("[ebp")!=std::string::npos || str.find("[esp")!=std::string::npos;
}

inline bool ifVariabe(std::string str)
{
	return ifMemory(str) && !ifStack(str);
}

#endif
