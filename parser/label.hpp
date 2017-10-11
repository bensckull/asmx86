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

/*! \file label.hpp
 *
 *  \author BroFreedom <jdoe1337@gmx.fr>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__LABEL__
#define __ASMX__LABEL__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

class AsmLabel
{
    private:
        std::string __name;

        unsigned int __position;

    public:
        /*! Constructor
         *
         *  \param name the label name
         */
        AsmLabel(const std::string& name): __name(name) {}

        /*! Constructor
         *
         *  \param name the label name
         *  \param position the label position
         */
        AsmLabel(const std::string& name, const unsigned int & position):
            __name(name), __position(position) {}

        /*! Set label
         *
         *  \param name the label string
         */
        void set_name(const std::string& name)
        {
            __name = name;
        }

        /*! Get the name
         *
         *  \return a string name
         */
        std::string get_name()
        {
            return __name;
        }

        /*! Set the label position in section
         *
         *  \param position the new position in section
         */
        void set_position(const unsigned int & position)
        {
            __position = position;
        }

        /*! Get the label position in section
         *
         *  \return the position as integer
         */
        int get_position()
        {
            return __position;
        }

};

#endif // __ASMX__LABEL__


