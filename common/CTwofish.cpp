#include "CTwofish.h"
#include "UMemory.h"

// KDXServer.exe: 00485aa7
static const byte Q[2][256] = {
    {0xd8, 0x00, 0x01, 0x17, 0x02, 0x2e, 0x18, 0x53, 0x03, 0x6a, 0x2f, 0x93, 0x19, 0x34, 0x54,
     0x45, 0x04, 0x5c, 0x6b, 0xb6, 0x30, 0xa6, 0x94, 0x4b, 0x1a, 0x8c, 0x35, 0x81, 0x55, 0xaa,
     0x46, 0x0d, 0x05, 0x24, 0x5d, 0x87, 0x6c, 0x9b, 0xb7, 0xc1, 0x31, 0x2b, 0xa7, 0xa3, 0x95,
     0x98, 0x4c, 0xca, 0x1b, 0xe6, 0x8d, 0x73, 0x36, 0xcd, 0x82, 0x12, 0x56, 0x62, 0xab, 0xf0,
     0x47, 0x4f, 0x0e, 0xbd, 0x06, 0xd4, 0x25, 0xd2, 0x5e, 0x27, 0x88, 0x66, 0x6d, 0xd6, 0x9c,
     0x79, 0xb8, 0x08, 0xc2, 0xdf, 0x32, 0x68, 0x2c, 0xfd, 0xa8, 0x8a, 0xa4, 0x5a, 0x96, 0x29,
     0x99, 0x22, 0x4d, 0x60, 0xcb, 0xe4, 0x1c, 0x7b, 0xe7, 0x3b, 0x8e, 0x9e, 0x74, 0xf4, 0x37,
     0xd8, 0xce, 0xf9, 0x83, 0x6f, 0x13, 0xb2, 0x57, 0xe1, 0x63, 0xdc, 0xac, 0xc4, 0xf1, 0xaf,
     0x48, 0x0a, 0x50, 0x42, 0x0f, 0xba, 0xbe, 0xc7, 0x07, 0xde, 0xd5, 0x78, 0x26, 0x65, 0xd3,
     0xd1, 0x5f, 0xe3, 0x28, 0x21, 0x89, 0x59, 0x67, 0xfc, 0x6e, 0xb1, 0xd7, 0xf8, 0x9d, 0xf3,
     0x7a, 0x3a, 0xb9, 0xc6, 0x09, 0x41, 0xc3, 0xae, 0xe0, 0xdb, 0x33, 0x44, 0x69, 0x92, 0x2d,
     0x52, 0xfe, 0x16, 0xa9, 0x0c, 0x8b, 0x80, 0xa5, 0x4a, 0x5b, 0xb5, 0x97, 0xc9, 0x2a, 0xa2,
     0x9a, 0xc0, 0x23, 0x86, 0x4e, 0xbc, 0x61, 0xef, 0xcc, 0x11, 0xe5, 0x72, 0x1d, 0x3d, 0x7c,
     0xeb, 0xe8, 0xe9, 0x3c, 0xea, 0x8f, 0x7d, 0x9f, 0xec, 0x75, 0x1e, 0xf5, 0x3e, 0x38, 0xf6,
     0xd9, 0x3f, 0xcf, 0x76, 0xfa, 0x1f, 0x84, 0xa0, 0x70, 0xed, 0x14, 0x90, 0xb3, 0x7e, 0x58,
     0xfb, 0xe2, 0x20, 0x64, 0xd0, 0xdd, 0x77, 0xad, 0xda, 0xc5, 0x40, 0xf2, 0x39, 0xb0, 0xf7,
     0x49, 0xb4, 0x0b, 0x7f, 0x51, 0x15, 0x43, 0x91, 0x10, 0x71, 0xbb, 0xee, 0xbf, 0x85, 0xc8,
     0xa1},
    {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x4d, 0x9a, 0x79, 0xf2, 0xa9, 0x1f, 0x3e,
     0x7c, 0xf8, 0xbd, 0x37, 0x6e, 0xdc, 0xf5, 0xa7, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0,
     0xcd, 0xd7, 0xe3, 0x8b, 0x5b, 0xb6, 0x21, 0x42, 0x84, 0x45, 0x8a, 0x59, 0xb2, 0x29, 0x52,
     0xa4, 0x05, 0x0a, 0x14, 0x28, 0x50, 0xa0, 0x0d, 0x1a, 0x34, 0x68, 0xd0, 0xed, 0x97, 0x63,
     0xc6, 0xc1, 0xcf, 0xd3, 0xeb, 0x9b, 0x7b, 0xf6, 0xa1, 0x0f, 0x1e, 0x3c, 0x78, 0xf0, 0xad,
     0x17, 0x2e, 0x5c, 0xb8, 0x3d, 0x7a, 0xf4, 0xa5, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0x8d,
     0x57, 0xae, 0x11, 0x22, 0x44, 0x88, 0x5d, 0xba, 0x39, 0x72, 0xe4, 0x85, 0x47, 0x8e, 0x51,
     0xa2, 0x09, 0x12, 0x24, 0x48, 0x90, 0x6d, 0xda, 0xf9, 0xbf, 0x33, 0x66, 0xcc, 0xd5, 0xe7,
     0x83, 0x4b, 0x96, 0x61, 0xc2, 0xc9, 0xdf, 0xf3, 0xab, 0x1b, 0x36, 0x6c, 0xd8, 0xfd, 0xb7,
     0x23, 0x46, 0x8c, 0x55, 0xaa, 0x19, 0x32, 0x64, 0xc8, 0xdd, 0xf7, 0xa3, 0x0b, 0x16, 0x2c,
     0x58, 0xb0, 0x2d, 0x5a, 0xb4, 0x25, 0x4a, 0x94, 0x65, 0xca, 0xd9, 0xff, 0xb3, 0x2b, 0x56,
     0xac, 0x15, 0x2a, 0x54, 0xa8, 0x1d, 0x3a, 0x74, 0xe8, 0x9d, 0x77, 0xee, 0x91, 0x6f, 0xde,
     0xf1, 0xaf, 0x13, 0x26, 0x4c, 0x98, 0x7d, 0xfa, 0xb9, 0x3f, 0x7e, 0xfc, 0xb5, 0x27, 0x4e,
     0x9c, 0x75, 0xea, 0x99, 0x7f, 0xfe, 0xb1, 0x2f, 0x5e, 0xbc, 0x35, 0x6a, 0xd4, 0xe5, 0x87,
     0x43, 0x86, 0x41, 0x82, 0x49, 0x92, 0x69, 0xd2, 0xe9, 0x9f, 0x73, 0xe6, 0x81, 0x4f, 0x9e,
     0x71, 0xe2, 0x89, 0x5f, 0xbe, 0x31, 0x62, 0xc4, 0xc5, 0xc7, 0xc3, 0xcb, 0xdb, 0xfb, 0xbb,
     0x3b, 0x76, 0xec, 0x95, 0x67, 0xce, 0xd1, 0xef, 0x93, 0x6b, 0xd6, 0xe1, 0x8f, 0x53, 0xa6,
     0x01},
};

// KDXServer.exe: 00485d93
static const byte P[512] = {
    0xa9, 0x75, 0x67, 0xf3, 0xb3, 0xc6, 0xe8, 0xf4, 0x04, 0xdb, 0xfd, 0x7b, 0xa3, 0xfb, 0x76, 0xc8,
    0x9a, 0x4a, 0x92, 0xd3, 0x80, 0xe6, 0x78, 0x6b, 0xe4, 0x45, 0xdd, 0x7d, 0xd1, 0xe8, 0x38, 0x4b,
    0x0d, 0xd6, 0xc6, 0x32, 0x35, 0xd8, 0x98, 0xfd, 0x18, 0x37, 0xf7, 0x71, 0xec, 0xf1, 0x6c, 0xe1,
    0x43, 0x30, 0x75, 0x0f, 0x37, 0xf8, 0x26, 0x1b, 0xfa, 0x87, 0x13, 0xfa, 0x94, 0x06, 0x48, 0x3f,
    0xf2, 0x5e, 0xd0, 0xba, 0x8b, 0xae, 0x30, 0x5b, 0x84, 0x8a, 0x54, 0x00, 0xdf, 0xbc, 0x23, 0x9d,
    0x19, 0x6d, 0x5b, 0xc1, 0x3d, 0xb1, 0x59, 0x0e, 0xf3, 0x80, 0xae, 0x5d, 0xa2, 0xd2, 0x82, 0xd5,
    0x63, 0xa0, 0x01, 0x84, 0x83, 0x07, 0x2e, 0x14, 0xd9, 0xb5, 0x51, 0x90, 0x9b, 0x2c, 0x7c, 0xa3,
    0xa6, 0xb2, 0xeb, 0x73, 0xa5, 0x4c, 0xbe, 0x54, 0x16, 0x92, 0x0c, 0x74, 0xe3, 0x36, 0x61, 0x51,
    0xc0, 0x38, 0x8c, 0xb0, 0x3a, 0xbd, 0xf5, 0x5a, 0x73, 0xfc, 0x2c, 0x60, 0x25, 0x62, 0x0b, 0x96,
    0xbb, 0x6c, 0x4e, 0x42, 0x89, 0xf7, 0x6b, 0x10, 0x53, 0x7c, 0x6a, 0x28, 0xb4, 0x27, 0xf1, 0x8c,
    0xe1, 0x13, 0xe6, 0x95, 0xbd, 0x9c, 0x45, 0xc7, 0xe2, 0x24, 0xf4, 0x46, 0xb6, 0x3b, 0x66, 0x70,
    0xcc, 0xca, 0x95, 0xe3, 0x03, 0x85, 0x56, 0xcb, 0xd4, 0x11, 0x1c, 0xd0, 0x1e, 0x93, 0xd7, 0xb8,
    0xfb, 0xa6, 0xc3, 0x83, 0x8e, 0x20, 0xb5, 0xff, 0xe9, 0x9f, 0xcf, 0x77, 0xbf, 0xc3, 0xba, 0xcc,
    0xea, 0x03, 0x77, 0x6f, 0x39, 0x08, 0xaf, 0xbf, 0x33, 0x40, 0xc9, 0xe7, 0x62, 0x2b, 0x71, 0xe2,
    0x81, 0x79, 0x79, 0x0c, 0x09, 0xaa, 0xad, 0x82, 0x24, 0x41, 0xcd, 0x3a, 0xf9, 0xea, 0xd8, 0xb9,
    0xe5, 0xe4, 0xc5, 0x9a, 0xb9, 0xa4, 0x4d, 0x97, 0x44, 0x7e, 0x08, 0xda, 0x86, 0x7a, 0xe7, 0x17,
    0xa1, 0x66, 0x1d, 0x94, 0xaa, 0xa1, 0xed, 0x1d, 0x06, 0x3d, 0x70, 0xf0, 0xb2, 0xde, 0xd2, 0xb3,
    0x41, 0x0b, 0x7b, 0x72, 0xa0, 0xa7, 0x11, 0x1c, 0x31, 0xef, 0xc2, 0xd1, 0x27, 0x53, 0x90, 0x3e,
    0x20, 0x8f, 0xf6, 0x33, 0x60, 0x26, 0xff, 0x5f, 0x96, 0xec, 0x5c, 0x76, 0xb1, 0x2a, 0xab, 0x49,
    0x9e, 0x81, 0x9c, 0x88, 0x52, 0xee, 0x1b, 0x21, 0x5f, 0xc4, 0x93, 0x1a, 0x0a, 0xeb, 0xef, 0xd9,
    0x91, 0xc5, 0x85, 0x39, 0x49, 0x99, 0xee, 0xcd, 0x2d, 0xad, 0x4f, 0x31, 0x8f, 0x8b, 0x3b, 0x01,
    0x47, 0x18, 0x87, 0x23, 0x6d, 0xdd, 0x46, 0x1f, 0xd6, 0x4e, 0x3e, 0x2d, 0x69, 0xf9, 0x64, 0x48,
    0x2a, 0x4f, 0xce, 0xf2, 0xcb, 0x65, 0x2f, 0x8e, 0xfc, 0x78, 0x97, 0x5c, 0x05, 0x58, 0x7a, 0x19,
    0xac, 0x8d, 0x7f, 0xe5, 0xd5, 0x98, 0x1a, 0x57, 0x4b, 0x67, 0x0e, 0x7f, 0xa7, 0x05, 0x5a, 0x64,
    0x28, 0xaf, 0x14, 0x63, 0x3f, 0xb6, 0x29, 0xfe, 0x88, 0xf5, 0x3c, 0xb7, 0x4c, 0x3c, 0x02, 0xa5,
    0xb8, 0xce, 0xda, 0xe9, 0xb0, 0x68, 0x17, 0x44, 0x55, 0xe0, 0x1f, 0x4d, 0x8a, 0x43, 0x7d, 0x69,
    0x57, 0x29, 0xc7, 0x2e, 0x8d, 0xac, 0x74, 0x15, 0xb7, 0x59, 0xc4, 0xa8, 0x9f, 0x0a, 0x72, 0x9e,
    0x7e, 0x6e, 0x15, 0x47, 0x22, 0xdf, 0x12, 0x34, 0x58, 0x35, 0x07, 0x6a, 0x99, 0xcf, 0x34, 0xdc,
    0x6e, 0x22, 0x50, 0xc9, 0xde, 0xc0, 0x68, 0x9b, 0x65, 0x89, 0xbc, 0xd4, 0xdb, 0xed, 0xf8, 0xab,
    0xc8, 0x12, 0xa8, 0xa2, 0x2b, 0x0d, 0x40, 0x52, 0xdc, 0xbb, 0xfe, 0x02, 0x32, 0x2f, 0xa4, 0xa9,
    0xca, 0xd7, 0x10, 0x61, 0x21, 0x1e, 0xf0, 0xb4, 0xd3, 0x50, 0x5d, 0x04, 0x0f, 0xf6, 0x00, 0xc2,
    0x6f, 0x16, 0x9d, 0x25, 0x36, 0x86, 0x42, 0x56, 0x4a, 0x55, 0x5e, 0x09, 0xc1, 0xbe, 0xe0, 0x91};

