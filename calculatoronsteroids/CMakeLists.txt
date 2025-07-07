add_executable(calculatoronsteroids src/main.cpp)# Add your Source Files here
target_link_libraries(calculatoronsteroids PRIVATE Boost::multiprecision)
target_include_directories(calculatoronsteroids PRIVATE ${BARKEEP_INCLUDE_DIRS})
