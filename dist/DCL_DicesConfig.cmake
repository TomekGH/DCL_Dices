# This file is used when other components needs to use something provided by this DCL. 
# Provide any include paths and lib directories. Use /home/tpokorsk/Pulpit/DCL/DCL_Dices/dist
# to point to 'dist' directory of current DCL, it'll be substituted during installation. 

# directory containing header files
SET(DCL_Dices_INCLUDE_DIR /home/tpokorsk/Pulpit/DCL/DCL_Dices/dist/include)
INCLUDE_DIRECTORIES(${DCL_Dices_INCLUDE_DIR})

# directory containing libraries
SET(DCL_Dices_LIB_DIR /home/tpokorsk/Pulpit/DCL/DCL_Dices/dist/lib)
LINK_DIRECTORIES(${DCL_Dices_LIB_DIR})

# list of libraries to link against when using features of DCL_Dices
# add all additional libraries built by this dcl (NOT components)
# SET(DCL_Dices_LIBS lib_1 lib_2)
# SET(ADDITIONAL_LIB_DIRS /home/tpokorsk/Pulpit/DCL/DCL_Dices/dist/lib ${ADDITIONAL_LIB_DIRS})
