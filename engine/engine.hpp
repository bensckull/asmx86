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
 
 /*! \file engine.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__ENGINE__
#define __ASMX__ENGINE__

#include <map>
#include "parser/parser.hpp"
#include "register.hpp"
#include "variable.hpp"
#include "stack.hpp"
#include "library/mul.hpp"


using namespace std;

class AsmEngine: public AsmParser
{
     
	private:
     
        
         AsmVariableCollection * __variables;
         AsmRegisterCollection * __registers;
        
        
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
                __variables->add_variable( create_variable(instruction,++id));
            }
        }
        
        /*  Initialize variables and registers  */ 
              
        void init()
        {
            __variables = new  AsmVariableCollection();
		    __registers = new  AsmRegisterCollection();
		    
            init_variables();
             
            __registers->init_registers();
            
        }
        
        /*  Start instruction block
         *  
         *  \note this function call the defined functions from library (mov,mul,..) 
         *  
         */
        void start()
        {
              for (AsmInstruction * instruction:get_sections()[1]->get_instructions())
            {
               string name = instruction->get_name() ;
               
               if (name.find("mul") != string::npos)
               {
                         
                AsmMul * mul = new AsmMul(__registers->get_registers(),
		                                  __variables->get_variables());
		                                  
		        mul->mul();        
               
               }
            }
            
        }
	
	public:
	
	    /*! Constructor
         *
         *  \param path asm file path
         */ 
		AsmEngine(const std::string& path):AsmParser(path)
		{
		   
		   init();  
		   start();
		   
		   //cout << (__variables->get_variables())[0]->get_name() << endl	   
		   // cout << (__registers->findRegister("eax"))->get_value() << endl;
	
		}	
    	
};


#endif
