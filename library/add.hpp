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
 
 /*! \file add.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__ADD__
#define __ASMX__ADD__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>
#include <vector>
#include "parser/utils.hpp"




/* --------------------------------------------------------------------------
 *  Functions
 * -------------------------------------------------------------------------- */

class AsmAdd: public AsmRegisterCollection,AsmVariableCollection , AsmStack
{
    
   private:
    
     AsmStack * __stack;
    public:
    
 
        /*! Constructor
         *
         *  \param reg the Registers Collection
         *  \param var the variables Collection
         *  \param stack
         *  
         */
        AsmAdd(vector<AsmRegister*> reg,vector<AsmVariable*> var,AsmStack * stack):
        AsmRegisterCollection(reg),AsmVariableCollection(var),__stack(stack)
        {}
           
        
        
        /*! Add function 
         *
         *  \param destination
         *  \param source
         *  
         */
        void add(string destination,string source)
        {
              
                int src = get_value(source);
                int dest= get_value(destination);
                dest=dest+src;
            
            if(ifRegister(destination)) 
            {
                /* the dastination is a stack register 
                   add esp,16 = remove the first 16 bits in the stack */
                   
                if(findRegister(destination)->get_label().find("sp") != std::string::npos)
                {
                     __stack->remove(src);   
                
                }
                else
                {   
                    findRegister(destination)->set_value(dest);
                                
                }

            }
                
                
            if(ifMemory(destination))
            {
                int size = extractSize(destination);
                 __stack->set_value(size,dest);
            }
        }
        
        /* Return the real value of the parameter 
         *
         *  \param parameter parameter to evaluate 
         *  \note get value from  register or  stack
         *  \note if the parameter is variable get the id that reference to the variable address in
         *   the stack 
         *  \return int value
         *  
         */
        
        
        int get_value(std::string parameter)
        {
         
         if(ifRegister(parameter))
         {
           
            if(findRegister(parameter) != NULL) 
                return  findRegister(parameter)->get_value(); 
      
            else
			    return findVariable(parameter)->get_id() ;
          } 
          			  
	       if(ifInt(parameter))
	        return std::stoi(parameter);
	        
	       	if(ifMemory(parameter)){
	       	
	       	    if (ifStack(parameter)) 
	       	    {
			         
			         int size = extractSize(parameter);
				     return __stack->get_value(size); 
			    }
			    else
			    {		
				     parameter = extractVariable(parameter);
				     return std::stoi(findVariable(parameter)->get_value()) ;	
			   	}		
			}				        		  			
	       return 0;				
        }       

};
#endif

