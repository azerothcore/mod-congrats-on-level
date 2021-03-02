CU_SET_PATH("CMAKE_MOD_CONGRATSONLEVEL_DIR" "${CMAKE_CURRENT_LIST_DIR}")

AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/mod_congratsonlevel.cpp")

AC_ADD_SCRIPT_LOADER("CongratsOnLevel" "${CMAKE_CURRENT_LIST_DIR}/src/loader_congratsonlevel.h")

AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/mod_congratsonlevel.conf.dist")
