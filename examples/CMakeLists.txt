# This file lists all examples as optional build targets

option(example_playground "Example DISP playground" ON)

if(${example_playground})
    add_subdirectory(playground)
endif()