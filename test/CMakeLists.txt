include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/test/)
include_directories(${FF_INCLUDE_DIR})
link_directories(${FF_LIB_DIR})

file(GLOB sub_folders ./*)
foreach(folder ${sub_folders})
  if(IS_DIRECTORY ${folder})
    if(EXISTS ${folder}/CMakeLists.txt)
      add_subdirectory(${folder})
    endif()
  endif()
endforeach()
