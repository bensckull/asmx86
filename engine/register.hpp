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

/*! \file register.hpp
 *
 *  \author Adnan44 <adnane.mounassib@gmail.com>
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__REGISTER__
#define __ASMX__REGISTER__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

class AsmRegister
{
    private:
        std::string __label;

        std::string __value;

    public:
        /*! Constructor
         *
         *  \param label the Register label
         */
        AsmRegister(const std::string& label): __label(label) {}

        /*! Constructor
         *
         *  \param name the register name
         *  \param value the register value
         */
        AsmRegister(const std::string& label, const std::string& value):
            __label(label), __value(value) {}

        /*! Set register
         *
         *  \param label the register string
         */
        void set_label(const std::string& label)
        {
            __label = label;
        }

        /*! Get the label
         *
         *  \return a string label
         */
        std::string get_label()
        {
            return __label;
        }

        /*! Set the register value
         *
         *  \param value 
         */
        void set_value(const unsigned int & value)
        {
            __value = value;
        }

        /*! Get the rigester value
         *
         *  \return the value as string
         */
        int get_value()
        {
            return __value;
        }

};

#endif // __ASMX__REGISTER__
