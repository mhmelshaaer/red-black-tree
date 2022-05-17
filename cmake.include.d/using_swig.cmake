FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

if(python)
    FIND_PACKAGE(PythonLibs)
endif()


include(UseSWIG)

SET(CMAKE_SWIG_FLAGS "")

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

SET_SOURCE_FILES_PROPERTIES(${target_interface} PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(${target_interface} PROPERTIES SWIG_FLAGS "-includeall")

SWIG_ADD_LIBRARY(${target} TYPE SHARED
    LANGUAGE ${module_lang}
    SOURCES ${target_source}
    OUTPUT_DIR ${swig_output_dir}
    OUTFILE_DIR ${swig_outfile_dir}
)
