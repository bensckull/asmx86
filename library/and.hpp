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

/*! \file mov.hpp
 *
 *  \author Adnan44 <adnane.mounassib@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__And__
#define __ASMX__And__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include "engine/register.hpp"
#include "parser/utils.h"
#include "engine/stack.hpp"
#include "engine/variable.h"
/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */                  

class AsmAnd:public AsmRegisterCollection,AsmVariableCollection , AsmStack
{
  

    public:

	 AsmAnd(vector<AsmRegister*> reg,vector<AsmVariable*> var):
        AsmRegisterCollection(reg),AsmVariableCollection(var),AsmStack()
        {}
        /*! Constructor
         *
         *  \param name the function name
         */
        AsmAnd():{}

        /*! Set label
         *
         *  \param name the label string
         */
        void and(std::string destination, std::string source)
        {
		if(ifMemory(destination)){
			int size = exctractSize(destination);
			int dest = AsmStack::get_value(size);
			int boolean;
			if(ifInt(source){
				int src = std::stoi(source);
				boolean = src & dest;
				AsmStack::push(boolean,size);			
			}
			if(ifRegister(source){
				int src = findRegister(source)->get_value();
				int size2 = findRegister(source)->get_size();
				boolean = src & dest;
				AsmStack::push(boolean,size2);				
			}
			if(ifMemory(source){
				int size2 = exctractSize(source);
				int src = AsmStack::get_value(size2);
				boolean = src & dest;
				AsmStack::push(boolean,size2);
			}						
		}else if (ifRegister(destination)){
			int dest = findRegister(destination)->get_value();
			if(ifInt(source){
				int src = toInt(source);
				boolean = src & dest;
				findRegister(destination)->set_value(boolean);			
			}
			if(ifRegister(source){
				int src = findRegister(source)->get_value();				
				findRegister(destination)->set_value(boolean);			
			}
			if(ifMemory(source){
				int size = exctractSize(source);
				int dest = AsmStack::get_value(size);
				boolean = src & dest;
				findRegister(destination)->set_value(boolean);
			}
		
        }


};

#endif
