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

/*! \file and.hpp
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
#include "parser/utils.hpp"
#include "engine/stack.hpp"
#include "engine/variable.hpp"
/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */                  

class AsmAnd:public AsmRegisterCollection,AsmVariableCollection , AsmStack
{

    public:
        /*! Constructor
         *
         *  \param name the function name
         */

	AsmAnd(vector<AsmRegister*> reg,vector<AsmVariable*> var):
        AsmRegisterCollection(reg),AsmVariableCollection(var),AsmStack()
        {}

        /*! function and 
         *
         *  \and function for and instruction :
         *  \and destination, source
         *  \destination = destination AND source
         */
        void anD(std::string destination, std::string source)
        {
                int boolean;
		bool boolean2;
		if(ifMemory(destination)){
			int size = extractSize(destination);
			int dest = AsmStack::get_value(size);
			
			if(ifInt(source)){
				int src = std::stoi(source);
				boolean2 = src && dest;
				boolean = toInt32(boolean2);
				AsmStack::push(boolean,size);			
			}
			if(ifRegister(source)){
				int src = findRegister(source)->get_value();
				int size2 = findRegister(source)->get_size();
				boolean2 = src && dest;
				boolean = toInt32(boolean2);
				AsmStack::push(boolean,size2);				
			}
			if(ifMemory(source)){
				int size2 = extractSize(source);
				int src = AsmStack::get_value(size2);
				boolean2 = src && dest;
				boolean = toInt32(boolean2);
				AsmStack::push(boolean,size2);
			}						
		}else if (ifRegister(destination)){
			int dest = findRegister(destination)->get_value();
			if(ifInt(source)){
				int src = toInt(source);
				boolean2 = src && dest;
				boolean = toInt32(boolean2);
				findRegister(destination)->set_value(boolean);			
			}
			if(ifRegister(source)){
				int src = findRegister(source)->get_value();
				boolean2 = src && dest;
				boolean = toInt32(boolean2);				
				findRegister(destination)->set_value(boolean);			
			}
			if(ifMemory(source)){
				int size = extractSize(source);
				int src = AsmStack::get_value(size);
				boolean2 = src && dest;
				boolean = toInt32(boolean2);
				findRegister(destination)->set_value(boolean);
			}
		
        }


};

#endif
