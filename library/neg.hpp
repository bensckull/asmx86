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

/*! \file neg.hpp
 *
 *  \author Adnan44 <adnane.mounassib@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__Neg__
#define __ASMX__Neg__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include "parser/utils.hpp"

#include "engine/stack.hpp"
#include "engine/register.hpp"
#include "engine/variable.hpp"

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

class AsmNeg:public AsmRegisterCollection,AsmVariableCollection , AsmStack
{


    public:
        /*! Constructor
         *
         *  \param name the function name
         */
     AsmNeg(vector<AsmRegister*> reg,vector<AsmVariable*> var):
        AsmRegisterCollection(reg),AsmVariableCollection(var),AsmStack()
        {}
        /*! function neg
         *
         *  \negation function for neg instruction :
         *  \neg destination
         *  \destination = - destination
         */
        void neg(std::string destination)
        {
         if(ifRegister(destination)){
            int dest = findRegister(destination)->get_value();
            dest = - dest;
            findRegister(destination)->set_value(dest);

        }


};

#endif // __ASMX__Neg__
