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

 /*! \file div.hpp
 *
 *  \author Adnan44 <adnane.mounassib@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__Div__
#define __ASMX__Div__

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

class AsmDiv: public AsmRegisterCollection,AsmVariableCollection , AsmStack
{


    public:

        /*! Constructor
         *
         *  \param name the function name
         */

        AsmDiv(vector<AsmRegister*> reg,vector<AsmVariable*> var):
        AsmRegisterCollection(reg),AsmVariableCollection(var),AsmStack()
        {}

          /*! function div
         *
     *  \parameters source and size (2 for 16bits 4 for 32bits and 8 for 64bits)
         *  \div function for division instruction :
         *  \div source
         *  \eax = eax * source
         *  \edx = eax % source
         */
        void div(std::string source, int size)
        {
        //int eax,edx,ax,dx,rax,rdx;
        if (size==2){
        int ax = findRegister("ax")->get_value();
        int dx = findRegister("dx")->get_value();
                if(ifInt(source)){
                int src = std::stoi(source);
                ax = ax * src;
                dx = ax % src;
                findRegister("ax")->set_value(ax);
                findRegister("dx")->set_value(dx);
            }
            if(ifRegister(source)){
                int src = findRegister(source)->get_value();
                ax = ax * src;
                dx = ax % src;
                findRegister("ax")->set_value(ax);
                findRegister("dx")->set_value(dx);
            }
            if(ifMemory(source)){
                int size2 = extractSize(source);
                int src = AsmStack::get_value(size2);
                ax = ax * src;
                dx = ax % src;
                findRegister("ax")->set_value(ax);
                findRegister("dx")->set_value(dx);
            }
            }
        if (size==4){
                int eax = findRegister("eax")->get_value();
                int edx = findRegister("edx")->get_value();
                if(ifInt(source)){
                int src = std::stoi(source);
                eax = eax * src;
                edx = eax % src;
                findRegister("eax")->set_value(eax);
                findRegister("edx")->set_value(edx);
            }
            if(ifRegister(source)){
                int src = findRegister(source)->get_value();
                eax = eax * src;
                edx = eax % src;
                findRegister("eax")->set_value(eax);
                findRegister("edx")->set_value(edx);
            }
            if(ifMemory(source)){
                int size2 = extractSize(source);
                int src = AsmStack::get_value(size2);
                eax = eax * src;
                edx = eax % src;
                findRegister("eax")->set_value(eax);
                findRegister("edx")->set_value(edx);
            }
                if (size==8){
                        int rax = findRegister("rax")->get_value();
                int rdx = findRegister("rdx")->get_value();
                if(ifInt(source)){
                int src = std::stoi(source);
                rax = rax * src;
                rdx = rax % src;
                findRegister("rax")->set_value(rax);
                findRegister("rdx")->set_value(rdx);
            }
            if(ifRegister(source)){
                int src = findRegister(source)->get_value();
                rax = rax * src;
                rdx = rax % src;
                findRegister("rax")->set_value(rax);
                findRegister("rdx")->set_value(rdx);
            }
            if(ifMemory(source)){
                int size2 = extractSize(source);
                int src = AsmStack::get_value(size2);
                rax = rax * src;
                rdx = rax % src;
                findRegister("rax")->set_value(rax);
                findRegister("rdx")->set_value(rdx);
            }
            }
        }


};


#endif //__ASMX__Div__
