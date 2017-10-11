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

/*! \file parser.hpp
 *
 *  \author BroFreedom <jdoe1337@gmx.fr>
 *  \version 1.0
 *  \date october 2017
 */

#ifndef __ASMX__PARSER__
#define __ASMX__PARSER__

/* --------------------------------------------------------------------------
 *  Modules
 * -------------------------------------------------------------------------- */

#include "file/file.hpp"

#include "parser/utils.hpp"
#include "parser/label.hpp"
#include "parser/macro.hpp"
#include "parser/section.hpp"
#include "parser/instruction.hpp"

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

class AsmParser : public File
{
    private:
        std::string __name;

        std::vector<std::string> __modules;

        std::vector<AsmMacro*> __macros;

        std::vector<AsmSection*> __sections;

        /*! Parse the file and store all the keywords for futher management
         *
         *  \note This function replace comma in the line with a space
         */
        void __parser()
        {
            bool macro_block = false;

            /* ---------------------------------------
             *  Read buffer content
             * --------------------------------------- */

            for(std::string buffer_line : get_buffer()) {

                // Check semicolon for comments lines
                std::size_t semicolon = reduce(buffer_line).find_first_of(';');
                // Check percent for macro lines
                std::size_t percent = reduce(buffer_line).find_first_of('%');

                /* ---------------------------------------
                 *  Only read uncommented lines
                 * --------------------------------------- */

                if(reduce(buffer_line).length() > 0 and semicolon > 0) {
                    // Reduce buffer_line
                    buffer_line = reduce(buffer_line);

                    // Detect a semicolon in the line
                    if(semicolon != std::string::npos)
                        buffer_line = reduce(buffer_line.substr(0, semicolon));

                    // Check colon for labels and conditions
                    std::size_t colon = buffer_line.find_first_of(':');
                    std::size_t space = buffer_line.find_first_of(' ');

                    /* ---------------------------------------
                     *  Detect a colon character
                     * --------------------------------------- */

                    if(colon != std::string::npos and space == std::string::npos) {
                        AsmLabel* label = new AsmLabel(
                            buffer_line.substr(0, colon));

                        if(!macro_block) {
                            AsmSection* section = get_last_section();
                            label->set_position(section->get_instructions().size());

                            section->add_label(label);
                        }
                        else {
                            AsmSection* section = get_last_macro()->get_last_section();
                            label->set_position(section->get_instructions().size());

                            section->add_label(label);
                        }
                    }

                    /* ---------------------------------------
                     *  Detect a percent character
                     * --------------------------------------- */

                    else if(percent != std::string::npos) {

                        // Split elements in line
                        std::vector<std::string> line = split(buffer_line);

                        if(line[0] == "%macro") {
                            macro_block = true;

                            if(line.size() > 1) {
                                __macros.push_back(new AsmMacro(line[1]));
                            }
                        }

                        if(line[0] == "%endmacro") {
                            macro_block = false;
                        }
                    }

                    /* ---------------------------------------
                     *  Normal line
                     * --------------------------------------- */

                    else {

                        // Avoid to have a comma between two words whitout space
                        std::replace(
                            buffer_line.begin(), buffer_line.end(), ',', ' ');

                        // Split elements in line
                        std::vector<std::string> line = split(buffer_line);

                        /* ---------------------------------------
                         *  Avoid to manipulate empty lines
                         * --------------------------------------- */

                        if(line.size() > 0) {

                            // Transform first keyword to lowercase
                            std::transform(
                                line[0].begin(), line[0].end(),
                                line[0].begin(), ::tolower);

                            /* ---------------------------------------
                             *  Global
                             * --------------------------------------- */

                            if(line[0] == "global") {
                                __name = line[1];
                            }

                            /* ---------------------------------------
                             *  Extern
                             * --------------------------------------- */

                            else if(line[0] == "extern") {
                                __modules.push_back(line[1]);
                            }

                            /* ---------------------------------------
                             *  Section
                             * --------------------------------------- */

                            else if(line[0] == "section") {
                                // Remove the dot at the beggining of the string
                                std::string label = line[1].substr(
                                    1, line[1].length());

                                if(!macro_block) {
                                    __sections.push_back(
                                        new AsmSection(label));
                                }
                                else {
                                    get_last_macro()->add_section(
                                        new AsmSection(label));
                                }
                            }

                            /* ---------------------------------------
                             *  Instruction
                             * --------------------------------------- */

                            else if(line.size() > 0) {
                                std::vector<std::string> parameters;

                                // Remove last colon in variable name
                                if(colon != std::string::npos)
                                    line[0] = line[0].substr(0, colon);

                                AsmInstruction* instruction = new AsmInstruction(
                                    line[0]);

                                // Store parameters
                                if(line.size() > 1) {
                                    for(unsigned int i = 1; i < line.size(); ++i)
                                        instruction->add_parameter(line[i]);
                                }

                                // Store instruction with parameters in data
                                if(!macro_block) {
                                    AsmSection* section = get_last_section();

                                    if(section != nullptr)
                                        section->add_instruction(instruction);
                                }
                                else {
                                    AsmSection* section = get_last_macro()->get_last_section();

                                    if(section != nullptr)
                                        section->add_instruction(instruction);
                                }
                            }
                        }
                    }
                }
            }
        }

    public:
        /*! Constructor
         *
         *  \param path the file path on filesystem
         */
        AsmParser(const std::string& path) : File(path)
        {
            // Fill buffer with file content
            read();

            // Parse file content
            __parser();
        }

        /*! Get program name
         *
         *  \return a string
         */
        std::string get_name()
        {
            return __name;
        }

        /*! Get program modules
         *
         *  \return a vector of modules string
         */
        std::vector<std::string> get_modules()
        {
            return __modules;
        }

        /*! Get program macros
         *
         *  \return a vector of AsmMacro
         */
        std::vector<AsmMacro*> get_macros()
        {
            return __macros;
        }

        /*! Get last macro
         *
         *  \return an AsmMacro or nullptr
         */
        AsmMacro* get_last_macro()
        {
            if(__macros.size() > 0)
                return __macros[__macros.size() - 1];

            return nullptr;
        }

        /*! Get program sections
         *
         *  \return a vector of AsmSection
         */
        std::vector<AsmSection*> get_sections()
        {
            return __sections;
        }

        /*! Get last section
         *
         *  \return an AsmSection or nullptr
         */
        AsmSection* get_last_section()
        {
            if(__sections.size() > 0)
                return __sections[__sections.size() - 1];

            return nullptr;
        }
};

#endif // __ASMX__PARSER__
