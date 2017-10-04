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

/*! \file file.hpp
 *
 *  \author BroFreedom <jdoe1337@gmx.fr>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__FILE__
#define __ASMX__FILE__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include <sys/stat.h>

/* --------------------------------------------------------------------------
 *  Global
 * -------------------------------------------------------------------------- */

#ifdef _WIN32
const char separator = '\\';
#else
const char separator = '/';
#endif

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

enum FileMode
{
    APPEND, REPLACE
};

class File
{
    private:
        /*! File path */
        std::string __path;
        /*! File buffer content */
        std::vector<std::string> __buffer;

    public:
        /*! Constructor
         *
         *  \param path the file path on filesystem
         *
         *  \exception std::length_error when path length is empty
         */
        File(const std::string& path)
        {
            __path = path;

            if(path.length() == 0)
                throw std::length_error("Path is empty");
        }

        /*! Read File content
         *
         *  \exception std::runtime_error when path cannot be readed
         */
        void read()
        {
            std::ifstream buffer(__path, std::ios::out);

            if(buffer.is_open()) {
                // Reset current File buffer
                __buffer.clear();

                std::string line;

                // Store file lines into File buffer
                while(getline(buffer, line))
                    __buffer.push_back(line);

                buffer.close();
            }
            else {
                throw std::runtime_error("Cannot open current file");
            }
        }

        /*! Write pipe content into File
         *
         *  \param pipe the string buffer
         *  \param mode the file writing mode (Default: Append to end of file)
         *
         *  \exception std::runtime_error when path cannot be readed
         */
        void write(const std::string& pipe, const FileMode& mode = FileMode::APPEND)
        {
            std::ofstream buffer;

            switch(mode) {
                case FileMode::APPEND:
                    buffer.open(__path, std::ios::in | std::ios::app);
                    break;

                case FileMode::REPLACE:
                    buffer.open(__path, std::ios::in | std::ios::trunc);
                    break;

                default:
                    buffer.open(__path, std::ios::in);
                    break;
            }

            if(buffer.is_open()) {
                buffer << pipe << std::endl;

                buffer.close();

                // Refresh main buffer
                read();
            }
            else {
                throw std::runtime_error("Cannot open current file");
            }
        }

        /*! Check if File exists on filesystem
         *
         *  \return true if exists, false otherwise
         */
        bool exists()
        {
            // Define a stat structure
            struct stat buffer;

            return (stat(__path.c_str(), &buffer) == 0);
        }

        /*! Check if File is a file
         *
         *  \return true if it's a file, false otherwise
         */
        bool is_file()
        {
            // Define a stat structure
            struct stat buffer;

            return (
                stat(__path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
        }

        /*! Check if File is a directory
         *
         *  \return true if it's a directory, false otherwise
         */
        bool is_directory()
        {
            // Define a stat structure
            struct stat buffer;

            return (
                stat(__path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
        }

        /*! Get basename
         *
         *  \return the basename of current path
         */
        std::string get_basename()
        {
            std::size_t position = __path.find_last_of(separator);

            if(position != std::string::npos) {
                std::string temp = __path;

                return temp.erase(0, position + 1);
            }

            return __path;
        }

        /*! Get filename
         *
         *  \return the current path
         */
        std::string get_filename()
        {
            return __path;
        }

        /*! Get buffer content
         *
         *  \return a vector of string
         */
        std::vector<std::string> get_buffer()
        {
            return __buffer;
        }
};

#endif // __ASMX__FILE__
