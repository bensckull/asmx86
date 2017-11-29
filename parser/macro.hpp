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

/*! \file macro.hpp
 *
 *  \author BroFreedom <jdoe1337@gmx.fr>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__MACRO__
#define __ASMX__MACRO__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include "parser/section.hpp"

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

class AsmMacro
{
    private:
        std::string __name;

        std::vector<std::string> __parameters;

        std::vector<AsmSection*> __sections;

    public:
        /*! Constructor
         *
         *  \param name the macro name
         */
        AsmMacro(const std::string& name): __name(name) {}

        /*! Get macro name
         *
         *  \return a string
         */
        std::string get_name()
        {
            return __name;
        }

        /*! Get macro parameters
         *
         *  \return a vector of modules string
         */
        std::vector<std::string> get_parameters()
        {
            return __parameters;
        }

        /*! Get macro sections
         *
         *  \return a vector of AsmSection
         */
        std::vector<AsmSection*> get_sections()
        {
            return __sections;
        }

        /*! Add a new macro section
         *
         *  \param section the new section
         */
        void add_section(AsmSection* section)
        {
            __sections.push_back(section);
        }

        /*! Get last macro section
         *
         *  \return an AsmSection or nullptr
         */
        AsmSection* get_last_section()
        {
            if(__sections.size() > 0)
                return __sections[__sections.size() - 1];

            return nullptr;
        }
};

#endif // __ASMX__MACRO__


