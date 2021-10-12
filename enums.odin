package vma 

import c "core:c"

AllocatorCreateFlags :: distinct bit_set [AllocatorCreateFlagBit; c.int]

AllocatorCreateFlagBit :: enum c.int {
	EXTERNALLY_SYNCHRONIZED     = 0,
	KHR_DEDICATED_ALLOCATION    = 1,
	KHR_BIND_MEMORY2            = 2,
	EXT_MEMORY_BUDGET           = 3,
	AMD_DEVICE_COHERENT_MEMORY  = 5,
	BUFFER_DEVICE_ADDRESS       = 6,
	EXT_MEMORY_PRIORITY         = 7,
}

RecordFlagBit :: enum c.int {
	AFTER_CALL = 0,
}

RecordFlags :: distinct bit_set [RecordFlagBit; c.int]

MemoryUsage :: enum {
	UNKNOWN                  = 0,
	GPU_ONLY                 = 1,
	CPU_ONLY                 = 2,
	CPU_TO_GPU               = 3,
	GPU_TO_CPU               = 4,
	CPU_COPY                 = 5,
	GPU_LAZILY_ALLOCATED     = 6,
}

AllocationCreateFlags :: distinct bit_set [AllocationCreateFlagBit; c.int]

AllocationCreateFlagBit :: enum c.int {
	DEDICATED_MEMORY                   = 0,
	NEVER_ALLOCATE                     = 1,
	MAPPED                             = 2,
	CAN_BECOME_LOST                    = 4,
	CAN_MAKE_OTHER_LOST                = 5,
	USER_DATA_COPY_STRING              = 6,
	UPPER_ADDRESS                      = 7,
	DONT_BIND                          = 8,
	WITHIN_BUDGET                      = 9,
	STRATEGY_BEST_FIT                  = 17,
	STRATEGY_WORST_FIT                 = 18,
	STRATEGY_FIRST_FIT                 = 19,
	STRATEGY_MIN_MEMORY                = STRATEGY_BEST_FIT,
	STRATEGY_MIN_TIME                  = STRATEGY_FIRST_FIT,
	STRATEGY_MIN_FRAGMENTATION         = STRATEGY_WORST_FIT,
	STRATEGY_MASK                      = STRATEGY_BEST_FIT | STRATEGY_WORST_FIT | STRATEGY_FIRST_FIT,
}

PoolCreateFlags :: distinct bit_set [PoolCreateFlagBit; c.int]

PoolCreateFlagBit :: enum c.int {
	IGNORE_BUFFER_IMAGE_GRANULARITY     = 1,
	LINEAR_ALGORITHM                    = 2,
	BUDDY_ALGORITHM                     = 3,
	ALGORITHM_MASK                      = LINEAR_ALGORITHM | BUDDY_ALGORITHM,
}

DefragmentationFlags :: distinct bit_set [DefragmentationFlagBit; c.int]

DefragmentationFlagBit :: enum {
	INCREMENTAL = 1,
}

