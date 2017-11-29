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

 /*! \file mul.hpp
 *
 *  \author Adnan44 <adnane.mounassib@gmail.com>
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date november 2017
 */


#ifndef __ASMX__Mul__
#define __ASMX__Mul__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include "parser/utils.hpp"

#include "engine/stack.hpp"
#include "engine/register.hpp"
#include "engine/variable.hpp"

/* --------------------------------------------------------------------------
 *  Functions
 * -------------------------------------------------------------------------- */

class AsmMul: public AsmRegisterCollection,AsmVariableCollection , AsmStack
{


    public:

        AsmMul(vector<AsmRegister*> reg,vector<AsmVariable*> var):
        AsmRegisterCollection(reg),AsmVariableCollection(var),AsmStack()
        {}

        /*! function mul
         *
     *  \parameters source and size (2,4 or 8 for 16bits,32bits and 64bits)
         *  \mul function for multiplication instruction :
         *  \mul source
         *  \edx = eax * source
         */
        void mul(std::string source, int size)
        {
        if (size==2){
        int ax = findRegister("ax")->get_value();
                if(ifInt(source)){
                int src = std::stoi(source);
                ax = ax * src;
                findRegister("dx")->set_value(ax);
            }
            if(ifRegister(source)){
                int src = findRegister(source)->get_value();
                ax = ax * src;
                findRegister("dx")->set_value(ax);
            }
            if(ifMemory(source)){
                int size2 = extractSize(source);
                int src = AsmStack::get_value(size2);
                ax = ax * src;
                findRegister("dx")->set_value(ax);
            }
                }
        if (size==4){
        int eax = findRegister("eax")->get_value();
                if(ifInt(source)){
                int src = std::stoi(source);
                eax = eax * src;
                findRegister("edx")->set_value(eax);
            }
            if(ifRegister(source)){
                int src = findRegister(source)->get_value();
                eax = eax * src;
                findRegister("edx")->set_value(eax);
            }
            if(ifMemory(source)){
                int size2 = extractSize(source);
                int src = AsmStack::get_value(size2);
                eax = eax * src;
                findRegister("edx")->set_value(eax);
            }
                }
        if (size==8){
        int rax = findRegister("rax")->get_value();
                if(ifInt(source)){
                int src = std::stoi(source);
                rax = rax * src;
                findRegister("rdx")->set_value(rax);
            }
            if(ifRegister(source)){
                int src = findRegister(source)->get_value();
                rax = rax * src;
                findRegister("rdx")->set_value(rax);
            }
            if(ifMemory(source)){
                int size2 = extractSize(source);
                int src = AsmStack::get_value(size2);
                rax = rax * src;
                findRegister("rdx")->set_value(rax);
            }
                }

        }

};


#endif
