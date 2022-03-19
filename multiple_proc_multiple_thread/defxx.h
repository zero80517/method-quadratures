#pragma once

#define NUM_PHYSICAL_CORES 6 // number of physical cores
#define NUM_THREADS 2 // number of simultaneously threads
#define _USE_MATH_DEFINES

// MSVC compiler says that fopen() is deprecated,
// but Microsoft's *_s functions are unportable
#define _CRT_SECURE_NO_WARNINGS
