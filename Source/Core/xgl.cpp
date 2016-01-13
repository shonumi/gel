/****** XGL ******/
/****** Parse XGL Data From File ******/

#include "xgl.h"

/****** Parse XGL file into vector of strings ******/
bool parse_xgl_string(std::string filename, std::vector <std::string>& contents)
{
	std::ifstream file(filename.c_str(), std::ios::in); 
	std::string input_line = "";
	std::string line_char = "";

	/* Clear Vector */
	contents.clear();

	if(!file.is_open()) { return false; }

	/* Cycle through whole file, line-by-line */
	while(getline(file, input_line))
	{
		line_char = input_line[0];	
	
		/* Check if line starts with [ - if not, skip line */
		if(line_char == "[")
		{
			std::string line_item = "";

			/* Cycle through line, character-by-character */
			for(int x = 0; ++x < input_line.length();)
			{
				line_char = input_line[x];

				/* Check the character for item limiter : or ] - Push to Vector */
				if((line_char == ":") || (line_char == "]")) { contents.push_back(line_item); line_item = ""; }

				else { line_item += line_char; }
			}
		}
	}
	
	file.close();
	return true;
}

/****** Parse XGL file into vector of ints ******/
bool parse_xgl_int(std::string filename, std::vector <int>& contents)
{
	std::ifstream file(filename.c_str(), std::ios::in); 
	std::string input_line = "";
	std::string line_char = "";
	int output = 0;

	/* Clear Vector */
	contents.clear();

	if(!file.is_open()) { return false; }

	/* Cycle through whole file, line-by-line */
	while(getline(file, input_line))
	{
		line_char = input_line[0];	
	
		/* Check if line starts with [ - if not, skip line */
		if(line_char == "[")
		{
			std::string line_item = "";

			/* Cycle through line, character-by-character */
			for(int x = 0; ++x < input_line.length();)
			{
				line_char = input_line[x];

				/* Check the character for item limiter : or ] - Push to Vector */
				if((line_char == ":") || (line_char == "]")) 
				{
					/* Convert string to int before pushing it to the vector */
					output = 0;
					std::stringstream temp_stream(line_item);
					temp_stream >> output;
					contents.push_back(output); 
					line_item = ""; 
				}

				else { line_item += line_char; }
			}
		}
	}
	
	file.close();
	return true;
}

/****** Convert string into double ******/
double numparse(std::string input)
{
	double output = 0;
	std::stringstream temp_stream(input);
	temp_stream >> output;
	return output;
}	