// KDXServer.exe: 004848a8
static const byte MDS[2][256] = {
    {0xa9, 0x67, 0xb3, 0xe8, 0x04, 0xfd, 0xa3, 0x76, 0x9a, 0x92, 0x80, 0x78, 0xe4, 0xdd, 0xd1,
     0x38, 0x0d, 0xc6, 0x35, 0x98, 0x18, 0xf7, 0xec, 0x6c, 0x43, 0x75, 0x37, 0x26, 0xfa, 0x13,
     0x94, 0x48, 0xf2, 0xd0, 0x8b, 0x30, 0x84, 0x54, 0xdf, 0x23, 0x19, 0x5b, 0x3d, 0x59, 0xf3,
     0xae, 0xa2, 0x82, 0x63, 0x01, 0x83, 0x2e, 0xd9, 0x51, 0x9b, 0x7c, 0xa6, 0xeb, 0xa5, 0xbe,
     0x16, 0x0c, 0xe3, 0x61, 0xc0, 0x8c, 0x3a, 0xf5, 0x73, 0x2c, 0x25, 0x0b, 0xbb, 0x4e, 0x89,
     0x6b, 0x53, 0x6a, 0xb4, 0xf1, 0xe1, 0xe6, 0xbd, 0x45, 0xe2, 0xf4, 0xb6, 0x66, 0xcc, 0x95,
     0x03, 0x56, 0xd4, 0x1c, 0x1e, 0xd7, 0xfb, 0xc3, 0x8e, 0xb5, 0xe9, 0xcf, 0xbf, 0xba, 0xea,
     0x77, 0x39, 0xaf, 0x33, 0xc9, 0x62, 0x71, 0x81, 0x79, 0x09, 0xad, 0x24, 0xcd, 0xf9, 0xd8,
     0xe5, 0xc5, 0xb9, 0x4d, 0x44, 0x08, 0x86, 0xe7, 0xa1, 0x1d, 0xaa, 0xed, 0x06, 0x70, 0xb2,
     0xd2, 0x41, 0x7b, 0xa0, 0x11, 0x31, 0xc2, 0x27, 0x90, 0x20, 0xf6, 0x60, 0xff, 0x96, 0x5c,
     0xb1, 0xab, 0x9e, 0x9c, 0x52, 0x1b, 0x5f, 0x93, 0x0a, 0xef, 0x91, 0x85, 0x49, 0xee, 0x2d,
     0x4f, 0x8f, 0x3b, 0x47, 0x87, 0x6d, 0x46, 0xd6, 0x3e, 0x69, 0x64, 0x2a, 0xce, 0xcb, 0x2f,
     0xfc, 0x97, 0x05, 0x7a, 0xac, 0x7f, 0xd5, 0x1a, 0x4b, 0x0e, 0xa7, 0x5a, 0x28, 0x14, 0x3f,
     0x29, 0x88, 0x3c, 0x4c, 0x02, 0xb8, 0xda, 0xb0, 0x17, 0x55, 0x1f, 0x8a, 0x7d, 0x57, 0xc7,
     0x8d, 0x74, 0xb7, 0xc4, 0x9f, 0x72, 0x7e, 0x15, 0x22, 0x12, 0x58, 0x07, 0x99, 0x34, 0x6e,
     0x50, 0xde, 0x68, 0x65, 0xbc, 0xdb, 0xf8, 0xc8, 0xa8, 0x2b, 0x40, 0xdc, 0xfe, 0x32, 0xa4,
     0xca, 0x10, 0x21, 0xf0, 0xd3, 0x5d, 0x0f, 0x00, 0x6f, 0x9d, 0x36, 0x42, 0x4a, 0x5e, 0xc1,
     0xe0},
    {0x75, 0xf3, 0xc6, 0xf4, 0xdb, 0x7b, 0xfb, 0xc8, 0x4a, 0xd3, 0xe6, 0x6b, 0x45, 0x7d, 0xe8,
     0x4b, 0xd6, 0x32, 0xd8, 0xfd, 0x37, 0x71, 0xf1, 0xe1, 0x30, 0x0f, 0xf8, 0x1b, 0x87, 0xfa,
     0x06, 0x3f, 0x5e, 0xba, 0xae, 0x5b, 0x8a, 0x00, 0xbc, 0x9d, 0x6d, 0xc1, 0xb1, 0x0e, 0x80,
     0x5d, 0xd2, 0xd5, 0xa0, 0x84, 0x07, 0x14, 0xb5, 0x90, 0x2c, 0xa3, 0xb2, 0x73, 0x4c, 0x54,
     0x92, 0x74, 0x36, 0x51, 0x38, 0xb0, 0xbd, 0x5a, 0xfc, 0x60, 0x62, 0x96, 0x6c, 0x42, 0xf7,
     0x10, 0x7c, 0x28, 0x27, 0x8c, 0x13, 0x95, 0x9c, 0xc7, 0x24, 0x46, 0x3b, 0x70, 0xca, 0xe3,
     0x85, 0xcb, 0x11, 0xd0, 0x93, 0xb8, 0xa6, 0x83, 0x20, 0xff, 0x9f, 0x77, 0xc3, 0xcc, 0x03,
     0x6f, 0x08, 0xbf, 0x40, 0xe7, 0x2b, 0xe2, 0x79, 0x0c, 0xaa, 0x82, 0x41, 0x3a, 0xea, 0xb9,
     0xe4, 0x9a, 0xa4, 0x97, 0x7e, 0xda, 0x7a, 0x17, 0x66, 0x94, 0xa1, 0x1d, 0x3d, 0xf0, 0xde,
     0xb3, 0x0b, 0x72, 0xa7, 0x1c, 0xef, 0xd1, 0x53, 0x3e, 0x8f, 0x33, 0x26, 0x5f, 0xec, 0x76,
     0x2a, 0x49, 0x81, 0x88, 0xee, 0x21, 0xc4, 0x1a, 0xeb, 0xd9, 0xc5, 0x39, 0x99, 0xcd, 0xad,
     0x31, 0x8b, 0x01, 0x18, 0x23, 0xdd, 0x1f, 0x4e, 0x2d, 0xf9, 0x48, 0x4f, 0xf2, 0x65, 0x8e,
     0x78, 0x5c, 0x58, 0x19, 0x8d, 0xe5, 0x98, 0x57, 0x67, 0x7f, 0x05, 0x64, 0xaf, 0x63, 0xb6,
     0xfe, 0xf5, 0xb7, 0x3c, 0xa5, 0xce, 0xe9, 0x68, 0x44, 0xe0, 0x4d, 0x43, 0x69, 0x29, 0x2e,
     0xac, 0x15, 0x59, 0xa8, 0x0a, 0x9e, 0x6e, 0x47, 0xdf, 0x34, 0x35, 0x6a, 0xcf, 0xdc, 0x22,
     0xc9, 0xc0, 0x9b, 0x89, 0xd4, 0xed, 0xab, 0x12, 0xa2, 0x0d, 0x52, 0xbb, 0x02, 0x2f, 0xa9,
     0xd7, 0x61, 0x1e, 0xb4, 0x50, 0x04, 0xf6, 0xc2, 0x16, 0x25, 0x86, 0x56, 0x55, 0x09, 0xbe,
     0x91},
};

