#pragma once
typedef signed char        i8;
typedef short              i16;
typedef int                i32;
typedef long long          i64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef long long          imax;
typedef unsigned long long umax;

typedef u32 b32;

#define ERROR_NONE 0x00000000
#define ERROR_UNKNOWN 0xffffffff
#define ERROR_NULLPTR 0xfffffffe
#define ERROR_OUT_OF_BOUNDS 0xfffffffd
#define ERROR_INVALID_ARGUMENT 0xfffffffc
#define ERROR_INVALID_OPERATION 0xfffffffb
#define ERROR_INVALID_STATE 0xfffffffa
#define ERROR_INVALID_TYPE 0xfffffff9
#define ERROR_INVALID_VALUE 0xfffffff8
#define ERROR_INVALID_SIZE 0xfffffff7
#define ERROR_INVALID_FORMAT 0xfffffff6
#define ERROR_INVALID_NAME 0xfffffff5
#define ERROR_INVALID_PATH 0xfffffff4
#define ERROR_INVALID_FILE 0xfffffff3
#define ERROR_INVALID_DIRECTORY 0xfffffff2
#define ERROR_INVALID_HANDLE 0xfffffff1
#define ERROR_MEMORY_ALLOCATION_FAILED 0xfffffff0
#define ERROR_MEMORY_ACCESS_VIOLATION  0xffffffef
#define ERROR_RESOURCE_NOT_FOUND       0xffffffee
#define ERROR_RESOURCE_ALREADY_EXISTS  0xffffffed
#define ERROR_RESOURCE_LOAD_FAILED     0xffffffec
#define ERROR_SHADER_COMPILATION_FAILED 0xffffffeb
#define ERROR_SHADER_LINK_FAILED       0xffffffea
#define ERROR_TEXTURE_CREATION_FAILED  0xffffffe9
#define ERROR_BUFFER_CREATION_FAILED   0xffffffe8
#define ERROR_MESH_CREATION_FAILED     0xffffffe7
#define ERROR_AUDIO_INITIALIZATION_FAILED 0xffffffe6
#define ERROR_AUDIO_DEVICE_NOT_FOUND   0xffffffe5
#define ERROR_NETWORK_DISCONNECTED     0xffffffe4
#define ERROR_NETWORK_TIMEOUT          0xffffffe3
#define ERROR_THREAD_CREATION_FAILED   0xffffffe2
#define ERROR_MUTEX_LOCK_FAILED        0xffffffe1
#define ERROR_MUTEX_UNLOCK_FAILED      0xffffffe0
#define ERROR_FILE_READ_FAILED         0xffffffdf
#define ERROR_FILE_WRITE_FAILED        0xffffffde
#define ERROR_FILE_PERMISSION_DENIED   0xffffffdd
#define ERROR_UNSUPPORTED_OPERATION    0xffffffdc
#define ERROR_NOT_IMPLEMENTED          0xffffffdb
#define ERROR_GRAPHICS_API_UNSUPPORTED 0xffffffda
#define ERROR_GPU_INITIALIZATION_FAILED 0xffffffd9
#define ERROR_PIPELINE_CREATION_FAILED 0xffffffd8
#define ERROR_WINDOW_CREATION_FAILED   0xffffffd7
#define ERROR_CONTEXT_CREATION_FAILED  0xffffffd6
#define ERROR_EVENT_REGISTRATION_FAILED 0xffffffd5
#define ERROR_CONFIG_PARSING_FAILED    0xffffffd4
#define ERROR_DATA_CORRUPTION_DETECTED 0xffffffd3
#define ERROR_WINDOW_CREATION_FAILED     0xffffffd7
#define ERROR_WINDOW_ALREADY_EXISTS      0xffffffd6
#define ERROR_WINDOW_NOT_FOUND           0xffffffd5
#define ERROR_WINDOW_RESIZE_FAILED       0xffffffd4
#define ERROR_WINDOW_FULLSCREEN_FAILED   0xffffffd3
#define ERROR_WINDOW_MINIMIZE_FAILED     0xffffffd2
#define ERROR_WINDOW_MAXIMIZE_FAILED     0xffffffd1
#define ERROR_WINDOW_CLOSE_FAILED        0xffffffd0
#define ERROR_WINDOW_CONTEXT_LOST        0xffffffcf
#define ERROR_WINDOW_INPUT_INITIALIZATION_FAILED 0xffffffce
#define ERROR_WINDOW_INPUT_UNSUPPORTED   0xffffffcd
#define ERROR_WINDOW_TITLE_SET_FAILED    0xffffffcc
#define ERROR_WINDOW_POSITION_SET_FAILED 0xffffffcb
#define ERROR_WINDOW_ICON_SET_FAILED     0xffffffca
#define ERROR_WINDOW_CURSOR_CREATION_FAILED 0xffffffc9
#define ERROR_WINDOW_CURSOR_SET_FAILED   0xffffffc8
#define ERROR_WINDOW_BUFFER_SWAP_FAILED  0xffffffc7
#define ERROR_WINDOW_VSYNC_FAILED        0xffffffc6
#define ERROR_WINDOW_RENDER_CONTEXT_FAILED 0xffffffc5
#define ERROR_WINDOW_STYLE_UNSUPPORTED   0xffffffc4
#define ERROR_WINDOW_MONITOR_NOT_FOUND   0xffffffc3
#define ERROR_WINDOW_EVENT_POLL_FAILED   0xffffffc2
