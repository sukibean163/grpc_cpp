project(grpc_cpp)

add_compile_options(-std=c++11)
add_compile_options(-pthread)




# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)
# find_package(OpenCV REQUIRED)

set(PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/helloworld.proto
)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})

include_directories(
    ${PROTO_SRC_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../${PROJECT_NAME}/include    
    ${CMAKE_CURRENT_LIST_DIR}/../darknet/include  
    )

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

# yolo_plugin
file(GLOB_RECURSE SOURCE_FILES src/yolo.cpp)

# add_library(yolo_plugin

#     ${SOURCE_FILES}
# )

file(GLOB_RECURSE HEADER_FILES include/*.h)
foreach(type server client)
    file(GLOB_RECURSE ${type}_FILES ${type}/*.cc)
    add_executable(${PROJECT_NAME}_${type}
        ${${type}_FILES}
        ${PROTO_SRCS}
        ${GRPC_SRCS}
        ${HEADER_FILES}
    )


    target_link_libraries(${PROJECT_NAME}_${type}
        ${PROTOBUF_LIBRARIES} 

        # yolo_plugin
        # darknet
        gRPC::grpc++_reflection
        protobuf::libprotobuf

        # ${OpenCV_LIBS}
        pthread
    )

    install(TARGETS ${PROJECT_NAME}_${type}
            DESTINATION lib
            )
endforeach()



# # Building server
# add_executable(greeter_server
#     ${CMAKE_CURRENT_SOURCE_DIR}/greeter_server.cc
#     ${PROTO_SRCS}
#     ${GRPC_SRCS}
# )
# target_link_libraries(greeter_server
#     gRPC::grpc++_reflection
#     protobuf::libprotobuf
# )

# # Building client
# add_executable(greeter_client
#     ${CMAKE_CURRENT_SOURCE_DIR}/greeter_client.cc
#     ${PROTO_SRCS}
#     ${GRPC_SRCS}
# )
# target_link_libraries(greeter_client
#     gRPC::grpc++_reflection
#     protobuf::libprotobuf
# )