// KDXServer.exe: 00484aa8
static const uint MDS_GF_FB[256] = {
    0xBCBC3275, 0xECEC21F3, 0x202043C6, 0xB3B3C9F4, 0xDADA03DB, 0x02028B7B, 0xE2E22BFB, 0x9E9EFAC8,
    0xC9C9EC4A, 0xD4D409D3, 0x18186BE6, 0x1E1E9F6B, 0x98980E45, 0xB2B2387D, 0xA6A6D2E8, 0x2626B74B,
    0x3C3C57D6, 0x93938A32, 0x8282EED8, 0x525298FD, 0x7B7BD437, 0xBBBB3771, 0x5B5B97F1, 0x474783E1,
    0x24243C30, 0x5151E20F, 0xBABAC6F8, 0x4A4AF31B, 0xBFBF4887, 0x0D0D70FA, 0xB0B0B306, 0x7575DE3F,
    0xD2D2FD5E, 0x7D7D20BA, 0x666631AE, 0x3A3AA35B, 0x59591C8A, 0x00000000, 0xCDCD93BC, 0x1A1AE09D,
    0xAEAE2C6D, 0x7F7FABC1, 0x2B2BC7B1, 0xBEBEB90E, 0xE0E0A080, 0x8A8A105D, 0x3B3B52D2, 0x6464BAD5,
    0xD8D888A0, 0xE7E7A584, 0x5F5FE807, 0x1B1B1114, 0x2C2CC2B5, 0xFCFCB490, 0x3131272C, 0x808065A3,
    0x73732AB2, 0x0C0C8173, 0x79795F4C, 0x6B6B4154, 0x4B4B0292, 0x53536974, 0x94948F36, 0x83831F51,
    0x2A2A3638, 0xC4C49CB0, 0x2222C8BD, 0xD5D5F85A, 0xBDBDC3FC, 0x48487860, 0xFFFFCE62, 0x4C4C0796,
    0x4141776C, 0xC7C7E642, 0xEBEB24F7, 0x1C1C1410, 0x5D5D637C, 0x36362228, 0x6767C027, 0xE9E9AF8C,
    0x4444F913, 0x1414EA95, 0xF5F5BB9C, 0xCFCF18C7, 0x3F3F2D24, 0xC0C0E346, 0x7272DB3B, 0x54546C70,
    0x29294CCA, 0xF0F035E3, 0x0808FE85, 0xC6C617CB, 0xF3F34F11, 0x8C8CE4D0, 0xA4A45993, 0xCACA96B8,
    0x68683BA6, 0xB8B84D83, 0x38382820, 0xE5E52EFF, 0xADAD569F, 0x0B0B8477, 0xC8C81DC3, 0x9999FFCC,
    0x5858ED03, 0x19199A6F, 0x0E0E0A08, 0x95957EBF, 0x70705040, 0xF7F730E7, 0x6E6ECF2B, 0x1F1F6EE2,
    0xB5B53D79, 0x09090F0C, 0x616134AA, 0x57571682, 0x9F9F0B41, 0x9D9D803A, 0x111164EA, 0x2525CDB9,
    0xAFAFDDE4, 0x4545089A, 0xDFDF8DA4, 0xA3A35C97, 0xEAEAD57E, 0x353558DA, 0xEDEDD07A, 0x4343FC17,
    0xF8F8CB66, 0xFBFBB194, 0x3737D3A1, 0xFAFA401D, 0xC2C2683D, 0xB4B4CCF0, 0x32325DDE, 0x9C9C71B3,
    0x5656E70B, 0xE3E3DA72, 0x878760A7, 0x15151B1C, 0xF9F93AEF, 0x6363BFD1, 0x3434A953, 0x9A9A853E,
    0xB1B1428F, 0x7C7CD133, 0x88889B26, 0x3D3DA65F, 0xA1A1D7EC, 0xE4E4DF76, 0x8181942A, 0x91910149,
    0x0F0FFB81, 0xEEEEAA88, 0x161661EE, 0xD7D77321, 0x9797F5C4, 0xA5A5A81A, 0xFEFE3FEB, 0x6D6DB5D9,
    0x7878AEC5, 0xC5C56D39, 0x1D1DE599, 0x7676A4CD, 0x3E3EDCAD, 0xCBCB6731, 0xB6B6478B, 0xEFEF5B01,
    0x12121E18, 0x6060C523, 0x6A6AB0DD, 0x4D4DF61F, 0xCECEE94E, 0xDEDE7C2D, 0x55559DF9, 0x7E7E5A48,
    0x2121B24F, 0x03037AF2, 0xA0A02665, 0x5E5E198E, 0x5A5A6678, 0x65654B5C, 0x62624E58, 0xFDFD4519,
    0x0606F48D, 0x404086E5, 0xF2F2BE98, 0x3333AC57, 0x17179067, 0x05058E7F, 0xE8E85E05, 0x4F4F7D64,
    0x89896AAF, 0x10109563, 0x74742FB6, 0x0A0A75FE, 0x5C5C92F5, 0x9B9B74B7, 0x2D2D333C, 0x3030D6A5,
    0x2E2E49CE, 0x494989E9, 0x46467268, 0x77775544, 0xA8A8D8E0, 0x9696044D, 0x2828BD43, 0xA9A92969,
    0xD9D97929, 0x8686912E, 0xD1D187AC, 0xF4F44A15, 0x8D8D1559, 0xD6D682A8, 0xB9B9BC0A, 0x42420D9E,
    0xF6F6C16E, 0x2F2FB847, 0xDDDD06DF, 0x23233934, 0xCCCC6235, 0xF1F1C46A, 0xC1C112CF, 0x8585EBDC,
    0x8F8F9E22, 0x7171A1C9, 0x9090F0C0, 0xAAAA539B, 0x0101F189, 0x8B8BE1D4, 0x4E4E8CED, 0x8E8E6FAB,
    0xABABA212, 0x6F6F3EA2, 0xE6E6540D, 0xDBDBF252, 0x92927BBB, 0xB7B7B602, 0x6969CA2F, 0x3939D9A9,
    0xD3D30CD7, 0xA7A72361, 0xA2A2AD1E, 0xC3C399B4, 0x6C6C4450, 0x07070504, 0x04047FF6, 0x272746C2,
    0xACACA716, 0xD0D07625, 0x50501386, 0xDCDCF756, 0x84841A55, 0xE1E15109, 0x7A7A25BE, 0x1313EF91};

// KDXServer.exe: 00484ea8
static const uint MDS_GF_FD[256] = {
    0xA9D93939, 0x67901717, 0xB3719C9C, 0xE8D2A6A6, 0x04050707, 0xFD985252, 0xA3658080, 0x76DFE4E4,
    0x9A084545, 0x92024B4B, 0x80A0E0E0, 0x78665A5A, 0xE4DDAFAF, 0xDDB06A6A, 0xD1BF6363, 0x38362A2A,
    0x0D54E6E6, 0xC6432020, 0x3562CCCC, 0x98BEF2F2, 0x181E1212, 0xF724EBEB, 0xECD7A1A1, 0x6C774141,
    0x43BD2828, 0x7532BCBC, 0x37D47B7B, 0x269B8888, 0xFA700D0D, 0x13F94444, 0x94B1FBFB, 0x485A7E7E,
    0xF27A0303, 0xD0E48C8C, 0x8B47B6B6, 0x303C2424, 0x84A5E7E7, 0x54416B6B, 0xDF06DDDD, 0x23C56060,
    0x1945FDFD, 0x5BA33A3A, 0x3D68C2C2, 0x59158D8D, 0xF321ECEC, 0xAE316666, 0xA23E6F6F, 0x82165757,
    0x63951010, 0x015BEFEF, 0x834DB8B8, 0x2E918686, 0xD9B56D6D, 0x511F8383, 0x9B53AAAA, 0x7C635D5D,
    0xA63B6868, 0xEB3FFEFE, 0xA5D63030, 0xBE257A7A, 0x16A7ACAC, 0x0C0F0909, 0xE335F0F0, 0x6123A7A7,
    0xC0F09090, 0x8CAFE9E9, 0x3A809D9D, 0xF5925C5C, 0x73810C0C, 0x2C273131, 0x2576D0D0, 0x0BE75656,
    0xBB7B9292, 0x4EE9CECE, 0x89F10101, 0x6B9F1E1E, 0x53A93434, 0x6AC4F1F1, 0xB499C3C3, 0xF1975B5B,
    0xE1834747, 0xE66B1818, 0xBDC82222, 0x450E9898, 0xE26E1F1F, 0xF4C9B3B3, 0xB62F7474, 0x66CBF8F8,
    0xCCFF9999, 0x95EA1414, 0x03ED5858, 0x56F7DCDC, 0xD4E18B8B, 0x1C1B1515, 0x1EADA2A2, 0xD70CD3D3,
    0xFB2BE2E2, 0xC31DC8C8, 0x8E195E5E, 0xB5C22C2C, 0xE9894949, 0xCF12C1C1, 0xBF7E9595, 0xBA207D7D,
    0xEA641111, 0x77840B0B, 0x396DC5C5, 0xAF6A8989, 0x33D17C7C, 0xC9A17171, 0x62CEFFFF, 0x7137BBBB,
    0x81FB0F0F, 0x793DB5B5, 0x0951E1E1, 0xADDC3E3E, 0x242D3F3F, 0xCDA47676, 0xF99D5555, 0xD8EE8282,
    0xE5864040, 0xC5AE7878, 0xB9CD2525, 0x4D049696, 0x44557777, 0x080A0E0E, 0x86135050, 0xE730F7F7,
    0xA1D33737, 0x1D40FAFA, 0xAA346161, 0xED8C4E4E, 0x06B3B0B0, 0x706C5454, 0xB22A7373, 0xD2523B3B,
    0x410B9F9F, 0x7B8B0202, 0xA088D8D8, 0x114FF3F3, 0x3167CBCB, 0xC2462727, 0x27C06767, 0x90B4FCFC,
    0x20283838, 0xF67F0404, 0x60784848, 0xFF2EE5E5, 0x96074C4C, 0x5C4B6565, 0xB1C72B2B, 0xAB6F8E8E,
    0x9E0D4242, 0x9CBBF5F5, 0x52F2DBDB, 0x1BF34A4A, 0x5FA63D3D, 0x9359A4A4, 0x0ABCB9B9, 0xEF3AF9F9,
    0x91EF1313, 0x85FE0808, 0x49019191, 0xEE611616, 0x2D7CDEDE, 0x4FB22121, 0x8F42B1B1, 0x3BDB7272,
    0x47B82F2F, 0x8748BFBF, 0x6D2CAEAE, 0x46E3C0C0, 0xD6573C3C, 0x3E859A9A, 0x6929A9A9, 0x647D4F4F,
    0x2A948181, 0xCE492E2E, 0xCB17C6C6, 0x2FCA6969, 0xFCC3BDBD, 0x975CA3A3, 0x055EE8E8, 0x7AD0EDED,
    0xAC87D1D1, 0x7F8E0505, 0xD5BA6464, 0x1AA8A5A5, 0x4BB72626, 0x0EB9BEBE, 0xA7608787, 0x5AF8D5D5,
    0x28223636, 0x14111B1B, 0x3FDE7575, 0x2979D9D9, 0x88AAEEEE, 0x3C332D2D, 0x4C5F7979, 0x02B6B7B7,
    0xB896CACA, 0xDA583535, 0xB09CC4C4, 0x17FC4343, 0x551A8484, 0x1FF64D4D, 0x8A1C5959, 0x7D38B2B2,
    0x57AC3333, 0xC718CFCF, 0x8DF40606, 0x74695353, 0xB7749B9B, 0xC4F59797, 0x9F56ADAD, 0x72DAE3E3,
    0x7ED5EAEA, 0x154AF4F4, 0x229E8F8F, 0x12A2ABAB, 0x584E6262, 0x07E85F5F, 0x99E51D1D, 0x34392323,
    0x6EC1F6F6, 0x50446C6C, 0xDE5D3232, 0x68724646, 0x6526A0A0, 0xBC93CDCD, 0xDB03DADA, 0xF8C6BABA,
    0xC8FA9E9E, 0xA882D6D6, 0x2BCF6E6E, 0x40507070, 0xDCEB8585, 0xFE750A0A, 0x328A9393, 0xA48DDFDF,
    0xCA4C2929, 0x10141C1C, 0x2173D7D7, 0xF0CCB4B4, 0xD309D4D4, 0x5D108A8A, 0x0FE25151, 0x00000000,
    0x6F9A1919, 0x9DE01A1A, 0x368F9494, 0x42E6C7C7, 0x4AECC9C9, 0x5EFDD2D2, 0xC1AB7F7F, 0xE0D8A8A8};

