package vma

import vk "vendor:vulkan"

Pool :: ^Pool_T;
Pool_T :: struct {};

Allocation :: ^Allocation_T;
Allocation_T :: struct {};

Allocator_T :: struct {};
Allocator :: ^Allocator_T;

DeviceMemoryCallbacks :: struct {
    pfnAllocate : PFN_vmaAllocateDeviceMemoryFunction,
    pfnFree     : PFN_vmaFreeDeviceMemoryFunction,
    pUserData   : rawptr,
}

VulkanFunctions :: struct {
    GetPhysicalDeviceProperties           : vk.ProcGetPhysicalDeviceProperties,
    GetPhysicalDeviceMemoryProperties     : vk.ProcGetPhysicalDeviceMemoryProperties,
    AllocateMemory                        : vk.ProcAllocateMemory,
    FreeMemory                            : vk.ProcFreeMemory,
    MapMemory                             : vk.ProcMapMemory,
    UnmapMemory                           : vk.ProcUnmapMemory,
    FlushMappedMemoryRanges               : vk.ProcFlushMappedMemoryRanges,
    InvalidateMappedMemoryRanges          : vk.ProcInvalidateMappedMemoryRanges,
    BindBufferMemory                      : vk.ProcBindBufferMemory,
    BindImageMemory                       : vk.ProcBindImageMemory,
    GetBufferMemoryRequirements           : vk.ProcGetBufferMemoryRequirements,
    GetImageMemoryRequirements            : vk.ProcGetImageMemoryRequirements,
    CreateBuffer                          : vk.ProcCreateBuffer,
    DestroyBuffer                         : vk.ProcDestroyBuffer,
    CreateImage                           : vk.ProcCreateImage,
    DestroyImage                          : vk.ProcDestroyImage,
    CmdCopyBuffer                         : vk.ProcCmdCopyBuffer,
    GetBufferMemoryRequirements2KHR       : vk.ProcGetBufferMemoryRequirements2KHR,
    GetImageMemoryRequirements2KHR        : vk.ProcGetImageMemoryRequirements2KHR,
    BindBufferMemory2KHR                  : vk.ProcBindBufferMemory2KHR,
    BindImageMemory2KHR                   : vk.ProcBindImageMemory2KHR,
    GetPhysicalDeviceMemoryProperties2KHR : vk.ProcGetPhysicalDeviceMemoryProperties2KHR,
}

RecordSettings :: struct {
    flags     : RecordFlags,
    pFilePath : cstring,
}

AllocatorCreateInfo :: struct {
    flags                          : AllocatorCreateFlags,
    physicalDevice                 : vk.PhysicalDevice,
    device                         : vk.Device,
    preferredLargeHeapBlockSize    : vk.DeviceSize,
    pAllocationCallbacks           : ^vk.AllocationCallbacks,
    pDeviceMemoryCallbacks         : ^DeviceMemoryCallbacks,
    frameInUseCount                : u32,
    pHeapSizeLimit                 : ^vk.DeviceSize,
    pVulkanFunctions               : ^VulkanFunctions,
    pRecordSettings                : ^RecordSettings,
    instance                       : vk.Instance,
    vulkanApiVersion               : u32,
    pTypeExternalMemoryHandleTypes : ^vk.ExternalMemoryHandleTypeFlagsKHR,
}

AllocatorInfo :: struct {
    instance       : vk.Instance,
    physicalDevice : vk.PhysicalDevice,
    device         : vk.Device,
}

StatInfo :: struct {
    blockCount         : u32,
    allocationCount    : u32,
    unusedRangeCount   : u32,
    usedBytes          : vk.DeviceSize,
    unusedBytes        : vk.DeviceSize,
    allocationSizeMin  : vk.DeviceSize,
    allocationSizeAvg  : vk.DeviceSize,
    allocationSizeMax  : vk.DeviceSize,
    unusedRangeSizeMin : vk.DeviceSize,
    unusedRangeSizeAvg : vk.DeviceSize,
    unusedRangeSizeMax : vk.DeviceSize,
}

Stats :: struct {
    memoryType : [32]StatInfo,
    memoryHeap : [16]StatInfo,
    total      : StatInfo,
}

Budget :: struct {
    blockBytes      : vk.DeviceSize,
    allocationBytes : vk.DeviceSize,
    usage           : vk.DeviceSize,
    budget          : vk.DeviceSize,
}

AllocationCreateInfo :: struct {
    flags          : AllocationCreateFlags,
    usage          : MemoryUsage,
    requiredFlags  : vk.MemoryPropertyFlags,
    preferredFlags : vk.MemoryPropertyFlags,
    memoryTypeBits : u32,
    pool           : Pool,
    pUserData      : rawptr,
    priority       : f32,
}

PoolCreateInfo :: struct {
    memoryTypeIndex        : u32,
    flags                  : PoolCreateFlags,
    blockSize              : vk.DeviceSize,
    minBlockCount          : uint,
    maxBlockCount          : uint,
    frameInUseCount        : u32,
    priority               : f32,
    minAllocationAlignment : vk.DeviceSize,
    pMemoryAllocateNext    : rawptr,
}

PoolStats :: struct {
    size               : vk.DeviceSize,
    unusedSize         : vk.DeviceSize,
    allocationCount    : uint,
    unusedRangeCount   : uint,
    unusedRangeSizeMax : vk.DeviceSize,
    blockCount         : uint,
}

AllocationInfo :: struct {
    memoryType   : u32,
    deviceMemory : vk.DeviceMemory,
    offset       : vk.DeviceSize,
    size         : vk.DeviceSize,
    pMappedData  : rawptr,
    pUserData    : rawptr,
}

DefragmentationContext :: ^DefragmentationContext_T

DefragmentationContext_T :: struct {}

DefragmentationInfo2 :: struct {
    flags                   : DefragmentationFlags,
    allocationCount         : u32,
    pAllocations            : ^Allocation,
    pAllocationsChanged     : ^b32,
    poolCount               : u32,
    pPools                  : ^Pool,
    maxCpuBytesToMove       : vk.DeviceSize,
    maxCpuAllocationsToMove : u32,
    maxGpuBytesToMove       : vk.DeviceSize,
    maxGpuAllocationsToMove : u32,
    commandBuffer           : vk.CommandBuffer,
}

DefragmentationPassMoveInfo :: struct {
    allocation : Allocation,
    memory     : vk.DeviceMemory,
    offset     : vk.DeviceSize,
}

DefragmentationPassInfo :: struct {
    moveCount : u32,
    pMoves    : ^DefragmentationPassMoveInfo,
}

DefragmentationInfo :: struct {
    maxBytesToMove       : vk.DeviceSize,
    maxAllocationsToMove : u32,
}

DefragmentationStats :: struct {
    bytesMoved              : vk.DeviceSize,
    bytesFreed              : vk.DeviceSize,
    allocationsMoved        : u32,
    deviceMemoryBlocksFreed : u32,
}
