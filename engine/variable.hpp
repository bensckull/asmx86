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

/*! \file variable.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__VARIABLE__
#define __ASMX__VARIABLE__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>
using namespace std;

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */


class AsmVariable
{
    private:
        
        int __id;
        string __name;
        string __value;
	    int __size;


    public:
  
        /*! Constructor
         *
         *  \param id to identify the variable in the stack " [ebp-size]=id " 
         *  \param name variable name
         *  \param value variable value    
         *  \param size db=2 dd=4 dw=8  
         *
         */
        AsmVariable(int id,const std::string& name,
                    const std::string& value,int size): 
                    
		    __id(id),__name(name),
		    __value(value),__size(size){}
		    
		    
		/*! Get the variable name
         *
         *  \return a string name
         */           
        string get_name()
        {
            return __name;
        }
        
       /*! Set the variabler name
        *
        *  \param name
        */     
        void set_name(string name)
        {
            __name=name;
        }
    
        /*! Get the variable value
         *
         *  \return a string value
         */
        string get_value()
        {
            return __value;
        }
        
        /*! Set the variable value
         *
         *  \param value
         */
        void set_value(int value)
        {
            __value = value;
        }
   
        /*! Get the variable size
         *
         *  \return a int
         */
        int get_size()
        {
            return __size;
        }
        
        /*! Set the variable size
         *
         *  \param size
         */
        void set_size(int size)
        {
            __size=size;
        }
        
        /*! Get the variable id
         *
         *  \return int
         */
        
        int get_id() 
        {
            return __id;
        }
        
        /*! Set the variable id
         *
         *  \param id
         */
        void set_id(int id) 
        {
            __id=id;
        }

};

class AsmVariableCollection 
{
    private:
        
        vector<AsmVariable*> __variables;

    public:
    
        /*! Constructor */
        AsmVariableCollection(){}
        
        /*! Constructor
         *
         *  \param var the variables vector
         */
        AsmVariableCollection(vector<AsmVariable*> var)
                              :__variables(var){}
                              
        /*! Get the collection
         *
         *  \return variables vector
         */
        vector<AsmVariable*>  get_variables()
        {
            return __variables;
        }
        
        /*! Get a new variables
         *
         *  \param variable new variables
         */
        void add_variable(AsmVariable* variable)
        {
            __variables.push_back(variable);
        }
        
        /*! check if the string is a name of variable ?
         *
         *  \param nameVariable
         *  \return variable if yes else return null
         */
        
        AsmVariable* findVariable(string  nameVariable)
        {
           for (auto var:__variables)
           {
            if (var->get_name() == nameVariable) return var;
           }
           return NULL ;
        }
        
        /*! Search a variable by id ?
         *
         *  \param id id variable
         *  \return variable if yes else return null
         */
        
        AsmVariable* findVariableById(int id)
        {
           for (auto var:__variables)
           {
            if (var->get_id() == id) return var;
           }
           return NULL ;
        }
    
    
};

#endif // __ASMX__VARIABLE__