// KDXServer.exe: 004852a8
static const uint MDS_GF_FE[256] = {
    0xBC75BC32, 0xECF3EC21, 0x20C62043, 0xB3F4B3C9, 0xDADBDA03, 0x027B028B, 0xE2FBE22B, 0x9EC89EFA,
    0xC94AC9EC, 0xD4D3D409, 0x18E6186B, 0x1E6B1E9F, 0x9845980E, 0xB27DB238, 0xA6E8A6D2, 0x264B26B7,
    0x3CD63C57, 0x9332938A, 0x82D882EE, 0x52FD5298, 0x7B377BD4, 0xBB71BB37, 0x5BF15B97, 0x47E14783,
    0x2430243C, 0x510F51E2, 0xBAF8BAC6, 0x4A1B4AF3, 0xBF87BF48, 0x0DFA0D70, 0xB006B0B3, 0x753F75DE,
    0xD25ED2FD, 0x7DBA7D20, 0x66AE6631, 0x3A5B3AA3, 0x598A591C, 0x00000000, 0xCDBCCD93, 0x1A9D1AE0,
    0xAE6DAE2C, 0x7FC17FAB, 0x2BB12BC7, 0xBE0EBEB9, 0xE080E0A0, 0x8A5D8A10, 0x3BD23B52, 0x64D564BA,
    0xD8A0D888, 0xE784E7A5, 0x5F075FE8, 0x1B141B11, 0x2CB52CC2, 0xFC90FCB4, 0x312C3127, 0x80A38065,
    0x73B2732A, 0x0C730C81, 0x794C795F, 0x6B546B41, 0x4B924B02, 0x53745369, 0x9436948F, 0x8351831F,
    0x2A382A36, 0xC4B0C49C, 0x22BD22C8, 0xD55AD5F8, 0xBDFCBDC3, 0x48604878, 0xFF62FFCE, 0x4C964C07,
    0x416C4177, 0xC742C7E6, 0xEBF7EB24, 0x1C101C14, 0x5D7C5D63, 0x36283622, 0x672767C0, 0xE98CE9AF,
    0x441344F9, 0x149514EA, 0xF59CF5BB, 0xCFC7CF18, 0x3F243F2D, 0xC046C0E3, 0x723B72DB, 0x5470546C,
    0x29CA294C, 0xF0E3F035, 0x088508FE, 0xC6CBC617, 0xF311F34F, 0x8CD08CE4, 0xA493A459, 0xCAB8CA96,
    0x68A6683B, 0xB883B84D, 0x38203828, 0xE5FFE52E, 0xAD9FAD56, 0x0B770B84, 0xC8C3C81D, 0x99CC99FF,
    0x580358ED, 0x196F199A, 0x0E080E0A, 0x95BF957E, 0x70407050, 0xF7E7F730, 0x6E2B6ECF, 0x1FE21F6E,
    0xB579B53D, 0x090C090F, 0x61AA6134, 0x57825716, 0x9F419F0B, 0x9D3A9D80, 0x11EA1164, 0x25B925CD,
    0xAFE4AFDD, 0x459A4508, 0xDFA4DF8D, 0xA397A35C, 0xEA7EEAD5, 0x35DA3558, 0xED7AEDD0, 0x431743FC,
    0xF866F8CB, 0xFB94FBB1, 0x37A137D3, 0xFA1DFA40, 0xC23DC268, 0xB4F0B4CC, 0x32DE325D, 0x9CB39C71,
    0x560B56E7, 0xE372E3DA, 0x87A78760, 0x151C151B, 0xF9EFF93A, 0x63D163BF, 0x345334A9, 0x9A3E9A85,
    0xB18FB142, 0x7C337CD1, 0x8826889B, 0x3D5F3DA6, 0xA1ECA1D7, 0xE476E4DF, 0x812A8194, 0x91499101,
    0x0F810FFB, 0xEE88EEAA, 0x16EE1661, 0xD721D773, 0x97C497F5, 0xA51AA5A8, 0xFEEBFE3F, 0x6DD96DB5,
    0x78C578AE, 0xC539C56D, 0x1D991DE5, 0x76CD76A4, 0x3EAD3EDC, 0xCB31CB67, 0xB68BB647, 0xEF01EF5B,
    0x1218121E, 0x602360C5, 0x6ADD6AB0, 0x4D1F4DF6, 0xCE4ECEE9, 0xDE2DDE7C, 0x55F9559D, 0x7E487E5A,
    0x214F21B2, 0x03F2037A, 0xA065A026, 0x5E8E5E19, 0x5A785A66, 0x655C654B, 0x6258624E, 0xFD19FD45,
    0x068D06F4, 0x40E54086, 0xF298F2BE, 0x335733AC, 0x17671790, 0x057F058E, 0xE805E85E, 0x4F644F7D,
    0x89AF896A, 0x10631095, 0x74B6742F, 0x0AFE0A75, 0x5CF55C92, 0x9BB79B74, 0x2D3C2D33, 0x30A530D6,
    0x2ECE2E49, 0x49E94989, 0x46684672, 0x77447755, 0xA8E0A8D8, 0x964D9604, 0x284328BD, 0xA969A929,
    0xD929D979, 0x862E8691, 0xD1ACD187, 0xF415F44A, 0x8D598D15, 0xD6A8D682, 0xB90AB9BC, 0x429E420D,
    0xF66EF6C1, 0x2F472FB8, 0xDDDFDD06, 0x23342339, 0xCC35CC62, 0xF16AF1C4, 0xC1CFC112, 0x85DC85EB,
    0x8F228F9E, 0x71C971A1, 0x90C090F0, 0xAA9BAA53, 0x018901F1, 0x8BD48BE1, 0x4EED4E8C, 0x8EAB8E6F,
    0xAB12ABA2, 0x6FA26F3E, 0xE60DE654, 0xDB52DBF2, 0x92BB927B, 0xB702B7B6, 0x692F69CA, 0x39A939D9,
    0xD3D7D30C, 0xA761A723, 0xA21EA2AD, 0xC3B4C399, 0x6C506C44, 0x07040705, 0x04F6047F, 0x27C22746,
    0xAC16ACA7, 0xD025D076, 0x50865013, 0xDC56DCF7, 0x8455841A, 0xE109E151, 0x7ABE7A25, 0x139113EF};

// KDXServer.exe: 004856a8
static const uint MDS_GF_FF[256] = {
    0xD939A9D9, 0x90176790, 0x719CB371, 0xD2A6E8D2, 0x05070405, 0x9852FD98, 0x6580A365, 0xDFE476DF,
    0x08459A08, 0x024B9202, 0xA0E080A0, 0x665A7866, 0xDDAFE4DD, 0xB06ADDB0, 0xBF63D1BF, 0x362A3836,
    0x54E60D54, 0x4320C643, 0x62CC3562, 0xBEF298BE, 0x1E12181E, 0x24EBF724, 0xD7A1ECD7, 0x77416C77,
    0xBD2843BD, 0x32BC7532, 0xD47B37D4, 0x9B88269B, 0x700DFA70, 0xF94413F9, 0xB1FB94B1, 0x5A7E485A,
    0x7A03F27A, 0xE48CD0E4, 0x47B68B47, 0x3C24303C, 0xA5E784A5, 0x416B5441, 0x06DDDF06, 0xC56023C5,
    0x45FD1945, 0xA33A5BA3, 0x68C23D68, 0x158D5915, 0x21ECF321, 0x3166AE31, 0x3E6FA23E, 0x16578216,
    0x95106395, 0x5BEF015B, 0x4DB8834D, 0x91862E91, 0xB56DD9B5, 0x1F83511F, 0x53AA9B53, 0x635D7C63,
    0x3B68A63B, 0x3FFEEB3F, 0xD630A5D6, 0x257ABE25, 0xA7AC16A7, 0x0F090C0F, 0x35F0E335, 0x23A76123,
    0xF090C0F0, 0xAFE98CAF, 0x809D3A80, 0x925CF592, 0x810C7381, 0x27312C27, 0x76D02576, 0xE7560BE7,
    0x7B92BB7B, 0xE9CE4EE9, 0xF10189F1, 0x9F1E6B9F, 0xA93453A9, 0xC4F16AC4, 0x99C3B499, 0x975BF197,
    0x8347E183, 0x6B18E66B, 0xC822BDC8, 0x0E98450E, 0x6E1FE26E, 0xC9B3F4C9, 0x2F74B62F, 0xCBF866CB,
    0xFF99CCFF, 0xEA1495EA, 0xED5803ED, 0xF7DC56F7, 0xE18BD4E1, 0x1B151C1B, 0xADA21EAD, 0x0CD3D70C,
    0x2BE2FB2B, 0x1DC8C31D, 0x195E8E19, 0xC22CB5C2, 0x8949E989, 0x12C1CF12, 0x7E95BF7E, 0x207DBA20,
    0x6411EA64, 0x840B7784, 0x6DC5396D, 0x6A89AF6A, 0xD17C33D1, 0xA171C9A1, 0xCEFF62CE, 0x37BB7137,
    0xFB0F81FB, 0x3DB5793D, 0x51E10951, 0xDC3EADDC, 0x2D3F242D, 0xA476CDA4, 0x9D55F99D, 0xEE82D8EE,
    0x8640E586, 0xAE78C5AE, 0xCD25B9CD, 0x04964D04, 0x55774455, 0x0A0E080A, 0x13508613, 0x30F7E730,
    0xD337A1D3, 0x40FA1D40, 0x3461AA34, 0x8C4EED8C, 0xB3B006B3, 0x6C54706C, 0x2A73B22A, 0x523BD252,
    0x0B9F410B, 0x8B027B8B, 0x88D8A088, 0x4FF3114F, 0x67CB3167, 0x4627C246, 0xC06727C0, 0xB4FC90B4,
    0x28382028, 0x7F04F67F, 0x78486078, 0x2EE5FF2E, 0x074C9607, 0x4B655C4B, 0xC72BB1C7, 0x6F8EAB6F,
    0x0D429E0D, 0xBBF59CBB, 0xF2DB52F2, 0xF34A1BF3, 0xA63D5FA6, 0x59A49359, 0xBCB90ABC, 0x3AF9EF3A,
    0xEF1391EF, 0xFE0885FE, 0x01914901, 0x6116EE61, 0x7CDE2D7C, 0xB2214FB2, 0x42B18F42, 0xDB723BDB,
    0xB82F47B8, 0x48BF8748, 0x2CAE6D2C, 0xE3C046E3, 0x573CD657, 0x859A3E85, 0x29A96929, 0x7D4F647D,
    0x94812A94, 0x492ECE49, 0x17C6CB17, 0xCA692FCA, 0xC3BDFCC3, 0x5CA3975C, 0x5EE8055E, 0xD0ED7AD0,
    0x87D1AC87, 0x8E057F8E, 0xBA64D5BA, 0xA8A51AA8, 0xB7264BB7, 0xB9BE0EB9, 0x6087A760, 0xF8D55AF8,
    0x22362822, 0x111B1411, 0xDE753FDE, 0x79D92979, 0xAAEE88AA, 0x332D3C33, 0x5F794C5F, 0xB6B702B6,
    0x96CAB896, 0x5835DA58, 0x9CC4B09C, 0xFC4317FC, 0x1A84551A, 0xF64D1FF6, 0x1C598A1C, 0x38B27D38,
    0xAC3357AC, 0x18CFC718, 0xF4068DF4, 0x69537469, 0x749BB774, 0xF597C4F5, 0x56AD9F56, 0xDAE372DA,
    0xD5EA7ED5, 0x4AF4154A, 0x9E8F229E, 0xA2AB12A2, 0x4E62584E, 0xE85F07E8, 0xE51D99E5, 0x39233439,
    0xC1F66EC1, 0x446C5044, 0x5D32DE5D, 0x72466872, 0x26A06526, 0x93CDBC93, 0x03DADB03, 0xC6BAF8C6,
    0xFA9EC8FA, 0x82D6A882, 0xCF6E2BCF, 0x50704050, 0xEB85DCEB, 0x750AFE75, 0x8A93328A, 0x8DDFA48D,
    0x4C29CA4C, 0x141C1014, 0x73D72173, 0xCCB4F0CC, 0x09D4D309, 0x108A5D10, 0xE2510FE2, 0x00000000,
    0x9A196F9A, 0xE01A9DE0, 0x8F94368F, 0xE6C742E6, 0xECC94AEC, 0xFDD25EFD, 0xAB7FC1AB, 0xD8A8E0D8};

