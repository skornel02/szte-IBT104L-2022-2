cmake_minimum_required (VERSION 3.8)

project ("kasszas-projekt" C)

add_subdirectory ("Billentyu")
add_subdirectory ("Nyomtato")
add_subdirectory ("Kaszas")

cmake_policy(SET CMP0079 NEW)
target_link_libraries(Kaszas Billentyu)
target_link_libraries(Kaszas Nyomtato)