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

/*! \file stack.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__STACK__
#define __ASMX__STACK__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>
#include <map>
#include <stack>
#include <vector>

#include "engine/register.hpp"

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */
 
using namespace std;

class AsmStack 
{
    private:
    
        map<int,int> __ebp;
        map<int,int> __esp;
        int __pointerP;  
        int __pointerV; 
        
    public:
      
        AsmStack(){}
        
       /*! add function parameters to the stack (ebp)
        *
        * \param value the function parameter 
        * \param size the size of value (2(16 bits)s,4(32 bits),..)
        * \param pointerP the the address in the stack(ebp+4, ..)
        *
        */
         
        void pushP(int value,int size)
        {          
            __pointerP +=size;
            __ebp.insert(std::pair<int,int>(__pointerP, value));
              
        } 
        
        /*! Add local variables to the stack (ebp)
         *
         * \param adr the address of the variable (a:1 ,msg:2,..)
         * \param size the size of value (2(16 bits)s,4(32 bits),..)
         *
         */
                
        void pushV(int adr,int size) 
        {          
            __pointerV +=size;
            __ebp.insert(std::pair<int,int>(-__pointerV,adr));
                                                             
        } 
        
        /*! Copy ebp into esp    */

     
        void FillEsp() 
        {
            map<int,int>::reverse_iterator rit=__ebp.rbegin(); 
            map<int,int>::iterator it;
            __esp.clear();
            for (auto it:__ebp)
            {
                if (it.first>0)
                {
                    __esp.insert(std::pair<int,int>(-rit->first,it.second));
                    rit= next(rit);
                }
            }                  
        }
        
        /*! Retrieve the contents of the top of the stack  
         *  and transfer it to the register __ register
         */
        void popR(AsmRegister * __register)
        {     
            int value = __ebp.at((--__ebp.end())->first);
            __ebp.erase(--__ebp.end());
            __register->set_value(value);     
        } 
        
        /*! Empty the stack  */
       
        
        void pop() 
        {  
           __ebp.clear();
           __esp.clear();
        } 
        
       /*! get a value of the specified address
         *
         * \param address the address of value 
         * \return value
         */ 
        
        int get_value(int address) 
        {  
            return __ebp.at(address);
        }
         
         
        /*! modify the socked value 
         *
         *  \param address the address of value to modify
         *  \param Value the new value
         */
        void set_value(int address,int value) 
        {  
            __ebp.at(address)=value;
        }
        
        /*! Get ebp
         *
         *  \return a map
         */
        map<int,int> get_ebp() 
        {  
            return __ebp;
        }  
         
        /*! Get esp
        *
        *  \return a map
        */
        map<int,int> get_esp() 
        {  
            return __esp;
        } 

};

#endif // __ASMX__STACK__