// KDXServer.exe: 0043d8d0
CTwofish::CTwofish(const void *inData)
{
	byte bVar1;
	byte bVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	byte local_5e;
	byte local_5d;
	byte local_5c;
	byte local_5b;
	byte local_5a;
	byte local_59;
	byte local_58;
	byte local_57;
	byte local_56;
	byte local_55;
	byte local_54;
	byte local_53;
	byte local_52;
	byte local_51;

	bVar1 = 0;
	local_57 = 0;
	local_58 = 0;
	local_5a = 0;
	local_53 = 0;
	local_51 = 0;
	local_56 = 0;
	local_54 = 0;
	local_55 = 0;
	local_52 = 0;
	local_5b = 0;
	local_5c = 0;

	if (*(byte *)inData != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)inData];
		bVar1 = Q[1][uVar4];
		local_57 = Q[1][uVar4 + 0x2d];
		local_58 = Q[1][uVar4 + 1];
	}
	local_5e = local_57;
	if (*(byte *)((ulonglong)inData + 1) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 1)];
		bVar1 = bVar1 ^ Q[1][uVar4 + 0x2d];
		local_58 = local_58 ^ Q[1][uVar4 + 0x44];
		local_5e = local_57 ^ Q[1][uVar4 + 0x8a];
		local_57 = local_57 ^ Q[1][uVar4 + 0xa4];
	}
	if (*(byte *)((ulonglong)inData + 2) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 2)];
		bVar1 = bVar1 ^ Q[1][uVar4 + 0x8a];
		local_57 = local_57 ^ Q[1][uVar4 + 0xd5];
		local_58 = local_58 ^ Q[1][uVar4 + 0xbf];
		local_5e = local_5e ^ Q[1][uVar4 + 0xd1];
	}
	if (*(byte *)((ulonglong)inData + 3) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 3)];
		bVar1 = bVar1 ^ Q[1][uVar4 + 0xd1];
		local_57 = local_57 ^ Q[1][uVar4 + 0x7f];
		local_58 = local_58 ^ Q[1][uVar4 + 0x3d];
		local_5e = local_5e ^ Q[1][uVar4 + 0x99];
	}
	if (*(byte *)((ulonglong)inData + 4) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 4)];
		bVar1 = bVar1 ^ Q[1][uVar4 + 0x99];
		local_57 = local_57 ^ Q[1][uVar4 + 0x46];
		local_58 = local_58 ^ Q[1][uVar4 + 0x66];
		local_5e = local_5e ^ Q[1][uVar4 + 0x96];
	}
	if (*(byte *)((ulonglong)inData + 5) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 5)];
		bVar1 = bVar1 ^ Q[1][uVar4 + 0x96];
		local_57 = local_57 ^ Q[1][uVar4 + 0x3c];
		local_58 = local_58 ^ Q[1][uVar4 + 0x5b];
		local_5e = local_5e ^ Q[1][uVar4 + 0xed];
	}
	if (*(byte *)((ulonglong)inData + 6) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 6)];
		bVar1 = bVar1 ^ Q[1][uVar4 + 0xed];
		local_57 = local_57 ^ Q[1][uVar4 + 0x37];
		local_58 = local_58 ^ Q[1][uVar4 + 0x4f];
		local_5e = local_5e ^ Q[1][uVar4 + 0xe0];
	}
	if (*(byte *)((ulonglong)inData + 7) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 7)];
		bVar1 = bVar1 ^ Q[1][uVar4 + 0xe0];
		local_57 = local_57 ^ Q[1][uVar4 + 0xd0];
		local_58 = local_58 ^ Q[1][uVar4 + 0x8c];
		local_5e = local_5e ^ Q[1][uVar4 + 0x17];
	}
	if (*(byte *)((ulonglong)inData + 8) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 8)];
		local_5a = Q[1][uVar4];
		local_51 = Q[1][uVar4 + 0x2d];
		local_53 = Q[1][uVar4 + 1];
	}
	local_59 = local_51;
	if (*(byte *)((ulonglong)inData + 9) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 9)];
		local_5a = local_5a ^ Q[1][uVar4 + 0x2d];
		local_59 = local_51 ^ Q[1][uVar4 + 0xa4];
		local_53 = local_53 ^ Q[1][uVar4 + 0x44];
		local_51 = local_51 ^ Q[1][uVar4 + 0x8a];
	}
	if (*(byte *)((ulonglong)inData + 10) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 10)];
		local_5a = local_5a ^ Q[1][uVar4 + 0x8a];
		local_59 = local_59 ^ Q[1][uVar4 + 0xd5];
		local_53 = local_53 ^ Q[1][uVar4 + 0xbf];
		local_51 = local_51 ^ Q[1][uVar4 + 0xd1];
	}
	if (*(byte *)((ulonglong)inData + 0xb) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0xb)];
		local_5a = local_5a ^ Q[1][uVar4 + 0xd1];
		local_59 = local_59 ^ Q[1][uVar4 + 0x7f];
		local_53 = local_53 ^ Q[1][uVar4 + 0x3d];
		local_51 = local_51 ^ Q[1][uVar4 + 0x99];
	}
	if (*(byte *)((ulonglong)inData + 0xc) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0xc)];
		local_5a = local_5a ^ Q[1][uVar4 + 0x99];
		local_59 = local_59 ^ Q[1][uVar4 + 0x46];
		local_53 = local_53 ^ Q[1][uVar4 + 0x66];
		local_51 = local_51 ^ Q[1][uVar4 + 0x96];
	}
	if (*(byte *)((ulonglong)inData + 0xd) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0xd)];
		local_5a = local_5a ^ Q[1][uVar4 + 0x96];
		local_59 = local_59 ^ Q[1][uVar4 + 0x3c];
		local_53 = local_53 ^ Q[1][uVar4 + 0x5b];
		local_51 = local_51 ^ Q[1][uVar4 + 0xed];
	}
	if (*(byte *)((ulonglong)inData + 0xe) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0xe)];
		local_5a = local_5a ^ Q[1][uVar4 + 0xed];
		local_59 = local_59 ^ Q[1][uVar4 + 0x37];
		local_53 = local_53 ^ Q[1][uVar4 + 0x4f];
		local_51 = local_51 ^ Q[1][uVar4 + 0xe0];
	}
	if (*(byte *)((ulonglong)inData + 0xf) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0xf)];
		local_5a = local_5a ^ Q[1][uVar4 + 0xe0];
		local_59 = local_59 ^ Q[1][uVar4 + 0xd0];
		local_53 = local_53 ^ Q[1][uVar4 + 0x8c];
		local_51 = local_51 ^ Q[1][uVar4 + 0x17];
	}
	if (*(byte *)((ulonglong)inData + 0x10) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x10)];
		local_56 = Q[1][uVar4];
		local_54 = Q[1][uVar4 + 0x2d];
		local_55 = Q[1][uVar4 + 1];
	}
	local_5d = local_54;
	if (*(byte *)((ulonglong)inData + 0x11) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x11)];
		local_56 = local_56 ^ Q[1][uVar4 + 0x2d];
		local_55 = local_55 ^ Q[1][uVar4 + 0x44];
		local_5d = local_54 ^ Q[1][uVar4 + 0x8a];
		local_54 = local_54 ^ Q[1][uVar4 + 0xa4];
	}
	if (*(byte *)((ulonglong)inData + 0x12) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x12)];
		local_56 = local_56 ^ Q[1][uVar4 + 0x8a];
		local_54 = local_54 ^ Q[1][uVar4 + 0xd5];
		local_55 = local_55 ^ Q[1][uVar4 + 0xbf];
		local_5d = local_5d ^ Q[1][uVar4 + 0xd1];
	}
	if (*(byte *)((ulonglong)inData + 0x13) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x13)];
		local_56 = local_56 ^ Q[1][uVar4 + 0xd1];
		local_54 = local_54 ^ Q[1][uVar4 + 0x7f];
		local_55 = local_55 ^ Q[1][uVar4 + 0x3d];
		local_5d = local_5d ^ Q[1][uVar4 + 0x99];
	}
	if (*(byte *)((ulonglong)inData + 0x14) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x14)];
		local_56 = local_56 ^ Q[1][uVar4 + 0x99];
		local_54 = local_54 ^ Q[1][uVar4 + 0x46];
		local_55 = local_55 ^ Q[1][uVar4 + 0x66];
		local_5d = local_5d ^ Q[1][uVar4 + 0x96];
	}
	if (*(byte *)((ulonglong)inData + 0x15) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x15)];
		local_56 = local_56 ^ Q[1][uVar4 + 0x96];
		local_54 = local_54 ^ Q[1][uVar4 + 0x3c];
		local_55 = local_55 ^ Q[1][uVar4 + 0x5b];
		local_5d = local_5d ^ Q[1][uVar4 + 0xed];
	}
	if (*(byte *)((ulonglong)inData + 0x16) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x16)];
		local_56 = local_56 ^ Q[1][uVar4 + 0xed];
		local_54 = local_54 ^ Q[1][uVar4 + 0x37];
		local_55 = local_55 ^ Q[1][uVar4 + 0x4f];
		local_5d = local_5d ^ Q[1][uVar4 + 0xe0];
	}
	if (*(byte *)((ulonglong)inData + 0x17) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x17)];
		local_56 = local_56 ^ Q[1][uVar4 + 0xe0];
		local_54 = local_54 ^ Q[1][uVar4 + 0xd0];
		local_55 = local_55 ^ Q[1][uVar4 + 0x8c];
		local_5d = local_5d ^ Q[1][uVar4 + 0x17];
	}
	if (*(byte *)((ulonglong)inData + 0x18) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x18)];
		local_52 = Q[1][uVar4];
		local_5b = Q[1][uVar4 + 0x2d];
		local_5c = Q[1][uVar4 + 1];
	}
	bVar2 = local_5b;
	if (*(byte *)((ulonglong)inData + 0x19) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x19)];
		local_52 = local_52 ^ Q[1][uVar4 + 0x2d];
		local_5c = local_5c ^ Q[1][uVar4 + 0x44];
		bVar2 = local_5b ^ Q[1][uVar4 + 0x8a];
		local_5b = local_5b ^ Q[1][uVar4 + 0xa4];
	}
	if (*(byte *)((ulonglong)inData + 0x1a) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x1a)];
		local_52 = local_52 ^ Q[1][uVar4 + 0x8a];
		local_5b = local_5b ^ Q[1][uVar4 + 0xd5];
		local_5c = local_5c ^ Q[1][uVar4 + 0xbf];
		bVar2 = bVar2 ^ Q[1][uVar4 + 0xd1];
	}
	if (*(byte *)((ulonglong)inData + 0x1b) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x1b)];
		local_52 = local_52 ^ Q[1][uVar4 + 0xd1];
		local_5b = local_5b ^ Q[1][uVar4 + 0x7f];
		local_5c = local_5c ^ Q[1][uVar4 + 0x3d];
		bVar2 = bVar2 ^ Q[1][uVar4 + 0x99];
	}
	if (*(byte *)((ulonglong)inData + 0x1c) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x1c)];
		local_52 = local_52 ^ Q[1][uVar4 + 0x99];
		local_5b = local_5b ^ Q[1][uVar4 + 0x46];
		local_5c = local_5c ^ Q[1][uVar4 + 0x66];
		bVar2 = bVar2 ^ Q[1][uVar4 + 0x96];
	}
	if (*(byte *)((ulonglong)inData + 0x1d) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x1d)];
		local_52 = local_52 ^ Q[1][uVar4 + 0x96];
		local_5b = local_5b ^ Q[1][uVar4 + 0x3c];
		local_5c = local_5c ^ Q[1][uVar4 + 0x5b];
		bVar2 = bVar2 ^ Q[1][uVar4 + 0xed];
	}
	if (*(byte *)((ulonglong)inData + 0x1e) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x1e)];
		local_52 = local_52 ^ Q[1][uVar4 + 0xed];
		local_5b = local_5b ^ Q[1][uVar4 + 0x37];
		local_5c = local_5c ^ Q[1][uVar4 + 0x4f];
		bVar2 = bVar2 ^ Q[1][uVar4 + 0xe0];
	}
	if (*(byte *)((ulonglong)inData + 0x1f) != 0)
	{
		uVar4 = (uint)Q[0][*(byte *)((ulonglong)inData + 0x1f)];
		local_52 = local_52 ^ Q[1][uVar4 + 0xe0];
		local_5b = local_5b ^ Q[1][uVar4 + 0xd0];
		local_5c = local_5c ^ Q[1][uVar4 + 0x8c];
		bVar2 = bVar2 ^ Q[1][uVar4 + 0x17];
	}
	iVar5 = 0;
	iVar6 = 0;
	iVar3 = 1;
	do
	{
		mSBox[0][iVar6] =
		    MDS_GF_FB[MDS[0][MDS[0][MDS[1][*(byte *)((ulonglong)P + iVar3) ^ bVar1] ^ local_5a] ^
		                     local_56] ^
		              local_52];
		mSBox[1][iVar6] =
		    MDS_GF_FD[MDS[0][MDS[1][MDS[1][*(byte *)((ulonglong)P + iVar5) ^ local_57] ^ local_59] ^
		                     local_54] ^
		              local_5b];
		mSBox[2][iVar6] =
		    MDS_GF_FE[MDS[1][MDS[0][MDS[0][*(byte *)((ulonglong)P + iVar5) ^ local_58] ^ local_53] ^
		                     local_55] ^
		              local_5c];
		mSBox[3][iVar6] =
		    MDS_GF_FF[MDS[1][MDS[1][MDS[0][*(byte *)((ulonglong)P + iVar3) ^ local_5e] ^ local_51] ^
		                     local_5d] ^
		              bVar2];
		iVar6 = iVar6 + 1;
		iVar5 = iVar5 + 2;
		iVar3 = iVar3 + 2;
	} while (iVar6 < 0x100);
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x67]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0xf3]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x67]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0xf3]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xa9]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0x75]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xa9]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0x75]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[1] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0xe8]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0xf4]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0xe8]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0xf4]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xb3]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xc6]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xb3]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xc6]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[2] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[3] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0xfd]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x7b]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0xfd]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x7b]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 4]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xdb]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 4]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xdb]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[4] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[5] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x76]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 200]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x76]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 200]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xa3]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xfb]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xa3]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xfb]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[6] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[7] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x92]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0xd3]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x92]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0xd3]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x9a]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0x4a]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x9a]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0x4a]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[8] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[9] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x78]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x6b]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x78]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x6b]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x80]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xe6]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x80]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xe6]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[10] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0xb] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0xdd]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x7d]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0xdd]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x7d]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xe4]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0x45]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xe4]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0x45]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0xc] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0xd] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x38]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x4b]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x38]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x4b]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xd1]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xe8]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xd1]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xe8]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0xe] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0xf] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0xc6]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x32]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0xc6]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x32]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xd]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xd6]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xd]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xd6]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x10] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x11] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x98]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0xfd]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x98]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0xfd]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x35]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xd8]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x35]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xd8]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x12] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x13] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0xf7]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x71]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0xf7]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x71]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x18]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0x37]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x18]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0x37]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x14] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x15] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x6c]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0xe1]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x6c]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0xe1]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xec]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xf1]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xec]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xf1]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x16] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x17] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x75]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0xf]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x75]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0xf]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x43]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0x30]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x43]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0x30]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x18] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x19] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x26]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x1b]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x26]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x1b]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x37]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xf8]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x37]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xf8]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x1a] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x1b] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x13]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0xfa]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x13]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0xfa]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xfa]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0x87]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xfa]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0x87]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x1c] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x1d] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x48]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x3f]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x48]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x3f]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x94]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 6]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x94]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 6]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x1e] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x1f] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0xd0]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0xba]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0xd0]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0xba]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xf2]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0x5e]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xf2]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0x5e]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x20] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x21] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x30]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x5b]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x30]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x5b]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x8b]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xae]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x8b]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xae]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x22] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x23] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x54]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c)]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x54]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f)]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0x84]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0x8a]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0x84]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0x8a]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	mKey[0x24] = uVar4;
	uVar4 = iVar3 + uVar4;
	mKey[0x25] = (uVar4 >> 0x17) + uVar4 * 0x200;
	/* WARNING: Load size is inaccurate */
	uVar4 = MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x15) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1d) ^ 0x23]] ^
	                         *(byte *)((ulonglong)inData + 0xd)] ^
	                  *(byte *)((ulonglong)inData + 5)] ^
	        MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x14) ^
	                                MDS[1][*(byte *)((ulonglong)inData + 0x1c) ^ 0x9d]] ^
	                         *(byte *)((ulonglong)inData + 0xc)] ^
	                  *(byte *)((ulonglong)inData + 4)] ^
	        MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x16) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1e) ^ 0x23]] ^
	                         *(byte *)((ulonglong)inData + 0xe)] ^
	                  *(byte *)((ulonglong)inData + 6)] ^
	        MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x17) ^
	                                MDS[0][*(byte *)((ulonglong)inData + 0x1f) ^ 0x9d]] ^
	                         *(byte *)((ulonglong)inData + 0xf)] ^
	                  *(byte *)((ulonglong)inData + 7)];
	iVar3 = (uVar4 >> 0x18) + uVar4 * 0x100;
	uVar4 = (MDS_GF_FD[MDS[0][MDS[1][*(byte *)((ulonglong)inData + 0x11) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x19) ^ 0xdf]] ^
	                          *(byte *)((ulonglong)inData + 9)] ^
	                   *(byte *)((ulonglong)inData + 1)] ^
	         MDS_GF_FB[MDS[0][MDS[0][*(byte *)((ulonglong)inData + 0x10) ^
	                                 MDS[1][*(byte *)((ulonglong)inData + 0x18) ^ 0xbc]] ^
	                          *(byte *)((ulonglong)inData + 8)] ^
	                   *(byte *)inData] ^
	         MDS_GF_FE[MDS[1][MDS[0][*(byte *)((ulonglong)inData + 0x12) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1a) ^ 0xdf]] ^
	                          *(byte *)((ulonglong)inData + 10)] ^
	                   *(byte *)((ulonglong)inData + 2)] ^
	         MDS_GF_FF[MDS[1][MDS[1][*(byte *)((ulonglong)inData + 0x13) ^
	                                 MDS[0][*(byte *)((ulonglong)inData + 0x1b) ^ 0xbc]] ^
	                          *(byte *)((ulonglong)inData + 0xb)] ^
	                   *(byte *)((ulonglong)inData + 3)]) +
	        iVar3;
	uVar7 = iVar3 + uVar4;
	mKey[0x26] = uVar4;
	mKey[0x27] = (uVar7 >> 0x17) + uVar7 * 0x200;
	return;
}

