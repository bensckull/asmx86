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

        int __value;

	int __operandSize;

    public:
        /*! Constructor
         *
         *  \param label the Register label
         */
        AsmRegister(const std::string& label, int operandSize): 
		__label(label), __operandSize(operandSize){}

        /*! Constructor
         *
         *  \param name the register name
         *  \param value the register value
         */
        AsmRegister(const std::string& label, int value):
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
        void set_value(int value)
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
	/*! Set the operand size (16 for AX BX.., 32 for EAX EBX..., 64 for RAX RBX...) value
         *
         *  \ value 
         */
        void set_operandSize(int operandSize)
        {
            __operandSize = operandSize;
        }

        /*! Get the operand size value
         *
         *  \return the value
         */
        int get_operandSize()
        {
            return __operandSize;
        }

};

#endif // __ASMX__REGISTER__
