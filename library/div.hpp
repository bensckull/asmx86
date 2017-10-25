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
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__Div__
#define __ASMX__Div__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>
#include <vector>

#include "engine/register.hpp"
#include "parser/utils.h"
#include "engine/stack.hpp"
#include "engine/variable.h"

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
        
         /*! Set label
         *
         *  \param name the label string
         */
        void div(std::string source)
        {
		int eax,edx;
		eax = findRegister("eax")->get_value();
		edx = findRegister("eax")->get_value();  
        		if(ifInt(source){
				int src = std::stoi(source);
				eax = eax * src;
				edx = eax % src;
				(findRegister("eax")->set_value(eax);
				(findRegister("edx")->set_value(edx);				
			}
			if(ifRegister(source){
				int src = findRegister(source)->get_value();
				eax = eax * src;
				edx = eax % src;
				(findRegister("eax")->set_value(eax);
				(findRegister("edx")->set_value(edx);				
			}
			if(ifMemory(source){
				int size2 = exctractSize(source);
				int src = AsmStack::get_value(size2);
				eax = eax * src;
				edx = eax % src;
				(findRegister("eax")->set_value(eax);
				(findRegister("edx")->set_value(edx);				
			}
		
        	}
    

                            
             
        }
        

};

git 
#endif //__ASMX__Div__