// KDXServer.exe: 004406b0
void CTwofish::Encrypt(const void *inData, void *outData)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;
	int iVar4;
	uint uVar5;
	uint uVar6;
	uint uVar7;
	uint uVar8;
	undefined1 local_18;
	undefined1 local_14;

	/* WARNING: Load size is inaccurate */
	uVar1 = *(byte *)inData ^ mKey[0];
	uVar7 = *(uint *)((ulonglong)inData + 4) ^ mKey[1];
	uVar2 = *(uint *)((ulonglong)inData + 0xc) ^ mKey[3];
	uVar6 = mSBox[1][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 8 & 0xff] ^ mSBox[3][uVar7 >> 0x10 & 0xff] ^
	        mSBox[0][uVar7 >> 0x18];
	iVar4 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar6;
	uVar3 = *(uint *)((ulonglong)inData + 8) ^ mKey[2] ^ iVar4 + mKey[8];
	uVar5 = uVar3 * -0x80000000 + (uVar3 >> 1);
	uVar3 = uVar2 * 2 - ((int)uVar2 >> 0x1f) ^ uVar6 + iVar4 + mKey[9];
	uVar2 = mSBox[1][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 8 & 0xff] ^ mSBox[3][uVar3 >> 0x10 & 0xff] ^
	        mSBox[0][uVar3 >> 0x18];
	iVar4 = (mSBox[1][uVar5 >> 8 & 0xff] ^ mSBox[0][uVar5 & 0xff] ^ mSBox[2][uVar5 >> 0x10 & 0xff] ^
	         mSBox[3][uVar5 >> 0x18]) +
	        uVar2;
	uVar1 = uVar1 ^ iVar4 + mKey[10];
	uVar6 = uVar1 * -0x80000000 + (uVar1 >> 1);
	uVar7 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ uVar2 + iVar4 + mKey[0xb];
	uVar2 = mSBox[1][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 8 & 0xff] ^ mSBox[3][uVar7 >> 0x10 & 0xff] ^
	        mSBox[0][uVar7 >> 0x18];
	iVar4 = (mSBox[1][uVar6 >> 8 & 0xff] ^ mSBox[0][uVar6 & 0xff] ^ mSBox[2][uVar6 >> 0x10 & 0xff] ^
	         mSBox[3][uVar6 >> 0x18]) +
	        uVar2;
	uVar5 = uVar5 ^ iVar4 + mKey[0xc];
	uVar1 = uVar5 * -0x80000000 + (uVar5 >> 1);
	uVar8 = uVar3 * 2 - ((int)uVar3 >> 0x1f) ^ uVar2 + iVar4 + mKey[0xd];
	uVar3 = mSBox[1][uVar8 & 0xff] ^ mSBox[2][uVar8 >> 8 & 0xff] ^ mSBox[3][uVar8 >> 0x10 & 0xff] ^
	        mSBox[0][uVar8 >> 0x18];
	iVar4 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar3;
	uVar6 = uVar6 ^ iVar4 + mKey[0xe];
	uVar2 = uVar6 * -0x80000000 + (uVar6 >> 1);
	uVar3 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ uVar3 + iVar4 + mKey[0xf];
	uVar7 = mSBox[1][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 8 & 0xff] ^ mSBox[3][uVar3 >> 0x10 & 0xff] ^
	        mSBox[0][uVar3 >> 0x18];
	iVar4 = (mSBox[1][uVar2 >> 8 & 0xff] ^ mSBox[0][uVar2 & 0xff] ^ mSBox[2][uVar2 >> 0x10 & 0xff] ^
	         mSBox[3][uVar2 >> 0x18]) +
	        uVar7;
	uVar1 = uVar1 ^ iVar4 + mKey[0x10];
	uVar5 = uVar1 * -0x80000000 + (uVar1 >> 1);
	uVar7 = uVar8 * 2 - ((int)uVar8 >> 0x1f) ^ uVar7 + iVar4 + mKey[0x11];
	uVar6 = mSBox[1][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 8 & 0xff] ^ mSBox[3][uVar7 >> 0x10 & 0xff] ^
	        mSBox[0][uVar7 >> 0x18];
	iVar4 = (mSBox[1][uVar5 >> 8 & 0xff] ^ mSBox[0][uVar5 & 0xff] ^ mSBox[2][uVar5 >> 0x10 & 0xff] ^
	         mSBox[3][uVar5 >> 0x18]) +
	        uVar6;
	uVar2 = uVar2 ^ iVar4 + mKey[0x12];
	uVar1 = uVar2 * -0x80000000 + (uVar2 >> 1);
	uVar8 = uVar3 * 2 - ((int)uVar3 >> 0x1f) ^ uVar6 + iVar4 + mKey[0x13];
	uVar2 = mSBox[1][uVar8 & 0xff] ^ mSBox[2][uVar8 >> 8 & 0xff] ^ mSBox[3][uVar8 >> 0x10 & 0xff] ^
	        mSBox[0][uVar8 >> 0x18];
	iVar4 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar2;
	uVar5 = uVar5 ^ iVar4 + mKey[0x14];
	uVar3 = uVar5 * -0x80000000 + (uVar5 >> 1);
	uVar6 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ uVar2 + iVar4 + mKey[0x15];
	uVar7 = mSBox[1][uVar6 & 0xff] ^ mSBox[2][uVar6 >> 8 & 0xff] ^ mSBox[3][uVar6 >> 0x10 & 0xff] ^
	        mSBox[0][uVar6 >> 0x18];
	iVar4 = (mSBox[1][uVar3 >> 8 & 0xff] ^ mSBox[0][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 0x10 & 0xff] ^
	         mSBox[3][uVar3 >> 0x18]) +
	        uVar7;
	uVar1 = uVar1 ^ iVar4 + mKey[0x16];
	uVar1 = uVar1 * -0x80000000 + (uVar1 >> 1);
	uVar7 = uVar8 * 2 - ((int)uVar8 >> 0x1f) ^ uVar7 + iVar4 + mKey[0x17];
	uVar2 = mSBox[1][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 8 & 0xff] ^ mSBox[3][uVar7 >> 0x10 & 0xff] ^
	        mSBox[0][uVar7 >> 0x18];
	iVar4 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar2;
	uVar3 = uVar3 ^ iVar4 + mKey[0x18];
	uVar5 = uVar3 * -0x80000000 + (uVar3 >> 1);
	uVar3 = uVar6 * 2 - ((int)uVar6 >> 0x1f) ^ uVar2 + iVar4 + mKey[0x19];
	uVar2 = mSBox[1][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 8 & 0xff] ^ mSBox[3][uVar3 >> 0x10 & 0xff] ^
	        mSBox[0][uVar3 >> 0x18];
	iVar4 = (mSBox[1][uVar5 >> 8 & 0xff] ^ mSBox[0][uVar5 & 0xff] ^ mSBox[2][uVar5 >> 0x10 & 0xff] ^
	         mSBox[3][uVar5 >> 0x18]) +
	        uVar2;
	uVar1 = uVar1 ^ iVar4 + mKey[0x1a];
	uVar8 = uVar1 * -0x80000000 + (uVar1 >> 1);
	uVar7 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ uVar2 + iVar4 + mKey[0x1b];
	uVar2 = mSBox[1][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 8 & 0xff] ^ mSBox[3][uVar7 >> 0x10 & 0xff] ^
	        mSBox[0][uVar7 >> 0x18];
	iVar4 = (mSBox[1][uVar8 >> 8 & 0xff] ^ mSBox[0][uVar8 & 0xff] ^ mSBox[2][uVar8 >> 0x10 & 0xff] ^
	         mSBox[3][uVar8 >> 0x18]) +
	        uVar2;
	uVar5 = uVar5 ^ iVar4 + mKey[0x1c];
	uVar1 = uVar5 * -0x80000000 + (uVar5 >> 1);
	uVar6 = uVar3 * 2 - ((int)uVar3 >> 0x1f) ^ uVar2 + iVar4 + mKey[0x1d];
	uVar3 = mSBox[1][uVar6 & 0xff] ^ mSBox[2][uVar6 >> 8 & 0xff] ^ mSBox[3][uVar6 >> 0x10 & 0xff] ^
	        mSBox[0][uVar6 >> 0x18];
	iVar4 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar3;
	uVar8 = uVar8 ^ iVar4 + mKey[0x1e];
	uVar2 = uVar8 * -0x80000000 + (uVar8 >> 1);
	uVar5 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ uVar3 + iVar4 + mKey[0x1f];
	uVar3 = mSBox[1][uVar5 & 0xff] ^ mSBox[2][uVar5 >> 8 & 0xff] ^ mSBox[3][uVar5 >> 0x10 & 0xff] ^
	        mSBox[0][uVar5 >> 0x18];
	iVar4 = (mSBox[1][uVar2 >> 8 & 0xff] ^ mSBox[0][uVar2 & 0xff] ^ mSBox[2][uVar2 >> 0x10 & 0xff] ^
	         mSBox[3][uVar2 >> 0x18]) +
	        uVar3;
	uVar1 = uVar1 ^ iVar4 + mKey[0x20];
	uVar7 = uVar1 * -0x80000000 + (uVar1 >> 1);
	uVar6 = uVar6 * 2 - ((int)uVar6 >> 0x1f) ^ uVar3 + iVar4 + mKey[0x21];
	uVar3 = mSBox[1][uVar6 & 0xff] ^ mSBox[2][uVar6 >> 8 & 0xff] ^ mSBox[3][uVar6 >> 0x10 & 0xff] ^
	        mSBox[0][uVar6 >> 0x18];
	iVar4 = (mSBox[1][uVar7 >> 8 & 0xff] ^ mSBox[0][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 0x10 & 0xff] ^
	         mSBox[3][uVar7 >> 0x18]) +
	        uVar3;
	uVar2 = uVar2 ^ iVar4 + mKey[0x22];
	uVar1 = uVar2 * -0x80000000 + (uVar2 >> 1);
	uVar8 = uVar5 * 2 - ((int)uVar5 >> 0x1f) ^ uVar3 + iVar4 + mKey[0x23];
	uVar2 = mSBox[1][uVar8 & 0xff] ^ mSBox[2][uVar8 >> 8 & 0xff] ^ mSBox[3][uVar8 >> 0x10 & 0xff] ^
	        mSBox[0][uVar8 >> 0x18];
	iVar4 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar2;
	uVar7 = uVar7 ^ iVar4 + mKey[0x24];
	uVar3 = uVar7 * -0x80000000 + (uVar7 >> 1);
	uVar7 = uVar6 * 2 - ((int)uVar6 >> 0x1f) ^ uVar2 + iVar4 + mKey[0x25];
	uVar5 = mSBox[1][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 8 & 0xff] ^ mSBox[3][uVar7 >> 0x10 & 0xff] ^
	        mSBox[0][uVar7 >> 0x18];
	iVar4 = (mSBox[1][uVar3 >> 8 & 0xff] ^ mSBox[0][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 0x10 & 0xff] ^
	         mSBox[3][uVar3 >> 0x18]) +
	        uVar5;
	uVar2 = mKey[0x27];
	uVar1 = uVar1 ^ iVar4 + mKey[0x26];
	uVar3 = uVar3 ^ mKey[4];
	*(char *)outData = (char)uVar3;
	*(char *)((ulonglong)outData + 1) = (char)(uVar3 >> 8);
	*(char *)((ulonglong)outData + 2) = (char)(uVar3 >> 0x10);
	*(char *)((ulonglong)outData + 3) = (char)(uVar3 >> 0x18);
	uVar7 = uVar7 ^ mKey[5];
	*(char *)((ulonglong)outData + 4) = (char)uVar7;
	*(char *)((ulonglong)outData + 5) = (char)(uVar7 >> 8);
	*(char *)((ulonglong)outData + 6) = (char)(uVar7 >> 0x10);
	*(char *)((ulonglong)outData + 7) = (char)(uVar7 >> 0x18);
	uVar7 = uVar1 * -0x80000000 + (uVar1 >> 1) ^ mKey[6];
	local_14 = (undefined1)uVar7;
	*(undefined1 *)((ulonglong)outData + 8) = local_14;
	*(char *)((ulonglong)outData + 9) = (char)(uVar7 >> 8);
	*(char *)((ulonglong)outData + 10) = (char)(uVar7 >> 0x10);
	local_14 = (undefined1)(uVar7 >> 0x18);
	*(undefined1 *)((ulonglong)outData + 0xb) = local_14;
	uVar7 = uVar8 * 2 - ((int)uVar8 >> 0x1f) ^ uVar5 + iVar4 + uVar2 ^ mKey[7];
	local_18 = (undefined1)uVar7;
	*(undefined1 *)((ulonglong)outData + 0xc) = local_18;
	*(char *)((ulonglong)outData + 0xd) = (char)(uVar7 >> 8);
	*(char *)((ulonglong)outData + 0xe) = (char)(uVar7 >> 0x10);
	local_18 = (undefined1)(uVar7 >> 0x18);
	*(undefined1 *)((ulonglong)outData + 0xf) = local_18;
	return;
}

