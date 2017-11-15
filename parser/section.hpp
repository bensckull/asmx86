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

/*! \file section.hpp
 *
 *  \author BroFreedom <jdoe1337@gmx.fr>
 *  \author BroFreedom <hanan.najim6@gmail.com>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__SECTION__
#define __ASMX__SECTION__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include <vector>
#include <string>

#include "parser/label.hpp"
#include "parser/instruction.hpp"

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

class AsmSection {

    private:
        std::string __name;

        std::vector<AsmInstruction*> __instructions;

        std::vector<AsmLabel*> __labels;

    public:
        /*! Constructor
         */
        AsmSection(const std::string& name): __name(name) {}

        /*! Set instruction label
         *
         *  \param name the instruction label string
         */
        void set_name(const std::string& name)
        {
            __name = name;
        }

        /*! Get the instruction name
         *
         *  \return a string name
         */
        std::string get_name()
        {
            return __name;
        }

        /*! Add a new instruction to section
         *
         *  \param instruction the new instruction to add
         */
        void add_instruction(AsmInstruction* instruction)
        {
            __instructions.push_back(instruction);
        }

        /*! Get instructions list
         *
         *  \return a vector of AsmInstruction
         */
        std::vector<AsmInstruction*> get_instructions()
        {
            return __instructions;
        }

        /*! Add a new label to section
         *
         *  \param label the new label to add
         */
        void add_label(AsmLabel* label)
        {
            __labels.push_back(label);
        }

        /*! Get labels list
         *
         *  \return a vector of AsmLabel
         */
        std::vector<AsmLabel*> get_labels()
        {
            return __labels;
        }
        
         /*! search label by name
         *
         *  \param  NameLabel
         *  \return Label 
         */
         
        AsmLabel * find_label(std::string NameLabel)
        {
           for (auto lab:__labels)
           {
            if (lab->get_name() == NameLabel) return lab;
           }
           return NULL;
        }
};

#endif // __ASMX__SECTION__
