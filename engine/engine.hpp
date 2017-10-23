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


#ifndef __ASMX__ENGINE__
#define __ASMX__ENGINE__

#include <map>
#include "parser/parser.hpp"
#include "variable.hpp"

using namespace std;

class AsmEngine: public AsmParser
{
     
	private:
     
        vector<AsmVariable*> __variables;
               
        /*  Create a new variable 
         *
         *  \param instruction the instruction contains the variable informations 
         *  \param id variable id 
         *
         *  \ return AsmVariable
         */
        AsmVariable* create_variable(AsmInstruction * instruction,int id)
        {
  
            string _size = instruction->get_parameters()[0];
            int size = (_size == "dd")? 4: (_size == "db")? 8:2;
            
            return new AsmVariable(id,instruction->get_name(),
                                   instruction->get_parameters()[1],size);  
                                                                
        }
        
        /*  Add a new variable to variables collection 
         *  
         *  \note this function increment the id of variables 
         *  
         */
        void init_variables()
        {
            int id =0;
		    for (AsmInstruction * instruction:get_sections()[0]->get_instructions())
            {
                __variables.push_back( create_variable(instruction,++id));
            }
        }
        
        void start()
        {
            init_variables();      
        }
	
	public:
	   
		AsmEngine(const std::string& path):AsmParser(path)
		{
		   start();              	    
		}
			
};


#endif
