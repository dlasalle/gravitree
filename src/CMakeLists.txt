include_directories(.)
file(GLOB sources *.cpp)

# libraries
add_library(gravitree ${GRAVITREE_LIBRARY_TYPE} 
  ${sources}
) 

if (NOT WIN32)
  # windows does not have a /lib equivalent
  install(TARGETS gravitree
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
endif()

if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  add_subdirectory("test")
endif()
