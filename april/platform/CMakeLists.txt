
set(PLATFORM_HEADER 
     platform/PlatformConfig.h
)

if(MACOSX)
        set(APRIL_PLATFORM_SPECIFIC_HEADER 
          platform/Mac/GL-Mac.h
        )
        
endif()

set(PLATFORM_SRC
 ${APRIL_PLATFORM_SPECIFIC_HEADER}
)

