# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE( Boost REQUIRED serialization)

SET(DisCODe_LIBRARIES
    ${DisCODe_LIBRARIES}
    ${Boost_SERIALIZATION_LIBRARY}
)

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

# Create an executable file from sources:
ADD_LIBRARY(DcDiceReading SHARED ${files})
TARGET_LINK_LIBRARIES(DcDiceReading ${DisCODe_LIBRARIES})

INSTALL_COMPONENT(DcDiceReading)