// KDXServer.exe: 004308f0
void CTwofish::EncryptCBC(void *outData, uint *ioPartialBlockSize, const void *inData,
                          uint inDataSize)
{
	uint inSize;
	uint uVar1;
	void *inData_00;

	inData_00 = outData;
	uVar1 = *ioPartialBlockSize;
	if (uVar1 != 0)
	{
		inSize = 0x10 - uVar1;
		if (inDataSize < inSize)
		{
			UMemory::Move((void *)((ulonglong)inData_00 + uVar1), inData, inDataSize);
			*ioPartialBlockSize = uVar1 + inDataSize;
			return;
		}
		UMemory::Move((void *)((ulonglong)inData_00 + uVar1), inData, inSize);
		inDataSize = inDataSize - inSize;
		inData = (void *)((ulonglong)inData + inSize);
		EncryptCBCIteration(inData_00, inData_00);
		inData_00 = (void *)((ulonglong)inData_00 + 0x10);
	}
	for (uVar1 = inDataSize >> 4; uVar1 != 0; uVar1 = uVar1 - 1)
	{
		EncryptCBCIteration(inData, inData_00);
		inData = (void *)((ulonglong)inData + 0x10);
		inData_00 = (void *)((ulonglong)inData_00 + 0x10);
	}
	UMemory::Move(inData_00, inData, inDataSize & 0xf);
	*(void **)outData = inData_00;
	*ioPartialBlockSize = inDataSize & 0xf;
	return;
}

