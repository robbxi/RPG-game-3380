#include "Helper.h"

namespace Helper {
  Texture2D loadTexture(std::string filePath) {
    std::string fullFilePath = "./assets/" + filePath;
    return LoadTexture(fullFilePath.c_str());
  }

  std::string parseGameObjectType(const std::string& input) {
    // Find the position of the '-' character
    size_t dashPos = input.find('-');

    // Check if the dash character was found
    if (dashPos != std::string::npos) {
      // Extract the prefix (substring before the '-')
      std::string prefix = input.substr(0, dashPos);
      return prefix;
    }
    else {
      // If no dash was found, return the original string
      return input;
    }
  }

  void parseString(const std::string& input, int& intValue, std::string& stringValue) {
    // Find the position of the hyphen
    size_t hyphenPos = input.find('-');

    if (hyphenPos != std::string::npos) {
      // Split the string into two parts
      std::string intPart = input.substr(0, hyphenPos);
      std::string strPart = input.substr(hyphenPos + 1);

      // Convert the integer part to an integer
      std::istringstream(intPart) >> intValue;

      // Assign the string part
      stringValue = strPart;
    }
    else {
      // Handle the case where there's no hyphen
      std::cerr << "Input does not contain a hyphen: " << input << std::endl;
      intValue = 0;  // Default value for integer
      stringValue = ""; // Default value for string
    }
  }

  void parseCoordinate(const std::string& input, int& firstInt, int& secondInt) {
    // Find the position of the hyphen
    size_t hyphenPos = input.find('-');

    if (hyphenPos != std::string::npos) {
      // Split the string into two parts
      std::string firstPart = input.substr(0, hyphenPos);
      std::string secondPart = input.substr(hyphenPos + 1);

      // Convert the parts to integers
      std::istringstream(firstPart) >> firstInt;
      std::istringstream(secondPart) >> secondInt;
    }
    else {
      // Handle the case where there's no hyphen
      std::cerr << "Input does not contain a hyphen: " << input << std::endl;
      firstInt = 0;   // Default value for the first integer
      secondInt = 0;  // Default value for the second integer
    }
  }
}
