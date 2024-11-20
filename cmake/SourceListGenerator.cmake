include(${ROOT_DIR}/cmake/TargetAndFolderAssoc.cmake)

foreach(pair IN ZIP_LISTS __TARGETS_LIST __DIRECTORIES_LIST)
  # Execute find and get list of source files
  execute_process(
    COMMAND find ${pair_1} -type f -name "*.cpp"
    OUTPUT_VARIABLE ENUMERATED_SRC
  )
  
  ##string(REGEX MATCHALL "[^a-zA-Z]\n[^a-zA-Z]$" SOURCES_${pair_0} ${ENUMERATED_SRC})
  #string(REGEX REPLACE "\n" ";" SOURCES_${pair_0} "${ENUMERATED_SRC}")
  set(SOURCES_${pair_0} ${ENUMERATED_SRC})
  string(REPLACE "\n" ";" SOURCES_${pair_0} ${ENUMERATED_SRC})
  list(LENGTH SOURCES_${pair_0} CNT_${pair_0})
  message(STATUS "Found ${CNT_${pair_0}} source files for target ${pair_0}")
endforeach()
