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

 /*! \file errors.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__ERRORS__
#define __ASMX__ERRORS__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include "parser/utils.hpp"
#include "parser/section.hpp"
#include "library/extern.hpp"

/* --------------------------------------------------------------------------
 *  Functions
 * -------------------------------------------------------------------------- */

class AsmErrors: public AsmRegisterCollection,AsmVariableCollection , AsmStack
{

   private:

     AsmStack * __stack;
     AsmExtern* function;
    

    public:




        /*! Constructor
         *
         *  \param reg the Registers Collection
         *  \param var the variables Collection
         *  \param stack
         *
         */
        AsmErrors(vector<AsmRegister*> reg,vector<AsmVariable*> var,AsmStack * stack):
        AsmRegisterCollection(reg),AsmVariableCollection(var),__stack(stack)
        {
                    function = new AsmExtern(var,stack);
        }

        /*! Check errors in the instruction parameters
         *
         *  \param parameter
         *  \section help to check the existing labels in the programm
         *  \return true is no error detected
         *
         */
        bool check_parameters(vector<string> parameters,AsmSection* section)
        {
        
        
            for (auto p:parameters)
            {
               
                if (!check_parameter(p,section))
                   return false;
         
            }
            
            return true;
        
        }

        
        /*! Check errors in the instruction parameter
         *
         *  \param parameter
         *  \section help to check the existing labels in the programm
         *  \return true is no error detected
         *
         */
        bool check_parameter(std::string parameter,AsmSection* section)
        {
         bool check = true;
         if(ifRegister(parameter))
         {
      
            if(findRegister(parameter) != NULL)
            {
               
                check=true;
            }
            else
            {
                if(findVariable(parameter) != NULL)
             
                    check=true;
                    
                else if (section->find_label(parameter))
                      
                      check=true;
                else if (function->findFunction(parameter))
                 
                      check=true;
                else
                {
                      check=false;
                }
            }
       
          }
          if(ifInt(parameter))
          {

            check=true;

          }

          if(ifMemory(parameter))
          {

                if (ifStack(parameter))
                {

                   check=true;
                }
                else
                {

                     parameter = extractVariable(parameter);
                     if ( findVariable(parameter) != NULL )
                     {
                        check=true;
                     }
                     else
                        check=false;
                     
                }
          }       
            
        return check;
        }



};
#endif

