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

/* --------------------------------------------------------------------------
 *  Class
 * -------------------------------------------------------------------------- */

class AsmInstruction {

    private:
        std::string __name;

        std::vector<std::string> __parameters;

    public:
        /*! Constructor
         *
         *  \param name the instruction label
         */
        AsmInstruction(const std::string& name): __name(name)
        {}

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

        /*! Add a new parameter to instruction
         *
         *  \param parameter the new parameter to add
         */
        void add_parameter(const std::string& parameter)
        {
            __parameters.push_back(parameter);
        }

        /*! Remove a specific parameter
         *
         *  \param parameter the parameter to remove from parameters
         */
        void remove_parameter(const std::string& parameter)
        {
            std::vector<std::string>::iterator iter = std::find(
                __parameters.begin(), __parameters.end(), parameter);

            if(iter != __parameters.end()) {
                __parameters.erase(iter);
            }
        }

        /*! Get the instruction parameters
         *
         *  \return a vector of string
         */
        std::vector<std::string> get_parameters()
        {
            return __parameters;
        }
};

class AsmSection {

    private:
        std::string __name;

        std::vector<AsmInstruction*> __instructions;

    public:
        /*! Constructor
         */
        AsmSection(const std::string& name): __name(name)
        {}

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
};

class AsmParser : public File
{
    private:
        std::string __name;

        std::vector<std::string> __modules;

        std::vector<AsmSection*> __sections;

        /*! Parse the file and store all the keywords for futher management
         *
         *  \note This function replace comma in the line with a space
         */
        void __parser()
        {
            int current_section_index = -1;

            // Read buffer content and parse data
            for(std::string buffer_line : get_buffer()) {

                // Check semicolon for comments lines
                std::size_t semicolon = reduce(buffer_line).find_first_of(';');

                // Avoid to read commented line
                if(semicolon > 0) {

                    // Check colon for labels and conditions
                    std::size_t colon = reduce(buffer_line).find_first_of(':');
                    std::size_t space = reduce(buffer_line).find_first_of(' ');

                    // A label has been spotted
                    if(colon != std::string::npos and space == std::string::npos) {
                        std::cout << buffer_line << std::endl;
                    }

                    // No label here, sorry
                    else {

                        // Avoid to have a comma between two words whitout space
                        std::replace(
                            buffer_line.begin(), buffer_line.end(), ',', ' ');

                        // Detect a semicolon in the line
                        if(semicolon != std::string::npos)
                            buffer_line = buffer_line.substr(0, semicolon);

                        // Split elements in line
                        std::vector<std::string> line = split(buffer_line);

                        // Avoid to manipulate empty lines
                        if(line.size() > 0) {

                            // Store program name
                            if(line[0] == "global") {
                                __name = line[1];
                            }

                            // Store modules
                            else if(line[0] == "extern") {
                                __modules.push_back(line[1]);
                            }

                            // Store sections data
                            else if(line[0] == "section") {
                                // Remove the dot at the beggining of the string
                                std::string label = line[1].substr(
                                    1, line[1].length());

                                __sections.push_back(new AsmSection(label));

                                // Get current section position in storage
                                current_section_index = __sections.size() - 1;
                            }

                            // Instructions
                            else if(line.size() > 0) {
                                std::vector<std::string> parameters;

                                AsmInstruction* instruction = new AsmInstruction(
                                    line[0]);

                                // Store parameters
                                if(line.size() > 1) {
                                    for(unsigned int i = 1; i < line.size(); ++i)
                                        instruction->add_parameter(line[i]);
                                }

                                // Store instruction with parameters in data
                                __sections[current_section_index]->add_instruction(
                                    instruction);
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

        /*! Get program sections
         *
         *  \return a vector of AsmSection
         */
        std::vector<AsmSection*> get_sections()
        {
            return __sections;
        }
};

#endif // __ASMX__PARSER__
