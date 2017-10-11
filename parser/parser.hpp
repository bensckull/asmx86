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

class AsmLabel
{
    private:
        std::string __name;

        unsigned int __position;

    public:
        /*! Constructor
         *
         *  \param name the label name
         */
        AsmLabel(const std::string& name): __name(name) {}

        /*! Constructor
         *
         *  \param name the label name
         *  \param position the label position
         */
        AsmLabel(const std::string& name, const unsigned int & position):
            __name(name), __position(position) {}

        /*! Set label
         *
         *  \param name the label string
         */
        void set_name(const std::string& name)
        {
            __name = name;
        }

        /*! Get the name
         *
         *  \return a string name
         */
        std::string get_name()
        {
            return __name;
        }

        /*! Set the label position in section
         *
         *  \param position the new position in section
         */
        void set_position(const unsigned int & position)
        {
            __position = position;
        }

        /*! Get the label position in section
         *
         *  \return the position as integer
         */
        int get_position()
        {
            return __position;
        }

};

class AsmInstruction {

    private:
        std::string __name;

        std::vector<std::string> __parameters;

    public:
        /*! Constructor
         *
         *  \param name the instruction label
         */
        AsmInstruction(const std::string& name): __name(name) {}

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
};

class AsmMacro
{
    private:
        std::string __name;

        std::vector<std::string> __parameters;

        std::vector<AsmSection*> __sections;

    public:
        /*! Constructor
         *
         *  \param name the macro name
         */
        AsmMacro(const std::string& name): __name(name) {}

        /*! Get macro name
         *
         *  \return a string
         */
        std::string get_name()
        {
            return __name;
        }

        /*! Get macro parameters
         *
         *  \return a vector of modules string
         */
        std::vector<std::string> get_parameters()
        {
            return __parameters;
        }

        /*! Get macro sections
         *
         *  \return a vector of AsmSection
         */
        std::vector<AsmSection*> get_sections()
        {
            return __sections;
        }

        /*! Add a new macro section
         *
         *  \param section the new section
         */
        void add_section(AsmSection* section)
        {
            __sections.push_back(section);
        }

        /*! Get last macro section
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
