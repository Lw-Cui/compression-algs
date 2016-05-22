FIND_PATH(COMPRESSION_ALGS_INCLUDE_DIR NAMES compression-algs.hpp)
FIND_LIBRARY(COMPRESSION_ALGS_LIBRARY NAMES compression-algs)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(COMPRESSION_ALGS REQUIRED_VARS 
	COMPRESSION_ALGS_LIBRARY COMPRESSION_ALGS_INCLUDE_DIR)

IF(COMPRESSION_ALGS_FOUND)
    SET(COMPRESSION_ALGS_LIBRARIES ${COMPRESSION_ALGS_LIBRARY})
    SET(COMPRESSION_ALGS_INCLUDE_DIRS ${COMPRESSION_ALGS_INCLUDE_DIR})
ENDIF()