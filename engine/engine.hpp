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

#include "parser/parser.hpp"

#include "engine/register.hpp"
#include "engine/variable.hpp"
#include "engine/stack.hpp"
#include "engine/errors.hpp"

#include "library/jmp.hpp"
#include "library/mov.hpp"
#include "library/cmp.hpp"
#include "library/push.hpp"
#include "library/add.hpp"
#include "library/sub.hpp"

using namespace std;

class AsmEngine: public AsmParser
{
    private:
        AsmVariableCollection* __variables;

        AsmRegisterCollection* __registers;

        AsmStack* __stack;
        
        AsmErrors* __errors;

        AsmSection* __data_section;
        AsmSection* __main_section;

        bool end_loop=false;
       

        /*! Create a new variable
         *
         *  \param instruction the instruction contains the variable informations
         *  \param id variable id
         *
         *  \return AsmVariable
         */
        AsmVariable* create_variable(AsmInstruction * instruction,int id)
        {
            string _size = instruction->get_parameters()[0];

            int size = (_size == "dd") ? 4 : (_size == "db") ? 8 : 2;

            return new AsmVariable(
                id,instruction->get_name(),
                instruction->get_parameters()[1],
                size
            );
        }

        /*! Add a new variable to variables collection
         *
         *  \note this function increment the id of variables
         *
         */
        void init_variables()
        {
            if(__data_section != nullptr)
            {
                int id = 0;

                for(AsmInstruction* instruction : __data_section->get_instructions())
                {
                    cout << "    :: Variable " << instruction->get_name() << endl;

                    __variables->add_variable( create_variable(instruction,++id));
                }
            }
        }

        /*  Initialize variables and registers  */

        void init()
        {
            // Variables collection
            __variables = new AsmVariableCollection();
            // Registers collection
            __registers = new AsmRegisterCollection();
            // Stack structure
            __stack = new AsmStack();
            
          

            // Program main section reference
            __main_section = nullptr;
            // Program data section reference
            __data_section = nullptr;
        }

        /*! Start instruction block
         *
         *  \note this function call the defined functions from library (mov,mul,jmp,..)
         *
         */
        
        void start(unsigned int position)
        {
       

            cout << "--> Start instructions from position " << position << endl;

            /* ---------------------------------------
             *  Manage instructions
             * --------------------------------------- */

            vector<AsmInstruction*> instructions = __main_section->get_instructions();

            cout << " -> Found " << instructions.size() << " instructions" << endl;
         

            unsigned int index = position;
   
            while(!end_loop) {
                // Instruction name

                string name = instructions[index]->get_name();
                // Instruction parameters
                vector<string> parameters = instructions[index]->get_parameters();
                
              /* ---------------------------------------
               *  Manage errors
               * --------------------------------------- */
               
              __errors = new AsmErrors(
                            __registers->get_registers(),
                            __variables->get_variables(),
                            __stack
                            );
                
                if ( !__errors->check_parameters(parameters,__main_section) )
                {
                    cout << "<<< error detected in " << name;
                    cout << " instruction  : " << index+1 <<" !!" <<endl;
                    break;
                
                }

                cout << " -> Instruction " << name << endl;

                /* ---------------------------------------
                 *  JUMP instructions
                 * --------------------------------------- */

                if(name.find_first_of("j") != string::npos)
                {
                    if(parameters.size() == 1)
                    {
                        cout << "    :: Jump to ";
                        cout << parameters[0] << endl;
                        
                        AsmJmp* jmp = new AsmJmp(
                            __registers->get_registers()
                        );
                        
            
                      
                        if(name == "jmp" and jmp->jmp())
                            jump(index);

                        else if(name == "jge" and jmp->jge())
                            jump(index);

                        else if(name == "jle" and jmp->jle())
                            jump(index);

                        else if(name == "jg" and jmp->jg())
                            jump(index);

                        else if(name == "jl" and jmp->jl())
                            jump(index);
                    }

                    else
                        cerr << "  ! Cannot parse instruction" << endl;
                }

                /* ---------------------------------------
                 *  CMP instructions
                 * --------------------------------------- */

                else if(name == "cmp")
                {
                    if(parameters.size() == 2)
                    {
                        cout << "    :: Compare ";
                        cout << parameters[0] << " with ";
                        cout << parameters[1] << endl;

                        AsmCmp* cmp = new AsmCmp(
                            __registers->get_registers(),
                            __variables->get_variables(),
                            __stack
                        );

                        cmp->cmp(parameters[0], parameters[1]);
                    }

                    else
                        cerr << "  ! Cannot parse instruction" << endl;
                }

                /* ---------------------------------------
                 *  MOV instructions
                 * --------------------------------------- */

                else if(name == "mov")
                {
                    if(parameters.size() == 2)
                    {
                        cout << "    :: Move ";
                        cout << parameters[1] << " to ";
                        cout << parameters[0] << endl;

                        AsmMov* mov = new AsmMov(
                            __registers->get_registers(),
                            __variables->get_variables(),
                            __stack
                        );

                        mov->mov(parameters[0], parameters[1]);
                    }

                    else
                        cerr << "  ! Cannot parse instruction" << endl;
                }
                
                /* ---------------------------------------
                 *  ADD instructions
                 * --------------------------------------- */
                  
                else if(name == "add")
                {
                         
                   if(parameters.size() == 2)
                   {
                        cout << "    :: Add ";
                        cout << parameters[1] << " to ";
                        cout << parameters[0] << endl;
 
                        AsmAdd* add = new AsmAdd(
                            __registers->get_registers(),
                            __variables->get_variables(),
                            __stack
                        );

                        add->add(parameters[0], parameters[1]);
                    }
                        
                    else
                        cerr << "  ! Cannot parse instruction" << endl;
                }
                
                 /* ---------------------------------------
                 *  SUB instructions
                 * --------------------------------------- */
                  
                else if(name == "sub")
                {
                         
                   if(parameters.size() == 2)
                   {
                        cout << "    :: Substract ";
                        cout << parameters[1] << " from ";
                        cout << parameters[0] << endl;
 
                        AsmSub* sub = new AsmSub(
                            __registers->get_registers(),
                            __variables->get_variables(),
                            __stack
                        );

                        sub->sub(parameters[0], parameters[1]);
                    }
                        
                    else
                        cerr << "  ! Cannot parse instruction" << endl;
                }

                /* ---------------------------------------
                 *  PUSH instructions
                 * --------------------------------------- */

                else if(name == "push")
                {
                    if(parameters.size() == 1)
                    {
                        cout << "    :: Push ";
                        cout << parameters[0] << endl;

                        AsmPush* push = new AsmPush(
                            __registers->get_registers(),
                            __variables->get_variables(),
                            __stack
                        );

                        push->Push(parameters[0]);
                    }

                    else
                        cerr << "  ! Cannot parse instruction" << endl;
                }

                /* ---------------------------------------
                 *  CALL Functions
                 * --------------------------------------- */

                else if(name == "call")
                {
                    if(parameters.size() == 1)
                    {
                        cout << "    :: Call ";
                        cout << parameters[0] << endl;

                        AsmLabel* label = __main_section->find_label(
                            parameters[0]
                        );

                        // This is a label
                        if (label != nullptr)
                        {
                            start(label->get_position());
                        }

                       
                        // This is a function
                        else
                        {
                        
                            /* ---------------------------------------
                             *  Printf function
                             * --------------------------------------- */
                 
                            AsmExtern* function = new AsmExtern(
                                __variables->get_variables(),
                                __stack
                            );
                            
                            showStack(parameters[0]);

                            if(parameters[0].find("printf") != string::npos)
                            {
                                cout << "<<< " << function->printf() << endl;
                            }
                          
                            
                        }
                        
                    }
                 }
                    
                 
                /* ---------------------------------------
                 *  Manage while loop
                 * --------------------------------------- */

                ++index;
                
                if(index >= instructions.size()) 
                    end_loop = true;
            }
        }

