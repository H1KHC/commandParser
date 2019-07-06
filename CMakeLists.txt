PROJECT(CommandParser)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FILE(GLOB CommandParserCWrapper_SOURCES "./*.cpp")
FILE(GLOB test_c_SOURCE "example/*.c")
FILE(GLOB test_cpp_SOURCE "example/*.cpp")

ADD_LIBRARY(CommandParserCWrapper STATIC ${CommandParserCWrapper_SOURCES})

ADD_EXECUTABLE(test_cpp ${test_cpp_SOURCE})

ADD_EXECUTABLE(test_c ${test_c_SOURCE})
TARGET_LINK_LIBRARIES(test_c CommandParserCWrapper)
