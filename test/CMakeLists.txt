add_subdirectory(c++)

if(PYTHON_SDK)

add_subdirectory(python)

elseif(CSHARP_SDK)

add_subdirectory(csharp)

endif()