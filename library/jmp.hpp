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
 
 /*! \file jmp.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__JMP__
#define __ASMX__JMP__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>
#include <vector>




/* --------------------------------------------------------------------------
 *  Functions
 * -------------------------------------------------------------------------- */

class AsmJmp: public AsmRegisterCollection
{
    
    private:
    
        int __value1;
        int __value2;
    public:
    
        /*! Constructor
         *
         *  \param reg the Registers Collection
         *  \note get the flags value
         */
     
        AsmJmp(vector<AsmRegister*> reg):AsmRegisterCollection(reg)
        
        {
             __value1 = findRegister("SF")->get_value();
             __value2 = findRegister("OF")->get_value();
        }
        
         /*! jmp function
         *
         *  \return true
         */ 
        bool jmp() {return true;}
        
        /*! jump if greater or equal
         *
         *  \return true  if value1 greater or equal to value2
         */
        
        bool jge() 
        {        
         if (__value1 >= __value2) return true;
         return false;            
        }
        
        /*! jump if less or equal
         *
         *  \return true  if value1 less or equal to value 2
         */
        bool jle() 
        {        
         if (__value1 <= __value2) return true;
         return false;            
        }
        
         /*! jump if less 
         *
         *  \return true  if value1 less then value2
         */
        bool jl() 
        {        
         if (__value1 < __value2) return true;
         return false;            
        }
        
        /*! jump if greater 
         *
         *  \return true  if value1 greater then value2
         */
        bool jg() 
        {        
         if (__value1 > __value2) return true;
         return false;            
        }
 

        

};


#endif
