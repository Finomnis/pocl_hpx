#=============================================================================
#   CMake build system files
#
#   Copyright (c) 2014 pocl developers
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in
#   all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#   THE SOFTWARE.
#
#=============================================================================


include_directories(BEFORE "../../fix-include/OpenCL")
include_directories(AFTER "devices" ".")

add_subdirectory("devices")

set(POCL_LIB_SOURCES  "clCreateContextFromType.c"
                   "clReleaseContext.c"
                   "clRetainContext.c"
                   "clGetContextInfo.c"
                   "clCreateCommandQueue.c"
                   "clReleaseCommandQueue.c"
                   "clRetainCommandQueue.c"
                   "clGetCommandQueueInfo.c"
                   "clCreateBuffer.c"
                   "clCreateSubBuffer.c"
                   "clEnqueueFillImage.c"
                   "clEnqueueReadBuffer.c"
                   "clEnqueueReadBufferRect.c"
                   "clEnqueueMapBuffer.c"  "clEnqueueMapBuffer.h"
                   "clEnqueueUnmapMemObject.c"
                   "clEnqueueMarkerWithWaitList.c"
                   "clReleaseMemObject.c"
                   "clRetainMemObject.c"
                   "clGetMemObjectInfo.c"
                   "clSetMemObjectDestructorCallback.c"
                   "clCreateProgramWithSource.c"
                   "clCreateProgramWithBinary.c"
                   "clReleaseProgram.c"
                   "clRetainProgram.c"
                   "clBuildProgram.c"
                   "clCreateKernel.c"
                   "clReleaseKernel.c"
                   "clRetainKernel.c"
                   "clSetKernelArg.c"
                   "clEnqueueNDRangeKernel.c"
                   "clEnqueueNativeKernel.c"
                   "clCreateKernelsInProgram.c"
                   "clGetKernelInfo.c"
                   "clGetKernelArgInfo.c"
                   "clGetPlatformIDs.c"
                   "clGetPlatformInfo.c"
                   "clGetDeviceIDs.c"
                   "clGetDeviceInfo.c"
                   "clCreateContext.c"
                   "clGetProgramBuildInfo.c"
                   "clEnqueueWriteBuffer.c"
                   "clEnqueueWriteBufferRect.c"
                   "clEnqueueCopyBuffer.c"
                   "clEnqueueCopyBufferRect.c"
                   "clEnqueueCopyBufferToImage.c"
                   "clEnqueueCopyImageToBuffer.c"
                   "clFinish.c"
                   "clFlush.c"
                   "clEnqueueBarrier.c"
                   "clEnqueueMarker.c"
                   "clGetKernelWorkGroupInfo.c"
                   "clGetProgramInfo.c"
                   "clGetEventProfilingInfo.c"
                   "clWaitForEvents.c"
                   "clEnqueueWaitForEvents.c"
                   "clReleaseEvent.c"
                   "clRetainEvent.c"
                   "clSetEventCallback.c"
                   "clGetEventInfo.c"
                   "clCreateUserEvent.c"
                   "clSetUserEventStatus.c"
                   "clEnqueueTask.c"
                   "clCreateImage.c"
                   "clCreateImage2D.c"
                   "clCreateImage3D.c"
                   "clEnqueueReadImage.c"
                   "clEnqueueWriteImage.c"
                   "clCreateSampler.c"
                   "clReleaseSampler.c"
                   "clRetainSampler.c"
                   "clGetSamplerInfo.c"
                   "clEnqueueCopyImage.c"
                   "clEnqueueMapImage.c"
                   "clGetImageInfo.c"
                   "clCreateFromGLTexture2D.c"
                   "clCreateFromGLTexture3D.c"
                   "clUnloadCompiler.c"
                   "clGetSupportedImageFormats.c"
                   "clGetExtensionFunctionAddress.c"
                   "clIcdGetPlatformIDsKHR.c"
                   "clReleaseDevice.c"
                   "clRetainDevice.c"
                   "clCreateSubDevices.c"
                   "pocl_cl.h" "pocl_util.h" "pocl_util.c"
                   "pocl_image_util.c" "pocl_image_util.h"
                   "pocl_icd.h" "pocl_llvm.h"
                   "pocl_runtime_config.c" "pocl_runtime_config.h"
                   "pocl_mem_management.c"  "pocl_mem_management.h"
                   "pocl_llvm_api.cc" "pocl_hash.c")

set(LIBPOCL_OBJS "$<TARGET_OBJECTS:llvmpasses>;$<TARGET_OBJECTS:libpocl_unlinked_objs>;${POCL_DEVICES_OBJS}")

add_compile_options(${OCL_ICD_CFLAGS})

# set llvm C++ flags on pocl_llvm_api.cc
set_source_files_properties("pocl_llvm_api.cc" PROPERTIES COMPILE_FLAGS "${LLVM_CXXFLAGS} -I\"${CMAKE_CURRENT_SOURCE_DIR}/../llvmopencl\"")

if(MSVC)
  set_source_files_properties( ${POCL_LIB_SOURCES} PROPERTIES LANGUAGE CXX )
endif(MSVC)

# this is so that we don't compile twice when building both libpocl and libOpenCL
add_library("libpocl_unlinked_objs" OBJECT ${POCL_LIB_SOURCES})

#################################################################

if (MSVC)
  set(POCL_PUBLIC_LINK_LIST ${Hwloc_LIBRARIES} ${Pthreads_LIBRARIES} ${POCL_DEVICES_LINK_LIST})
else()
  set(POCL_PUBLIC_LINK_LIST ${Hwloc_LIBRARIES} "${LTDL_LIB}" ${CMAKE_THREAD_LIBS_INIT} ${POCL_DEVICES_LINK_LIST})
endif()

set(POCL_PRIVATE_LINK_LIST ${CLANG_LIB_NAMES} ${POCL_LLVM_LIBS} ${LLVM_SYSLIBS})

#################################################################


add_library("pocl" ${LIBPOCL_OBJS} )

set_target_properties("pocl" PROPERTIES SOVERSION "${LIB_API_VERSION}" 
  VERSION "${LIB_BUILD_VERSION}" 
  LINK_FLAGS "${LLVM_LDFLAGS} ${ICD_LD_FLAGS}")
target_link_libraries("pocl" PUBLIC ${POCL_PUBLIC_LINK_LIST} PRIVATE ${POCL_PRIVATE_LINK_LIST} )
install(TARGETS "pocl"
        LIBRARY DESTINATION ${POCL_INSTALL_PUBLIC_LIBDIR}
        ARCHIVE DESTINATION ${POCL_INSTALL_PUBLIC_LIBDIR}/static)


if(DIRECT_LINKAGE)
  add_library("OpenCL" ${LIBPOCL_OBJS})
  set_target_properties("OpenCL" PROPERTIES SOVERSION "${LIB_API_VERSION}" VERSION "${LIB_BUILD_VERSION}" LINK_FLAGS "${LLVM_LDFLAGS} ${ICD_LD_FLAGS}")
  target_link_libraries("OpenCL" PUBLIC ${POCL_PUBLIC_LINK_LIST} PRIVATE ${POCL_PRIVATE_LINK_LIST} )
  if(NOT ENABLE_ICD)
    install(TARGETS "OpenCL"
          LIBRARY DESTINATION ${POCL_INSTALL_PUBLIC_LIBDIR}
          ARCHIVE DESTINATION ${POCL_INSTALL_PUBLIC_LIBDIR}/static)
  endif()
endif()


