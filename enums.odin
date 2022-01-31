package vma 

import c "core:c"

AllocatorCreateFlags :: distinct bit_set [AllocatorCreateFlagBit; u32]

AllocatorCreateFlagBit :: enum u32 {
	EXTERNALLY_SYNCHRONIZED     = 0,
	KHR_DEDICATED_ALLOCATION    = 1,
	KHR_BIND_MEMORY2            = 2,
	EXT_MEMORY_BUDGET           = 3,
	AMD_DEVICE_COHERENT_MEMORY  = 5,
	BUFFER_DEVICE_ADDRESS       = 6,
	EXT_MEMORY_PRIORITY         = 7,
}

MemoryUsage :: enum u32 {
	UNKNOWN                  = 0,
	GPU_ONLY                 = 1,
	CPU_ONLY                 = 2,
	CPU_TO_GPU               = 3,
	GPU_TO_CPU               = 4,
	CPU_COPY                 = 5,
	GPU_LAZILY_ALLOCATED     = 6,
}

AllocationCreateFlags :: distinct bit_set [AllocationCreateFlagBit; u32]

AllocationCreateFlagBit :: enum u32 {
	DEDICATED_MEMORY                   = 0,
	NEVER_ALLOCATE                     = 1,
	MAPPED                             = 2,
	USER_DATA_COPY_STRING              = 6,
	UPPER_ADDRESS                      = 7,
	DONT_BIND                          = 8,
	WITHIN_BUDGET                      = 9,
	CAN_ALIAS                          = 10,
	STRATEGY_MIN_MEMORY                = 17,
	STRATEGY_MIN_TIME                  = 18,
	STRATEGY_BEST_FIT                  = STRATEGY_MIN_MEMORY,
	STRATEGY_FIRST_FIT                 = STRATEGY_MIN_TIME,
	STRATEGY_MASK                      = STRATEGY_MIN_MEMORY | STRATEGY_MIN_TIME,
}

PoolCreateFlags :: distinct bit_set [PoolCreateFlagBit; u32]

PoolCreateFlagBit :: enum u32 {
	IGNORE_BUFFER_IMAGE_GRANULARITY     = 1,
	LINEAR_ALGORITHM                    = 2,
	BUDDY_ALGORITHM                     = 3,
	TLSF_ALGORITHM                      = 4,
	ALGORITHM_MASK                      = LINEAR_ALGORITHM | BUDDY_ALGORITHM | TLSF_ALGORITHM,
}

DefragmentationFlags :: distinct bit_set [DefragmentationFlagBit; u32]

DefragmentationFlagBit :: enum u32 {
	INCREMENTAL = 1,
}

