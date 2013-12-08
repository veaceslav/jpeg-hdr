##########################################################
#
#	Sample OpenCL
#	Threshold image processing sample
#	Lupescu Grigore @2012
#
##########################################################

cmake_minimum_required (VERSION 2.6)
project (IMGCL)

###################################
# OpenCL env setup
###################################

#Linux
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	SET (EXTRA_LIBS ${EXTRA_LIBS} OpenCL)
	SET (EXTRA_LIBS ${EXTRA_LIBS} jpeg)
	SET (EXTRA_LIBS ${EXTRA_LIBS} m)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/AMDAPP/include -L/opt/AMDAPP/lib/x86_64/ -g")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#Windows support
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	INCLUDE_DIRECTORIES("C:\\Program Files\ (x86)\\Intel\\OpenCL\ SDK\\2.0\\include")
	LINK_DIRECTORIES("C:\\Program Files\ (x86)\\Intel\\OpenCL\ SDK\\2.0\\lib\\x86")
	SET (EXTRA_LIBS ${EXTRA_LIBS} OpenCL.lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

###################################
# BUILD ALL
###################################

add_executable(imgcl main.c openclwrap.c jpegapi.c hdr.c)
target_link_libraries(imgcl ${EXTRA_LIBS})






