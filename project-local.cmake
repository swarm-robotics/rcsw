################################################################################
# Configuration Options                                                        #
################################################################################
set(${target}_CHECK_LANGUAGE "C")
set(${target}_HAS_RECURSIVE_DIRS YES)

################################################################################
# Includes                                                                     #
################################################################################
set(${target}_INCLUDE_DIRS "${${target}_INC_PATH}" ${rcppsw_INCLUDE_DIRS})

################################################################################
# Submodules                                                                   #
################################################################################

# Must be first in list to get linking dependencies right
if (WITH_TESTS)
  add_subdirectory(tests)
endif()

list(APPEND ${target}_SUBDIRS adapter)
list(APPEND ${target}_SUBDIRS algorithm)
list(APPEND ${target}_SUBDIRS common)
list(APPEND ${target}_SUBDIRS ds)
list(APPEND ${target}_SUBDIRS multithread)
list(APPEND ${target}_SUBDIRS pulse)
list(APPEND ${target}_SUBDIRS stdio)
list(APPEND ${target}_SUBDIRS utils)

if (WITH_MPI)
  list(APPEND ${target}_SUBDIRS multiprocess)
endif()

foreach(d ${${target}_SUBDIRS})
  add_subdirectory(src/${d})
  target_include_directories(${target}-${d} PUBLIC ${${target}_INCLUDE_DIRS})
  target_include_directories(${target}-${d} SYSTEM PRIVATE ext)
endforeach()


################################################################################
# Libraries                                                                    #
################################################################################
set(${target}_LIBRARIES
  )

if (NOT TARGET ${target})
  add_library(${target} STATIC
    $<TARGET_OBJECTS:${target}-adapter>
    $<TARGET_OBJECTS:${target}-algorithm>
    $<TARGET_OBJECTS:${target}-common>
    $<TARGET_OBJECTS:${target}-ds>
    $<TARGET_OBJECTS:${target}-multithread>
    $<TARGET_OBJECTS:${target}-pulse>
    $<TARGET_OBJECTS:${target}-stdio>
    $<TARGET_OBJECTS:${target}-utils>)
  target_link_libraries(${target} ${${target}_LIBRARIES})
endif()


################################################################################
# Exports                                                                      #
################################################################################
if (NOT IS_ROOT_PROJECT)
  set(${target}_INCLUDE_DIRS "${${target}_INCLUDE_DIRS}" PARENT_SCOPE)
  set(${target}_LIBRARIES "${${target}_LIBRARIES}" PARENT_SCOPE)
  set(${target}_LIBRARY_DIRS "${${target}_LIBRARY_DIRS}" PARENT_SCOPE)
endif()
