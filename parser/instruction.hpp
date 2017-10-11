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

/*! \file instruction.hpp
 *
 *  \author BroFreedom <jdoe1337@gmx.fr>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__INSTRUCTION__
#define __ASMX__INSTRUCTION__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <vector>
#include <string>

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

class AsmInstruction {

    private:
        std::string __name;

        std::vector<std::string> __parameters;

    public:
        /*! Constructor
         *
         *  \param name the instruction label
         */
        AsmInstruction(const std::string& name): __name(name) {}

        /*! Set instruction label
         *
         *  \param name the instruction label string
         */
        void set_name(const std::string& name)
        {
            __name = name;
        }

        /*! Get the instruction name
         *
         *  \return a string name
         */
        std::string get_name()
        {
            return __name;
        }

        /*! Add a new parameter to instruction
         *
         *  \param parameter the new parameter to add
         */
        void add_parameter(const std::string& parameter)
        {
            __parameters.push_back(parameter);
        }

        /*! Remove a specific parameter
         *
         *  \param parameter the parameter to remove from parameters
         */
        void remove_parameter(const std::string& parameter)
        {
            std::vector<std::string>::iterator iter = std::find(
                __parameters.begin(), __parameters.end(), parameter);

            if(iter != __parameters.end()) {
                __parameters.erase(iter);
            }
        }

        /*! Get the instruction parameters
         *
         *  \return a vector of string
         */
        std::vector<std::string> get_parameters()
        {
            return __parameters;
        }
};

#endif // __ASMX__INSTRUCTION__

