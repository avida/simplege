README.md

To make debug version:
    cmake .. -G "MinGW Makefiles"   -DCMAKE_BUILD_TYPE=Debug
-----------------------------------------------------------------
Tips to build assimp:

To compile assimp with mingw go to the AssimpPCH.h and insert following lines:
 #define strcasecmp _stricmp
 #define strncasecmp(x,y,z) _strnicmp(x,y,z)
This should fix  '::strcasecmp' has not been declared and '::strncasecmp' has not been declared 
error messages.
To get rid of DirectX SDK dependencie remove/rename tools and test directories.

To exclude unwanted formats add such lines into CMakeLists.txt:
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_X_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_MD3_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_MDL_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_MD2_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_PLY_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_ASE_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_OBJ_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_HMP_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_SMD_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_MDC_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_MD5_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_STL_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_LWO_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_DXF_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_NFF_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_RAW_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_OFF_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_AC_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_BVH_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_IRRMESH_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_IRR_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_Q3D_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_B3D_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_COLLADA_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_TERRAGEN_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_CSM_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_3D_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_LWS_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_OGRE_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_MS3D_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_COB_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_BLEND_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_Q3BSP_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_NDO_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_IFC_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_M3_IMPORTER)
ADD_DEFINITIONS(-DASSIMP_BUILD_NO_XGL_IMPORTER)


