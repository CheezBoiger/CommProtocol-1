# Tools config files, which are added into a set for compilation
include_directories(SYSTEM libxbee3/)
set(NETWORK_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CommProto/include/CommProto/network/)
set(NETWORK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CommProto/src/network/)


set(NETWORK_HEADERS
  ${NETWORK_HEADER_DIR}udp.h
  ${NETWORK_HEADER_DIR}serial.h
  ${NETWORK_HEADER_DIR}/seriallink.h
  ${NETWORK_HEADER_DIR}/commxbee.h
  ${NETWORK_HEADER_DIR}/xbeelink.h
  ${NETWORK_HEADER_DIR}/udplink.h
  ${NETWORK_HEADER_DIR}commsocket.h
  ${NETWORK_HEADER_DIR}commslink.h
  ${NETWORK_HEADER_DIR}crc32.h
  ${NETWORK_HEADER_DIR}parser.h)
  #${NETWORK_HEADER_DIR}znodetable.h)

set(NETWORK_GRAPH_HEADERS
  ${NETWORK_HEADER_DIR}/network_graph/network_edge.h
  ${NETWORK_HEADER_DIR}/network_graph/network_graph.h
  ${NETWORK_HEADER_DIR}/network_graph/network_graph_builder.h
  ${NETWORK_HEADER_DIR}/network_graph/network_node.h)
	

set(NETWORK_SOURCES
  ${NETWORK_SOURCE_DIR}udp.cpp
  ${NETWORK_SOURCE_DIR}serial.cpp
  ${NETWORK_SOURCE_DIR}/seriallink.cc
  ${NETWORK_SOURCE_DIR}/commxbee.cc
  ${NETWORK_SOURCE_DIR}/xbeelink.cc
  ${NETWORK_SOURCE_DIR}/udplink.cc
  # ${NETWORK_SOURCE_DIR}/znodetable.cc
  ${NETWORK_SOURCE_DIR}tcpsocket.cpp
  ${NETWORK_SOURCE_DIR}crc32.cpp
  ${NETWORK_SOURCE_DIR}parser.cpp)


set (NGCP_GLOB
  ${NGCP_GLOB}
  ${NETWORK_GRAPH_HEADERS}
  ${NETWORK_HEADERS}
  ${NETWORK_SOURCES})