#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include <raylib.h>
#include <sstream>

namespace Helper {
  Texture2D loadTexture(std::string filePath);
  void parseString(const std::string& input, int& intValue, std::string& stringValue);
  void parseCoordinate(const std::string& input, int& firstInt, int& secondInt);
  std::string parseGameObjectType(const std::string& input);
}
