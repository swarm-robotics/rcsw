################################################################################
# External Projects                                                            #
################################################################################

################################################################################
# Submodules                                                                   #
################################################################################
set(${target}_CHECK_LANGUAGE "C")
set(${target}_HAS_RECURSIVE_DIRS YES)

# Must be first in list to get linking dependencies right
if (WITH_TESTS)
  list(APPEND ${target}_SUBDIRS tests)
endif()

list(APPEND ${target}_SUBDIRS tests)
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
  # The include directory for common tests bits needs to be added to
  # each target
  target_include_directories(${target}-${d} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/tests/include)

  target_include_directories(${target}-${d} PUBLIC "${${target}_INC_PATH}")
  target_include_directories(${target}-${d} SYSTEM PUBLIC ext)
endforeach()

################################################################################
# Includes                                                                     #
################################################################################
set(${target}_INCLUDE_DIRS "${${target}_INC_PATH}")

################################################################################
# Libraries                                                                    #
################################################################################

set(${target}_LIBS
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
endif()


################################################################################
# Exports                                                                      #
################################################################################
if (NOT IS_ROOT_PROJECT)
  set(${target}_INCLUDE_DIRS "${${target}_INCLUDE_DIRS}" PARENT_SCOPE)
  set(${target}_LIBS "${${target}_LIBS}" PARENT_SCOPE)
endif()
