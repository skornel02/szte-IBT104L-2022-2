cmake_minimum_required (VERSION 3.8)

project ("kasszas-projekt" C)

include(CTest)

add_subdirectory ("Common")
add_subdirectory ("Billentyu")
add_subdirectory ("Nyomtato")
add_subdirectory ("Kaszas")

cmake_policy(SET CMP0079 NEW)
target_link_libraries(Billentyu Common)
target_link_libraries(Nyomtato Common)
target_link_libraries(Kaszas Common Billentyu Nyomtato)

add_executable(CUnitRunner utest.c)
target_link_libraries(CUnitRunner cunit Common Billentyu Nyomtato)
add_test(NAME CUnitRunner
        COMMAND CUnitRunner)
