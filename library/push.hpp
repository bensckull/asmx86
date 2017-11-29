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

 /*! \file push.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__PUSH__
#define __ASMX__PUSH__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include "parser/utils.hpp"

/* --------------------------------------------------------------------------
 *  Functions
 * -------------------------------------------------------------------------- */

class AsmPush: public AsmRegisterCollection,AsmVariableCollection , AsmStack
{

   private:

     AsmStack * __stack;
     int size;
     int value;
    public:




        /*! Constructor
         *
         *  \param reg the Registers Collection
         *  \param var the variables Collection
         *  \param stack
         *
         */
        AsmPush(vector<AsmRegister*> reg,vector<AsmVariable*> var,AsmStack * stack):
        AsmRegisterCollection(reg),AsmVariableCollection(var),__stack(stack)
        {}


        /* Push function call push finction from the stack
         *
         *  \param parameter value to insert
         *
         *
         */
        void Push(string parameter)
        {
          get_value(parameter);
          __stack->push(value,size);

        }



         /* Get the real value of the parameter
         *
         *  \param parameter parameter to evaluate
         *  \note get value from  register or  stack
         *  \note if the parameter is variable get the id that reference to the variable address in
         *   the stack
         *
         */

        void get_value(std::string parameter)
        {

         if(ifRegister(parameter)){
            if(findRegister(parameter) != NULL)
            {
                size = findRegister(parameter)->get_size();
                value= findRegister(parameter)->get_value();
            }
            else
            {
                size = findVariable(parameter)->get_size();
                value= findVariable(parameter)->get_id() ;

            }
          }

          if(ifInt(parameter))
         {

            value= std::stoi(parameter);

         }

         if(ifMemory(parameter)){

                if (ifStack(parameter))
                {

                     size = extractSize(parameter);
                     value= __stack->get_value(size);
                }
                else
                {

                     parameter = extractVariable(parameter);
                     size = findVariable(parameter)->get_size();
                     value= findVariable(parameter)->get_id() ;
                }
          }



        }





};
#endif

