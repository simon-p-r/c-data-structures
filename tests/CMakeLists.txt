# cds tests
set(cds_inc_folder ${CMAKE_SOURCE_DIR}/include)


macro(add_cds_test NAME)
    add_executable(${NAME} ${NAME}.c)
    target_link_libraries(${NAME} cds)
    add_test(NAME ${NAME} COMMAND ${NAME})
endmacro(add_cds_test)


add_cds_test(test-dlist)
add_cds_test(test-list)
add_cds_test(test-map)
add_cds_test(test-vec)