        /*! Jump to the instructions label
         *
         *  \param index the index of the first instruction
         */
        void jump(size_t index)
        {
            vector<AsmInstruction*> instructions = __main_section->get_instructions();

            if(index < 0 or index >= instructions.size())
            {
                throw runtime_error(
                    "Cannot access to index " + index
                );
            }

            // Instruction parameters
            vector<string> parameters = instructions[index]->get_parameters();

            if(parameters.size() > 0)
            {
                AsmLabel* label = __main_section->find_label(
                    parameters[0]
                );

                if(label != nullptr)
                {
                    start(label->get_position());
                }

                else
                {
                    throw runtime_error(
                        "Cannot access position for " + parameters[0]
                    );
                }
            }

            else
            {
                throw length_error(
                    "Instructions structure is empty"
                );
            }
        }
        
        /*! Show the stack values while calling function
         *
         *  \param nameFunction the index of the first instruction
         *
         *  \note this function is temporary here , just for showing the running traces
         *
         */
        void showStack(string nameFunction)
        {
        
            map<int,int> ebp,esp ;
            __stack->FillEsp();
            ebp = __stack->get_ebp();
            esp = __stack->get_esp();
            map<int,int>::iterator j=esp.begin();
            
            cout << endl;
            cout << "  > Stack values while calling  "<< nameFunction << " function : " << endl << endl;
        
            for(map<int,int>::iterator i=ebp.begin(); i!=ebp.end(); ++i) 
            {
                
                cout << "   [ebp+" << i->first<< "]" << "    " <<i->second;
                cout << "    [esp" << j->first << "]"<< endl;
         
                ++j;
                
             }
             cout << endl;
        }


    public:
        /*! Constructor
         *
         *  \param path asm file path
         */
        AsmEngine(const std::string& path):AsmParser(path)
        {
            // Manage main label position
            int position = -1;

            cout << "--> Initialize AsmEngine" << endl;
            init();

            cout << "--> Check sections" << endl;
            for(AsmSection* section : get_sections())
            {
                cout << " -> Section " << section->get_name() << endl;

                for(AsmLabel* label : section->get_labels())
                {
                    // Check main label
                    if(label->get_name() == "main")
                    {
                        cout << "    :: Found label " << label->get_name() << endl;

                        // Manage section reference
                        __main_section = section;

                        if(position != -1)
                            cerr << " !! Already set main label " << endl;

                        // Get main label position
                        position = label->get_position();
                    }
                }

                // Check data section
                if(section->get_name() == "data")
                {
                    __data_section = section;

                    // Initialize program variables
                    init_variables();
                    // Initialize program regiseters
                    __registers->init_registers();
                }
            }

            cout << "--> Check main position" << endl;
            if(position != -1)
                start(position);

            else
                cerr << "  ! No main label has been founded in this program" << endl;


        }
};

#endif
