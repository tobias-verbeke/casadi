# TRY TO FIND THE INCLUDE DIRECTORY
FIND_PROGRAM(OCTAVE_EXECUTABLE octave
PATHS "C:/Octave/*/bin"
)

FILE(GLOB OCTAVE_INCLUDE_PATHS "/usr/include/octave-*/")


FIND_PATH(OCTAVE_INCLUDE_DIR octave/oct.h
HINTS ${OCTAVE_INCLUDE_PATH} ${OCTAVE_INCLUDE_PATHS}
)

IF(OCTAVE_EXECUTABLE AND OCTAVE_INCLUDE_DIR)
  SET(OCTAVE_FOUND TRUE)
ELSE(OCTAVE_EXECUTABLE AND OCTAVE_INCLUDE_DIR)
  SET(OCTAVE_FOUND FALSE)
ENDIF(OCTAVE_EXECUTABLE AND OCTAVE_INCLUDE_DIR)
