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
 
 /*! \file mul.hpp
 *
 *  \author Hanan6 <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */


#ifndef __ASMX__Mul__
#define __ASMX__Mul__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <string>
#include <vector>




/* --------------------------------------------------------------------------
 *  Functions
 * -------------------------------------------------------------------------- */

class AsmMul: public AsmRegisterCollection,AsmVariableCollection , AsmStack
{
    

    public:
     
        AsmMul(vector<AsmRegister*> reg,vector<AsmVariable*> var):
        AsmRegisterCollection(reg),AsmVariableCollection(var),AsmStack()
        {}
        
        
        void mul()
        {
        
           /*  traitements de la fonctions mul( parametre )
             
             pour changer la valeur d'un registre i : 
             
                (get_registers())[i]->set_value("value") ;
             
             pour recuperer la valeur d'un registre i  : 
             
                (get_registers())[i]->get_value() ;
             
             pour trouver le registre du parametre (si le parametre est un registre): 
             
                findRegister("eax")->set_value(13); 
                
             !! Idem pour les variables 
             
             pour recuperer une valeur de stack " [ebp+4] " :
             
                get_value(4)
                
             !! pour remplir le stack faut faire des push(value,size)
             
             pour appler la fonction :
             
                dans le engine.hpp la fonction start 
                         
             
             */

                            
             
        }
        

};


#endif
