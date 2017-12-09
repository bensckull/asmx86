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

 /*! \file extern.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__EXTERN__
#define __ASMX__EXTERN_

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <algorithm>

#include "parser/utils.hpp"

/* --------------------------------------------------------------------------
 *  Functions
 * -------------------------------------------------------------------------- */

class AsmExtern: public AsmVariableCollection,AsmStack
{

    private:
        AsmStack * __stack;
        vector<string> __extern;
        int index=1;

    public:
        /*! Constructor
         *
         *  \param var the variables Collection
         *  \param stack
         *
         */
        AsmExtern(vector<AsmVariable*> var,AsmStack * stack):
        AsmVariableCollection(var),__stack(stack) 
        {
              __extern.push_back("printf");
        }


         /* Printf function
         *
         *  \note replace the %d or %f .. with the last inserted value in the stack
         *  \return message to print
         *
         */
        string printf()
        {
           
           string message = findVariableById(__stack->top(index))->get_value();

            while (message.find("%") != string::npos)
                message.replace(message.find("%"),2,to_string(__stack->top(++index)));

            return message;
        }
        
        
        /* Find extern function
         *
         *  \para name name function
         *  \return bool value
         *
         */
        bool findFunction(string name)
        {
          for (auto e:__extern)
           {
            if (e == name) return true;
           }
           return false ;
        }
        
        
        
};
#endif

