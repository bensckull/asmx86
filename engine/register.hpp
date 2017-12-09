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

        int __size;

    public:
        /*! Constructor
         *
         *  \param label the Register label
         */
        AsmRegister(const std::string& label,int value, int size):
        __label(label),__value(value), __size(size){}


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
        
           if(__label != "ebp" && __label != "esp")
             std::cout << "       +"<<__label << " = " << value << std::endl;
             
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
        /*! Set the size (2 for AX BX.., 4 for EAX EBX...,8 for RAX RBX...) value
         *
         *  \ value
         */
        void set_size(int size)
        {
            __size = size;
        }

        /*! Get the size value
         *
         *  \return the value
         */
        int get_size()
        {
            return __size;
        }

};

class AsmRegisterCollection
{
    private:

        std::vector<AsmRegister*> __registers;

    public:

        /*! Constructor */
        AsmRegisterCollection(){}

        /*! Constructor
         *
         *  \param reg the registers vector
         */
        AsmRegisterCollection(std::vector<AsmRegister*> reg):__registers(reg){}

        /*! Get the collection
         *
         *  \return registers vector
         */
        std::vector<AsmRegister*>  get_registers()
        {
            return __registers;
        }

        /*! check if the string is a name of register ?
         *
         *  \param nameRegister
         *  \return register if yes else return null
         */
        AsmRegister* findRegister(std::string nameRegister)
        {
           for (auto reg:__registers)
           {
            if (reg->get_label() == nameRegister) return reg;
           }
           return NULL ;
        }

        /* Initialize registers */
        void init_registers()
        {
            __registers.push_back(new AsmRegister("eax",0,4));
            __registers.push_back(new AsmRegister("ebx",0,4));
            __registers.push_back(new AsmRegister("ecx",0,4));
            __registers.push_back(new AsmRegister("edx",0,4));
            __registers.push_back(new AsmRegister("edx",0,4));
            __registers.push_back(new AsmRegister("esi",0,4));
            __registers.push_back(new AsmRegister("edi",0,4));
            __registers.push_back(new AsmRegister("ebp",0,4));
            __registers.push_back(new AsmRegister("esp",0,4));

            __registers.push_back(new AsmRegister("ax",0,2));
            __registers.push_back(new AsmRegister("bx",0,2));
            __registers.push_back(new AsmRegister("cx",0,2));
            __registers.push_back(new AsmRegister("dx",0,2));
            __registers.push_back(new AsmRegister("dx",0,2));
            __registers.push_back(new AsmRegister("si",0,2));
            __registers.push_back(new AsmRegister("di",0,2));
            __registers.push_back(new AsmRegister("bp",0,2));
            __registers.push_back(new AsmRegister("sp",0,2));

            // Les indicateurs FLAGS register

             __registers.push_back(new AsmRegister("CF",0,2));
             __registers.push_back(new AsmRegister("ZF",0,2));
             __registers.push_back(new AsmRegister("PF",0,2));
             __registers.push_back(new AsmRegister("OF",0,2));
             __registers.push_back(new AsmRegister("SF",0,2));


        }

};

#endif // __ASMX__REGISTER__