// KDXServer.exe: 004413a0
void CTwofish::EncryptCBCIteration(const void *inData, void *outData)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;
	int iVar6;
	uint uVar7;
	undefined1 local_24;
	undefined1 local_14;

	uVar7 = *(byte *)inData ^ mKey[4];
	uVar4 = *(uint *)((ulonglong)inData + 4) ^ mKey[5];
	uVar1 = *(uint *)((ulonglong)inData + 8) ^ mKey[6];
	uVar2 = mSBox[1][uVar4 & 0xff] ^ mSBox[2][uVar4 >> 8 & 0xff] ^ mSBox[3][uVar4 >> 0x10 & 0xff] ^
	        mSBox[0][uVar4 >> 0x18];
	iVar6 = (mSBox[1][uVar7 >> 8 & 0xff] ^ mSBox[0][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 0x10 & 0xff] ^
	         mSBox[3][uVar7 >> 0x18]) +
	        uVar2;
	uVar2 = *(uint *)((ulonglong)inData + 0xc) ^ mKey[7] ^ uVar2 + iVar6 + mKey[0x27];
	uVar2 = uVar2 * -0x80000000 + (uVar2 >> 1);
	uVar3 = uVar1 * 2 - ((int)uVar1 >> 0x1f) ^ iVar6 + mKey[0x26];
	uVar1 = mSBox[1][uVar2 & 0xff] ^ mSBox[2][uVar2 >> 8 & 0xff] ^ mSBox[3][uVar2 >> 0x10 & 0xff] ^
	        mSBox[0][uVar2 >> 0x18];
	iVar6 = (mSBox[1][uVar3 >> 8 & 0xff] ^ mSBox[0][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 0x10 & 0xff] ^
	         mSBox[3][uVar3 >> 0x18]) +
	        uVar1;
	uVar4 = uVar4 ^ uVar1 + iVar6 + mKey[0x25];
	uVar1 = uVar4 * -0x80000000 + (uVar4 >> 1);
	uVar5 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ iVar6 + mKey[0x24];
	uVar7 = mSBox[1][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 8 & 0xff] ^ mSBox[3][uVar1 >> 0x10 & 0xff] ^
	        mSBox[0][uVar1 >> 0x18];
	iVar6 = (mSBox[1][uVar5 >> 8 & 0xff] ^ mSBox[0][uVar5 & 0xff] ^ mSBox[2][uVar5 >> 0x10 & 0xff] ^
	         mSBox[3][uVar5 >> 0x18]) +
	        uVar7;
	uVar2 = uVar2 ^ uVar7 + iVar6 + mKey[0x23];
	uVar4 = uVar2 * -0x80000000 + (uVar2 >> 1);
	uVar7 = uVar3 * 2 - ((int)uVar3 >> 0x1f) ^ iVar6 + mKey[0x22];
	uVar2 = mSBox[1][uVar4 & 0xff] ^ mSBox[2][uVar4 >> 8 & 0xff] ^ mSBox[3][uVar4 >> 0x10 & 0xff] ^
	        mSBox[0][uVar4 >> 0x18];
	iVar6 = (mSBox[1][uVar7 >> 8 & 0xff] ^ mSBox[0][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 0x10 & 0xff] ^
	         mSBox[3][uVar7 >> 0x18]) +
	        uVar2;
	uVar1 = uVar1 ^ uVar2 + iVar6 + mKey[0x21];
	uVar2 = uVar5 * 2 - ((int)uVar5 >> 0x1f) ^ iVar6 + mKey[0x20];
	uVar5 = uVar1 * -0x80000000 + (uVar1 >> 1);
	uVar1 = mSBox[1][uVar5 & 0xff] ^ mSBox[2][uVar5 >> 8 & 0xff] ^ mSBox[3][uVar5 >> 0x10 & 0xff] ^
	        mSBox[0][uVar5 >> 0x18];
	iVar6 = (mSBox[1][uVar2 >> 8 & 0xff] ^ mSBox[0][uVar2 & 0xff] ^ mSBox[2][uVar2 >> 0x10 & 0xff] ^
	         mSBox[3][uVar2 >> 0x18]) +
	        uVar1;
	uVar4 = uVar4 ^ uVar1 + iVar6 + mKey[0x1f];
	uVar3 = uVar4 * -0x80000000 + (uVar4 >> 1);
	uVar7 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ iVar6 + mKey[0x1e];
	uVar4 = mSBox[1][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 8 & 0xff] ^ mSBox[3][uVar3 >> 0x10 & 0xff] ^
	        mSBox[0][uVar3 >> 0x18];
	iVar6 = (mSBox[1][uVar7 >> 8 & 0xff] ^ mSBox[0][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 0x10 & 0xff] ^
	         mSBox[3][uVar7 >> 0x18]) +
	        uVar4;
	uVar5 = uVar5 ^ uVar4 + iVar6 + mKey[0x1d];
	uVar4 = uVar5 * -0x80000000 + (uVar5 >> 1);
	uVar1 = uVar2 * 2 - ((int)uVar2 >> 0x1f) ^ iVar6 + mKey[0x1c];
	uVar2 = mSBox[1][uVar4 & 0xff] ^ mSBox[2][uVar4 >> 8 & 0xff] ^ mSBox[3][uVar4 >> 0x10 & 0xff] ^
	        mSBox[0][uVar4 >> 0x18];
	iVar6 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar2;
	uVar3 = uVar3 ^ uVar2 + iVar6 + mKey[0x1b];
	uVar2 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ iVar6 + mKey[0x1a];
	uVar3 = uVar3 * -0x80000000 + (uVar3 >> 1);
	uVar7 = mSBox[1][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 8 & 0xff] ^ mSBox[3][uVar3 >> 0x10 & 0xff] ^
	        mSBox[0][uVar3 >> 0x18];
	iVar6 = (mSBox[1][uVar2 >> 8 & 0xff] ^ mSBox[0][uVar2 & 0xff] ^ mSBox[2][uVar2 >> 0x10 & 0xff] ^
	         mSBox[3][uVar2 >> 0x18]) +
	        uVar7;
	uVar4 = uVar4 ^ uVar7 + iVar6 + mKey[0x19];
	uVar4 = uVar4 * -0x80000000 + (uVar4 >> 1);
	uVar7 = uVar1 * 2 - ((int)uVar1 >> 0x1f) ^ iVar6 + mKey[0x18];
	uVar1 = mSBox[1][uVar4 & 0xff] ^ mSBox[2][uVar4 >> 8 & 0xff] ^ mSBox[3][uVar4 >> 0x10 & 0xff] ^
	        mSBox[0][uVar4 >> 0x18];
	iVar6 = (mSBox[1][uVar7 >> 8 & 0xff] ^ mSBox[0][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 0x10 & 0xff] ^
	         mSBox[3][uVar7 >> 0x18]) +
	        uVar1;
	uVar3 = uVar3 ^ uVar1 + iVar6 + mKey[0x17];
	uVar1 = uVar2 * 2 - ((int)uVar2 >> 0x1f) ^ iVar6 + mKey[0x16];
	uVar3 = uVar3 * -0x80000000 + (uVar3 >> 1);
	uVar2 = mSBox[1][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 8 & 0xff] ^ mSBox[3][uVar3 >> 0x10 & 0xff] ^
	        mSBox[0][uVar3 >> 0x18];
	iVar6 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar2;
	uVar4 = uVar4 ^ uVar2 + iVar6 + mKey[0x15];
	uVar2 = uVar4 * -0x80000000 + (uVar4 >> 1);
	uVar7 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ iVar6 + mKey[0x14];
	uVar4 = mSBox[1][uVar2 & 0xff] ^ mSBox[2][uVar2 >> 8 & 0xff] ^ mSBox[3][uVar2 >> 0x10 & 0xff] ^
	        mSBox[0][uVar2 >> 0x18];
	iVar6 = (mSBox[1][uVar7 >> 8 & 0xff] ^ mSBox[0][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 0x10 & 0xff] ^
	         mSBox[3][uVar7 >> 0x18]) +
	        uVar4;
	uVar3 = uVar3 ^ uVar4 + iVar6 + mKey[0x13];
	uVar4 = uVar3 * -0x80000000 + (uVar3 >> 1);
	uVar3 = uVar1 * 2 - ((int)uVar1 >> 0x1f) ^ iVar6 + mKey[0x12];
	uVar1 = mSBox[1][uVar4 & 0xff] ^ mSBox[2][uVar4 >> 8 & 0xff] ^ mSBox[3][uVar4 >> 0x10 & 0xff] ^
	        mSBox[0][uVar4 >> 0x18];
	iVar6 = (mSBox[1][uVar3 >> 8 & 0xff] ^ mSBox[0][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 0x10 & 0xff] ^
	         mSBox[3][uVar3 >> 0x18]) +
	        uVar1;
	uVar2 = uVar2 ^ uVar1 + iVar6 + mKey[0x11];
	uVar1 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ iVar6 + mKey[0x10];
	uVar5 = uVar2 * -0x80000000 + (uVar2 >> 1);
	uVar7 = mSBox[1][uVar5 & 0xff] ^ mSBox[2][uVar5 >> 8 & 0xff] ^ mSBox[3][uVar5 >> 0x10 & 0xff] ^
	        mSBox[0][uVar5 >> 0x18];
	iVar6 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar7;
	uVar4 = uVar4 ^ uVar7 + iVar6 + mKey[0xf];
	uVar4 = uVar4 * -0x80000000 + (uVar4 >> 1);
	uVar7 = uVar3 * 2 - ((int)uVar3 >> 0x1f) ^ iVar6 + mKey[0xe];
	uVar2 = mSBox[1][uVar4 & 0xff] ^ mSBox[2][uVar4 >> 8 & 0xff] ^ mSBox[3][uVar4 >> 0x10 & 0xff] ^
	        mSBox[0][uVar4 >> 0x18];
	iVar6 = (mSBox[1][uVar7 >> 8 & 0xff] ^ mSBox[0][uVar7 & 0xff] ^ mSBox[2][uVar7 >> 0x10 & 0xff] ^
	         mSBox[3][uVar7 >> 0x18]) +
	        uVar2;
	uVar5 = uVar5 ^ uVar2 + iVar6 + mKey[0xd];
	uVar3 = uVar1 * 2 - ((int)uVar1 >> 0x1f) ^ iVar6 + mKey[0xc];
	uVar2 = uVar5 * -0x80000000 + (uVar5 >> 1);
	uVar1 = mSBox[1][uVar2 & 0xff] ^ mSBox[2][uVar2 >> 8 & 0xff] ^ mSBox[3][uVar2 >> 0x10 & 0xff] ^
	        mSBox[0][uVar2 >> 0x18];
	iVar6 = (mSBox[1][uVar3 >> 8 & 0xff] ^ mSBox[0][uVar3 & 0xff] ^ mSBox[2][uVar3 >> 0x10 & 0xff] ^
	         mSBox[3][uVar3 >> 0x18]) +
	        uVar1;
	uVar4 = uVar4 ^ uVar1 + iVar6 + mKey[0xb];
	uVar4 = uVar4 * -0x80000000 + (uVar4 >> 1);
	uVar1 = uVar7 * 2 - ((int)uVar7 >> 0x1f) ^ iVar6 + mKey[10];
	uVar7 = mSBox[1][uVar4 & 0xff] ^ mSBox[2][uVar4 >> 8 & 0xff] ^ mSBox[3][uVar4 >> 0x10 & 0xff] ^
	        mSBox[0][uVar4 >> 0x18];
	iVar6 = (mSBox[1][uVar1 >> 8 & 0xff] ^ mSBox[0][uVar1 & 0xff] ^ mSBox[2][uVar1 >> 0x10 & 0xff] ^
	         mSBox[3][uVar1 >> 0x18]) +
	        uVar7;
	uVar2 = uVar2 ^ uVar7 + iVar6 + mKey[9];
	uVar1 = uVar1 ^ mKey[0];
	uVar7 = mKey[8];
	*(char *)outData = (char)uVar1;
	*(char *)((ulonglong)outData + 1) = (char)(uVar1 >> 8);
	*(char *)((ulonglong)outData + 2) = (char)(uVar1 >> 0x10);
	*(char *)((ulonglong)outData + 3) = (char)(uVar1 >> 0x18);
	uVar4 = uVar4 ^ mKey[1];
	local_24 = (undefined1)uVar4;
	*(undefined1 *)((ulonglong)outData + 4) = local_24;
	*(char *)((ulonglong)outData + 5) = (char)(uVar4 >> 8);
	*(char *)((ulonglong)outData + 6) = (char)(uVar4 >> 0x10);
	local_24 = (undefined1)(uVar4 >> 0x18);
	*(undefined1 *)((ulonglong)outData + 7) = local_24;
	uVar7 = uVar3 * 2 - ((int)uVar3 >> 0x1f) ^ iVar6 + uVar7 ^ mKey[2];
	*(char *)((ulonglong)outData + 8) = (char)uVar7;
	*(char *)((ulonglong)outData + 9) = (char)(uVar7 >> 8);
	*(char *)((ulonglong)outData + 10) = (char)(uVar7 >> 0x10);
	*(char *)((ulonglong)outData + 0xb) = (char)(uVar7 >> 0x18);
	uVar7 = uVar2 * -0x80000000 + (uVar2 >> 1) ^ mKey[3];
	local_14 = (undefined1)uVar7;
	*(undefined1 *)((ulonglong)outData + 0xc) = local_14;
	*(char *)((ulonglong)outData + 0xd) = (char)(uVar7 >> 8);
	*(char *)((ulonglong)outData + 0xe) = (char)(uVar7 >> 0x10);
	local_14 = (undefined1)(uVar7 >> 0x18);
	*(undefined1 *)((ulonglong)outData + 0xf) = local_14;
	return;
}
