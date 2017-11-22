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

#ifndef __ASMX__MOV__
#define __ASMX__MOV__

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

class AsmMov:public AsmRegisterCollection,AsmVariableCollection , AsmStack
{
  

    public:
 	/*! Constructor
         *
         *  \param name the function name
         */
	AsmMov(vector<AsmRegister*> reg,vector<AsmVariable*> var):
        AsmRegisterCollection(reg),AsmVariableCollection(var),AsmStack()
        {}
      
        AsmMov();

         /*! function mov
         *
         *  \mov function for mov instruction :
         *  \mov destination, source
         *  \destination = source
         */
        void mov(std::string destination, std::string source)
        {
		if(ifMemory(destination)){
			int size = extractSize(destination);
			//int dest = AsmStack::get_value(size);
			if(ifInt(source)){
				int src = std::stoi(source);
				AsmStack::push(src,size);			
			}
			if(ifRegister(source)){
				int src = findRegister(source)->get_value();
				int size2 = findRegister(source)->get_size();
				AsmStack::push(src,size2);				
			}
			if(ifMemory(source)){
				int size2 = extractSize(source);
				int src = AsmStack::get_value(size2);
				AsmStack::push(src,size2);
			}						
		}else if (ifRegister(destination)){
			//int dest = findRegister(destination)->get_value();
			if(ifInt(source)){
				int src = toInt(source);
				findRegister(destination)->set_value(src);			
			}
			if(ifRegister(source)){
			     int src=findRegister(source)->get_value();				
				findRegister(destination)->set_value(src);			
			}
			if(ifMemory(source)){
				//int size = exctractSize(source);
				//int dest = AsmStack::get_value(size);
				int src = findRegister(source)->get_value();
				findRegister(destination)->set_value(src);
			}
		
        }


};

#endif // __ASMX__MOV__
