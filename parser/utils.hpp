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

#endif
