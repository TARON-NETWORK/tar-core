set(tar_genesis_tool_sources
  tar_genesis_tool.cpp)

monero_add_executable(tar_genesis_tool
  ${tar_genesis_tool_sources})
target_link_libraries(tar_genesis_tool
  PRIVATE
    cryptonote_basic
    common
    epee
    version
    ${Boost_FILESYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${EXTRA_LIBRARIES})
add_dependencies(tar_genesis_tool
  version)
install(TARGETS tar_genesis_tool DESTINATION bin)
